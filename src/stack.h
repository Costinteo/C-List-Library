#ifndef stack
#define stack

#include "node/forward_node.h"
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

struct Stack {
    Forward_Node * top;
    int size;
};
typedef struct Stack Stack;

Stack * pushInStack(Stack * s, int data);
Stack * popFromStack(Stack * s);
int stackTop(Stack * s);
int isStackEmpty(Stack * s);
void printStack(Stack * s);
Stack * deleteStack(Stack * s);


#endif