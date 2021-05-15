#ifndef ordered_list
#define ordered_list

#include "node/doubly_node.h"
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

struct Ordered_List {
    Doubly_Node * head;
    Doubly_Node * tail;
    int (*comparator)(int, int);
    int customComp;
    int size;
};
typedef struct Ordered_List Ordered_List;

int defaultComparator(int x, int y);
Ordered_List * setComparator(Ordered_List * ordlist, int (*comparator)(int, int));
Ordered_List * addToOrdered(Ordered_List * orddlist, int data);
Ordered_List * removeLastFromOrdered(Ordered_List * ordlist);
Ordered_List * removeIndexFromOrdered(Ordered_List * ordlist, unsigned int index);
int getDataFromOrdered(Ordered_List * ordlist, unsigned int index);
void setDataFromOrdered(Ordered_List * ordlist, int newData, unsigned int index);
int searchOrdered(Ordered_List * ordlist, int dataToSearch);
void printOrderedList(Ordered_List * ordlist);
void printOrderedListReversed(Ordered_List * ordlist);
Ordered_List * deleteOrderedList(Ordered_List * ordlist);


#endif