all: first

first: first.o
	gcc -Wall -Werror -fsanitize=address first.o -std=c99 -o first
first.o: first.c first.h
	gcc -Wall -Werror -fsanitize=address -g -c -std=c99 first.c
clean: 
	rm -f *.o first
