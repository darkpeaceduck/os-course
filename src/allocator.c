#include "allocator.h"
#include <stdint.h>
#include "list.h"
#include "buddy_allocator.h"
#include "boot_allocator.h"
#include "slab_allocator.h"
#include "print.h"
#include "memory.h"

typedef struct {
	slab_t * slab;
	struct list_head list;
}pool_desc_t;

static slab_t * desc_slab;
static struct list_head pools;

int allocator_init(){
	boot_allocator_init( buddy_get_component_size());
	if(buddy_allocator_init())
		return -1;

	desc_slab = slab_init(sizeof(pool_desc_t), 1);
	if(desc_slab == NULL){
		return -1;
	}
	list_init(&pools);
	return 0;
}

static int get_page_level(uint64_t size){
	for(int i = 0; ; i++){
		if((uint64_t)PAGE_SIZE * (1<<i) >= size)
			return i;
	}
}

void * malloc(uint64_t size){
	if(size >= PAGE_SIZE){
		return buddy_allocate_page(get_page_level(size));
	}
	LIST_FOR_EACH(i, &pools){
		pool_desc_t * pool = LIST_ENTRY(i, pool_desc_t, list);
		if(pool->slab->size >= size){
			void * ptr = slab_allocate(pool->slab);
			if(ptr){
				return ptr;
			}
		}
	}

	pool_desc_t * new_slab_desc = slab_allocate(desc_slab);
	if(new_slab_desc){
		slab_t * new_slab = slab_init(size, 1);
		if(!new_slab){
			slab_free(desc_slab, new_slab_desc);
			return NULL;
		}
		new_slab_desc->slab = new_slab;
		list_init(&new_slab_desc->list);
		list_add(&new_slab_desc->list, &pools);

		return slab_allocate(new_slab);
	}
	return NULL;
}

void free(void * ptr){
	slab_t * slab = buddy_get_slab(ptr);
	if(slab == NULL){
		buddy_free_page(ptr);
	} else {
		slab_free(slab, ptr);
	}
}
