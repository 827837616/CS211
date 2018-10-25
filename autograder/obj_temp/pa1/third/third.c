#include <stdio.h>
#include <stdlib.h>
struct node{
//	int key;
	int data;
	struct node* next;
};
void insert (struct node* root, int num, int key);
int hashf(int num);
struct node* hash[10000];
int main(int argc, char** argv) {
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("error\n");
		return 0;
	}
	//check if file is empty
	char op; int num;
	//struct node** head = hash;
	for (int i = 0; i < 10000; i++) {
		hash[i] = NULL;
	}
	//struct node* first = NULL;
	while (fscanf(fp, "%c\t%d\n", &op, &num) !=EOF) {
		//struct node* first = NULL;
		int key = hashf(num);
		if (op =='i') {
			//if (hash[key] == NULL) { // no items in that bucket location
			//	insert(first, num, key); //pass NULL pointer
			//} else {
				struct node* existing = hash[key]; // pass pointer to bucket if not empty
				 insert(existing, num, key);
			//} 
		} else if (op == 's') {
			if (hash[key] == NULL) { //hash location doesnt have anything thus nonexistant
				printf("absent\n");
			} else {
				int boo = 0;
				struct node* existing = hash[key];	
				//search(existing, num);
				//if (existing == NULL) {
				//	printf("absent\n");
				//} else {
					struct node* ptr = existing;
					while (ptr != NULL) {
						if (ptr->data == num) {
							boo = 1;
							break;
						}
						ptr = ptr->next;
					}
			//	}
				if (boo == 0) {
					printf("absent\n");
				} else {
					printf("present\n");
				}
			}
		} else {
			printf("error\n");
		}
	}
	fclose(fp);
	return 0;
}

int hashf(int num) {
	int key = num % 10000;
	if (key < 0) key = key * -1;
	//printf("hash: %d\n", key);
	return key;
}

void insert (struct node* root, int num, int key) {
	//printf("insert %d\t", num);
	if (root == NULL) {
		//create first item
		struct node* new =(struct node*) malloc(sizeof(struct node));
		new->data = num;
		new->next = NULL; //first item
		hash[key] = new;
		printf("inserted\n");
		return;
	} else {
	// find the location to insert in list;
		struct node* move = root;
		while ( move->next != NULL) {
			if (move->data == num) {
				printf("duplicate\n");
				//break;
				return;
			}
			move = move->next; // check next pos	
		}
		struct node* nnode = (struct node*)  malloc(sizeof(struct node));
		nnode->data = num;
		nnode->next =NULL;
		move->next = nnode;
		//move->next = nnode;
		//hash[key] = nnode;
		printf("inserted\n");
		return;
	}
}
