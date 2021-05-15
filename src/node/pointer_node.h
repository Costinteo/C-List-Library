#ifndef pointer_node
#define pointer_node

#include <malloc.h>
#include <errno.h>

struct Pointer_Node {
    void * data;
    struct Pointer_Node * next;
};

typedef struct Pointer_Node Pointer_Node;

Pointer_Node * createPointerNode(void * data);

#endif