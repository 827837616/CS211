all: first

first: first.c
	gcc -Wall -Werror -fsanitize=address -std=c99 -o first first.c

clean:
	rm -rf first
