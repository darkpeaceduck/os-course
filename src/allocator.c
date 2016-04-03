#include "allocator.h"
#include <stdint.h>
#include "list.h"
#include "buddy_allocator.h"
#include "boot_allocator.h"
#include "slab_allocator.h"
#include "print.h"
#include "memory.h"
#include "paging.h"
#include "lock.h"
#include "strings.h"
#include "threads.h"

typedef struct {
	slab_pool * slab_pool;
	struct list_head list;
}pool_desc_t;

static slab_t * desc_slab;
static struct list_head pools;
static thread_mutex * allocator_mutex = NULL;

void allocator_set_sync() {
	allocator_mutex = thread_mutex_create();
}

static void allocator_mutex_lock() {
	if(allocator_mutex != NULL) {
		thread_mutex_lock(allocator_mutex);
	}
}

static void allocator_mutex_unlock() {
	if (allocator_mutex != NULL) {
		thread_mutex_unlock(allocator_mutex);
	}
}

int allocator_init(){
	boot_allocator_init( buddy_get_component_size() + paging_get_component_size());
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
	allocator_mutex_lock();
	if(size >= PAGE_SIZE){
		unlock(allocator_mutex);
		return buddy_allocate_page(get_page_level(size));
	}
	LIST_FOR_EACH(i, &pools){
		pool_desc_t * pool = LIST_ENTRY(i, pool_desc_t, list);
		if(pool->slab_pool->size >= size && size * 2 >= pool->slab_pool->size ){
			void * ret = slab_pool_allocate(pool->slab_pool);
			allocator_mutex_unlock();
			return ret;
		}
	}

	pool_desc_t * new_slab_desc = slab_allocate(desc_slab);
	if(new_slab_desc){
		slab_pool * new_slab_pool = slab_pool_init(size, 1);
		new_slab_desc->slab_pool = new_slab_pool;
		list_init(&new_slab_desc->list);
		list_add(&new_slab_desc->list, &pools);
		void * ret = slab_pool_allocate(new_slab_pool);
		allocator_mutex_unlock();
		return ret;
	}

	allocator_mutex_unlock();
	return NULL;
}

void free(void * ptr){
	allocator_mutex_lock();
	slab_t * slab = buddy_get_slab(ptr);
	if(slab == NULL){
		buddy_free_page(ptr);
	} else {
		slab_free(slab, ptr);
	}
	allocator_mutex_unlock();
}

void * realloc(void * ptr, uint64_t new_size) {
	allocator_mutex_lock();
	slab_t * slab = buddy_get_slab(ptr);
	size_t size = 0;
	if(slab == NULL) {
		size = buddy_get_alocated_size(ptr);
	} else {
		size = slab->size;
	}
	if (new_size <= size) {
		allocator_mutex_unlock();
		return ptr;
	}
	void * new_ptr = malloc(new_size);
	memcpy(new_ptr, ptr, size);
	free(ptr);
	allocator_mutex_unlock();
	return new_ptr;
}


