#include "doubly_node.h"

Doubly_Node * createDoublyNode(int data) {
    Doubly_Node * newNode = (Doubly_Node*) malloc(sizeof(Doubly_Node));
    if (newNode == NULL) {
            printf("Doubly Node initialization failed...\n");
            return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}