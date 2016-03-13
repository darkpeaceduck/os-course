
#ifndef SRC_SLAB_ALLOCATOR_H_
#define SRC_SLAB_ALLOCATOR_H_

#include "list.h"

#include <stdint.h>

typedef struct slab{
	uint64_t size;
	struct list_head desc_list;
	struct slab * small;
}slab_t;

slab_t * slab_init(uint64_t size, uint64_t align);
void * slab_allocate(slab_t * slab);
void slab_free(slab_t * slab, void * addr);



#endif /* SRC_SLAB_ALLOCATOR_H_ */
