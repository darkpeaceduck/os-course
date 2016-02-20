#include "pit.h"
#include "utils.h"
#include "ioport.h"
#include "memory.h"
#include "interrupt.h"
#include "pic.h"
#include "video.h"
#include "strings.h"
#include "handler_wrapper.h"

DO_WRAP(default_pit_handler){
	pic_eoi(0);
}

void pit_replace_vector(uint64_t handler){
	idt_set_gate(PIC_BOUND_MASTER , handler, KERNEL_CODE, INTGATE_TYPE);
}

void pit_setup(){
	out8(PIT_CONTROL_PORT, PIT_CONTROL_COMMAND);
	out8(PIT_DATA_PORT_CHANNEL_0, LOW(PIT_COUNTER, 8));
	out8(PIT_DATA_PORT_CHANNEL_0, SPLICE(PIT_COUNTER, 8, 16));
	pit_replace_vector((uint64_t )&WRAP(default_pit_handler));
}
