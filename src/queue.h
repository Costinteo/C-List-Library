#ifndef queue
#define queue

#include "node/forward_node.h"
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

struct Queue {
    Forward_Node * front;
    Forward_Node * back;
    int size;
};
typedef struct Queue Queue;

Queue * pushInQueue(Queue * q, int data);
Queue * popFromQueue(Queue * q);
int queueFront(Queue * q);
int isQueueEmpty(Queue * q);
void printQueue(Queue * q);
Queue * deleteQueue(Queue * q);


#endif