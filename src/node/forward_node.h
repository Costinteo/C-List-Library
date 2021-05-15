#ifndef forward_node
#define forward_node

#include <malloc.h>
#include <errno.h>

struct Forward_Node {
    int data;
    struct Forward_Node * next;
};

typedef struct Forward_Node Forward_Node;

Forward_Node * createForwardNode(int data);

#endif