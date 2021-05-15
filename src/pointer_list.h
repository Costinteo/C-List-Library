#ifndef pointer_list
#define pointer_list

// this pointer list is more used as a utility list, and it has to be used manually by the user
// the user has to manually cast the data to the type he used in the list to print / use it
// you can keep more complex things with it, generalising the data type used
// possibly unsafe to use

#include "node/pointer_node.h"
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

struct Pointer_List {
    Pointer_Node * head;
    Pointer_Node * tail;
    int size;
};
typedef struct Pointer_List Pointer_List;

Pointer_List * addToPointerList(Pointer_List * plist, void * data);
Pointer_List * removeLastFromPointerList(Pointer_List * plist);
Pointer_List * removeIndexFromPointerList(Pointer_List * plist, unsigned int index);
Pointer_List * deletePointerList(Pointer_List * plist);
void * getPointer(Pointer_List * plist, unsigned int index);
void setPointer(Pointer_List * plist, void * newPointer, unsigned int index);

#endif