#include "List.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

List *listAllocate(List* lptr)
{
    lptr = (List*)calloc(1, sizeof(List));
    return lptr;
}

void listClear(List* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
}

Node* listAddToHead(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        lptr = listAllocate(lptr);
    }

    Node* ptr = nodeAllocate(data, sz);

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

Node* listAddToTail(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        lptr = listAllocate(lptr);
    }

    Node* ptr = nodeAllocate(data, sz);

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

Node* listInsert(List* lptr, void* data, size_t sz, int pos)
{
	if (lptr == NULL)
	{
		if (pos == 0)
		{
			lptr = listAllocate(lptr);
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
        return listAddToHead(lptr, data, sz);
    }

    int idx = 1;

    Node* ptr = NULL;	
	
	if (lptr != NULL)
	{
		if (pos == lptr->Count)
		{
			return listAddToTail(lptr, data, sz);
		}

		for(Node* curptr = lptr->Head ; curptr->Next != NULL; curptr = curptr->Next, idx++)
		{
			if(pos == idx)
			{
				ptr = nodeAllocate(data, sz);

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

void listRemoveFromHead(List* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    Node* oldhead = lptr->Head;
    lptr->Head = lptr->Head->Next;
    lptr->Head->Previous = NULL;
    nodeFree(oldhead);
    lptr->Count--;
}

void listRemoveFromTail(List* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    Node* oldtail = lptr->Tail;
    lptr->Tail = oldtail->Previous;
    lptr->Tail->Next = NULL;
    nodeFree(oldtail);
    lptr->Count--;
}

void listRemove(List* lptr, const Node* node)
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
                listRemoveFromTail(lptr);
            }

            if(curptr->Previous == NULL)
            {
                listRemoveFromHead(lptr);
            }

            Node* prev = curptr->Previous;
            Node* next = curptr->Next;

			if (prev != NULL)
			{
				prev->Next = next;
			}

            next->Previous = prev;

            nodeFree(curptr);

            lptr->Count--;
            break;
        }
    }
}

void listRemoveAt(List* lptr, int pos)
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
        listRemoveFromTail(lptr);
    }

    if(pos == 0)
    {
        listRemoveFromHead(lptr);
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

            nodeFree(curptr);

            lptr->Count--;
            break;
        }
    }
}

void listRemoveValue(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return;
    }

    Node* ptr = NULL;

    Node* node = nodeAllocate(data, sz);

    ptr = listGetFirst(lptr);

    int idx = 0;

    while(1)
    {
        if(ptr == NULL)
        {
            break;
        }

        if(nodeAreEqual(ptr, node))
        {
            if(idx == lptr->Count - 1)
            {
                listRemoveFromTail(lptr);
                break;
            }

            if(idx == 0)
            {
                listRemoveFromHead(lptr);
                break;
            }

            Node* prev = ptr->Previous;
            Node* next = ptr->Next;

            prev->Next = next;
            next->Previous = prev;

            nodeFree(ptr);
            lptr->Count--;
            break;
        }

        ptr = listGetNext(lptr);
        idx++;
    }

    nodeFree(node);
    return;
}

size_t listItemCount(List* lptr)
{
    if(lptr != NULL)
    {
        return lptr->Count;
    }

    return -1;
}

size_t listIndexOf(List *lptr, const Node* node)
{
    if(lptr == NULL)
    {
        return -1;
    }

    Node* ptr = NULL;

    ptr = listGetFirst(lptr);

	size_t idx = 0;

    if(ptr == node)
    {
        return idx;
    }

    while(1)
    {
        if(ptr == NULL)
        {
            break;
        }

        ptr = listGetNext(lptr);
        idx++;

        if(ptr == node)
        {
            return idx;
        }
    }

    return -1;
}

size_t listIndexOfValue(List* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return -1;
    }

    Node* ptr = NULL;

    Node* node = nodeAllocate(data, sz);

    ptr = listGetFirst(lptr);

	size_t idx = 0;

    if(nodeAreEqual(ptr, node))
    {
        nodeFree(node);
        return idx;
    }

    while(1)
    {
        if(ptr == NULL)
        {
            break;
        }

        ptr = listGetNext(lptr);
        idx++;

        if(nodeAreEqual(ptr, node))
        {
            nodeFree(node);
            return idx;
        }
    }

    nodeFree(node);
    return -1;
}

Node* listGetAt(List* lptr, int atpos)
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

    ptr = listGetFirst(lptr);

    if(atpos > 0)
    {
        for(int idx = 0; idx < atpos; idx++)
        {
            ptr = listGetNext(lptr);
        }
    }

    return ptr;
}

Node* listGetFirst(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->Head;
    return lptr->IteratorPosition;
}

Node* listGetNext(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->IteratorPosition->Next;

    return lptr->IteratorPosition;
}

Node* listGetLast(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->Tail;
    return lptr->IteratorPosition;
}

Node* listGetPrevious(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->IteratorPosition = lptr->IteratorPosition->Previous;

    return lptr->IteratorPosition;
}

List *listSort(List* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    return NULL;
}

List* listMerge(List* lptrFirst, List* lptrSecond)
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

List* listJoin(List* lptrFirst, List* lptrSecond)
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
