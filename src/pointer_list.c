#include "pointer_list.h"

Pointer_List * addToPointerList(Pointer_List * plist, void * data) {
    // initializing list
    if (plist == NULL) {
        plist = (Pointer_List*) malloc(sizeof(Pointer_List));
        if (plist == NULL) {
            printf("Pointer List initialization failed...\n");
            return NULL;
        }
        plist->head = NULL;
        plist->tail = NULL;
        plist->size = 0;
        
    }

    // checking if list is empty
    if (plist->head == NULL) {
        plist->head = createPointerNode(data);
        plist->tail = plist->head;
    } else {
        // add new node to the tail of the list
        plist->tail->next = createPointerNode(data);
        plist->tail = plist->tail->next;
    }

    plist->size++;

    return plist;
}

Pointer_List * removeLastFromPointerList(Pointer_List * plist) {
    // check if list is initialized
    if (plist == NULL) {
        printf("Pointer List not initialized...\n");
        return NULL;
    }

    if (plist->size == 0) {
        printf("Pointer List empty, nothing removed...\n");
        return plist;
    }

    // case where list only has one node
    if (plist->size == 1) {
        // also free the void pointer
        if (plist->head->data != NULL) {
            free(plist->head->data);
        }
        free(plist->head);
        plist->head = NULL;
        plist->tail = NULL;
        plist->size--;
        return plist;
    }

    Pointer_Node * temp = plist->head;
    // we iterate until we get to the node previous to tail
    while (temp->next != plist->tail) {
        temp = temp->next;
    }
    if (plist->tail->data != NULL) {
            free(plist->tail->data);
    }
    // remove node pointed to by tail
    free(plist->tail);
    // move tail to the new last node
    plist->tail = temp;
    plist->tail->next = NULL;
    plist->size--;

    return plist;
}

Pointer_List * removeIndexFromPointerList(Pointer_List * plist, unsigned int index) {
    // check if list is initialized
    if (plist == NULL) {
        printf("Pointer List not initialized...\n");
        return NULL;
    }

    if (plist->size == 0) {
        printf("Pointer List empty, nothing removed...\n");
        return plist;
    }

    if (index >= plist->size) {
        printf("Index out of bounds, nothing removed...\n");
        return plist;
    }

    // we have 3 cases:
    // case 1: we're removing the first node (the head)
    // case 2: we're removing the last node (the tail)
    // case 3: we're removing a node that isn't the first or last one (in between)
    if (index == 0) {
        
        Pointer_Node * temp = plist->head->next;
        if (plist->head->data != NULL) {
            free(plist->head->data);
        }
        free(plist->head);
        plist->head = temp;

    } else if (index == plist->size - 1) {

        Pointer_Node * temp = plist->head;
        // we iterate until we get to the node previous to tail
        while (temp->next != plist->tail) {
            temp = temp->next;
        }
        if (plist->tail->data != NULL) {
            free(plist->tail->data);
        }
        // remove node pointed to by tail
        free(plist->tail);
        // move tail to the new last node
        plist->tail = temp;
        plist->tail->next = NULL;

    } else {

        Pointer_Node * temp = plist->head;
        // move temp to the node previous to the one we're removing
        for (unsigned int i = 0; i < index; i++) {
            temp = temp->next;
        }
        Pointer_Node * tempNext = temp->next->next;
        if (temp->next->data != NULL) {
            free(temp->next->data);
        }
        free(temp->next);
        temp->next = tempNext;

    }

    plist->size--;

    return plist;
}

Pointer_List * deletePointerList(Pointer_List * plist) {
    if (plist == NULL) {
        printf("Pointer List not initialized, nothing to free...\n");
        return NULL;
    }

    Pointer_Node * temp = plist->head;
    while (temp != NULL) {
        Pointer_Node * nodeToDelete = temp;
        temp = temp->next;
        if (nodeToDelete->data != NULL) {
            free(nodeToDelete->data);
        }
        free(nodeToDelete);
    }
    free(plist);
    printf("Pointer List deleted...\n");
    return NULL;
}

void * getPointer(Pointer_List * plist, unsigned int index) {
    // check if list is initialized
    if (plist == NULL) {
        printf("Pointer List not initialized, returned 0...\n");
        return 0;
    }

    if (plist->size == 0) {
        printf("Pointer List empty, returned 0...\n");
        return 0;
    }

    if (index >= plist->size) {
        printf("Index out of bounds, returned 0...\n");
        return 0;
    }

    if (index == 0) {
        return plist->head->data;
    } else if (index == plist->size - 1) {
        return plist->tail->data;
    } else {
        Pointer_Node * temp = plist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        return temp->data; 
    }
}

void setPointer(Pointer_List * plist, void * newPointer, unsigned int index) {
    // check if list is initialized
    if (plist == NULL) {
        printf("Pointer List not initialized, data not set...\n");
        return;
    }

    if (plist->size == 0) {
        printf("Pointer List empty, data not set...\n");
        return;
    }

    if (index >= plist->size) {
        printf("Index out of bounds, data not set...\n");
        return;
    }

    if (index == 0) {
        plist->head->data = newPointer;
    } else if (index == plist->size - 1) {
        plist->tail->data = newPointer;
    } else {
        Pointer_Node * temp = plist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        temp->data = newPointer; 
    }
}