#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double** multiply(int r1, int c1, int r2, int c2, double** arr1, double** arr2);
double** transpose(int r, int c , double** arr);
double** inverse(int r, double** arr);

int main (int argc, char** argv){
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("error\n");
		return 0;
	}
	fseek (fp, 0, SEEK_END);
	int size = ftell(fp);
	if (size == ftell(fp)) {
		printf("error\n");
		return 0;
	}
	
	FILE* fp2 = fopen(argv[2], "r");
	if (fp == NULL) {
		printf("error\n");
		return 0;
	}
	fseek (fp2, 0, SEEK_END);
	int size2 = ftell(fp2);
	if (size2 == ftell(fp2)) {
		printf("error\n");
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
		for (int j = 0; j < (k + 1); j++) {
			if (j == 0) { // first value of x is always 1
				x[i][j] = 1;
			} else if (j == k + 1) { // last value goes to price matrix y
				fscanf(fp, "%d", z);
				y[i][0] = z;
			} else { // all values in the middle go to x matrix
				x[i][j] = fscanf(fp, "%d", z);
			}
		}
	}
	
	int m = 0;
	fscanf(fp2, "%ld", &m);
	double** test = (double**) malloc(m * sizeof(double*));
	for (int i = 0; i < m; i++) {
		test[i] = (double*) malloc((k) * sizeof(double));
		for (int j = 0; j < (k); j++) {
			fscanf(fp2, "%d", &z);
			test[i][j] = z;
		}
	}
	//w = (xt * x) ^-1 * xt * y
	double** xt = transpose(n, (k+1), x);
	double** xxt = multiply((k+1), n, n, (k+1), xt, x);
	double** ixxt = inverse(k+1, xxt);
	double** ixxtxt = multiply((k+1), n, n, n, xt, ixxt);
	double** w = multiply((k+1), n, n, 1, ixxtxt, y);
	//x* w = y
	double** ans = multiply((k+1), 1, m, k, test, w);
	printf("%0.0lf\n", ans[0][0]);
	return 0;
}

double** multiply(int r1, int c1, int r2, int c2, double** arr1, double** arr2) {
	double ans = 0;
	double** answer = (double**) malloc(sizeof(double*) * r1);
	for (int i = 0; i < r1; i++) {
		answer[i] = (int*) malloc(sizeof(int) * c2);
		for (int j = 0; j < c2; j++) {
			for (int k = 0; k < r2; k++) {
				ans += arr1[i][k] * arr2[k][j];
			}
			answer[i][j] = ans;
			ans = 0; //reset for each box;
		}
	}
	return answer;
}

double** transpose(int r, int c , double** arr) {
	double** t  = (double**) malloc(c * sizeof(double*) * c);
	for (int i = 0; i < c; i++) {
		t[i] = (double*) malloc(sizeof(double) * r);
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
//			t[j] = (double*) malloc(sizeof(double) * r);
			t[j][i] = arr[i][j];
		}
	}
	return t;
}

double** inverse(int r, double** arr) {
	//  r = c because you can only inverse a square
	double** ans = (double**) malloc(r * sizeof(double*);
	for (int i = 0; i < r; i++) {
		ans[i] = (double*) malloc(2 * r * sizeof(double));
		for (int j = 0; j < 2 * r; j++) {
			if (j <= r) {
				ans[i][j] = arr[i][j];
			} else if ((j - r) == r) {
				ans[i][j] = 1;
			} else {
				ans[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < r; i++) {
		if (arr[i][i] != 1) {
			double diag = arr[i][i];
			for (int j = 0; j < r) {
				arr[j][i] = arr[j][i] / diag;
			}
		} // all of the row is divided by diag so diag becomes 1
		for (int k = 0; k < r; k++) {
			if (i != k && arr[k][i] != 0) {
				for (int l = 0; l < r; l++) {
					arr[k][l] = arr[k][l] - arr[k][l] * arr[i][l];
				}
			}
		}
	}
	return ans;		
}
