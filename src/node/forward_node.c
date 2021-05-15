#include "forward_node.h"

Forward_Node * createForwardNode(int data) {
    Forward_Node * newNode = (Forward_Node*) malloc(sizeof(Forward_Node));
    if (newNode == NULL) {
            printf("Forward Node initialization failed...\n");
            return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}