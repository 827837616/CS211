all: ninth

ninth: ninth.c
	gcc -Wall -Werror -fsanitize=address -std=c99 -g ninth.c -o ninth

clean:
	rm -rf ninth
