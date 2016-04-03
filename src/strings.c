#include "strings.h"
#include "print.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
void memcpy(void * desc_arg, const void * src_arg, size_t size) {
	char * desc = desc_arg;
	const char * src = src_arg;
	for(size_t i = 0; i < size; i++) {
		desc[i] = src[i];
	}
}

static bool is_end(const char * s){
	return *s == '\0';
}

size_t strlen(const char * s) {
	size_t len = 0;
	while(!is_end(s))
		s++, len++;
	return len;
}

int strcmp(const char * left, const char * right) {
	while(!is_end(left) && !is_end(right)){
		if(*left < *right)
			return -1;
		if(*left > *right)
			return 1;
		left++; right++;
	}
	if(is_end(left) && !is_end(right))
		return -1;
	if(!is_end(left) && is_end(right))
		return 1;
	return 0;
}

int str_find_last(const char * str, char c, int limit){
	for(int i = limit - 1; i >= 0; i--) {
		if(str[i] == c){
			return i;
		}
	}
	return -1;
}
