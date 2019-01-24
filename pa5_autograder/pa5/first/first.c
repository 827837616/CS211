#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
typedef struct directives{
	int inSize;
	int outSize;
	int* inIndex; //location in values
	int* outIndex;
	int* multi; //array for mux inputs
	char operation[20]; //string name of gate
}direct;

char** variables = NULL;
//variables names' indexes correspond to location in values array
int* values = NULL;
direct* directives = NULL; 


int main(int argc, char** argv) {
	//___FILE OPENING____
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) { printf("error\n"); return 0;}
	fseek(fp, 0, SEEK_END);
	if (ftell(fp) == 0) { printf("error\n"); return 0;}
	rewind(fp);
	
	int lineCount = 0;
	for (char c = getc(fp); c != EOF; c = getc(fp)) {
		if (c == '\n') lineCount +=1;
	}
	rewind(fp);
	//printf("lineCount:%d\t", lineCount);
//	direct* directArr = (direct*) malloc(sizeof(direct) * (lineCount -2));
	direct directArr[lineCount-2];
	directives = directArr;
//	for (int i = 0; i < (lineCount - 2); i++) {
//		directives[i].operation = (char*) malloc(sizeof(char) * 50);
//	}

	char word[50]; //Line identifiers
	int inCount; //number of input vars
	int outCount; //num of output vars
	int iter = 0; //what line is being read
	int opInputCount; //gate inputs
	int opOutCount; //gate outputs	
	int onlyIn;
	while(fscanf(fp, "%s", word) != EOF) {
		if (strcmp(word, "INPUTVAR") == 0) {
			fscanf(fp, "%d", &inCount);
			//printf("inCount:%d\t", inCount);
			onlyIn = inCount;
			variables = (char**) malloc((2 + inCount) * sizeof(char*));
			for (int i  = 0; i < 2 + inCount; i++) {
				variables[i] = (char*) malloc(sizeof(char)*50);
			}
			variables[0] = "0";
			variables[1] = "1";
			for (int i = 0; i < inCount; i++) {
				fscanf(fp, "%s", word);	
				strcpy(variables[i+2], word);
			}
		}
		else if (strcmp(word, "OUTPUTVAR") == 0) {
			fscanf(fp, "%d", &outCount);
			//printf("outCount:%d\t", outCount);
			
			variables = (char**) realloc(variables, (inCount + outCount + 2) * sizeof(char*));
			for (int i = 0; i < outCount; i++) {
				variables[i+2+inCount] = (char*) malloc(sizeof(char)*50);
			}
			for (int i = 0; i < outCount; i++) {
				fscanf(fp, "%s", word);
				strcpy (variables[i+inCount+2], word);
			}
		}
		 else {
			int multi;
			opInputCount = 2;
			opOutCount = 1;
			strcpy(directives[iter].operation, word);
			if (strcmp(word, "NOT") == 0) {
				opInputCount = 1;
				opOutCount = 1;
			}else if (strcmp(word, "DECODER") == 0) {
				fscanf(fp, "%d", &opInputCount);
				opOutCount = pow(2, opInputCount);
			} else if (strcmp(word, "MULTIPLEXER") == 0) {
				fscanf(fp, "%d", &multi); // num of 
				opInputCount = log(multi) / log(2);
				opOutCount = 1;
			} else { 
				//printf("error invalid line identifier\n"); 
			}

		//	printf("var op: %s", directives[iter].operation);
		//	printf("%s\t", directives[iter].operation);

			//directives[iter].inSize = malloc(sizeof(int));
			directives[iter].inSize = opInputCount;
			//directives[iter].outSize = malloc(sizeof(int));
			directives[iter].outSize = opOutCount;
		//	printf("insize:%d\toutsize:%d", directives[iter].inSize, directives[iter].outSize);
			int found = 0;	
			directives[iter].inIndex = (int*) malloc(opInputCount * sizeof(int));
			for (int i = 0; i < opInputCount; i++) {
				fscanf(fp, "%s", word);
				for (int j = 0; j < (inCount + outCount + 2); j++) {
					if(variables[j] == word) {
						directives[iter].inIndex[i] = j;
						found = 1;
						break;
					}
				}
				if (found == 0) {		
				 	variables = (char**) realloc(variables, (inCount + outCount + 3) *sizeof(char*));
					variables[inCount+outCount+2] = (char*) malloc(sizeof(char)*50);
					strcpy (variables[outCount+inCount+2], word);//varName, word);
					directives[iter].inIndex[i] = (inCount+outCount+3);
					inCount++;
				}
			}


			found = 0;
			directives[iter].outIndex = (int*) malloc(opOutCount * sizeof(int));		
			for (int  i = 0; i < opOutCount; i++) {
				fscanf(fp, "%s", word);
				for (int j = 0; j < (inCount + outCount + 2); j++) {
					if (variables[i] == word) {
						directives[iter].outIndex[i] = j;
						found = 1;
						break;
					}
				}
				if (found == 0) {
					variables = (char**) realloc(variables, (inCount + outCount + 3) * sizeof(char*));
					variables[inCount+outCount+2] = (char*) malloc(sizeof(char)*50);
					strcpy (variables[outCount+inCount+2], word);//varName, word);
					directives[iter].inIndex[i] = (inCount+outCount+3);
					inCount++;
				}
			}
			iter++;
		}
	} //find where temp variables are used as inputs before outputs and shift around
