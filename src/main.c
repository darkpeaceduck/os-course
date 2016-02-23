#include "interrupt.h"
#include "pic.h"
#include "pit.h"
#include "video.h"
#include "handler_wrapper.h"
#include "uart.h"
#include "print.h"
#include "backtrace.h"

DO_WRAP(dno){
	int64_t buf[10];
	backtrace(buf, 4, 2);
	pic_eoi(0);
}
void f3(){
	int64_t buf[10];
	backtrace(buf, 10, -1);
}
void f2(){
	f3();
}
void f1(){
	f2();
}

void main(void)
{
	pic_setup();
	idt_setup();
	pit_setup();
	uart_setup();
	f1();
	pit_replace_vector((uint64_t)&WRAP(dno));
	sti();
	while (1);
}
