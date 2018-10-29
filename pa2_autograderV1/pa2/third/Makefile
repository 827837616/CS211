all: third

third: third.c
	gcc -Wall -Werror -fsanitize=address -std=c99 -o third third.c

clean:
	rm -rf third
