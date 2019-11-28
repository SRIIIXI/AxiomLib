#include "TreeNode.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

TreeNode* treenode_allocate(void* data, size_t sz)
{
	TreeNode* nd = (TreeNode*)calloc(1, sizeof(TreeNode));

	if (nd != NULL)
	{
		nd->Data = (char*)calloc(1, sz);
		nd->Size = sz;
		nd->Left = NULL;
		nd->Right = NULL;

		if (nd->Data != NULL)
		{
			memcpy(nd->Data, data, sz);
		}
	}
    return nd;
}

void treenode_free(TreeNode* ptr)
{
    free(ptr->Data);
    free(ptr);
}

void treenode_copy(TreeNode* dest, TreeNode* orig)
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

bool treenode_are_equal(TreeNode* first, TreeNode* second)
{
    if( (first != NULL && first->Data != NULL)
            && (second != NULL && second->Data != NULL) )
    {
        if(first->Size != second->Size)
        {
            return false;
        }

        if(memcmp(first->Data, second->Data, first->Size) == 0)
        {
            return true;
        }
    }

    return false;
}

bool treenode_is_greater(TreeNode* first, TreeNode* second)
{
    if( (first != NULL && first->Data != NULL)
            && (second != NULL && second->Data != NULL) )
    {
        if(first->Size != second->Size)
        {
            return false;
        }

        if(memcmp(first->Data, second->Data, first->Size) > 0)
        {
            return true;
        }
    }

    return false;
}

bool treenode_is_less(TreeNode* first, TreeNode* second)
{
    if( (first != NULL && first->Data != NULL)
            && (second != NULL && second->Data != NULL) )
    {
        if(first->Size != second->Size)
        {
            return false;
        }

        if(memcmp(first->Data, second->Data, first->Size) < 0)
        {
            return true;
        }
    }

    return false;
}

