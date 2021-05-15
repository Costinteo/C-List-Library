#ifndef doubly_node
#define doubly_node

#include <malloc.h>
#include <errno.h>

struct Doubly_Node {
    int data;
    struct Doubly_Node * next;
    struct Doubly_Node * prev;
};
typedef struct Doubly_Node Doubly_Node;


Doubly_Node * createDoublyNode(int data);

#endif