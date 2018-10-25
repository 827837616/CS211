#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void print(int** square, int size);
bool magic(int** square, int size);

int main(int argc, char** argv) {
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("error\n");
		return 0;
	}
	int size = 0; int num = 0;
	fscanf(fp, "%d\n", &size);
	//printf("size: %d\n", size);
	if (size == 1) {
		printf("magic\n");
	}	
	
	int** square = (int**) malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		square[i] = (int*) malloc(sizeof(int) * size);
		//alloc space for each collumn of the row
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fscanf(fp, "%d", &num);
			square[i][j] = num;
		}
	}
	if (magic(square, size) != true) {
		printf("not-magic\n");
	} else {
		printf("magic\n");
	}
	//print(square, size);
	fclose(fp);
	return 0;
}
// check for same nums, check for rows, check for columns, check i=j diag, 
// check for size-1 diag, check each sum with prev sum, then true
// what about matrix of all 0???? prev sum is always 0 so would it fail??
bool magic(int** square, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				for (int l  = 0; l < size; l++) {
					if (i != k && j!= l) {
						if (square[i][j] == square[l][i]){
								return false;
							}
					}
				}
			}
		}
	}
	int sum1 = 0;
	int prevsum1 = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			sum1 = sum1 + square[i][j]; 
		}
		if (prevsum1 != 0) {
			if (prevsum1 != sum1) {
				return false;
			}
		}
		prevsum1 = sum1;
		sum1 = 0;
	}
	int sum2 = 0;
	int prevsum2 = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// swapping j and i allows for the collumns of the matrix to be checked
			// sequentially
			sum2 = sum2 + square[j][i];
		}
		if (prevsum2 != 0) {
			if (prevsum2 != sum2) {
				return false;
			}
		}
		prevsum2 = sum2;
		sum2 = 0;
	}
	if (prevsum1 != prevsum2) {
		return false;
	}
	int sum3 = 0;
	int sum4 = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j == i) {
				sum3 = sum3 + square[i][j];
			}
			if (j + i == size - 1) {
				sum4 = sum4 + square[i][j];
			}
		}
	}
	
	if (sum3 != prevsum2) {
		return false;
	}
	if (sum4 != sum3) {
		return false;
	}
	return true;
}

void print(int** square, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d\t", square[i][j]);
		}
		printf("\n");
	}
	return;
}
