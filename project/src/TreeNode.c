/*
BSD 2-Clause License

Copyright (c) 2017, SRIIIXI (subratoroy@hotmail.com)
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

bool treenode_is_equal(TreeNode* first, TreeNode* second)
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

