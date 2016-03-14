
#ifndef SRC_ALLOCATOR_H_
#define SRC_ALLOCATOR_H_

#include <stdint.h>

int allocator_init();
void * malloc(uint64_t size);
void free(void * ptr);


#endif /* SRC_ALLOCATOR_H_ */
