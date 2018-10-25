all: fourth

fourth: fourth.c
	gcc -Wall -Werror -fsanitize=address -std=c99 -o fourth fourth.c

clean:
	rm -rf fourth
