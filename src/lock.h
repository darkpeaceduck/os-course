#ifndef SRC_LOCK_H_
#define SRC_LOCK_H_

#include <stdint.h>

#define TICKET_LOCK

#ifdef TICKET_LOCK

typedef struct {
	uint16_t users;
	uint16_t ticket;
	int global;
}ticket_lock;
#endif

void * lock_create(int global);
void lock(void *);
void unlock(void *);
void lock_set_global(void *);



#endif /* SRC_LOCK_H_ */
