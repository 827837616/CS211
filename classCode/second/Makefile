all: factorial

factorial: second.c
	gcc -Wall -Werror -fsanitize=address second.c -o factorial

clean:
	rm -rf factorial 
