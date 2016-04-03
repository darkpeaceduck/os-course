#include "interrupt.h"
#include "pic.h"
#include "pit.h"
#include "video.h"
#include "handler_wrapper.h"
#include "uart.h"
#include "print.h"
#include "backtrace.h"
#include "mmap.h"
#include "allocator.h"
#include "paging.h"
#include "buddy_allocator.h"
#include "threads.h"
#include <stddef.h>
#include "tests_list.h"





void main(void)
{
	pic_setup();
	idt_setup();
	pit_setup();
	uart_setup();
	pit_set_thread_manager_vector();

	mmap_init();
	allocator_init();
	mmap_print();
	paging_init();

	thread_manager_init(-1);
	sti();


	if(true) {
		test_threads();
	}

	if(false) {
		test_buddy();
		test_slab();
	}



	while (1);
}
