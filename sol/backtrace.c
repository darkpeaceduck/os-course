#include "backtrace.h"
#include "stdio.h"

void backtrace(uint64_t rbp, uintptr_t stack_begin, uintptr_t stack_end)
{
	int depth = 0;

	while (rbp >= stack_begin && rbp < stack_end - 2 * sizeof(uint64_t)) {
		uint64_t *stack_ptr = (void *)rbp;

		printf("%d: %p\n", depth++, (void *)stack_ptr[1]);
		rbp = stack_ptr[0];
	}
}
