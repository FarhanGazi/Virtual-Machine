CFLAGS = gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra

all: 
	${CFLAGS} test.c vm.h vm.c -o vm