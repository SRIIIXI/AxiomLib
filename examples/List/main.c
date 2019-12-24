/*
BSD 2-Clause License

Copyright (c) 2017, Subrato Roy (subratoroy@hotmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "List.h"
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


    return 0;
}

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

        printf("%s\n", (char*)ptr->NodeData->Data);
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

        printf("%s\n", (char*)ptr->NodeData->Data);
        ptr = list_get_previous(lptr);
    }
}

void listRandomAccess(List* lptr, size_t index)
{
    printf("Random access, index %zd\n", index);

    Node* ptr = list_get_at(lptr, 2);
    printf("%s\n", (char*)ptr->NodeData->Data);
}
