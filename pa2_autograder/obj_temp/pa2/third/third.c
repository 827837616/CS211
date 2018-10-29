#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print(int matrix[9][9]);
bool checkVal(int num, int r, int c, int matrix[9][9]);
bool solve(int matrix[9][9]);
int main(int argc, char** argv) {
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL ) {
//		printf("error\n");
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	if (ftell(fp) == 0) {
		printf("error\n");
		return 0;
	}
	rewind(fp);
	int sudoku[9][9];
	char val;
	//You can assume that all inputs will be valid meaning the spacing will be correct
	//and only the ‘-’ character and numbers 1-9 will be present in the test ﬁles. The
	//preset numbers in the test may not satisfy the constraints of Sudoku as in the
	//example test2.txt above resulting in an unsolvable Sudoku. 
	for (int i  = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf(fp, "%c\t", &val);
			int corval = val - '0';
		/*	if (corval >= 1  && corval <= 9) {
				sudoku[i][j] = corval;
			} else { 
				sudoku[i][j] = 0;
			} */
			if (corval < 0) {
				sudoku[i][j] = 0;
			} else {
				sudoku[i][j] = corval;
			}
		}
	}
//	print(sudoku);
	bool ans = solve(sudoku);
	if (!ans) {
		printf("no-solution\n");
//		return 0;
	}
	print(sudoku);
	fclose(fp);
	return 0;
}
bool solve(int matrix[9][9]) {
	for(int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (matrix[i][j] == 0) {
//				bool corr;
				for (int k = 1; k <= 9; k++) {
					bool valid = checkVal(k, i, j, matrix);
					if (valid) {
						matrix[i][j] = k;
					//	corr = solve(matrix);
						if (solve(matrix)) {
					//		printf("correct\n");
							return true;
						} //else {
					//		printf("reverted\n");
							matrix[i][j] = 0;
						//}
					}
				}
			//	if (corr != true) {
					return false;
			//	} 
			}
		}
	}
	return true;
//	return false;
}
bool checkVal(int num, int r, int c, int matrix[9][9]) {
//	int br = (r/3) * 3;
//	int bc = (c/3) * 3;
	for (int i = 0; i < 9; i++) {
		if (matrix[i][c] == num) {
			return false;
		}
		if (matrix[r][i] == num) {
			return false;
		} 
		if (matrix[(r / 3) * 3 + (i % 3) ][(c / 3) * 3 + (i % 3) ] == num) {
			return false;
		}
	}
	 
/*	int mr; int mc;
	if (r <= 2) mr = 2;
	if (r >= 2 && r <= 5) mr = 5;
	if (r >= 5 && r <= 8) mr = 8;
	if (c <= 2) mc = 2;
	if (c >= 2 && c <= 5) mc = 5;
	if (c >= 5 && c <= 8) mc = 8;
	for (int i = mr - 2; i < mr; i++) {
		for (int j = mc - 2; j < mc; j++) {
			if (matrix[i][j] == num) {
				return false;
			}
		}
	} */
	return true;
}
void print(int matrix[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j == 9) {
				printf("%d", matrix[i][j]);
			} else {
				printf("%d\t", matrix[i][j]);
			}
		}
		if (i != 9) {
			printf("\n");
		}
	}
}
