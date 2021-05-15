#include "pointer_node.h"

Pointer_Node * createPointerNode(void * data) {
    Pointer_Node * newNode = (Pointer_Node *) malloc(sizeof(Pointer_Node));
    if (newNode == NULL) {
            printf("Pointer Node initialization failed...\n");
            return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}