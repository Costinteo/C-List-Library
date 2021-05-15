#ifndef forward_list
#define forward_list

#include "node/forward_node.h"
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

struct Forward_List {
    Forward_Node * head;
    Forward_Node * tail;
    int size;
};
typedef struct Forward_List Forward_List;

Forward_List * addToForward(Forward_List * flist, int data);
Forward_List * insertInForward(Forward_List * flist, int data, unsigned int index);
Forward_List * removeLastFromForward(Forward_List * flist);
Forward_List * removeIndexFromForward(Forward_List * flist, unsigned int index);
Forward_List * removeDataFromForward(Forward_List * flist, int dataToRemove);
int getDataFromForward(Forward_List * flist, unsigned int index);
void setDataFromForward(Forward_List * flist, int newData, unsigned int index);
int searchForward(Forward_List * flist, int dataToSearch);
void printForwardList(Forward_List * flist);
Forward_List * deleteForwardList(Forward_List * flist);

#endif