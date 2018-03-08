#include <stdio.h>
#include <stdlib.h>
	

/* Struct */
typedef struct node Node;
struct node {
	Node* node;
};


/*Prototypes*/
Node* create(Node* node);
void freeNode(Node* node);

Node* create(Node* node){
	node = (Node*) malloc(sizeof(Node));
	if(node == NULL){
		NULL;
	}
	return node;
} 

void freeNode(Node* node){
	free(node);
}


