#include <stdio.h>
#include <stdlib.h>
long factorial (long);
long mynum = 6;

long factorial (long n){
// function prototype provides parameters and return type
// function definition
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}

int main( int argc, char** argv) {
// arg c refers to number of commandline inputs and argv refers tot he string 	
// man command to get manual
	long result;
	if (argc != 2) {
		printf("insufficient arguments\n");
		return 0;
	}
	mynum = atol(argv[1]);
	result = factorial(mynum);
	printf("the factorial of %ld is %ld\n " , mynum,  result);
	return 0;
}

