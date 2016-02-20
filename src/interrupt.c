#include "interrupt.h"
#include "memory.h"
#include "pic.h"
#include "handler_wrapper.h"

static idt_entry_t idt_entries[IDT_SIZE];
static idt_ptr_t idt_ptr;

DO_WRAP(default_handler){
}

void idt_set_gate(uint8_t id, uint64_t adress, uint16_t selector, uint8_t type){
	idt_entries[id].offset_1 = LOW(adress, 16);
	idt_entries[id].offset_2 = SPLICE(adress, 16, 32);
	idt_entries[id].offset_3 = SPLICE(adress, 32, 64);
	idt_entries[id].selector = selector;
	idt_entries[id].zero = 0;
	idt_entries[id].type_attr = type;
}

void idt_setup(){
	idt_ptr.size  = (sizeof (idt_entries)) - 1;
	idt_ptr.base = (uint64_t)&idt_entries;
	for(int i = 0; i < IDT_SIZE; i++){
		idt_set_gate(i, (uint64_t)&WRAP(default_handler), KERNEL_CODE, INTGATE_TYPE);
	}
	set_idt(&idt_ptr);
}
