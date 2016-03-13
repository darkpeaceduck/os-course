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
#include <stddef.h>

void main(void)
{
	pic_setup();
	idt_setup();
	pit_setup();
	uart_setup();

	mmap_init();
	mmap_print();
	allocator_init();

	sti();
	while (1);
}
