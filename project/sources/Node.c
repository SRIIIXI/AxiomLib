#include "Node.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

Node* nodeAllocate(void* data, size_t sz)
{
    Node* nd = (Node*)calloc(1, sizeof(Node));

	if (nd != NULL)
	{
		nd->Data = (char*)calloc(1, sz);
		nd->Size = sz;
		nd->Next = NULL;
		nd->Previous = NULL;

		if (nd->Data != NULL)
		{
			memcpy(nd->Data, data, sz);
		}
	}
    return nd;
}

void nodeFree(Node* ptr)
{
    free(ptr->Data);
    free(ptr);
}

void nodeCopy(Node* dest, Node* orig)
{
    if( (dest != NULL && dest->Data != NULL)
            && (orig != NULL && orig->Data != NULL) )
    {
        free(dest->Data);
        dest->Size = orig->Size;
        dest->Data = (char*)calloc(1, dest->Size);
        memcpy(dest->Data, orig->Data, dest->Size);
    }
}

int nodeAreEqual(Node* first, Node* second)
{
    if( (first != NULL && first->Data != NULL)
            && (second != NULL && second->Data != NULL) )
    {
        if(first->Size != second->Size)
        {
            return 0;
        }

        if(memcmp(first->Data, second->Data, first->Size) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int nodeIsGreater(Node* first, Node* second)
{
    if( (first != NULL && first->Data != NULL)
            && (second != NULL && second->Data != NULL) )
    {
        if(first->Size != second->Size)
        {
            return 0;
        }

        if(memcmp(first->Data, second->Data, first->Size) > 0)
        {
            return 1;
        }
    }

    return 0;
}

int nodeIsLess(Node* first, Node* second)
{
    if( (first != NULL && first->Data != NULL)
            && (second != NULL && second->Data != NULL) )
    {
        if(first->Size != second->Size)
        {
            return 0;
        }

        if(memcmp(first->Data, second->Data, first->Size) < 0)
        {
            return 1;
        }
    }

    return 0;
}

