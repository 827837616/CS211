#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
struct Node { 
	int data;
	struct Node* left;
	struct Node* right;
};
struct Node* head = NULL;
struct Node* pNode = NULL;
int height = 1;

struct Node* insert(int num, struct Node* point );
void search(int num, struct Node* node, int height);
void printInorder(struct Node* node);
struct Node* find( struct Node* pNode, int num, int getMin);
struct Node* delete (struct Node* root, int num, int height);
void deallocate(struct Node* n);
int main(int argc, char** argv) {
	if (access(argv[1], F_OK) == -1){
		printf("error\n");
		exit(0);
	}
	FILE* fp = fopen(argv[1], "r");
	//if ( fp == NULL) {
	//	printf("error");
	//}
//	if(ftell(fp) == 0){
//		exit(0);
//	}
//	rewind(fp);
	int num[1];
	char character[1];
	int height = 1;
	while (fscanf(fp, "%c\t%d\n", character, num) != EOF) { 
		if (*character == 'i') {
			insert(*num, head);
		} else if (*character == 's') {
			search(*num, head, 0);
		} else if( *character == 'd') {
			head= delete(head, *num, height);
		} else if (*character != 'i' || *character != 's' || *character != 'd') {
			printf("error\n");
			exit(0);
		} 
		
	
	}
	printInorder(head);
	deallocate(head);
	fclose(fp);
	return 0;
}

struct Node* insert(int num, struct Node* pCurNode ) {
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
		pCurNode->left = insert(num, pCurNode->left );
		height--;
	} else { 
		height++;
		pCurNode->right = insert(num, pCurNode->right );
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
	if ( node == NULL ) return;
	if (node->left != NULL) {
		printInorder(node->left);
	}
	//printf("value: %d\n", node->data);
	if (node-> right != NULL) {
		printInorder(node->right);
	} 
	return;
}

struct Node* find( struct Node* pNode, int num, int getMin) {
	if ( getMin == 1 ) {
		struct Node* current = pNode;
		while (current-> left != NULL) {
			current = current-> left;
		}
		return current;
	}
	else {
		struct Node* current = pNode;
		//struct Node* parent = pNode;
		while (current != NULL && current->data != num) {
			//parent = current;
			if (pNode->data < num) {
				current = current->right;
			} else if (pNode->data > num) {
				pNode = pNode->left;
			}
		}
		return current;
	}
}

struct Node* delete (struct Node* root, int num, int height) {
	/*struct Node* parOfNTBD =find(root, num, 0);	
	struct Node* ntbd = NULL;
	if (parOfNTBD->left->data == num) {
		ntbd = parOfNTBD->left;
	} else if (parOfNTBD->right->data == num) {
		ntbd = parOfNTBD->right;
	}
	if (ntbd == NULL) {
		printf("fail\n");
		return root;
	} */
	if (root == NULL) {
		printf("fail\n"); //root moved through and couldnt find mathc
	} else if(root->data > num) { //num is smalled move left
		root->left = delete(root->left, num, height + 1);
	} else if (root->data < num) { // bigger move right
		root->right = delete(root->right, num, height + 1);
	} else { // match found
		if (height == 1 && (root->right == NULL && root->left == NULL)) {
			printf("success\n");
			root = NULL;
			return root;
		} else if (root->right != NULL && root->left != NULL) {
			struct Node* saved = find(root->right, num, 1);
			root->data = saved->data;
			root->right = delete(root->right, saved->data, height + 1);
		} else if (root-> left == NULL && root ->right != NULL) {
			struct Node* saved = root->right;
			free(root);
			printf("success\n");
			return saved;
		} else if (root-> right == NULL && root ->left != NULL) {
			struct Node* saved = root->left;
			free(root);
			printf("success\n");
			return saved;
		} else { // both NULL
			struct Node* saved = root->right;
			free(root);
			printf("success\n");
			return saved;
		}
	}
	return root;	
	/*else {
		struct Node* savedNTBD = ntbd;
		//struct Node* savedParOfNTBD = parOfNTBD;
		if (ntbd->right != NULL && ntbd->left != NULL) {
			struct Node* ntri = NULL;
			ntri = find(root, num, 1);
			ntbd->data = ntri->data;
			delete(ntri, ntri->data);

		//	struct Node* savedNTBD = ntbd;
		//	struct Node* savedParOfNTBD = parOfNTBD;
		//	ntbd = find(ntbd->right, num, true, parOfNTBD);
		//	*savedParOfNTBD = ntbd;

		} else if (ntbd->right != NULL) {
			parOfNTBD = ntbd->right;
			free(savedNTBD);
			printf("success\n");
		} else if (ntbd->left != NULL) {
			parOfNTBD = ntbd->left;
			free(savedNTBD);
			printf("success\n");

		} else {
			free(savedNTBD);
			printf("success");
		}
	}
	return root; */
}
void deallocate(struct Node* n){
	if(n!=NULL){
		deallocate(n->left);
		deallocate(n->right);
		free(n);
	}
}
