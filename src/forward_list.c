#include "forward_list.h"

// adds to the tail of a Forward_List
Forward_List * addToForward(Forward_List * flist, int data) {
    // initializing list
    if (flist == NULL) {
        flist = (Forward_List*) malloc(sizeof(Forward_List));
        if (flist == NULL) {
            printf("Forward List initialization failed...\n");
            return NULL;
        }
        flist->head = NULL;
        flist->tail = NULL;
        flist->size = 0;
        
    }

    // checking if list is empty
    if (flist->head == NULL) {
        flist->head = createForwardNode(data);
        flist->tail = flist->head;
    } else {
        // add new node to the tail of the list
        flist->tail->next = createForwardNode(data);
        flist->tail = flist->tail->next;
    }

    flist->size++;

    return flist;
}

// insert data at a certain index in a Forward_List
Forward_List * insertInForward(Forward_List * flist, int data, unsigned int index) {
    // initializing list
    if (flist == NULL) {
        flist = (Forward_List*) malloc(sizeof(Forward_List));
        if (flist == NULL) {
            printf("Forward List initialization failed...\n");
            return NULL;
        }
    }

    if (index > flist->size) {
        printf("Index out of bounds, nothing added...\n");
        return flist;
    }

    if (index == 0) {
        Forward_Node * temp = flist->head;
        flist->head = createForwardNode(data);
        flist->head->next = temp;
    } else {
        Forward_Node * temp = flist->head;
        
        // we move temp to the node before the index we want to insert at
        for (unsigned int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        Forward_Node * tempNext = temp->next;
        temp->next = createForwardNode(data);
        temp->next->next = tempNext;
        // if the node before the index is the tail
        // we move the tail to the new node inserted
        if (temp == flist->tail) {
            flist->tail = temp->next;
        }

    }

    flist->size++;
    
    return flist; 
}

// removes the last node of a Forward_List
Forward_List * removeLastFromForward(Forward_List * flist) {
    // check if list is initialized
    if (flist == NULL) {
        printf("Forward List not initialized...\n");
        return NULL;
    }

    if (flist->size == 0) {
        printf("Forward List empty, nothing removed...\n");
        return flist;
    }

    // case where list only has one node
    if (flist->size == 1) {
        free(flist->head);
        flist->head = NULL;
        flist->tail = NULL;
        flist->size--;
        return flist;
    }

    Forward_Node * temp = flist->head;
    // we iterate until we get to the node previous to tail
    while (temp->next != flist->tail) {
        temp = temp->next;
    }
    // remove node pointed to by tail
    free(flist->tail);
    // move tail to the new last node
    flist->tail = temp;
    flist->tail->next = NULL;
    flist->size--;

    return flist;
}

// removes the data at index from Forward_List
Forward_List * removeIndexFromForward(Forward_List * flist, unsigned int index) {
    // check if list is initialized
    if (flist == NULL) {
        printf("Forward List not initialized...\n");
        return NULL;
    }

    if (flist->size == 0) {
        printf("Forward List empty, nothing removed...\n");
        return flist;
    }

    if (index >= flist->size) {
        printf("Index out of bounds, nothing removed...\n");
        return flist;
    }

    // we have 3 cases:
    // case 1: we're removing the first node (the head)
    // case 2: we're removing the last node (the tail)
    // case 3: we're removing a node that isn't the first or last one (in between)
    if (index == 0) {
        
        Forward_Node * temp = flist->head->next;
        free(flist->head);
        flist->head = temp;

    } else if (index == flist->size - 1) {

        Forward_Node * temp = flist->head;
        // we iterate until we get to the node previous to tail
        while (temp->next != flist->tail) {
            temp = temp->next;
        }
        // remove node pointed to by tail
        free(flist->tail);
        // move tail to the new last node
        flist->tail = temp;
        flist->tail->next = NULL;

    } else {

        Forward_Node * temp = flist->head;
        // move temp to the node previous to the one we're removing
        for (unsigned int i = 0; i < index; i++) {
            temp = temp->next;
        }
        Forward_Node * tempNext = temp->next->next;
        free(temp->next);
        temp->next = tempNext;

    }

    flist->size--;

    return flist;
}

// removes first occurence of data from forward list
// takes a pointer to a Forward_List and the data to lookup
Forward_List * removeDataFromForward(Forward_List * flist, int dataToRemove) {
    // check if list is initialized
    if (flist == NULL) {
        printf("Forward List not initialized...\n");
        return NULL;
    }

    if (flist->size == 0) {
        printf("Forward List empty, nothing removed...\n");
        return flist;
    }


    // check if we're removing the head
    if (flist->head->data == dataToRemove) {
        Forward_Node * temp = flist->head->next;
        free(flist->head);
        flist->head = temp;
        flist->size--;
        return flist;
    }
    Forward_Node * temp = flist->head;
    // we iterate until we get to the node previous to tail
    while (temp->next != NULL) {
        if (temp->next->data == dataToRemove)
            break;
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Data not found in list, nothing removed...\n");
        return flist;
    } else {

        if (temp->next == flist->tail) {
            flist->tail = temp;
        }

        Forward_Node * tempNext = temp->next->next;
        free(temp->next);
        temp->next = tempNext;
        flist->size--;
        return flist;
    }
}

// return data from a certain index in Forward_List
int getDataFromForward(Forward_List * flist, unsigned int index) {
    // check if list is initialized
    if (flist == NULL) {
        printf("Forward List not initialized, returned 0...\n");
        return 0;
    }

    if (flist->size == 0) {
        printf("Forward List empty, returned 0...\n");
        return 0;
    }

    if (index >= flist->size) {
        printf("Index out of bounds, returned 0...\n");
        return 0;
    }

    if (index == 0) {
        return flist->head->data;
    } else if (index == flist->size - 1) {
        return flist->tail->data;
    } else {
        Forward_Node * temp = flist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        return temp->data; 
    }
    
}

// sets data at a certain index in Forward_List
void setDataFromForward(Forward_List * flist, int newData, unsigned int index) {
    // check if list is initialized
    if (flist == NULL) {
        printf("Forward List not initialized, data not set...\n");
        return;
    }

    if (flist->size == 0) {
        printf("Forward List empty, data not set...\n");
        return;
    }

    if (index >= flist->size) {
        printf("Index out of bounds, data not set...\n");
        return;
    }

    if (index == 0) {
        flist->head->data = newData;
    } else if (index == flist->size - 1) {
        flist->tail->data = newData;
    } else {
        Forward_Node * temp = flist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        temp->data = newData; 
    }
}

// returns index of node containing dataToSearch if it's found in flist, -1 otherwise
int searchForward(Forward_List * flist, int dataToSearch) {
    if (flist == NULL) {
        printf("Forward List not initialized, can't search...\n");
        return 0;
    }

    if (flist->size == 0) {
        printf("Forward List empty, can't search...\n");
        return 0;
    }

    Forward_Node * temp = flist->head;
    unsigned int index = 0;
    while (temp != NULL) {
        if (temp->data == dataToSearch) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

void printForwardList(Forward_List * flist) {
    if (flist == NULL) {
        printf("Forward List not initialized...\n");
        return;
    }

    if (flist->size == 0) {
        printf("Forward List is empty.\n");
        return;
    }

    printf("Forward List of size %d, with nodes: ", flist->size);
    Forward_Node * temp = flist->head;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp == NULL) {
            printf("\n");
        } else printf(" ");
    }
}

Forward_List * deleteForwardList(Forward_List * flist) {
    if (flist == NULL) {
        printf("Forward List not initialized, nothing to free...\n");
        return NULL;
    }

    Forward_Node * temp = flist->head;
    while (temp != NULL) {
        Forward_Node * nodeToDelete = temp;
        temp = temp->next;
        free(nodeToDelete);
    }
    free(flist);
    printf("Forward List deleted...\n");
    return NULL;
}