#include "list_library.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// This is a demo for list_library

// simple lesser comparison
int lesser(int x, int y) {
    return (x < y);
}

// odd numbers ordered first and greater comparison
int oddFirst(int x, int y) {
    if (x % 2 != y % 2)
        return (x % 2 < y % 2);
    else return (x > y);
}

// even numbers ordered first and greater comparison
int evenFirst(int x, int y) {
    if (x % 2 != y % 2)
        return (x % 2 > y % 2);
    else return (x > y);
}

// we'll dinamically store the created lists in multiple global Pointer_Lists, this is also why we created pointer list
// since this isn't c++ and we can't use polymorphism, we'll use casts and pointer lists
// we'll also be keeping their names using char* lists (that are also pointer lists since I haven't written a char* forward list)

Pointer_List * mixedLists = NULL;
Pointer_List * mixedListsNames = NULL;

Pointer_List * forwardLists = NULL;
Pointer_List * forwardListsNames = NULL;

Pointer_List * doublyLists = NULL;
Pointer_List * doublyListsNames = NULL;

Pointer_List * orderedLists = NULL;
Pointer_List * orderedListsNames = NULL;

Pointer_List * queues = NULL;
Pointer_List * queuesNames = NULL;

Pointer_List * stacks = NULL;
Pointer_List * stacksNames = NULL;

void createListDisplay();
void accessListFuncDisplay();
void printListsDisplay();


/*********************************\
 *
 * complex demo function
 *
\*********************************/ 

void menuLoop() {
    printf("This is a demo application for this project.\n");

    while (1) {
        printf("Available actions:\n");
        printf("1.Create list\n");
        printf("2.Access list functions\n");
        printf("3.Print available lists\n");
        printf("4.Exit\n");
        printf("-----------------------\n");
        int commandNumber;
        printf("Input action number: ");
        scanf("%d", &commandNumber);
        printf("\n");
        switch(commandNumber) {
            case 1: {
                createListDisplay();
                break;
            }
            case 2: {
                accessListFuncDisplay();
                break;
            }
            case 3: {
                printListsDisplay();
                break;
            }
            case 4: {
                return;
            }
            default: {
                while (1) {
                    printf("Input command not found, do you want to retry? [y/n] ");
                    char ch;
                    scanf("%c", &ch);
                    if (ch == 'n') {
                        return; // return from function
                    } else if (ch == 'y') {
                        break; // break from while
                    } else {
                        printf("Please answer with lowercase y or n;\n");
                    }
                }
                break;
            }
        }

    }



}


/*********************************\
 *
 * simple demo
 *
\*********************************/ 

void simpleDemo() {
    Mixed_List * mlist = NULL;
    Forward_List * flist = NULL;
    Doubly_List * dlist = NULL;
    Ordered_List * ordlist = NULL;
    Queue * q = NULL;
    Stack * s = NULL;
    Pointer_List * plist = NULL;

    // setting comparator to a custom one
    ordlist = setComparator(ordlist, oddFirst);

    FILE* f = fopen("test.in", "r");
    if (f == NULL) {
        printf("File couldn't be opened, exiting...\n");
        exit(0);
    }
    int n;
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        fscanf(f, "%d", &x);
        int * a = malloc(sizeof(int));
        *a = x;
        flist = addToForward(flist, x);
        mlist = addToMixed(mlist, x);
        dlist = addToDoubly(dlist, x);
        ordlist = addToOrdered(ordlist, x);
        q = pushInQueue(q, x);
        s = pushInStack(s, x);
        plist = addToPointerList(plist, (void*)a);

    }

    printMixedList(mlist);
    printForwardList(flist);
    printDoublyList(dlist);
    printDoublyListReversed(dlist);
    printOrderedList(ordlist);
    printOrderedListReversed(ordlist);
    printQueue(q);
    printStack(s);


    printf("Pointer list: ");
    for (Pointer_Node * pNode = plist->head; pNode != NULL; pNode = pNode->next) {
        printf("%d ", *(int*)pNode->data);
    }
    printf("\n");
    

    mlist = deleteMixedList(mlist);
    flist = deleteForwardList(flist);
    dlist = deleteDoublyList(dlist);
    ordlist = deleteOrderedList(ordlist);
    q = deleteQueue(q);
    s = deleteStack(s);
    plist = deletePointerList(plist);
}

/*********************************\
 *
 * The main function
 *
\*********************************/ 

