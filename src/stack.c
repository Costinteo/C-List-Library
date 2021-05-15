#include "stack.h"

Stack * pushInStack(Stack * s, int data) {
    if (s == NULL) {
        s = (Stack*) malloc(sizeof(Stack));
        s->top = NULL;
        s->size = 0;
    }
    
    if (s->top == NULL) {
        s->top = createForwardNode(data);
    } else {
        Forward_Node * temp = s->top;
        s->top = createForwardNode(data);
        s->top->next = temp;
    }

    s->size++;
    
    return s;
}

Stack * popFromStack(Stack * s) {
    if (s == NULL) {
        printf("Stack is not initialized, nothing removed...\n");
        return NULL;
    }

    if (s->top == NULL) {
        printf("Stack is empty, nothing removed...\n");
        return s;
    }

    if (s->size == 1) {
        free(s->top);
        s->top = NULL;
        s->size--;
        return s;
    }

    Forward_Node * temp = s->top->next;
    free(s->top);
    s->top = temp;
    return s;
}

int stackTop(Stack * s) {
    if (s == NULL) {
        printf("Stack is not initialized, returned 0...\n");
        return 0;
    }

    if (s->top == NULL) {
        printf("Stack is empty, returned 0...\n");
        return 0;
    }

    return s->top->data;
    
}

int isStackEmpty(Stack * s) {
    if (s == NULL) return 1;
    return (s->size == 0);
}

void printStack(Stack * s) {
    if (s == NULL) {
        printf("Stack not initialized...\n");
        return;
    }

    if (s->size == 0) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack of size %d, with nodes: ", s->size);
    Forward_Node * temp = s->top;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp == NULL) {
            printf("\n");
        } else printf(" ");
    }
}

Stack * deleteStack(Stack * s) {
    if (s == NULL) {
        printf("Stack not initialized, nothing to free...\n");
        return NULL;
    }

    Forward_Node * temp = s->top;
    while (temp != NULL) {
        Forward_Node * nodeToDelete = temp;
        temp = temp->next;
        free(nodeToDelete);
    }
    free(s);
    printf("Stack deleted...\n");
    return NULL;
}
