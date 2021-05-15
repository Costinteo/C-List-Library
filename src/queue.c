#include "queue.h"

Queue * pushInQueue(Queue * q, int data) {
    if (q == NULL) {
        q = (Queue*) malloc(sizeof(Queue));
        if (q == NULL) {
            printf("Queue initialization failed...\n");
            return NULL;
        }
        q->front = NULL;
        q->back = NULL;
        q->size = 0;
    }
    
    if (q->front == NULL) {
        q->front = createForwardNode(data);
        q->back = q->front;
    } else {
        q->back->next = createForwardNode(data);
        q->back = q->back->next;
    }
    
    q->size++;
    
    return q;
}

Queue * popFromQueue(Queue *q) {
    if (q == NULL) {
        printf("Queue is not initialized, nothing removed...\n");
        return NULL;
    }

    if (q->size == 0) {
        printf("Queue is empty, nothing removed...\n");
        return q;
    }

    // case where there's only one node in q
    if (q->size == 1) {
        free(q->front);
        q->front = NULL;
        q->back = NULL;
        q->size--;
        return q;
    }

    Forward_Node * toDelete = q->front;
    q->front = q->front->next;
    q->size--;
    free(toDelete);
    return q;
}

int queueFront(Queue * q) {
    if (q == NULL) {
        printf("Queue is not initialized, returned 0...\n");
        return 0;
    }
    if (q->size == 0) {
        printf("Queue is empty, returned 0...\n");
        return 0;
    }
    return q->front->data;
}

int isQueueEmpty(Queue * q) {
    if (q == NULL) return 1;
    return (q->size == 0);
}

void printQueue(Queue * q) {
    if (q == NULL) {
        printf("Queue not initialized...\n");
        return;
    }

    if (q->size == 0) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue of size %d, with nodes: ", q->size);
    Forward_Node * temp = q->front;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp == NULL) {
            printf("\n");
        } else printf(" ");
    }
}

Queue * deleteQueue(Queue * q) {
    if (q == NULL) {
        printf("Queue not initialized, nothing to free...\n");
        return NULL;
    }

    Forward_Node * temp = q->front;
    while (temp != NULL) {
        Forward_Node * nodeToDelete = temp;
        temp = temp->next;
        free(nodeToDelete);
    }
    free(q);
    printf("Queue deleted...\n");
    return NULL;
}