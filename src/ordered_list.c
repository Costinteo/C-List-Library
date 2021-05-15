#include "ordered_list.h"

// basically a greater comparison, orders the list ascendantly
int defaultComparator(int x, int y) {
    return (x > y);
}

// takes an ordered list and sets its comparator to the one passed as argument
// then it returns a pointer to the changed ordered list
Ordered_List * setComparator(Ordered_List * ordlist, int (*comparator)(int, int)) {
    if (ordlist == NULL) {
        ordlist = (Ordered_List*) malloc(sizeof(Ordered_List));
        if (ordlist == NULL) {
            printf("Ordered List initialization failed...\n");
            return NULL;
        }
        ordlist->head = NULL;
        ordlist->tail = NULL;
        ordlist->size = 0;
        ordlist->customComp = 1;
    }
    ordlist->comparator = comparator;
    return ordlist;
}

// add to ordered list respecting its comparator
Ordered_List * addToOrdered(Ordered_List * ordlist, int data) {
    if (ordlist == NULL) {
        ordlist = (Ordered_List*) malloc(sizeof(Ordered_List));
        if (ordlist == NULL) {
            printf("Ordered List initialization failed...\n");
            return NULL;
        }
        ordlist->head = NULL;
        ordlist->tail = NULL;
        ordlist->size = 0;
        ordlist->customComp = 0;
        ordlist->comparator = defaultComparator;
    }

    // check if the data we're adding is the first item in list
    if (ordlist->head == NULL) {
        ordlist->head = createDoublyNode(data);
        ordlist->tail = ordlist->head;
        ordlist->size++;
        return ordlist;
    } else {
        Doubly_Node * temp = ordlist->head;
        while (temp != NULL) {
            // find the spot to insert in
            if (ordlist->comparator(temp->data, data)) {
                // check if we add before head
                if (temp == ordlist->head) {
                    ordlist->head = createDoublyNode(data);
                    ordlist->head->next = temp;
                    temp->prev = ordlist->head;
                    ordlist->size++;
                    return ordlist;
                }
                // add normally
                Doubly_Node * nodeBefore = temp->prev;
                nodeBefore->next = createDoublyNode(data);
                nodeBefore->next->prev = nodeBefore;
                nodeBefore->next->next = temp;
                temp->prev = nodeBefore->next;
                ordlist->size++;
                return ordlist;
            }
            temp = temp->next;
        }
        // if the while passes, it means we're adding the item
        // on the last position of the list, at list tail
        ordlist->tail->next = createDoublyNode(data);
        ordlist->tail->next->prev = ordlist->tail;
        ordlist->tail = ordlist->tail->next;
        ordlist->size++;
        return ordlist;
    }
}

Ordered_List * removeLastFromOrdered(Ordered_List * ordlist) {
    if (ordlist == NULL) {
        printf("Ordered List not initialized...\n");
        return NULL;
    }

    if (ordlist->size == 0) {
        printf("Ordered List empty, nothing removed...\n");
        return ordlist;
    }

    // case where list only has one node
    if (ordlist->size == 1) {
        free(ordlist->head);
        ordlist->head = NULL;
        ordlist->tail = NULL;
        ordlist->size--;
        return ordlist;
    }

    Doubly_Node * temp = ordlist->tail->prev;
    // remove node pointed to by tail
    free(ordlist->tail);
    // move tail to the new last node
    ordlist->tail = temp;
    ordlist->tail->next = NULL;
    ordlist->size--;

    return ordlist;
}

