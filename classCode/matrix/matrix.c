#include <stdio.h>
#include<stdlib.h>
int main(int argc, char** argv) {
	int size1;
	printf("enter size1 \n");
	scanf("%d", &size1);
	int ** matrix;
	matrix = (int**) malloc(size1 * sizeof(int*));
	for (int i = 0; i < size1; i++) {
		matrix[i] = (int*) malloc(size2 * sizeof(int));
		//
	}
	for (int i = 0; i <size1; i++) {
		for int j= 0; j< size2; j++) {
			matrix[i][j] = 0;
		}	
	}
	for (int i = 0; i <size1; i++){
		free(matrix[i]);
	}
	free(matrix);

	//int *a;
	//a = (int*) malloc( size1 * sizeof(int));
	//for (int i = 0; i <size1; i++) {
	//	a[i] = 10 * i;
	return 0;
