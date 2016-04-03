
#ifndef SRC_ALLOCATOR_H_
#define SRC_ALLOCATOR_H_

#include <stdint.h>

int allocator_init();
void allocator_set_sync();
void * malloc(uint64_t size);
void free(void * ptr);
void * realloc(void * ptr, uint64_t new_size);


#endif /* SRC_ALLOCATOR_H_ */
