#include <stdio.h>
#include <stdlib.h>
 //functions reside in stack
 //global variables exist for the entirety of the program
 //pointer is the adddress to the mem location
 //& obtains the adress of the var  or the index of array of bytes
 //* dereferncing operator
int main(int argc, int** argv) {
	if (argc != 2) {
	printf("not enough args\n");
	return 0;
	}
	
	File *fp;
	int b; char a;
	fp = fopen (argv[1], "r");
	if (fp == NULL){
	 return 0;
	}

	while (fscanf (fp, "%c %d\n", &a, &b) == 2) {
	printf("%c %d\n", a , b);
	}
	fclose(fp);
}
/*void swap(int*, int*);
void swap(int* a, int* b) {
	//printf("a = %d, b = %d", a, b);
	int temp = *a;
	*a = *b;
	*b = temp;
	//printf("aftersawp a = %d, b= %d", a, b);
}
int main(int argc, char** argv) {
	int p; int q;
	printf("enter p\n");
	scanf("%d, &p");
 	
	printf("enter q\n");
        scanf("%d, &q");
	
	printf("p = %d, q = %d",p,q);
	swap(&p, &q);
 	printf("after swap p = %d, q = %d", p, q);
	
	return 0;
	int a = 42;
	int * q;
 	q = &a;
	
	*q = 54;	
	a = 64;	

	printf(" ais %d\n", a);
	printf("the value at the location pointed by q is %d\n", *q);
	return 0;
} */
	
