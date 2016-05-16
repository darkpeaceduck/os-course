#include "test.h"
#include "threads.h"
#include "syscall.h"

#define EXEC_PATH "/initramfs/init"

static void * body(void * arg) {
	sys_exec(EXEC_PATH);
	return arg;
}

void test_fork() {
	thread_create(body, NULL);
}
