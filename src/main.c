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
#include "tmpfs.h"
#include "strings.h"
#include "initramfs.h"

void main(void)
{
	pic_setup();
	idt_setup();
	pit_setup();
	uart_setup();
	pit_set_thread_manager_vector();

	mmap_init();
	initramfs_init();
	allocator_init();

	mmap_print();
	paging_init();

	tmpfs_mount();
	initramfs_read_contents_push_to_tmpfs();

	thread_manager_init(-1);
	sti();

	printf("OK\n");

	if(false) {
		test_threads();
	}

	if(false) {
		test_buddy();
		test_slab();
	}



	while (1);
}
