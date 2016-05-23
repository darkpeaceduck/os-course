#include "process.h"
#include "elf.h"
#include "print.h"
#include "memory.h"
#include "handler_wrapper.h"
#include "syscall.h"
#include "interrupt.h"
#include "tss.h"

static int syscall_dispatcher(int num, void * param) {
	int ret = 0;
	switch(num){
	case 0:
		ret = sys_write(param);
		break;
	case 1:
		ret = sys_fork();
		break;
	default:
		ret = sys_err();
	}
	return ret;
}

SYSCALL_DO_WRAP(syscall_handler){
	uint64_t num;
	void * param;
	__asm__ volatile("mov %%rax, %0" : "=m"(num) :: "memory");
	__asm__ volatile("mov %%rbx, %0" : "=m"(param) :: "memory");
	int64_t code = syscall_dispatcher(num, param);
	__asm__ volatile("mov %0, %%rax"::"m"(code) : "rax");
}


int sys_exec(const char * path) {
	process_set_user_image(process_current(), parse_elf(path));
	process_jump_user();
	return 0;
}

int sys_write(void * param) {
	printf(param);
	return 0;
}

int sys_fork() {
	return process_fork();
}

int sys_err() {
	return SYSCALL_WRONG_ARG;
}

void syscall_init_handler() {
	idt_set_gate_dpl(SYSCALL_INTERRUPT_NUMB, (uint64_t)&WRAP(syscall_handler), KERNEL_CODE, TRAPGATE_TYPE, SYSCALL_DPL);
}
