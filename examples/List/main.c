#include "KeyValue.h"
#include "List.h"
#include "Map.h"
#include "Node.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define printLine printf("\n")
void listPrintForward(List* lptr);
void listPrintReverse(List* lptr);
void listRandomAccess(List* lptr, size_t index);

int main(int argc, char *argv[])
{
    int x = atoi("-123");

    List* list = NULL;

    list = listAllocate(list);

    listAddToTail(list, "One", strlen("One")+1);
    listAddToTail(list, "Two", strlen("Two")+1);
    listAddToTail(list, "Three", strlen("Three")+1);
    listAddToTail(list, "Four", strlen("Four")+1);
    listAddToTail(list, "Five", strlen("Five")+1);

    listPrintForward(list);

    printLine;

    listPrintReverse(list);

    printLine;

    listRandomAccess(list, 3);

    printLine;

    printf("Remove first\n");
    listRemoveFromHead(list);

    printLine;

    listPrintForward(list);

    printLine;

    listPrintReverse(list);

    printLine;

    printf("Remove last\n");
    listRemoveFromTail(list);

    printLine;

    listPrintForward(list);

    printLine;

    listPrintReverse(list);


    return 0;
}

void listPrintForward(List* lptr)
{
    printf("Forward traversal\n");
    Node* ptr = NULL;

    ptr = listGetFirst(lptr);

    while(1)
    {
        if(ptr == NULL)
        {
            break;
        }

        printf("%s\n", (char*)ptr->Data);
        ptr = listGetNext(lptr);
    }
}

void listPrintReverse(List* lptr)
{
    printf("Reverse traversal\n");
    Node* ptr = NULL;

    ptr = listGetLast(lptr);

    while(1)
    {
        if(ptr == NULL)
        {
            break;
        }

        printf("%s\n", (char*)ptr->Data);
        ptr = listGetPrevious(lptr);
    }
}

void listRandomAccess(List* lptr, size_t index)
{
    printf("Random access, index %zd\n", index);

    Node* ptr = listGetAt(lptr, 2);
    printf("%s\n", (char*)ptr->Data);
}
