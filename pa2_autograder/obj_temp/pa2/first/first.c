#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
double** multiply(int r1, int c1, int r2, int c2, double** arr1, double** arr2);
double** transpose(int r, int c , double** arr);
double** inverse(int r, double** arr);
void print(int r, int c, double** matrix);

int main (int argc, char** argv){
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("error\n");
		return 0;
	}
	fseek (fp, 0, SEEK_END);
	if (ftell(fp) == 0) {
//		printf("error\n");
		return 0;
	}
	
	FILE* fp2 = fopen(argv[2], "r");
	if (fp2 == NULL) {
		printf("error");
		return 0;
	}
	fseek (fp2, 0, SEEK_END);
	if (ftell(fp2) == 0) {
//		printf("error2\n");
		return 0;
	}
	rewind(fp);
	rewind(fp2);
	//FIX THE INVALID INPUT FRINGE CASES DONT FORGET
	
	int k = 0; //where K = attributes of given house
	int n = 0; //where N = number of training examples in the training set
	double z = 0.0;
	fscanf(fp, "%d", &k);
	fscanf(fp, "%d", &n);
	double** x = (double **) malloc(sizeof(double*) * n); //N x (K + 1) matrix 
	double** y = (double **) malloc(sizeof(double*) * n);
	for (int i = 0; i < n; i++) {
		x[i] = (double*) malloc((k + 1) * sizeof(double));
		y[i] = (double*) malloc(sizeof(double));
		for (int j = 0; j < (k + 2); j++) { // !!!!!!!!!!!!check
			if (j == 0) { // first value of x is always 1
				x[i][j] = 1;
			} else if (j == k + 1) { // last value goes to price matrix y
				fscanf(fp, "%lf", &z);
				y[i][0] = z;
			} else { // all values in the middle go to x matrix
				fscanf(fp, "%lf,",&z);
				x[i][j] = z;
			}
		}
	}/*
	printf("x:\n");
	print(n, k+1, x);
	printf("y:\n");
	print(n, 1, y); */

	int m = 0;
	fscanf(fp2, "%d", &m);
	double** test = (double**) malloc(m * sizeof(double*));
	for (int i = 0; i < m; i++) {
		test[i] = (double*) malloc((k+1) * sizeof(double));
		for (int j = 0; j < (k+1); j++) {
			if (j != 0) {
				if (j == k+1) {
					fscanf(fp2, "%lf", &z);
					test[i][j] = z;
				}else {
					fscanf(fp2, "%lf,", &z);
					test[i][j] = z;
				}
			} else { // j is 0 val is 1
				test[i][j] = 1;
			}
		}
	} 
//	print(m, k+1, test);
	
	//w = (xt * x) ^-1 * xt * y
//	printf("1: x transposed\n");
	double** xt = transpose(n, (k+1), x);
//	print(k+1, n, xt);

//	printf("2: xt X x\n");
	double** xxt = multiply((k+1), n, n, (k+1), xt, x);
//	print(k+1, k+1, xxt);

//	printf("3: (xt X x)I\n");
	double** ixxt = inverse(k+1, xxt);
//	print(k+1, k+1, ixxt);

//	printf("4: (xt X x)I X xt\n");
	double** ixxtxt = multiply((k+1), (k+1), (k+1), n,  ixxt, xt);
//	print(k+1, n, ixxtxt);

//	printf("5: (xt X x)I X xt X y\n");
	double** w = multiply((k+1), n, n, 1, ixxtxt, y);
//	print(k+1, 1, w);
	
	//x* w = y
//	printf("6: x * w\n");
	double** ans = multiply(m, (k+1), (k+1), 1, test, w);
	print(m, 1, ans);
	fclose(fp);
	fclose(fp2);
	return 0;
}
void print(int r, int c, double** matrix) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%0.0lf\t", matrix[i][j]); //0.0
		}
		printf("\n");
	}
}

double** multiply(int r1, int c1, int r2, int c2, double** arr1, double** arr2) {
	double ans = 0.0;
	double** answer = (double**) malloc(sizeof(double*) * r1);
	for (int i = 0; i < r1; i++) {
		answer[i] = (double*) malloc(sizeof(double) * c2);
		for (int j = 0; j < c2; j++) {
			for (int k = 0; k < r2; k++) {
				ans += arr1[i][k] * arr2[k][j];
			}
			answer[i][j] = ans;
			ans =0.0; //reset for each box;
		}
	}
	return answer;
}

double** transpose(int r, int c , double** arr) {
	double** t  = (double**) malloc(sizeof(double*) * c);
	for (int i = 0; i < c; i++) {
		t[i] = (double*) malloc(sizeof(double) * r);
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			t[j][i] = arr[i][j];
		}
	}
	return t;
}

double** inverse(int r, double** arr) {
	//  r = c because you can only inverse a square
	double** ans = (double**) malloc(r * sizeof(double*));
	for (int i = 0; i < r; i++) {
		ans[i] = (double*) malloc( r * sizeof(double));
		for (int j = 0; j <  r; j++) {
			if (j == i) {
				ans[i][j] = 1.0;
			} else {
				ans[i][j] = 0.0;
			}
		}
	}
//	printf("identity\n");
//	print(r, r, ans);
	for (int i = 0; i < r; i++) { //col
//		if (arr[i][i] != 1) {
			double diag = arr[i][i];
			for (int j = 0; j < r; j++) {
//				printf("%lf/%lf\n", arr[j][i], diag);
				arr[i][j] = arr[i][j] / diag;
				ans[i][j] = ans[i][j] / diag;

			}
//		} // all of the row is divided by diag so diag becomes 1
		for (int k = 0; k < r; k++) { //row
			if (i != k) {  //&& arr[k][i] != 0) { // not diag and not 0
				double coeff = arr[k][i];
				for (int l = 0; l < r; l++) {
//		printf("%lf=%lf-%lf * %lf\n",arr[k][l], arr[k][l], coeff, arr[i][l]);
					arr[k][l] =  arr[k][l] - coeff *  arr[i][l];
					ans[k][l] =  ans[k][l] - coeff * ans[i][l];
				}
			}
		}
	}
	return ans;
}
