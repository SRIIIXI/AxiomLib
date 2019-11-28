#include "Stack.h"
#include "Node.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define printLine printf("\n")

/*
void listPrintForward(List* lptr);
void listPrintReverse(List* lptr);
void listRandomAccess(List* lptr, size_t index);
*/

int main(int argc, char *argv[])
{
	/*
    List* list = NULL;

    list = list_allocate(list);

	list_add_to_tail(list, "One", strlen("One")+1);
	list_add_to_tail(list, "Two", strlen("Two")+1);
	list_add_to_tail(list, "Three", strlen("Three")+1);
	list_add_to_tail(list, "Four", strlen("Four")+1);
	list_add_to_tail(list, "Five", strlen("Five")+1);

    listPrintForward(list);

    printLine;

    listPrintReverse(list);

    printLine;

    listRandomAccess(list, 3);

    printLine;

    printf("Remove first\n");
	list_remove_from_head(list);

    printLine;

    listPrintForward(list);

    printLine;

    listPrintReverse(list);

    printLine;

    printf("Remove last\n");
	list_remove_from_tail(list);

    printLine;

    listPrintForward(list);

    printLine;

    listPrintReverse(list);
	*/

    return 0;
}

/*
void listPrintForward(List* lptr)
{
    printf("Forward traversal\n");
    Node* ptr = NULL;

    ptr = list_get_first(lptr);

    while(1)
    {
        if(ptr == NULL)
        {
            break;
        }

        printf("%s\n", (char*)ptr->Data);
        ptr = list_get_next(lptr);
    }
}

void listPrintReverse(List* lptr)
{
    printf("Reverse traversal\n");
    Node* ptr = NULL;

    ptr = list_get_last(lptr);

    while(1)
    {
        if(ptr == NULL)
        {
            break;
        }

        printf("%s\n", (char*)ptr->Data);
        ptr = list_get_previous(lptr);
    }
}

void listRandomAccess(List* lptr, size_t index)
{
    printf("Random access, index %zd\n", index);

    Node* ptr = list_get_at(lptr, 2);
    printf("%s\n", (char*)ptr->Data);
}
*/