#include <stdint.h>
#include "../syscall_user.h"
#include "../test.h"
#include <stddef.h>

void test() {
	test_set_log(uprintf);
	uint64_t pid;
	test_assert(fork(&pid) == 0);
	if(pid == 0) {
		test_pass("test fork child");
	} else {
		test_pass("test fork parent");
	}
}

void main()
{
	test();
	while(1);
}
