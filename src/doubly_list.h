#ifndef doubly_list
#define doubly_list

#include "node/doubly_node.h"
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

struct Doubly_List {
    Doubly_Node * head;
    Doubly_Node * tail;
    int size;
};
typedef struct Doubly_List Doubly_List;

Doubly_List * addToDoubly(Doubly_List * dlist, int data);
Doubly_List * insertInDoubly(Doubly_List * dlist, int data, unsigned int index);
Doubly_List * removeLastFromDoubly(Doubly_List * dlist);
Doubly_List * removeIndexFromDoubly(Doubly_List * dlist, unsigned int index);
Doubly_List * removeDataFromDoubly(Doubly_List * dlist, int dataToRemove);
int getDataFromDoubly(Doubly_List * dlist, unsigned int index);
void setDataFromDoubly(Doubly_List * dlist, int newData, unsigned int index);
int searchDoubly(Doubly_List * dlist, int dataToSearch);
void printDoublyList(Doubly_List * dlist);
void printDoublyListReversed(Doubly_List * dlist);
Doubly_List * deleteDoublyList(Doubly_List * dlist);
#endif