Ordered_List * removeIndexFromOrdered(Ordered_List * ordlist, unsigned int index) {
    // check if list is initialized
    if (ordlist == NULL) {
        printf("Ordered List not initialized...\n");
        return NULL;
    }

    if (ordlist->size == 0) {
        printf("Ordered List empty, nothing removed...\n");
        return ordlist;
    }

    if (index >= ordlist->size) {
        printf("Index out of bounds, nothing removed...\n");
        return ordlist;
    }

    // we have 3 cases:
    // case 1: we're removing the first node (the head)
    // case 2: we're removing the last node (the tail)
    // case 3: we're removing a node that isn't the first or last one (in between)
    if (index == 0) {

        Doubly_Node * temp = ordlist->head->next;
        free(ordlist->head);
        ordlist->head = temp;
        ordlist->head->prev = NULL;

    } else if (index == ordlist->size - 1) {

        Doubly_Node * temp = ordlist->tail->prev;
        // remove node pointed to by tail
        free(ordlist->tail);
        // move tail to the new last node
        ordlist->tail = temp;
        ordlist->tail->next = NULL;

    } else {

        Doubly_Node * temp = ordlist->head;
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

    if (ordlist->size == 1) {
        ordlist->head = NULL;
        ordlist->tail = NULL;
    }
    ordlist->size--;

    return ordlist;
}

int getDataFromOrdered(Ordered_List * ordlist, unsigned int index) {
    // check if list is initialized
    if (ordlist == NULL) {
        printf("Ordered List not initialized, returned 0...\n");
        return 0;
    }

    if (ordlist->size == 0) {
        printf("Ordered List empty, returned 0...\n");
        return 0;
    }

    if (index >= ordlist->size) {
        printf("Index out of bounds, returned 0...\n");
        return 0;
    }

    if (index == 0) {
        return ordlist->head->data;
    } else if (index == ordlist->size - 1) {
        return ordlist->tail->data;
    } else {
        Doubly_Node * temp = ordlist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        return temp->data; 
    }
}

void setDataFromOrdered(Ordered_List * ordlist, int newData, unsigned int index) {
    // check if list is initialized
    if (ordlist == NULL) {
        printf("Ordered List not initialized, data not set...\n");
        return;
    }

    if (ordlist->size == 0) {
        printf("Ordered List empty, data not set...\n");
        return;
    }

    if (index >= ordlist->size) {
        printf("Index out of bounds, data not set...\n");
        return;
    }

    if (index == 0) {
        ordlist->head->data = newData;
    } else if (index == ordlist->size - 1) {
        ordlist->tail->data = newData;
    } else {
        Doubly_Node * temp = ordlist->head;
        for (unsigned int i = 0; i <= index; i++) {
            temp = temp->next;
        }
        temp->data = newData; 
    }
}

int searchOrdered(Ordered_List * ordlist, int dataToSearch) {
    if (ordlist == NULL) {
        printf("Ordered List not initialized, can't search...\n");
        return 0;
    }

    if (ordlist->size == 0) {
        printf("Ordered List empty, can't search...\n");
        return 0;
    }

    Doubly_Node * temp = ordlist->head;
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

void printOrderedList(Ordered_List * ordlist) {
    if (ordlist == NULL) {
        printf("Ordered list not initialized...\n");
        return;
    }

    if (ordlist->size == 0) {
        printf("Ordered list is empty...\n");
        return;
    }

    printf("Ordered List of size %d, with nodes: ", ordlist->size);
    Doubly_Node * temp = ordlist->head;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp == NULL) {
            printf("\n");
        } else printf(" ");
    }

}

void printOrderedListReversed(Ordered_List * ordlist) {
    if (ordlist == NULL) {
        printf("Ordered list not initialized...\n");
        return;
    }

    if (ordlist->size == 0) {
        printf("Ordered list is empty...\n");
    }

    printf("Ordered List of size %d, with nodes (in reverse order): ", ordlist->size);
    Doubly_Node * temp = ordlist->tail;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->prev;
        if (temp == NULL) {
            printf("\n");
        } else printf(" ");
    }

}

Ordered_List * deleteOrderedList(Ordered_List * ordlist) {
    if (ordlist == NULL) {
        printf("Ordered List not initialized, nothing to free...\n");
        return NULL;
    }

    Doubly_Node * temp = ordlist->head;
    while (temp != NULL) {
        Doubly_Node * nodeToDelete = temp;
        temp = temp->next;
        free(nodeToDelete);
    }
    free(ordlist);
    printf("Ordered List deleted...\n");
    return NULL;
}