int main() {
    printf("Pick demo type:\n");
    printf("1.Simple demo with hardcoded values (changeable in simpleDemo func and test.in)\n");
    printf("2.Complex dynamic demo\n");
    int demoType;
    printf("Pick demo: ");
    scanf("%d", &demoType);
    switch(demoType) {
        case 1:
            simpleDemo();
            break;
        case 2:
            menuLoop();
            break;
        default:
            printf("Demo not found, exiting application...\n");
            break;
    }
}


/*********************************\
 *
 * other functions used
 * in complex demo function
 *
\*********************************/ 

void createListDisplay() {
    int valid = 1;
    while (valid) {
        printf("Which of the following do you wish to create:\n");
        printf("1.Mixed list\n");
        printf("2.Forward list\n");
        printf("3.Doubly list\n");
        printf("4.Ordered list\n");
        printf("5.Queue\n");
        printf("6.Stack\n");
        printf("-----------------------\n");

        int commandNumber;
        printf("Input list number: ");
        scanf("%d", &commandNumber);
        
        printf("Give your list a name (max 20 chars, no spaces):\n");
        char buffer[20];
        scanf("%s", buffer);
        char * name = malloc(sizeof(char) * (strlen(buffer) + 1));
        strncpy(name, buffer, strlen(buffer));
        name[strlen(buffer)] = '\0';

        // we set valid to 0, presuming we create a list, if not we set it back to one to continue looping in default case
        valid = 0;
        switch(commandNumber) {
            case 1: {
                Mixed_List * mlist = NULL;
                mixedLists = addToPointerList(mixedLists, (void*)mlist);
                mixedListsNames = addToPointerList(mixedListsNames, (void*)name);
                break;
            }
            case 2: {
                Forward_List * flist = NULL;
                forwardLists = addToPointerList(forwardLists, (void*)flist);
                forwardListsNames = addToPointerList(forwardListsNames, (void*)name);
                break;
            }
            case 3: {
                Doubly_List * dlist = NULL;
                doublyLists = addToPointerList(doublyLists, (void*)dlist);
                doublyListsNames = addToPointerList(doublyListsNames, (void*)name);
                break;
            }
            case 4: {
                Ordered_List * ordlist = NULL;
                printf("Pick a comparator for the ordered list:\n");
                printf("1.Greater(default)\n");
                printf("2.Lesser\n");
                printf("3.Odd first\n");
                printf("4.Even first\n");
                int compIdx;
                scanf("%d", &compIdx);
                switch(compIdx) {
                    case 1: {
                        // break cause it's default comparator anyways
                        break;
                    }
                    case 2: {
                        ordlist = setComparator(ordlist, lesser);
                        break;
                    }
                    case 3: {
                        ordlist = setComparator(ordlist, oddFirst);
                        break;
                    }
                    case 4: {
                        ordlist = setComparator(ordlist, evenFirst);
                        break;
                    }
                    default: {
                        printf("Comparator not found, resuming with default comparator...\n");
                        break;
                    }
                }
                orderedLists = addToPointerList(orderedLists, (void*)ordlist);
                orderedListsNames = addToPointerList(orderedListsNames, (void*)name);
                break;
            }
            case 5: {
                Queue * q = NULL;
                queues = addToPointerList(queues, (void*)q);
                queuesNames = addToPointerList(queuesNames, (void*)name);
                break;
            }
            case 6: {
                Stack * s = NULL;
                stacks = addToPointerList(stacks, (void*)s);
                stacksNames = addToPointerList(stacksNames, (void*)name);
                break;
            }
            default: {
                while (1) {
                    free(name);
                    printf("Input command not found, do you want to retry? [y/n] ");
                    char ch;
                    scanf("%c", &ch);
                    if (ch == 'n') {
                        return; // return from function
                    } else if (ch == 'y') {
                        break; // break from while
                    } else {
                        printf("Please answer with lowercase y or n;\n");
                    }
                }
                valid = 1;
                break;
            }
        }
        

    }
}

