#ifndef _TREE_NODE
#define _TREE_NODE

namespace CoreLib
{
	template <class V>
	class TreeNode
	{
	public:
		TreeNode();
		TreeNode(const V data);
		~TreeNode();
		bool operator!=(const TreeNode& other);
		bool operator==(const TreeNode& other);
		bool operator>(const TreeNode& other);
		bool operator<(const TreeNode& other);
		V Data;
		TreeNode* Left;
		TreeNode* Right;
	};

	template <class V>
	TreeNode<V>::TreeNode()
	{
		Next = nullptr;
		Previous = nullptr;
	}

	template <class V>
	TreeNode<V>::TreeNode(const V data)
	{
		Previous = nullptr;
		Next = nullptr;

		Data = data;
	}

	template <typename V>
	TreeNode<V>::~TreeNode()
	{
	}

	template <typename V>
	bool TreeNode<V>::operator!=(const Node& other)
	{
		return(Data != other.Data);
	}

	template <typename V>
	bool TreeNode<V>::operator==(const Node& other)
	{
		return(Data == other.Data);
	}

	template <typename V>
	bool TreeNode<V>::operator>(const Node& other)
	{
		return (Data > other.Data);
	}

	template <typename V>
	bool TreeNode<V>::operator<(const Node& other)
	{
		return (Data < other.Data);
	}
}
#endif
