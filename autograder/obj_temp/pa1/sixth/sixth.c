#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//For this part of the assignment, you will need to write a program that reads an input string 
//representing a sentence, and convert it into pig latin. We’ll be using two simple rules of pig latin:
//	1. If the word begins with a consonant then take all the letters up until the ﬁrst vowel and put 
//	them at the end and then add “ay” at the end.
//	2. If the word begins with a vowel then simply add “yay” to the end.
//For this problem vowels are deﬁned as: a, e, i, o, and u. There will only be characters in your input 
//(no numbers or punctuation). Input-Output format: This program takes a string of space-separated words 
//and should output the same space-separated words translated into pig latin
	int main(int argc, char** argv){
		for(int i = 1;i < argc; i++) {
			long int num = strlen(argv[i]);
			//printf("size: %ld\n", num);
			if (argv[i][0] == 'a' || argv[i][0] == 'e'|| argv[i][0] == 'i' ||
				argv[i][0] == 'o' || argv[i][0] == 'u' || argv[i][0] == 'A' ||
				argv[i][0] == 'E' || argv[i][0] == 'I' || argv[i][0] == 'O' ||
				argv[i][0] == 'U') {
				char *arr = malloc(sizeof(char) * (num + 4));
				char yay[4] = {'y', 'a', 'y', '\0'};
				strcpy(arr, argv[i]);
				strcat(arr, yay);
				printf("%s ", arr);
			} else { // begins with a consonant 
			//	int firstvow = 0;
				for (int j = 0; j < num; j++) {
					if (argv[i][j] == 'a' || argv[i][j] == 'e'|| argv[i][j] == 'i' ||
					argv[i][j] == 'o' || argv[i][j] == 'u' || argv[i][j] == 'A' ||
					argv[i][j] == 'E' || argv[i][j] == 'I' || argv[i][j] == 'O' ||
					argv[i][j] == 'U') {
			//			firstvow = j;
						//printf("fistvow is %d\n", firstvow);
						break;			
					} else {
					}
				}
				char* consonants = malloc(sizeof(char) * num);//firstvow);
				char* cutword = malloc(sizeof(char) * (num));// - firstvow));
				for (int j = 0; j < num; j++) {
					if (argv[i][j] == 'a' || argv[i][j] == 'e'|| argv[i][j] == 'i' ||
					argv[i][j] == 'o' || argv[i][j] == 'u' || argv[i][j] == 'A' ||
					argv[i][j] == 'E' || argv[i][j] == 'I' || argv[i][j] == 'O' ||
					argv[i][j] == 'U') {
						int m = 0;
						for (int k = j; k < num; k++) {
							cutword[m] = argv[i][k];
							m++;
						}
						break;			
					} else {
						consonants[j] = argv[i][j];
					}
				}
				char* arr = malloc(3 + sizeof(char) * num);
				strcpy(arr, cutword);
				strcat(arr, consonants);
				char end[3] = {'a', 'y', '\0'};
				strcat(arr, end);
				printf("%s ", arr);	
			} 
		}
		printf("\n");
		return 0;
	}
