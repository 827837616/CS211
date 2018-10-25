#include <stdlib.h>
#include <stdio.h>
//This program takes a file name as an argument from the command line.  The file is either blank or
//contains successive lines of input.  Each line starts with a character, either i’ or ’s’, followed by a
//tab and then an integer.  For each line that starts with ’i’, your program should insert that number
//in the binary search tree if it is not already there.  If it is already present, you will print
//”duplicate” and not change the tree.  If the line starts with a ’s’, your program should search 
//for the value.
struct Node { //Nodes: ptr forward, ptr down, num/data
	int data;
	struct Node* left;
	struct Node* right;
};
struct Node* head = NULL;
struct Node* pNode = NULL;

//struct Node* insert(int num, struct Node* point, int* height);
struct Node* insert(int num, struct Node* point );
void search(int num, struct Node* node, int height);
void printInorder(struct Node* node);

int height = 1;

int main(int argc, char** argv) {
	FILE* fp = fopen(argv[1], "r");
	if ( fp == NULL) {
		//Your program should print “error” (and nothing else) if the ﬁle does not exist.
		printf("error");
	}
	int num[1];
	char character[1];
	while (fscanf(fp, "%c\t%d\n", character, num) != EOF) { //> 0) { 
		//returns how many succesful matches, if correct, then it will remain 2
		//printf("%c \t %d\n", *character, *num);

		if (*character == 'i') {
			//insert(*num, head, &height);
			insert(*num, head);
		//	continue;
		}
		else if (*character == 's') {
			search(*num, head, 0);
		//	continue;
		}
		else if (*character != 'i' || *character != 's') {
			printf("error\n");
			exit(0);
		} 
		
	
	}
	printInorder(head);
	fclose(fp);
	return 0;
}

//struct Node* insert(int num, struct Node* pCurNode, int* height) {
struct Node* insert(int num, struct Node* pCurNode ) {
	//printf("insert\t%d", num);
	
		//printf("inserted %d", (*height));
	if (pCurNode == NULL) {
		pCurNode = (struct Node*) malloc( sizeof(struct Node));
		pCurNode->data = num;
		pCurNode->left = NULL;
		pCurNode->right = NULL;
		if (head == NULL) head = pCurNode;
		printf("inserted %d\n", height);
	} else if (pCurNode-> data == num) {
		printf("duplicate\n");
		return pCurNode;
	} else if (pCurNode->data > num) {
		height++;
		//pCurNode->left = insert(num, pCurNode->left, height + 1);
		pCurNode->left = insert(num, pCurNode->left );
		//insert(num, pCurNode->left, height + 1);
		height--;
	} else { 
		height++;
		//pCurNode->right = insert(num, pCurNode->right, height + 1);
		pCurNode->right = insert(num, pCurNode->right );
		//insert(num, pCurNode->right, height + 1);
		height--;
	}
	return pCurNode;
}

void search(int num, struct Node* node, int height) {
	if (node == NULL) {
		printf("absent\n");
	} else if (node->data == num) {
		printf("present %d\n", height + 1);
	} else if( node->data > num) {
		search(num, node->left, height + 1);
	} else {
		search(num, node->right, height +1);
	}
}

void printInorder(struct Node* node) {
	//if ( node != NULL ) printf("hi %d\n", node->data );
	if ( node == NULL ) return;
	if (node->left != NULL) {
			//printf("go left\n");
		printInorder(node->left);
	} 
	//printf("value : %d\n", node->data);
	if (node-> right != NULL) {
		//printf("go right\n");
		printInorder(node->right);
	} 
	return;
}
