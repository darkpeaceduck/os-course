#include "interrupt.h"
#include "pic.h"
#include "pit.h"
#include "video.h"
#include "handler_wrapper.h"
#include "uart.h"
#include "strings.h"

DO_WRAP(pit_uart_print){
	pic_eoi(0);
	printf(uart_putchar, "It's okey now\n");
}

void main(void)
{
	pic_setup();
	idt_setup();
	pit_setup();
	uart_setup();
	pit_replace_vector((uint64_t)&WRAP(pit_uart_print));
	sti();
	while (1);
}
