#ifndef _NODE
#define _NODE

namespace CoreLib
{
	template <typename V>
	class Node
	{
	public:
		Node();
		Node(V* data);
		~Node();
		bool operator!=(const Node& other);
		bool operator==(const Node& other);
		bool operator>(const Node& other);
		bool operator<(const Node& other);
		V* Data;
		Node* Previous;
		Node* Next;
	};

	template <typename V>
	Node<V>::Node()
	{
		Next = nullptr;
		Previous = nullptr;
	}

	template <typename V>
	Node<V>::Node(V* data)
	{
		Previous = nullptr;
		Next = nullptr;

		Data = data;
	}

	template <typename V>
	Node<V>::~Node()
	{
		if (Data != nullptr)
		{
			delete Data;
		}
	}

	template <typename V>
	bool Node<V>::operator!=(const Node& other)
	{
		return(*Data != *other.Data);
	}

	template <typename V>
	bool Node<V>::operator==(const Node& other)
	{
		return(*Data == *other.Data);
	}

	template <typename V>
	bool Node<V>::operator>(const Node& other)
	{
		return (*Data > *other.Data);
	}

	template <typename V>
	bool Node<V>::operator<(const Node& other)
	{
		return (*Data < *other.Data);
	}
}

#endif
