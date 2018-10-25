#include <stdio.h>
#include <stdlib.h>

struct listnode {
	//struct is the keyword to define a user defined type
	int value;
	struct listnode * next;
};
void traverse(struct listnode *);
void traverse(struct listnode * mylist) {
	struct listnode * t1 = mylist;
	while (t1 != NULL) {
		printf("%d\n", t1-> value);
		t1 = t1 -> nest;
	}
}
void cleanup( struct listnode * mylist) {
	struct listnode * t1 = mylist;
	struct listnode * t2 = NULL;
	while (t1 != NULL) {
		t2 = t1;
		t1 = t1 -> next;
		free(t2);
	}
}

int main( int argc, char** argv) {
	printf("how many elements\n");
	scanf("%d", &a);
	for (int i = 0;i < num; i++) {
 	struct listnode * temp = (struct listnode *)  malloc(1 * sizeof(struct listnode));
	temp -> value = a;
	temp -> next = head;
	head = temp;
	}
	
	int*  points; int num;
	//int points[5];
	//Dont do : int points[num] you can NOT use a variable as array size	
	
	int a, b, c;

	printf("How many elements:\n");
	scanf("%d", &num);
	//printf("enter 3 elements\n");
	//scanf("%d %d %d ", &a, &b, &c);
	//struct listnode * head = NULL;
	
	/*
	//Add to begining of list
	struct listnode * temp = (struct listnode *)  malloc(1 * sizeof(struct listnode));
	temp -> value = a;
	temp -> next = head;
	head = temp;
	//created a new structure, created new space, initilized value for a, linked to
	//elemnt, named next as head, head of list will be new element
	*/

	points = (int *) malloc(num *sizeof(int));
	if(points == NULL) {
		printf("not able to allocate mem\n");
	}
	//sizeof gives bytes of int for given device to allow for generic use of program
	//(int *) casts from generic pointer(void *) to int pointer
	//malloc allocates memory free returns the memory from the heap
	//malloc takes the memory size, or number of elements times the size of the type
	
	printf("Enter the elements now\n");
	for (int i = 0; i < num; i++) {
		scanf("%d", &points[i]);
	}
	free(points);

	traverse(head);
	cleanup(head);
	return 0;
}
