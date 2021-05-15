#ifndef mixed_list
#define mixed_list

#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

struct Mixed_List {
    int * nodes;
    int size;
};

typedef struct Mixed_List Mixed_List;

Mixed_List * addToMixed(Mixed_List * mlist, int data);
Mixed_List * removeIndexFromMixed(Mixed_List * mlist, unsigned int index);
Mixed_List * removeLastFromMixed(Mixed_List * mlist);
void printMixedList(Mixed_List * mlist);
Mixed_List * deleteMixedList(Mixed_List * mlist);

#endif