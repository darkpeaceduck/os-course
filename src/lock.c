#include "lock.h"
#include "utils.h"
#include "allocator.h"

#ifdef TICKET_LOCK
#include "interrupt.h"
#include <stddef.h>
#include <stdint.h>

static volatile int lock_ints_on = 1;

void * lock_create() {
	ticket_lock * lock = (ticket_lock *)malloc(sizeof(ticket_lock));
	lock->ticket = 0;
	lock->users = 0;
	lock->global = 0;
	return lock;
}

void lock(void * arg_lock) {
	if(arg_lock == NULL ){
		return;
	}
	ticket_lock * lock = (ticket_lock *)arg_lock;
	if(lock_ints_on){
		cli();
		lock->global = 1;
		lock_ints_on = 0;
	}
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
	if(lock->global){
		sti();
		lock_ints_on = 1;
	}
}

#endif
