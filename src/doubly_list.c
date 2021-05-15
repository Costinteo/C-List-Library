#include "doubly_list.h"

Doubly_List * addToDoubly(Doubly_List * dlist, int data) {
    // initializing list
    if (dlist == NULL) {
        dlist = (Doubly_List*) malloc(sizeof(Doubly_List));
        if (dlist == NULL) {
            printf("Doubly List initialization failed...\n");
            return NULL;
        }
        dlist->head = NULL;
        dlist->tail = NULL;
        dlist->size = 0;
        
    }

    // checking if list is empty
    if (dlist->head == NULL) {
        dlist->head = createDoublyNode(data);
        dlist->tail = dlist->head;
    } else {
        // add new node to the tail of the list
        dlist->tail->next = createDoublyNode(data);
        dlist->tail->next->prev = dlist->tail;
        dlist->tail = dlist->tail->next;
    }

    dlist->size++;

    return dlist;
}

Doubly_List * insertInDoubly(Doubly_List * dlist, int data, unsigned int index) {
    // initializing list
    if (dlist == NULL) {
        dlist = (Doubly_List*) malloc(sizeof(Doubly_List));
        if (dlist == NULL) {
            printf("Doubly List initialization failed...\n");
            return NULL;
        }
    }

    if (index > dlist->size) {
        printf("Index out of bounds, nothing added...\n");
        return dlist;
    }

    if (index == 0) {
        Doubly_Node * temp = dlist->head;
        dlist->head = createDoublyNode(data);
        dlist->head->next = temp;
        temp->prev = dlist->head;
        
    } else {
        Doubly_Node * temp = dlist->head;
        
        // we move temp to the node before the index we want to insert at
        for (unsigned int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        Doubly_Node * tempNext = temp->next;
        temp->next = createDoublyNode(data);
        // set the links to the new node
        temp->next->prev = temp;
        temp->next->next = tempNext;
        // set the link for the one after
        // if the node after the one we inserted exists only then we set the prev
        if (tempNext != NULL)
            tempNext->prev = temp->next;
        // if the node before the index is the tail
        // we move the tail to the new node inserted
        if (temp == dlist->tail) {
            dlist->tail = temp->next;
        }

    }

    dlist->size++;
    
    return dlist; 
}

Doubly_List * removeLastFromDoubly(Doubly_List * dlist) {
    // check if list is initialized
    if (dlist == NULL) {
        printf("Doubly List not initialized...\n");
        return NULL;
    }

    if (dlist->size == 0) {
        printf("Doubly List empty, nothing removed...\n");
        return dlist;
    }

    // case where list only has one node
    if (dlist->size == 1) {
        free(dlist->head);
        dlist->head = NULL;
        dlist->tail = NULL;
        dlist->size--;
        return dlist;
    }

    Doubly_Node * temp = dlist->tail->prev;
    // remove node pointed to by tail
    free(dlist->tail);
    // move tail to the new last node
    dlist->tail = temp;
    dlist->tail->next = NULL;
    dlist->size--;

    return dlist;
}

Doubly_List * removeIndexFromDoubly(Doubly_List * dlist, unsigned int index) {
    // check if list is initialized
    if (dlist == NULL) {
        printf("Doubly List not initialized...\n");
        return NULL;
    }

    if (dlist->size == 0) {
        printf("Doubly List empty, nothing removed...\n");
        return dlist;
    }

    if (index >= dlist->size) {
        printf("Index out of bounds, nothing removed...\n");
        return dlist;
    }

    // we have 3 cases:
    // case 1: we're removing the first node (the head)
    // case 2: we're removing the last node (the tail)
    // case 3: we're removing a node that isn't the first or last one (in between)
    if (index == 0) {

        Doubly_Node * temp = dlist->head->next;
        free(dlist->head);
        dlist->head = temp;
        dlist->head->prev = NULL;

    } else if (index == dlist->size - 1) {

        Doubly_Node * temp = dlist->tail->prev;
        // remove node pointed to by tail
        free(dlist->tail);
        // move tail to the new last node
        dlist->tail = temp;
        dlist->tail->next = NULL;

    } else {

        Doubly_Node * temp = dlist->head;
        // move temp to the node previous to the one we're removing
        for (unsigned int i = 0; i < index; i++) {
            temp = temp->next;
        }
        Doubly_Node * tempNext = temp->next->next;
        free(temp->next);
        temp->next = tempNext;
        if (tempNext != NULL)
            tempNext->prev = temp;

    }

    if (dlist->size == 1) {
        dlist->head = NULL;
        dlist->tail = NULL;
    }
    dlist->size--;

    return dlist;
}

Doubly_List * removeDataFromDoubly(Doubly_List * dlist, int dataToRemove) {
    // check if list is initialized
    if (dlist == NULL) {
        printf("Doubly List not initialized...\n");
        return NULL;
    }

    if (dlist->size == 0) {
        printf("Doubly List empty, nothing removed...\n");
        return dlist;
    }  

    // check if we're removing the head
    if (dlist->head->data == dataToRemove) {
        Doubly_Node * temp = dlist->head->next;
        free(dlist->head);
        dlist->head = temp;
        dlist->head->prev = NULL;
        dlist->size--;
        return dlist;
    }

    Doubly_Node * temp = dlist->head;
    // we iterate until we get to the node previous to tail
    while (temp->next != NULL) {
        if (temp->next->data == dataToRemove)
            break;
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Data not found in list, nothing removed...\n");
        return dlist;
    } else {

        if (temp->next == dlist->tail) {
            dlist->tail = temp;
        }

        Doubly_Node * tempNext = temp->next->next;
        free(temp->next);
        temp->next = tempNext;
        if (tempNext != NULL)
            tempNext->prev = temp;
        dlist->size--;
        return dlist;
    }
}

int getDataFromDoubly(Doubly_List * dlist, unsigned int index) {
    // check if list is initialized
    if (dlist == NULL) {
        printf("Doubly List not initialized, returned 0...\n");
        return 0;
    }

    if (dlist->size == 0) {
        printf("Doubly List empty, returned 0...\n");
        return 0;
    }

    if (index >= dlist->size) {
        printf("Index out of bounds, returned 0...\n");
        return 0;
    }

    if (index == 0) {
        return dlist->head->data;
    } else if (index == dlist->size - 1) {
        return dlist->tail->data;
    } else {
        Doubly_Node * temp = dlist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        return temp->data; 
    }
}

void setDataFromDoubly(Doubly_List * dlist, int newData, unsigned int index) {
    // check if list is initialized
    if (dlist == NULL) {
        printf("Doubly List not initialized, data not set...\n");
        return;
    }

    if (dlist->size == 0) {
        printf("Doubly List empty, data not set...\n");
        return;
    }

    if (index >= dlist->size) {
        printf("Index out of bounds, data not set...\n");
        return;
    }

    if (index == 0) {
        dlist->head->data = newData;
    } else if (index == dlist->size - 1) {
        dlist->tail->data = newData;
    } else {
        Doubly_Node * temp = dlist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        temp->data = newData; 
    }
}

int searchDoubly(Doubly_List * dlist, int dataToSearch) {
    if (dlist == NULL) {
        printf("Doubly List not initialized, can't search...\n");
        return 0;
    }

    if (dlist->size == 0) {
        printf("Doubly List empty, can't search...\n");
        return 0;
    }

    Doubly_Node * temp = dlist->head;
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

void printDoublyList(Doubly_List * dlist) {
    if (dlist == NULL) {
        printf("Doubly List not initialized...\n");
        return;
    }

    if (dlist->size == 0) {
        printf("Doubly List is empty.\n");
        return;
    }

    printf("Doubly List of size %d, with nodes: ", dlist->size);
    Doubly_Node * temp = dlist->head;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp == NULL) {
            printf("\n");
        } else printf(" ");
    }
}

void printDoublyListReversed(Doubly_List * dlist) {
    if (dlist == NULL) {
        printf("Doubly List not initialized...\n");
        return;
    }

    if (dlist->size == 0) {
        printf("Doubly List is empty.\n");
        return;
    }

    printf("Doubly List of size %d, with nodes (in reverse order): ", dlist->size);
    Doubly_Node * temp = dlist->tail;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->prev;
        if (temp == NULL) {
            printf("\n");
        } else printf(" ");
    }
}


Doubly_List * deleteDoublyList(Doubly_List * dlist) {
    if (dlist == NULL) {
        printf("Doubly List not initialized, nothing to free...\n");
        return NULL;
    }

    Doubly_Node * temp = dlist->head;
    while (temp != NULL) {
        Doubly_Node * nodeToDelete = temp;
        temp = temp->next;
        free(nodeToDelete);
    }
    free(dlist);
    printf("Doubly List deleted...\n");
    return NULL;
}