 #include "mixed_list.h"

// add to the end of a Mixed_List
Mixed_List * addToMixed(Mixed_List * mlist, int data) {
    // initializing mlist
    if (mlist == NULL) {
        mlist = (Mixed_List*) malloc(sizeof(Mixed_List));
        mlist->nodes = NULL;
        mlist->size = 0;
        if (mlist == NULL) {
            printf("Mixed List initialization failed...\n");
            return NULL;
        }
    }
    // creating the node to be added
    if (mlist->size < 100) {
        // realloc memory for size + 1 (the one to be added)
        mlist->nodes = (int*) realloc(mlist->nodes, sizeof(int) * (mlist->size + 1));
        if (mlist->nodes == NULL) {
            printf("Mixed List nodes array realloc failed...\n");
            return mlist;
        }
        mlist->nodes[mlist->size] = data;
        mlist->size++;
    } else {
        printf("Mixed List already reached limit! Last node not added...\n");
    }

    return mlist;

}

// remove index from Mixed_List
Mixed_List * removeIndexFromMixed(Mixed_List * mlist, unsigned int index) {
    if (mlist == NULL) {
        printf("Mixed List not initialized...\n");
        return NULL;
    }
    
    if (mlist->size == 0) {
        printf("Mixed List empty, nothing removed...\n");
        return mlist;
    }

    if (index >= mlist->size) {
        printf("Index given is out of bounds, nothing removed...\n");
        return mlist;
    }

    // moving all array elements one position to the left
    for (unsigned int i = index; i < mlist->size - 1; i++) {
        mlist->nodes[i] = mlist->nodes[i + 1];
    }
    mlist->size--;
    
    // free the associated memory by reallocating
    int hasBeenFreed = 0;
    if (mlist->size > 0) {
        mlist->nodes = (int*) realloc(mlist->nodes, sizeof(int) * mlist->size);
    } else {
        free(mlist->nodes);
        mlist->nodes = NULL;
        hasBeenFreed = 1;
    }

    if (mlist->nodes == NULL && !hasBeenFreed) {
        printf("Nodes array realloc on removal failed...\n");
        return mlist;
    }

    return mlist;
}

// remove last node from Mixed_List
Mixed_List * removeLastFromMixed(Mixed_List * mlist) {
    if (mlist == NULL) {
        printf("Mixed List not initialized...\n");
        return NULL;
    }

    if (mlist->size == 0) {
        printf("List empty, nothing removed...\n");
        return mlist;
    }

    mlist->size--;

    // free the associated memory and delete the data by reallocating nodes array
    int hasBeenFreed = 0;
    if (mlist->size > 0) {
        mlist->nodes = (int*) realloc(mlist->nodes, sizeof(int) * mlist->size);
    } else {
        free(mlist->nodes);
        mlist->nodes = NULL;
        hasBeenFreed = 1;
    }

    if (mlist->nodes == NULL && !hasBeenFreed) {
        printf("Nodes array realloc on removal failed...\n");
        return mlist;
    }

    return mlist;
}

void printMixedList(Mixed_List * mlist) {
    if (mlist == NULL) {
        printf("Mixed List not initialized...\n");
        return;
    }

    if (mlist->size == 0) {
        printf("Mixed List is empty.\n");
        return;
    }

    printf("Mixed List of size %d, with nodes: ", mlist->size);
    for (int i = 0; i < mlist->size; i++) {
        printf("%d", mlist->nodes[i]);
        if (i < mlist->size - 1) { 
            printf(" ");
        } else printf("\n");
    }
}

Mixed_List * deleteMixedList(Mixed_List * mlist) {
    if (mlist == NULL) {
        printf("Mixed List not initialized, nothing to delete...\n");
        return NULL;
    }

    free(mlist->nodes);
    free(mlist);
    printf("Mixed List deleted...\n");
    return NULL;

}