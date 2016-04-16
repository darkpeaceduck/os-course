#ifndef STRINGS_H_
#define STRINGS_H_

#include <stddef.h>
void memcpy(void * desc_arg, const void * src_arg, size_t size);
size_t strlen(const char * s);
int strcmp(const char * left, const char * right);
int str_find_last(const char * str, char c, int limit);
char * str_cpy(const char * str);

#endif /* STRINGS_H_ */
