#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//The seventh part requires you to read an input string representing a sentence, form a word whose 
//letters are the last letters or punctuation of the words in the given sentence, and print it. 
//Input and output format: This program takes a string of space-separated words, and should output a 
//single word as the output
int main(int argc, char** argv){
	int size = 0;
	for(int i = 1; i < argc; i++) {
		size = strlen(argv[i]); // checks size of the ith word and stores in size
		printf("%c", argv[i][size - 1]); //prints the ith word's last char
	}
	printf("\n");
	return 0;
}
