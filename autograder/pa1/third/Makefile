ALL: third

third: third.o
	gcc -Wall -Werror -fsanitize=address third.o -std=c99 -o third

third.o: third.c third.h
	gcc -Wall -Werror -fsanitize=address -g -c -std=c99 third.c
clean:
	rm -f *.o third
