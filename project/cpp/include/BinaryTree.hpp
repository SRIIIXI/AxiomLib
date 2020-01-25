#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "TreeNode.hpp"

namespace CoreLibrary
{
	template <class T>
	class BinaryTree
	{
	public:
		BinaryTree();
		virtual ~BinaryTree();

		void insert(const T data);
		T* remove(const T data);

		int count();
		int indexOf(const T data);
		void clear();

		T* getAt(int atpos);
		T* getFirst();
		T* getLast();
		T* getNode();
		T* getPrevious();

		T* operator[](const int index);

	private:
		int linearSearch(const T data);
		int binarySearch(const T data);
		TreeNode<T>* _Left;
		TreeNode<T>* _Right;
		TreeNode<T>* _Root;
		int _Count;
		TreeNode<T>* _IteratorPosition;
		bool _IsSorted;
	};

	/*
	template <class T>
	List<T>::List()
	{
		_Left = nullptr;
		_Right = nullptr;
		_Root = nullptr;
		_Count = 0;
		_IteratorPosition = nullptr;
		_IsSorted = false;
	}

	template <class T>
	List<T>::~List()
	{
		clear();
	}

	template <class T>
	void List<T>::insert(const T data, int atpos)
	{
		if(atpos > _Count || atpos < 0)
		{
			return;
		}

		int ctr = 0;

		Node<T>* newnode = new Node<T>(data);

		if (atpos == 0)
		{
			newnode->Next = _Left;
			_Left->Previous = newnode;
			_Left = newnode;
			_Count++;
			return;
		}

		if (atpos >= _Count)
		{
			_Right->Next = newnode;
			newnode->Previous = _Right;
			newnode->Next = nullptr;
			_Right = newnode;
			_Count++;
			return;
		}

		while(true)
		{
			if(prev == nullptr)
			{
				break;
			}

			if(ctr >= atpos - 1)
			{
				break;
			}

			prev = prev->Next;

			ctr++;
		}


		if(prev)
		{
			Node<T>* next = prev->Next;

			prev->Next = newnode;
			newnode->Previous = prev;

			newnode->Next = next;
			next->Previous = newnode;
		}
		else
		{
			_Left = _Right = newnode;
		}

		_Count++;

	}

	template <class T>
	T* List<T>::removeAt(int atpos)
	{
		T* ret = nullptr;

		if(atpos > _Count-1 || atpos < 0)
		{
			return ret;
		}

		int ctr = 0;

		if (atpos == 0)
		{
			Node<T>* temp = _Left;
			_Left->Next->Previous = nullptr;
			_Left = _Left->Next;

			ret = &temp->Data;

			delete temp;
			_Count--;
			return ret;
		}

		if (atpos >= _Count-1)
		{
			Node<T>* ndptr = _Right;

			_Right->Previous->Next = nullptr;
			_Right = _Right->Previous;

			ret = &ndptr->Data;

			delete ndptr;
			_Count--;

			return ret;
		}

		Node<T>* prev = _Left;

		while(true)
		{
			if(prev == nullptr)
			{
				break;
			}

			if(ctr >= atpos-1)
			{
				break;
			}

			prev = prev->Next;

			ctr++;
		}

		if(prev)
		{
			Node<T>* next = prev->Next->Next;

			Node<T>* delnode = prev->Next;

			prev->Next = next;
			next->Previous = prev;

			ret = &delnode->Data;

			delete delnode;

			_Count--;
		}

		return ret;
	}

	template <class T>
	T* List<T>::remove(const T data)
	{
		return removeAt(indexOf(data));
	}

	template <class T>
	void List<T>::append(const T data)
	{
		insert(data, _Count+1);
	}

	template <class T>
	T* List<T>::truncate()
	{
		return removeAt(_Count);
	}

	template <class T>
	int List<T>::count()
	{
		return _Count;
	}

	template <class T>
	void List<T>::sort()
	{
	}

	template <class T>
	void List<T>::clear()
	{
	}

	template <class T>
	int List<T>::indexOf(const T data)
	{
		if(_IsSorted)
		{
			return binarySearch(data);
		}
		else
		{
			return linearSearch(data);
		}
	}

	template <class T>
	int List<T>::linearSearch(const T data)
	{
		if(_Count < 1)
		{
			return -1;
		}

		int ctr = 0;

		Node<T>* ndptr = _Left;

		while(true)
		{
			if(ndptr == nullptr)
			{
				return nullptr;
			}

			if(ndptr->Data == data)
			{
				return ctr;
			}

			ndptr = ndptr->Next;

			ctr++;
		}

		return -1;
	}

	template <class T>
	int List<T>::binarySearch(const T data)
	{
		return -1;
	}

	template <class T>
	T *List<T>::getAt(int atpos)
	{
		if (atpos > _Count - 1 || atpos < 0)
		{
			return nullptr;
		}

		int ctr = 0;

		Node<T>* ptr = _Left;

		while (true)
		{
			if (ptr == nullptr)
			{
				return nullptr;
			}

			if (ctr >= atpos)
			{
				break;
			}

			ptr = ptr->Next;

			ctr++;
		}

		if (ptr == nullptr)
		{
			return nullptr;
		}

		return &ptr->Data;
	}

	template <class T>
	T *List<T>::operator[](const int index)
	{
		if (index < 0 || index >(_Count - 1))
		{
			return nullptr;
		}

		return getAt(index);
	}

	template <class T>
	T *List<T>::getFirst()
	{
		_IteratorPosition = _Left;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return &_IteratorPosition->Data;
	}

	template <class T>
	T *List<T>::getLast()
	{
		_IteratorPosition = _Right;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return &_IteratorPosition->Data;
	}

	template <class T>
	T* List<T>::getNode()
	{
		_IteratorPosition = _IteratorPosition->Next;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return &_IteratorPosition->Data;
	}

	template <class T>
	T *List<T>::getPrevious()
	{
		_IteratorPosition = _IteratorPosition->Previous;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return &_IteratorPosition->Data;
	}
	*/
}
#endif
