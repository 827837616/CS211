#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
struct node {
	int data;
	struct node* ptr;
};
struct node* head = NULL;
struct node* insert(int value);
struct node* delete( int value, struct node* head);
int size = 0;

int main(int argc, char** argv) {
	//Your program should print “error” (and nothing else) if the ﬁle does not exist. Your program
	//should print 0 followed by a blank line if the input ﬁle is empty or the resulting linked list 
	//has no nodes	
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) printf("error\n"); // file pointer points to nonexistant file	
	fseek(fp, 0, SEEK_END); // push file pointer to end
	if (ftell(fp) ==0) { //ftell returns position of the pointer
		// if 0, it never moved or file is empty
		return 0;
	}
	rewind(fp);
	char iod; int num;
	while ( fscanf(fp,"%c %d\n", &iod, &num) != EOF) {
		if (iod == ' ') {
			//printf("doing blank space");
		} else if (iod == 'i') {
			//printf("inserting%d\n", num);
		//	size++;
			head = insert(num);
		} else if ( iod == 'd') {
			//printf("deleting%d", num);
			head = delete(num, head);
		} else { //only two options for manipulating all else prints error
			printf("error\n");
		}
	}
	fclose(fp);
	//Output format: At the end of the execution, your program should print the number of nodes in 
	//the list in the ﬁrst line of the output and all the values of the linked list in sorted order 
	//in the next line. The values should be in a single line separated by tabs. 
	printf("%d\n", size); 
	struct node* pt;
	for (pt = head; pt != NULL; pt = pt->ptr) {
		printf( "%d\t", pt->data);
	}
	printf("\n");
	return 0;
}

struct node* insert(int value) {
	if (head == NULL) { // insert first item
		head = malloc( sizeof( struct node));
		head->data = value;
		head->ptr = NULL;
		size++;
		return head;
	}
	// if head has value bigger than or less than push accordingly
	else if ( head ->data > value) {
		//insert at front
		//return front as new head
		struct node* pushin = malloc(sizeof(struct node));
		pushin->data = value;
		pushin->ptr = head;
		size++;
		return pushin;
	} else{ //if ( head-> data < value) {
		// loop through till the data is greater than the value being inserted
		struct node* point = head;
		struct node* previous;
		while (point != NULL) {
			if (point-> data > value) {
				struct node* pushin;
				pushin = malloc(sizeof(struct node));
				pushin->data = value;
				pushin->ptr = previous->ptr;
				previous->ptr = pushin;
				size++;
				return head;
			} else if (point->data == value) {
				//ignore duplicate
		//		size--;
				return head;
			}
			previous = point;
			point = point->ptr;
		}
		struct node* pushin = malloc(sizeof(struct node));
		pushin->data = value;
		pushin->ptr = NULL;
		previous->ptr = pushin;
		size++;
		return head;
	}
	//size++;// for first case
	//return head;
}

struct node* delete(int value, struct node* head) {
	if (head == NULL) return head;
	else if (head->data == value) {
		if (head->ptr == NULL) {
			head = head->ptr; // NULL
			size--;
			return head;
		}
		size--;
		head = head->ptr;
	} //else {
	struct node* pt = head;//->ptr;
	struct node* previous = head;
	while (pt != NULL) {
		if (pt->data == value){
			//move previous ptr to point to next item 
			//decrement size after pt is removed
			previous->ptr = pt->ptr;
			size--;
			return head;
		}
		previous = pt;
		pt = pt->ptr;
	}
	//}
	//size--;
	return head;
}
