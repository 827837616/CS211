ALL: second

second: second.o
	gcc -Wall -Werror -fsanitize=address second.o -std=c99 -o second
second.o: second.c second.h
	gcc -Wall -Werror -fsanitize=address -g -c -std=c99 second.c
clean: 
	rm -f *.o second
