#ifndef HANDLER_WRAPPER_H_
#define HANDLER_WRAPPER_H_
#include "utils.h"

#define WRAP(name) name ## _wrapper

#define PUSH_ALL push %rax ;\
	push %rcx ;\
	push %rdx ;\
	push %rbx ;\
	push %rbp ;\
	push %rsi ;\
	push %rdi ;\
	push %r8 ;\
	push %r9 ;\
	push %r10 ;\
	push %r11 ;\
	push %r12 ;\
	push %r13 ;\
	push %r14 ;\
	push %r15 ;\

#define POP_ALL pop %r15 ;\
	pop %r14 ;\
	pop %r13 ;\
	pop %r12 ;\
	pop %r11 ;\
	pop %r10 ;\
	pop %r9 ;\
	pop %r8 ;\
	pop %rdi ;\
	pop %rsi ;\
	pop %rbp ;\
	pop %rbx ;\
	pop %rdx ;\
	pop %rcx ;\
	pop %rax ;\

#define ASM_WRAPPER(name) __asm__  ( \
						EXPAND(WRAP(name))": \n" \
						EXPAND(PUSH_ALL) \
						"call " #name " \n" \
						EXPAND(POP_ALL) \
						"iretq")

#define ER_ASM_WRAPPER(name) __asm__  ( \
						EXPAND(WRAP(name))": \n" \
						EXPAND(PUSH_ALL) \
						"call " #name " \n" \
						EXPAND(POP_ALL) \
						"add $8, %rsp \n" \
						"iretq")

#define DO_WRAP(name) VOID_FUNC(WRAP(name)); \
					 ASM_WRAPPER(name); \
					 VOID_FUNC(name)

#define ER_DO_WRAP(name) VOID_FUNC(WRAP(name)); \
					 ER_ASM_WRAPPER(name); \
					 VOID_FUNC(name)

#endif /* HANDLER_WRAPPER_H_ */
