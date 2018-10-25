#include <stdio.h>
#include <stdlib.h>


/*
struct node {
	int val;
	struct node* link;
};
void insert(struct node** list, int val);
void insert(struct node** list, int val) {
	//HEAD IS NEVER UPDATED FROM NULL
	struct node* t1 = NULL;
	t1 = (struct node*) malloc(sizeof(struct node));
	t1-> val = val;
	t1-> link = *list;
	*list = t1;
}
int main(int argc, char** argv) {
	int num;
	struct node* head = NULL;
	printf("enter a number");
	scanf("%d", &num);
	insert(&head, num);
	printf("the list i\n");
	while(head != NULL) {
		printf(" the value in the list is %d\n", head->val);
		head = head->link;
	}
	return 0;
} */
