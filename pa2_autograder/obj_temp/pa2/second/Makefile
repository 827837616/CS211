all: second

second: second.c
	gcc -Wall -Werror -fsanitize=address -std=c99 -o second second.c

clean:
	rm -rf second
