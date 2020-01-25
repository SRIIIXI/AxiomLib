#ifndef _LIST
#define _LIST

#include <cstddef>
#include "Node.hpp"

namespace CoreLib
{
	template <typename T>
	class List
	{
	public:
		List();
		virtual ~List();

		void insert(const T data, size_t atpos);
		void insert(const T data);
		void append(const T data);

		void insert(const T* data, size_t atpos);
		void insert(const T* data);
		void append(const T* data);

		void append(const List<T> &list);
		void merge(const List<T> &list);

		T* removeAt(size_t atpos);
		T* remove(const T data);
		T* remove(const T* data);
		T* truncate();

		size_t count();
		void sort();
		size_t indexOf(const T data);
		size_t indexOf(const T* data);
		void clear();

		T* getAt(size_t atpos);
		void setAt(size_t atpos, T data);
		void setAt(size_t atpos, T* data);
		T* getFirst();
		T* getLast();
		T* getNext();
		T* getPrevious();

		T operator[](size_t index);

	private:
		void copyNode(T* dest, const T* orig);
		size_t search(const T* data, Node<T>* ptr);
		Node<T>* _First;
		Node<T>* _Last;
		size_t _Count;
		Node<T>* _IteratorPosition;
		bool _IsSorted;
	};

	template <typename T>
	List<T>::List()
	{
		_First = nullptr;
		_Last = nullptr;
		_Count = 0;
		_IteratorPosition = nullptr;
		_IsSorted = false;
	}

	template <typename T>
	List<T>::~List()
	{
		clear();
	}

	template <typename T>
	void List<T>::insert(const T* data, size_t atpos)
	{
		if (atpos > _Count || atpos < 0)
		{
			return;
		}

		Node<T>* newnode = new Node<T>((T*)data);

		if (atpos == 0)
		{
			_First = newnode;
			_Last = newnode;
			_Last->Next = nullptr;
			_First->Previous = nullptr;
		}
		else
		{
			if (atpos >= _Count)
			{
				_Last->Next = newnode;
				newnode->Previous = _Last;
				newnode->Next = nullptr;
				_Last = newnode;
			}
			else
			{
				int ctr = 0;
				Node<T>* target = nullptr;
				Node<T>* targetsnext = nullptr;

				for (target = _First, ctr = 0; ctr < atpos; target = target->Next, ctr++) {}

				targetsnext = target->Next;
				newnode->Previous = target;
				newnode->Next = targetsnext;
				target->Next = newnode;

				if (targetsnext != nullptr)
				{
					targetsnext->Previous = newnode;
				}
			}
		}
		_Count++;

		_IsSorted = false;
	}

	template <typename T>
	void List<T>::insert(const T data, size_t atpos)
	{
		T* tempdata = new T();
		copyNode(tempdata, &data);
		insert(tempdata, atpos);
	}

	template <typename T>
	void List<T>::insert(const T* data)
	{
		Node<T>* newnode = new Node<T>((T*)data);

		// Special case for the first node
		if (_First == nullptr)
		{
			_First = newnode;
			_Last = newnode;
			_Last->Next = nullptr;
			_First->Previous = nullptr;
			_Count++;
			return;
		}

		if (_IsSorted)
		{
			// Locate the node before the point of insertion
			Node<T>* target = _First;
			Node<T>* targetsnext = nullptr;

			while (target->Next != nullptr)
			{
				if (target->Next->Data > data)
				{
					break;
				}

				target = target->Next;
			}

			targetsnext = target->Next;
			newnode->Previous = target;
			newnode->Next = targetsnext;
			target->Next = newnode;

			if (targetsnext != nullptr)
			{
				targetsnext->Previous = newnode;
			}
		}
		else
		{
			_Last->Next = newnode;
			newnode->Previous = _Last;
			newnode->Next = nullptr;
			_Last = newnode;
		}
	}

	template <typename T>
	void List<T>::insert(const T data)
	{
		T* tempdata = new T();
		copyNode(tempdata, &data);
		insert(tempdata);
	}

	template <typename T>
	void List<T>::append(const T* data)
	{
		T* tempdata = new T();
		copyNode(tempdata, data);
		insert(tempdata, _Count);
	}

	template <typename T>
	void List<T>::append(const T data)
	{
		insert(data, _Count);
	}

	template <typename T>
	void List<T>::append(const List<T> &list)
	{
		T* tempdata = ((List<T>)list).getFirst();

		while (tempdata != nullptr)
		{
			append(tempdata);
			tempdata = ((List<T>)list).getNext();
		}
	}

	template <typename T>
	void List<T>::merge(const List<T> &list)
	{
	}