/*	int isTemp = 0; int loc;
	char tempWord[50];
	for (int i = 0; i < (lineCount - 2); i++) {
		for (int j = 0; j < (directives[i].inSize); j++) {
			int loc = directives[i].inIndex[j];
			if(islower(variables[loc][0])) {
				isTemp = 1;
			}

		}
		for (int j = 0; j < (directives[i].outSize); j++) {
		
		}
	} */
//	values = (int*) malloc(sizeof(int) * (inCount+outCount+2));
//	printf("\n");
	int numArr[inCount+outCount+2];
	values = numArr;
	values[0] = 0;
	values[1] = 1;
	int greyCode;
	for (int i = 0; i < (inCount+outCount+2); i++) { values[i] = 0;}

	int para = 1 << onlyIn;	
	for (int i = 0; i < para; i++) {
		greyCode = i ^ (i >> 1);
	//	printf("%d::::", greyCode);
		for (int j = onlyIn+1; j >= 2; j--) {
			values[j] = greyCode % 2;
			greyCode = greyCode / 2;
		}
		for (int i = 0; i < (lineCount-2); i++) {
	//		printf("%d\t", directives[i].outIndex[0]);
			if ( strcmp(directives[i].operation, "NOT") == 0) {
				values[directives[i].outIndex[0]] = !values[directives[i].inIndex[0]];
			} else if ( strcmp(directives[i].operation, "AND") == 0) {
				values[directives[i].outIndex[0]] = values[directives[i].inIndex[0]] && values[directives[i].inIndex[1]];	
			} else if ( strcmp(directives[i].operation, "OR") == 0) {
				values[directives[i].outIndex[0]] = values[directives[i].inIndex[0]] || values[directives[i].inIndex[1]];	
			} else if ( strcmp(directives[i].operation, "NAND") == 0) {
				values[directives[i].outIndex[0]] = !(values[directives[i].inIndex[0]] && values[directives[i].inIndex[1]]);	
			} else if ( strcmp(directives[i].operation, "NOR") == 0) {
				values[directives[i].outIndex[0]] = (!values[directives[i].inIndex[0]] || values[directives[i].inIndex[1]]);	
			} else if ( strcmp(directives[i].operation, "XOR") == 0) {
				values[directives[i].outIndex[0]] = values[directives[i].inIndex[0]] ^ values[directives[i].inIndex[1]];	
			} else if ( strcmp(directives[i].operation, "MULTIPLEXER") == 0) {
				continue; //:((((((((((((((((((((
			} else if ( strcmp(directives[i].operation, "DECODER") == 0) {
				continue; //:((((((((((((((((((((
			}
		}
		for (int j = 2; j < onlyIn+outCount+2;j++) {//0; j < onlyIn+2; j++) { 
			printf("%d ", values[j]);
		}
		printf("\n");
		for (int i = 0; i < (inCount+outCount+2); i++) { values[i] = 0;}
	}
		
	return 0;
}
