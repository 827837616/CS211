#include <stdlib.h>
#include <stdio.h>
// string in c is array of chars with special character at end ( \0 )
char* mystrcpy(char* dest, char* src) {
	char * temp = dest;
	while(*src != '\0') {
		* dest = *src;
		dest++; //char is one byte so moves to next char in arr
		src++;
	}
	*dest = '\0';
	return temp;
}

int main(int argc, char** argv) {
 	int len;
	char c;
	char* ptr;
	printf("enter the num of characters\n");
	
	scanf("%d\n", &len);
	ptr = (char*) malloc(sizeof(char) *(len + 1));
	
	for (int i = 0; i < len; i++) {
		scanf("%c", &c);
		ptr[i] = c;
	}
	ptr[len] = '\0';
	printf("entered string is %s\n", ptr);

	char* mynew_string = (char*) malloc(100 * sizeof(char));
	char* temp = mystrcpy(mynew_string, ptr);

	printf("the copied string is %s\n", mynew_string);
	return temp;
}
