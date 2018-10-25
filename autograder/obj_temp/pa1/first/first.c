#include <stdio.h>
#include <stdlib.h>
void swap(int* ptr, int* ptr2);
void bubbleSort(int inputArr[], int size);
void evenOdd(int arr[], int size);

void swap (int *ptr, int *ptr2 ) {
	int temp = *ptr;
	*ptr = *ptr2;
	*ptr2 = temp;
	//printf("ptr1:\t%d\t\tptr\t%d\n", *ptr, *ptr2);	
}

void bubbleSort(int inputArr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (inputArr[j] > inputArr[j + 1]) { 
				swap(&inputArr[j], &inputArr[j + 1]);
			}
		}
	}
}

void evenOdd(int arr[], int size) {
	int l = 0; int r = size-1 ;
	while( l < r) {
		while ((arr[l] % 2 == 0) && ( l < r)) {
			l++;
		}
		while ((arr[r] % 2 != 0) && (l < r)) {
			r--;
		}
		if ( l < r) {
			swap(&arr[l], &arr[r]);
			l++; r--;
		}
	}
}

int main(int argc, char** argv) {
	FILE *fp;
	fp = fopen(argv[1], "r");
	int count;
	fscanf(fp, "%d\n", &count);
	
	int a[count];
	for(int i = 0; i < count; i++) {
		fscanf(fp, "%d \t", &a[i]);
	}
	evenOdd(a, count);
	for( int i = 0; i < count; i++) {
	}
	int l; int r;
	for( int i = 0; i < count; i++) {
		if (a[i] % 2 == 1 || a[i] % 2 == -1) {
			l = i -1;
			r = i;
			break;
		}
	}
	bubbleSort(a, l+1);
	bubbleSort(&a[r], (count - r));
	for( int i = 0; i < count; i++) {
		printf("%d\t", a[i]);
	}
	/*
	bubbleSort(a, count);
	for (int i = 0; i < count; i++) {
		printf("%d:%d\t\n", i, a[i]);
	}
	printf("sorting by even odd: \n");
	int odds;
	for(int i = 0; i < count; i++) {
		if(( a[i] % 2) != 0) {
			odds++;
		}
	}
	if (odds != 0) {
		evenOdd(a, count, odds);
	} */
	
	/* int temp;
	int count = 0;iii
	while (fscanf(fp, "%d \t", &temp) != EOF) {
		//printf("nums: %d \t \n", other);
		count ++;
	}
	int arr[count-1];
	rewind(fp);
	int loop = 0;
	while(fscanf(fp, "%d \t", &arr[loop]) != EOF) {
		loop++;
	}

	//arr = &arr[1];
	int array[count - 1];
	for(int j = 0; j < count; j++) {
		array[j] = arr[j+1];
		printf("%d: \t %d \n", j, array[j]);
	} */
	fclose(fp);
	return 0;
}