void accessListFuncDisplay() {
    while (1) {
        printf("Which of the following list types do you wish to print functions for:\n");
        printf("1.Mixed list\n");
        printf("2.Forward list\n");
        printf("3.Doubly list\n");
        printf("4.Ordered list\n");
        printf("5.Queue\n");
        printf("6.Stack\n");
        printf("7.Exit\n");
        printf("-----------------------\n");

        int commandNumber;
        printf("Input list number: ");
        scanf("%d", &commandNumber);

        switch(commandNumber) {
            //
            //
            // MIXED LISTS
            //
            //
            case 1: {
                if (mixedLists == NULL) {
                    printf("List array not initialized...\n");
                    break;
                }
                printf("Available lists:\n");
                for (int i = 0; i < mixedListsNames->size; i++) {
                    printf("%d.%s\n", i + 1, (char*)getPointer(mixedListsNames, i));
                }

                printf("Pick a list: ");
                int listNumber;
                scanf("%d", &listNumber);
                listNumber--;
                if (listNumber >= mixedListsNames->size || listNumber < 0) {
                    printf("List not found, exiting this list menu...\n");
                    break;
                }

                // select current list
                Mixed_List * current_list = (Mixed_List*) getPointer(mixedLists, listNumber);

                printf("Available functions:\n");
                printf("1.Add data\n");
                printf("2.Remove data at index\n");
                printf("3.Remove last item\n");
                printf("4.Print list\n");
                printf("5.Delete list\n");
                int listCommandNumber;
                printf("Input command number: ");
                scanf("%d", &listCommandNumber);
                switch(listCommandNumber) {
                    case 1: {
                        int data;
                        printf("Input data to add: ");
                        scanf("%d", &data);
                        setPointer(mixedLists, (void*)addToMixed(current_list, data), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 2: {
                        unsigned int idx;
                        printf("Input index from which to remove data: ");
                        scanf("%u", &idx);
                        setPointer(mixedLists, (void*)removeIndexFromMixed(current_list, idx), listNumber);
                        printf("Data removed!\n");
                        break;
                    }
                    case 3: {
                        setPointer(mixedLists, (void*)removeLastFromMixed(current_list), listNumber);
                        break;
                    }
                    case 4: {
                        printMixedList(current_list);
                        break;
                    }
                    case 5: {
                        setPointer(mixedLists, deleteMixedList(current_list), listNumber);
                        removeIndexFromPointerList(mixedLists, listNumber);
                        removeIndexFromPointerList(mixedListsNames, listNumber);
                        break;
                    }
                    default: {
                        printf("Input command not found.\n");
                        break;
                    }
                }

                break;
            }
            //
            //
            // FORWARD LISTS
            //
            //
            case 2: {
                if (forwardLists == NULL) {
                    printf("List array not initialized...\n");
                    break;
                }
                printf("Available lists:\n");
                for (int i = 0; i < forwardListsNames->size; i++) {
                    printf("%d.%s\n", i + 1, (char*)getPointer(forwardListsNames, i));
                }

                printf("Pick a list: ");
                int listNumber;
                scanf("%d", &listNumber);
                listNumber--;
                if (listNumber >= forwardListsNames->size || listNumber < 0) {
                    printf("List not found, exiting this list menu...\n");
                    break;
                }

                // select current list
                Forward_List * current_list = (Forward_List*) getPointer(forwardLists, listNumber);

                printf("Available functions:\n");
                printf("1.Add data\n");
                printf("2.Insert data\n");
                printf("3.Remove data at index\n");
                printf("4.Remove last item\n");
                printf("5.Remove first occurence of data\n");
                printf("6.Change data at index\n");
                printf("7.Search data in list\n");
                printf("8.Print list\n");
                printf("9.Delete list\n");
                int listCommandNumber;
                printf("Input command number: ");
                scanf("%d", &listCommandNumber);
                switch(listCommandNumber) {
                    case 1: {
                        int data;
                        printf("Input data to add: ");
                        scanf("%d", &data);
                        setPointer(forwardLists, (void*)addToForward(current_list, data), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 2: {
                        int data;
                        unsigned int idx;
                        printf("Input data to insert: ");
                        scanf("%d", &data);
                        printf("Input index to insert at: ");
                        scanf("%d", &idx);
                        setPointer(forwardLists, (void*)insertInForward(current_list, data, idx), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 3: {
                        unsigned int idx;
                        printf("Input index from which to remove data: ");
                        scanf("%u", &idx);
                        setPointer(forwardLists, (void*)removeIndexFromForward(current_list, idx), listNumber);
                        printf("Data removed!\n");
                        break;
                    }
                    case 4: {
                        setPointer(forwardLists, (void*)removeLastFromForward(current_list), listNumber);
                        break;
                    }
                    case 5: {
                        int data;
                        printf("Input data to search for: ");
                        scanf("%d", &data);
                        setPointer(forwardLists, (void*)removeDataFromForward(current_list, data), listNumber);
                        break;
                    }
                    case 6: {
                        int data;
                        unsigned int idx;
                        printf("Input new data: ");
                        scanf("%d", &data);
                        printf("Input index to change data at: ");
                        scanf("%d", &idx);
                        setDataFromForward(current_list, data, idx);
                        break;
                    }
                    case 7: {
                        int data;
                        printf("Input data to search for: ");
                        scanf("%d", &data);
                        unsigned int idx = searchForward(current_list, data);
                        if (idx == -1) {
                            printf("Data not found...\n");
                        } else printf("Data found at index %d\n", idx);
                        break;
                    }
                    case 8: {
                        printForwardList(current_list);
                        break;
                    }
                    case 9: {
                        setPointer(forwardLists, deleteForwardList(current_list), listNumber);
                        removeIndexFromPointerList(forwardLists, listNumber);
                        removeIndexFromPointerList(forwardListsNames, listNumber);
                        break;
                    }
                    default: {
                        printf("Input command not found.\n");
                        break;
                    }
                }

                break;
            }
            //
            //
            // DOUBLY LISTS
            //
            //
            case 3: {
                if (doublyLists == NULL) {
                    printf("List array not initialized...\n");
                    break;
                }
                printf("Available lists:\n");
                for (int i = 0; i < doublyListsNames->size; i++) {
                    printf("%d.%s\n", i + 1, (char*)getPointer(doublyListsNames, i));
                }

                printf("Pick a list: ");
                int listNumber;
                scanf("%d", &listNumber);
                listNumber--;
                if (listNumber >= doublyListsNames->size || listNumber < 0) {
                    printf("List not found, exiting this list menu...\n");
                    break;
                }

                // select current list
                Doubly_List * current_list = (Doubly_List*) getPointer(doublyLists, listNumber);

                printf("Available functions:\n");
                printf("1.Add data\n");
                printf("2.Insert data\n");
                printf("3.Remove data at index\n");
                printf("4.Remove last item\n");
                printf("5.Remove first occurence of data\n");
                printf("6.Change data at index\n");
                printf("7.Search data in list\n");
                printf("8.Print list\n");
                printf("9.Print list reversed\n");
                printf("10.Delete list\n");
                int listCommandNumber;
                printf("Input command number: ");
                scanf("%d", &listCommandNumber);
                switch(listCommandNumber) {
                    case 1: {
                        int data;
                        printf("Input data to add: ");
                        scanf("%d", &data);
                        setPointer(doublyLists, (void*)addToDoubly(current_list, data), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 2: {
                        int data;
                        unsigned int idx;
                        printf("Input data to insert: ");
                        scanf("%d", &data);
                        printf("Input index to insert at: ");
                        scanf("%d", &idx);
                        setPointer(doublyLists, (void*)insertInDoubly(current_list, data, idx), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 3: {
                        unsigned int idx;
                        printf("Input index from which to remove data: ");
                        scanf("%u", &idx);
                        setPointer(doublyLists, (void*)removeIndexFromDoubly(current_list, idx), listNumber);
                        printf("Data removed!\n");
                        break;
                    }
                    case 4: {
                        setPointer(doublyLists, (void*)removeLastFromDoubly(current_list), listNumber);
                        break;
                    }
                    case 5: {
                        int data;
                        printf("Input data to search for: ");
                        scanf("%d", &data);
                        setPointer(doublyLists, (void*)removeDataFromDoubly(current_list, data), listNumber);
                        break;
                    }
                    case 6: {
                        int data;
                        unsigned int idx;
                        printf("Input new data: ");
                        scanf("%d", &data);
                        printf("Input index to change data at: ");
                        scanf("%d", &idx);
                        setDataFromDoubly(current_list, data, idx);
                        break;
                    }
                    case 7: {
                        int data;
                        printf("Input data to search for: ");
                        scanf("%d", &data);
                        unsigned int idx = searchDoubly(current_list, data);
                        if (idx == -1) {
                            printf("Data not found...\n");
                        } else printf("Data found at index %d\n", idx);
                        break;
                    }
                    case 8: {
                        printDoublyList(current_list);
                        break;
                    }
                    case 9: {
                        printDoublyListReversed(current_list);
                        break;
                    }
                    case 10: {
                        setPointer(doublyLists, deleteDoublyList(current_list), listNumber);
                        removeIndexFromPointerList(doublyLists, listNumber);
                        removeIndexFromPointerList(doublyListsNames, listNumber);
                        break;
                    }
                    default: {
                        printf("Input command not found.\n");
                        break;
                    }
                }

                break;
            }
            //
            //
            // ORDERED LISTS
            //
            //
            case 4: {
                if (orderedLists == NULL) {
                    printf("List array not initialized...\n");
                    break;
                }
                printf("Available lists:\n");
                for (int i = 0; i < orderedListsNames->size; i++) {
                    printf("%d.%s\n", i + 1, (char*)getPointer(orderedListsNames, i));
                }

                printf("Pick a list: ");
                int listNumber;
                scanf("%d", &listNumber);
                listNumber--;
                if (listNumber >= orderedListsNames->size || listNumber < 0) {
                    printf("List not found, exiting this list menu...\n");
                    break;
                }

                // select current list
                Ordered_List * current_list = (Ordered_List*) getPointer(orderedLists, listNumber);

                printf("Available functions:\n");
                printf("1.Add data\n");
                printf("2.Remove data at index\n");
                printf("3.Remove last item\n");
                printf("4.Change data at index\n");
                printf("5.Search data in list\n");
                printf("6.Print list\n");
                printf("7.Print list reversed\n");
                printf("8.Delete list\n");
                int listCommandNumber;
                printf("Input command number: ");
                scanf("%d", &listCommandNumber);
                switch(listCommandNumber) {
                    case 1: {
                        int data;
                        printf("Input data to add: ");
                        scanf("%d", &data);
                        setPointer(orderedLists, (void*)addToOrdered(current_list, data), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 2: {
                        unsigned int idx;
                        printf("Input index from which to remove data: ");
                        scanf("%u", &idx);
                        setPointer(orderedLists, (void*)removeIndexFromOrdered(current_list, idx), listNumber);
                        printf("Data removed!\n");
                        break;
                    }
                    case 3: {
                        setPointer(orderedLists, (void*)removeLastFromOrdered(current_list), listNumber);
                        break;
                    }
                    case 4: {
                        int data;
                        unsigned int idx;
                        printf("Input new data: ");
                        scanf("%d", &data);
                        printf("Input index to change data at: ");
                        scanf("%d", &idx);
                        setDataFromOrdered(current_list, data, idx);
                        break;
                    }
                    case 5: {
                        int data;
                        printf("Input data to search for: ");
                        scanf("%d", &data);
                        unsigned int idx = searchOrdered(current_list, data);
                        if (idx == -1) {
                            printf("Data not found...\n");
                        } else printf("Data found at index %d\n", idx);
                        break;
                    }
                    case 6: {
                        printOrderedList(current_list);
                        break;
                    }
                    case 7: {
                        printOrderedListReversed(current_list);
                        break;
                    }
                    case 8: {
                        setPointer(orderedLists, deleteOrderedList(current_list), listNumber);
                        removeIndexFromPointerList(orderedLists, listNumber);
                        removeIndexFromPointerList(orderedListsNames, listNumber);
                        break;
                    }
                    default: {
                        printf("Input command not found.\n");
                        break;
                    }
                }

                break;
            }
            //
            //
            // QUEUES
            //
            //
            case 5: {
                if (queues == NULL) {
                    printf("Queues array not initialized...\n");
                    break;
                }
                printf("Available queues:\n");
                for (int i = 0; i < queuesNames->size; i++) {
                    printf("%d.%s\n", i + 1, (char*)getPointer(queuesNames, i));
                }

                printf("Pick a list: ");
                int listNumber;
                scanf("%d", &listNumber);
                listNumber--;
                if (listNumber >= queuesNames->size || listNumber < 0) {
                    printf("List not found, exiting this list menu...\n");
                    break;
                }

                // select current list
                Queue * current_list = (Queue*) getPointer(queues, listNumber);

                printf("Available functions:\n");
                printf("1.Push data\n");
                printf("2.Pop data\n");
                printf("3.Print queue\n");
                printf("4.Delete queue\n");
                int listCommandNumber;
                printf("Input command number: ");
                scanf("%d", &listCommandNumber);
                switch(listCommandNumber) {
                    case 1: {
                        int data;
                        printf("Input data to add: ");
                        scanf("%d", &data);
                        setPointer(queues, (void*)pushInQueue(current_list, data), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 2: {
                        setPointer(queues, (void*)popFromQueue(current_list), listNumber);
                        break;
                    }
                    case 3: {
                        printQueue(current_list);
                        break;
                    }
                    case 4: {
                        setPointer(queues, deleteQueue(current_list), listNumber);
                        removeIndexFromPointerList(queues, listNumber);
                        removeIndexFromPointerList(queuesNames, listNumber);
                        break;
                    }
                    default: {
                        printf("Input command not found.\n");
                        break;
                    }
                }

                break;
            }
            //
            //
            // STACKS
            //
            //
            case 6: {
                if (stacks == NULL) {
                    printf("Stacks array not initialized...\n");
                    break;
                }
                printf("Available stacks:\n");
                for (int i = 0; i < stacksNames->size; i++) {
                    printf("%d.%s\n", i + 1, (char*)getPointer(stacksNames, i));
                }

                printf("Pick a list: ");
                int listNumber;
                scanf("%d", &listNumber);
                listNumber--;
                if (listNumber >= stacksNames->size || listNumber < 0) {
                    printf("List not found, exiting this list menu...\n");
                    break;
                }

                // select current list
                Stack * current_list = (Stack*) getPointer(stacks, listNumber);

                printf("Available functions:\n");
                printf("1.Push data\n");
                printf("2.Pop data\n");
                printf("3.Print queue\n");
                printf("4.Delete queue\n");
                int listCommandNumber;
                printf("Input command number: ");
                scanf("%d", &listCommandNumber);
                switch(listCommandNumber) {
                    case 1: {
                        int data;
                        printf("Input data to add: ");
                        scanf("%d", &data);
                        setPointer(stacks, (void*)pushInStack(current_list, data), listNumber);
                        printf("Data added!\n");
                        break;
                    }
                    case 2: {
                        setPointer(stacks, (void*)popFromStack(current_list), listNumber);
                        break;
                    }
                    case 3: {
                        printStack(current_list);
                        break;
                    }
                    case 4: {
                        setPointer(stacks, deleteStack(current_list), listNumber);
                        removeIndexFromPointerList(stacks, listNumber);
                        removeIndexFromPointerList(stacksNames, listNumber);
                        break;
                    }
                    default: {
                        printf("Input command not found.\n");
                        break;
                    }
                }

                break;
            }
            case 7: {
                return;
            }
            default: {
                while (1) {
                    printf("Input command not found, do you want to retry? [y/n] ");
                    char ch;
                    scanf("%c", &ch);
                    if (ch == 'n') {
                        return; // return from function
                    } else if (ch == 'y') {
                        break; // break from while
                    } else {
                        printf("Please answer with lowercase y or n;\n");
                    }
                }
                break;
            }
        }

        printf("-----------------------\n");
    }
}

void printListsDisplay() {
    printf("Mixed lists: ");
    if (mixedLists != NULL) {
        for (int i = 0; i < mixedListsNames->size; i++) {
            printf("%s", (char*)getPointer(mixedListsNames, i));
            if (i < mixedListsNames->size - 1) printf(", ");
        }
    }
    printf("\n");
    printf("Forward lists: ");
    if (forwardLists != NULL) {
        for (int i = 0; i < forwardListsNames->size; i++) {
            printf("%s", (char*)getPointer(forwardListsNames, i));
            if (i < forwardListsNames->size - 1) printf(", ");
        }
    }
    printf("\n");
    printf("Doubly lists: ");
    if (doublyLists != NULL) {
        for (int i = 0; i < doublyListsNames->size; i++) {
            printf("%s", (char*)getPointer(doublyListsNames, i));
            if (i < doublyListsNames->size - 1) printf(", ");
        }
    }
    printf("\n");
    printf("Ordered lists: ");
    if (orderedLists != NULL) {
        for (int i = 0; i < orderedListsNames->size; i++) {
            printf("%s", (char*)getPointer(orderedListsNames, i));
            if (i < orderedListsNames->size - 1) printf(", ");
        }
    }
    printf("\n");
    printf("Queues: ");
    if (queues != NULL) {
        for (int i = 0; i < queuesNames->size; i++) {
            printf("%s", (char*)getPointer(queuesNames, i));
            if (i < queuesNames->size - 1) printf(", ");
        }
    }
    printf("\n");
    printf("Stacks: ");
    if (stacks != NULL) {
        for (int i = 0; i < stacksNames->size; i++) {
            printf("%s", (char*)getPointer(stacksNames, i));
            if (i < stacksNames->size - 1) printf(", ");
        }
    }
    printf("\n\n");

}