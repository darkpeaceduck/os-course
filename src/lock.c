#include "lock.h"
#include "utils.h"
#include "allocator.h"

#ifdef TICKET_LOCK
#include "interrupt.h"
#include <stddef.h>

void * lock_create() {
	ticket_lock * lock = (ticket_lock *)malloc(sizeof(ticket_lock));
	lock->ticket = 0;
	lock->users = 0;
	return lock;
}

void lock(void * arg_lock) {
	if(arg_lock == NULL ){
		return;
	}
	ticket_lock * lock = (ticket_lock *)arg_lock;
	cli();
	const uint16_t ticket = __sync_fetch_and_add(&lock->users, 1);
	while(lock->ticket != ticket) {
		barrier();
	}
	__sync_synchronize();
}

void unlock(void * arg_lock) {
	if(arg_lock == NULL ){
			return;
	}
	ticket_lock * lock = (ticket_lock *)arg_lock;
	__sync_synchronize();
	__sync_add_and_fetch(&lock->ticket, 1);
	sti();
}

#endif