	template <typename T>
	T* List<T>::removeAt(size_t atpos)
	{
		T* ret = nullptr;

		if (atpos > _Count - 1 || atpos < 0)
		{
			return ret;
		}

		int ctr = 0;

		if (atpos == 0)
		{
			Node<T>* temp = _First;
			_First->Next->Previous = nullptr;
			_First = _First->Next;
			ret = temp->Data;
			delete temp;

		}
		else
		{
			if (atpos >= _Count - 1)
			{
				Node<T>* ndptr = _Last;
				_Last->Previous->Next = nullptr;
				_Last = _Last->Previous;
				ret = ndptr->Data;
				delete ndptr;

			}
			else
			{
				int ctr = 0;
				Node<T>* target = nullptr;
				Node<T>* targetsnext = nullptr;
				Node<T>* targetsprev = nullptr;

				for (target = _First, ctr = 0; ctr < atpos; target = target->Next, ctr++) {}

				targetsnext = target->Next;
				targetsprev = target->Previous;

				targetsprev->Next = targetsnext;
				targetsnext->Previous = targetsprev;

				ret = target->Data;
				delete target;
			}
		}

		_Count--;

		_IsSorted = false;

		return ret;
	}

	template <typename T>
	T* List<T>::remove(const T data)
	{
		return remove(&data);
	}

	template <typename T>
	T* List<T>::remove(const T* data)
	{
		Node<T> *ptr = nullptr;
		int idx = 0;
		T* ret = nullptr;

		idx = search(data, ptr);

		if (idx < 0)
		{
			return ret;
		}

		Node<T>* target = ptr;
		Node<T>* targetsnext = nullptr;
		Node<T>* targetsprev = nullptr;

		targetsnext = target->Next;
		targetsprev = target->Previous;

		targetsprev->Next = targetsnext;
		targetsnext->Previous = targetsprev;

		ret = target->Data;
		delete target;

		return ret;
	}

	template <typename T>
	T* List<T>::truncate()
	{
		return removeAt(_Count - 1);
	}

	template <typename T>
	size_t List<T>::count()
	{
		return _Count;
	}

	template <typename T>
	void List<T>::sort()
	{
		Node<T> *currentnode;

		int i, j;

		for (i = 0; i < _Count; i++)
		{
			currentnode = _First;

			for (j = 0; j < _Count - 1 - i; j++)
			{
				if (currentnode->Data > currentnode->Next->Data)
				{
					T* temp = currentnode->Data;
					currentnode->Data = currentnode->Next->Data;
					currentnode->Next->Data = temp;
				}
				currentnode = currentnode->Next;
			}
		}

		_IsSorted = true;
	}

	template <typename T>
	void List<T>::clear()
	{
	}

	template <typename T>
	size_t List<T>::indexOf(const T data)
	{
		return indexOf(&data);
	}

	template <typename T>
	size_t List<T>::indexOf(const T* data)
	{
		Node<T> *ptr = nullptr;

		return search(data, ptr);
	}

	template <typename T>
	size_t List<T>::search(const T* data, Node<T> *ptr)
	{
		if (_Count < 1)
		{
			return -1;
		}

		int ctr = 0;
		ptr = _First;

		while (true)
		{
			if (ptr == nullptr)
			{
				break;
			}

			if (memcmp(data, ptr->Data, sizeof(T) == 0))
			{
				return ctr;
			}

			ptr = ptr->Next;

			ctr++;
		}

		return -1;
	}

	template <typename T>
	void List<T>::setAt(size_t atpos, T data)
	{
		setAt(atpos, &data);
	}

	template <typename T>
	void List<T>::setAt(size_t atpos, T* data)
	{
		T* d = getAt(atpos);

		if (d)
		{
			memcpy(d, data, sizeof(T));
		}
	}

	template <typename T>
	T *List<T>::getAt(size_t atpos)
	{
		if (atpos > _Count - 1 || atpos < 0)
		{
			return nullptr;
		}

		int ctr = 0;

		Node<T>* ptr = _First;

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

		return ptr->Data;
	}

	template <typename T>
	T List<T>::operator[](const size_t index)
	{
		if (index < 0 || index >(_Count - 1))
		{
			throw;
		}

		return *getAt(index);
	}

	template <typename T>
	T *List<T>::getFirst()
	{
		_IteratorPosition = _First;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return _IteratorPosition->Data;
	}

	template <typename T>
	T *List<T>::getLast()
	{
		_IteratorPosition = _Last;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return _IteratorPosition->Data;
	}

	template <typename T>
	T* List<T>::getNext()
	{
		_IteratorPosition = _IteratorPosition->Next;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return _IteratorPosition->Data;
	}

	template <typename T>
	T *List<T>::getPrevious()
	{
		_IteratorPosition = _IteratorPosition->Previous;

		if (_IteratorPosition == nullptr)
		{
			return nullptr;
		}

		return _IteratorPosition->Data;
	}

	template <typename T>
	void List<T>::copyNode(T* dest, const T* orig)
	{
		int sz = sizeof(T);

		char* destptr = (char*)dest;
		char* origptr = (char*)orig;

		for (int ctr = 0; ctr < sz; ctr++)
		{
			destptr[ctr] = origptr[ctr];
		}
	}

}

#endif
