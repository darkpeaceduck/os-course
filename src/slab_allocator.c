
#include "slab_allocator.h"
#include <stddef.h>
#include "list.h"
#include "memory.h"
#include "utils.h"
#include "buddy_allocator.h"
#include "print.h"

#define SLAB_BIG_BOUND ( PAGE_SIZE >> 3)

typedef struct {
	struct list_head list_desc;
}slab_small_descriptor_t;

typedef struct {
	struct list_head list_desc;
	virt_t addr;
}slab_big_descriptor_t;

static virt_t get_aligned_addr(virt_t addr, uint64_t align){
	if(addr % align == 0)
		return addr;
	return (addr / align + 1) * align;
}

static int is_small(uint64_t size){
	return size < SLAB_BIG_BOUND;
}

static slab_t * slab_init_small(uint64_t size, uint64_t align){
	void * page = buddy_allocate_page(0);
	if(page == NULL){
		return NULL;
	}
	slab_t * ret = (slab_t *) page;
	buddy_set_slab(page, ret);
	ret->small = NULL;
	ret->size = size;
	list_init(&ret->desc_list);
	for(virt_t i = get_aligned_addr(((virt_t)page) + sizeof(slab_t), align);
			   i <= ((virt_t)page) + PAGE_SIZE - sizeof(slab_small_descriptor_t) + size ;
			   i = get_aligned_addr(i + sizeof(slab_small_descriptor_t) + size,
					   align) ){
		slab_small_descriptor_t * new_desc = (slab_small_descriptor_t * ) i;
		list_init(&new_desc->list_desc);
		list_add(&new_desc->list_desc, &ret->desc_list);
	}
	return ret;
}

static void * slab_allocate_small(slab_t * slab){
	if(list_empty(&slab->desc_list)){
		return NULL;
	}
	slab_small_descriptor_t * ret_desc = LIST_ENTRY(slab->desc_list.next, slab_small_descriptor_t, list_desc);
	list_del(&ret_desc->list_desc);

	return (void *)(((uint64_t )ret_desc) + sizeof (struct list_head));
}

static void slab_free_small(slab_t * slab, void * addr){
	slab_small_descriptor_t * ins_desc = (slab_small_descriptor_t * )(((uint64_t)addr) - sizeof(struct list_head));
	list_add(&ins_desc->list_desc, &slab->desc_list);
}

static void slab_create_big_desc(slab_t * big_slab, virt_t addr){
	slab_big_descriptor_t * new_desc = (slab_big_descriptor_t *) slab_allocate_small(big_slab->small);
	list_init(&new_desc->list_desc);
	new_desc->addr = addr;
	list_add(&new_desc->list_desc, &big_slab->desc_list);
}

static slab_t * slab_init_big(uint64_t size, uint64_t align){
	slab_t * small = slab_init_small(MAX( (sizeof (slab_big_descriptor_t)), (sizeof(slab_t))), align);
	if(small == NULL){
		return NULL;
	}
	slab_t * ret = (slab_t * ) slab_allocate_small(small);
	ret->small = small;
	ret->size = size;
	list_init(&ret->desc_list);
	void * page = buddy_allocate_page(0);
	if(page == NULL){
		return NULL;
	}
	buddy_set_slab(page, ret);
	for(virt_t i = get_aligned_addr((virt_t) page, align);
			i <= ((virt_t)page) + PAGE_SIZE - size;
			i = get_aligned_addr(i + size, align)){
		slab_create_big_desc(ret, i);
	}
	return ret;
}

static void * slab_allocate_big(slab_t * slab){
	if(list_empty(&slab->desc_list)){
		return NULL;
	}
	slab_big_descriptor_t * ret_desc = LIST_ENTRY(slab->desc_list.next, slab_big_descriptor_t, list_desc);
	list_del(&ret_desc->list_desc);
	void * ret =  (void *)ret_desc->addr;
	slab_free_small(slab->small, (void *) ret_desc);
	return ret;
}

static void slab_free_big(slab_t * slab, void * addr){
	slab_create_big_desc(slab, (virt_t) addr);
}

slab_t * slab_init(uint64_t size, uint64_t align){
	if(size >= PAGE_SIZE) {
		return NULL;
	}
	if(is_small(size)){
		return slab_init_small(size, align);
	} else {
		return slab_init_big(size, align);
	}
}

void * slab_allocate(slab_t * slab){
	if(is_small(slab->size)){
		return slab_allocate_small(slab);
	} else {
		return slab_allocate_big(slab);
	}
}

void slab_free(slab_t * slab, void * addr){
	if(is_small(slab->size)){
		slab_free_small(slab, addr);
	} else {
		slab_free_big(slab, addr);
	}
}

