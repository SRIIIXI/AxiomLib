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

#include <string.h>
#include <memory.h>
#include <stdlib.h>

List * list_allocate(List* lptr)
{
    lptr = (List*)calloc(1, sizeof(List));
    return lptr;
}

void list_clear(List* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
}

Node* list_add_to_head(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        lptr = list_allocate(lptr);
    }

    Node* ptr = node_allocate(data, sz);

    if(lptr->Count == 0)
    {
        lptr->IteratorPosition = lptr->Head = lptr->Tail = ptr;
    }
    else
    {
        lptr->Head->Previous = ptr;
        ptr->Next = lptr->Head;
        lptr->Head = ptr;
    }

    lptr->Count++;

    return ptr;
}

Node* list_add_to_tail(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        lptr = list_allocate(lptr);
    }

    Node* ptr = node_allocate(data, sz);

    if(lptr->Count == 0)
    {
        lptr->IteratorPosition = lptr->Head = lptr->Tail = ptr;
    }
    else
    {
        lptr->Tail->Next = ptr;
        ptr->Previous = lptr->Tail;
        lptr->Tail = ptr;
    }

    lptr->Count++;

    return ptr;
}

Node* list_insert(List* lptr, void* data, size_t sz, int pos)
{
	if (lptr == NULL)
	{
		if (pos == 0)
		{
			lptr = list_allocate(lptr);
		}

		if (pos > 0)
		{
			return NULL;
		}
	}
	else
	{
		if (pos > lptr->Count || pos < 0)
		{
			return NULL;
		}
	}

    if(pos == 0)
    {
        return list_add_to_head(lptr, data, sz);
    }

    int idx = 1;

    Node* ptr = NULL;	
	
	if (lptr != NULL)
	{
		if (pos == lptr->Count)
		{
			return list_add_to_tail(lptr, data, sz);
		}

		for(Node* curptr = lptr->Head ; curptr->Next != NULL; curptr = curptr->Next, idx++)
		{
			if(pos == idx)
			{
				ptr = node_allocate(data, sz);

				Node* prev = curptr->Previous;
				Node* next = curptr->Next;

				prev->Next = ptr;
				ptr->Previous = prev;

				next->Previous = ptr;
				ptr->Next = next;

				lptr->Count++;
				break;
			}

			idx++;
		}	
	}

    return ptr;
}

void list_remove_from_head(List* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    Node* oldhead = lptr->Head;
    lptr->Head = lptr->Head->Next;
    lptr->Head->Previous = NULL;
    node_free(oldhead);
    lptr->Count--;
}

void list_remove_from_tail(List* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    Node* oldtail = lptr->Tail;
    lptr->Tail = oldtail->Previous;
    lptr->Tail->Next = NULL;
    node_free(oldtail);
    lptr->Count--;
}

void list_remove(List* lptr, const Node* node)
{
    if(lptr == NULL || node == NULL)
    {
        return;
    }

    for(Node* curptr = lptr->Head ; curptr->Next != NULL; curptr = curptr->Next)
    {
        if(node == curptr)
        {
            if(curptr->Next == NULL)
            {
				list_remove_from_tail(lptr);
            }

            if(curptr->Previous == NULL)
            {
				list_remove_from_head(lptr);
            }

            Node* prev = curptr->Previous;
            Node* next = curptr->Next;

			if (prev != NULL)
			{
				prev->Next = next;
			}

            next->Previous = prev;

            node_free(curptr);

            lptr->Count--;
            break;
        }
    }
}

void list_remove_at(List* lptr, int pos)
{
    if(lptr == NULL || pos < 0)
    {
        return;
    }

    if(pos > lptr->Count -1)
    {
        return;
    }

    if(pos == lptr->Count -1)
    {
		list_remove_from_tail(lptr);
    }

    if(pos == 0)
    {
		list_remove_from_head(lptr);
    }

    int idx = 1;
    for(Node* curptr = lptr->Head ; curptr->Next != NULL; curptr = curptr->Next, idx++)
    {
        if(idx == pos)
        {
            Node* prev = curptr->Previous;
            Node* next = curptr->Next;

            prev->Next = next;
            next->Previous = prev;

            node_free(curptr);

            lptr->Count--;
            break;
        }
    }
}

void list_remove_value(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return;
    }

    Node* ptr = NULL;

    Node* node = node_allocate(data, sz);

    ptr = list_get_first(lptr);

    int idx = 0;

    while(true)
    {
        if(ptr == NULL)
        {
            break;
        }

        if(node_is_equal(ptr, node))
        {
            if(idx == lptr->Count - 1)
            {
				list_remove_from_tail(lptr);
                break;
            }

            if(idx == 0)
            {
				list_remove_from_head(lptr);
                break;
            }

            Node* prev = ptr->Previous;
            Node* next = ptr->Next;

            prev->Next = next;
            next->Previous = prev;

            node_free(ptr);
            lptr->Count--;
            break;
        }

        ptr = list_get_next(lptr);
        idx++;
    }

    node_free(node);
    return;
}

size_t list_item_count(List* lptr)
{
    if(lptr != NULL)
    {
        return lptr->Count;
    }

    return -1;
}

size_t list_index_of(List *lptr, const Node* node)
{
    if(lptr == NULL)
    {
        return -1;
    }

    Node* ptr = NULL;

    ptr = list_get_first(lptr);

	size_t idx = 0;

    if(ptr == node)
    {
        return idx;
    }

    while(true)
    {
        if(ptr == NULL)
        {
            break;
        }

        ptr = list_get_next(lptr);
        idx++;

        if(ptr == node)
        {
            return idx;
        }
    }

    return -1;
}

size_t list_index_of_value(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return -1;
    }

    Node* ptr = NULL;

    Node* node = node_allocate(data, sz);

    ptr = list_get_first(lptr);

	size_t idx = 0;

    if(node_is_equal(ptr, node))
    {
        node_free(node);
        return idx;
    }

    while(true)
    {
        if(ptr == NULL)
        {
            break;
        }

        ptr = list_get_next(lptr);
        idx++;

        if(node_is_equal(ptr, node))
        {
			node_free(node);
            return idx;
        }
    }

	node_free(node);
    return -1;
}

Node* list_get_at(List* lptr, int atpos)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(atpos > (lptr->Count - 1) || atpos < 0)
    {
        return NULL;
    }

    Node* ptr = NULL;

    ptr = list_get_first(lptr);

    if(atpos > 0)
    {
        for(int idx = 0; idx < atpos; idx++)
        {
            ptr = list_get_next(lptr);
        }
    }

    return ptr;
}

Node* list_get_first(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->Head;
    return lptr->IteratorPosition;
}

Node* list_get_next(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->IteratorPosition->Next;

    return lptr->IteratorPosition;
}

Node* list_get_last(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->Tail;
    return lptr->IteratorPosition;
}

Node* list_get_previous(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->IteratorPosition->Previous;

    return lptr->IteratorPosition;
}

List * list_sort(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    return NULL;
}

List* list_merge(List* lptrFirst, List* lptrSecond)
{
    if(lptrFirst == NULL)
    {
        return lptrSecond;
    }

    if(lptrSecond == NULL)
    {
        return lptrFirst;
    }

    return NULL;
}

List* list_join(List* lptrFirst, List* lptrSecond)
{
    if(lptrFirst == NULL)
    {
        return lptrSecond;
    }

    if(lptrSecond == NULL)
    {
        return lptrFirst;
    }

    return NULL;
}
