#ifndef _TREE_NODE_C
#define _TREE_NODE_C

#include <stddef.h>
#include <stdbool.h>

typedef struct TreeNode
{
    void* Data;
    size_t Size;
    struct TreeNode* Left;
    struct TreeNode* Right;
}TreeNode;

extern TreeNode* treenode_allocate(void* data, size_t sz);

extern void treenode_free(TreeNode* ptr);
extern void treenode_copy(TreeNode* dest, TreeNode* orig);

extern bool treenode_is_equal(TreeNode* first, TreeNode* second);
extern bool treenode_is_greater(TreeNode* first, TreeNode* second);
extern bool treenode_is_less(TreeNode* first, TreeNode* second);

#endif
