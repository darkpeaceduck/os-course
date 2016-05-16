CC ?= gcc
LD ?= gcc

FLAGS=-mno-red-zone -mno-mmx -mno-sse -mno-sse2 -ffreestanding -Wall -Wextra -Werror -pedantic  -nostdlib --std=c11 
all:init

init:init.o
	$(LD) -T init.ld -o init init.o ../syscall_user.o ../print.o ../strings.o --unresolved-symbols=ignore-all
init.o:init.c
	$(CC)  -c init.c $(FLAGS) 
clean:
	rm -f init init.o