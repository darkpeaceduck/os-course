#ifndef SRC_LOCK_H_
#define SRC_LOCK_H_

#include <stdint.h>

#define TICKET_LOCK

#ifdef TICKET_LOCK

typedef struct {
	uint16_t users;
	uint16_t ticket;
}ticket_lock;
#endif

void * lock_create();
void lock(void *);
void unlock(void *);



#endif /* SRC_LOCK_H_ */
