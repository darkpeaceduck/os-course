#ifndef SRC_TEST_H_
#define SRC_TEST_H_
#include "print.h"

#define test_fail(...) \
	printf("FAILED : "); \
	printf(__VA_ARGS__); \
	printf("\n"); \
	sti(); \
	return;

#define test_pass(...) \
	printf("PASSED : "); \
	printf(__VA_ARGS__); \
	printf("\n"); \
	return;

#define test_assert(assertion) \
	if(!assertion) { \
		test_fail(#assertion); \
	}



#endif /* SRC_TEST_H_ */
