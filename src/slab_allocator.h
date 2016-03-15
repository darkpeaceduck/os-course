
#ifndef SRC_SLAB_ALLOCATOR_H_
#define SRC_SLAB_ALLOCATOR_H_

#include "list.h"

#include <stdint.h>

typedef struct slab{
	uint64_t size;
	struct list_head desc_list;
	struct list_head slab_list;
	void * pool_ptr;
	struct slab * small;
}slab_t;

typedef struct {
	uint64_t size;
	uint64_t align;
	uint64_t available_blocks;
	struct list_head slab_list_head;
	slab_t * current_slab;
}slab_pool;

slab_t * slab_init(uint64_t size, uint64_t align);
void * slab_allocate(slab_t * slab);
void slab_free(slab_t * slab, void * addr);

void slab_pool_init(slab_pool * pool, uint64_t size, uint64_t align);
void * slab_pool_allocate(slab_pool * pool);



#endif /* SRC_SLAB_ALLOCATOR_H_ */
