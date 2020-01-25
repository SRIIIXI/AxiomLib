#ifndef _STACK
#define _STACK

#include "List.hpp"

namespace CoreLibrary
{
	template <class T>
	class Stack : protected List<T>
	{
	public:
		Stack();
		virtual ~Stack();

		void push(const T data);
		T* pop();

		int count();
		void clear();
	};

	template <class T>
	Stack<T>::Stack()
	{
	}

	template <class T>
	Stack<T>::~Stack()
	{
		List<T>::clear();
	}

	template <class T>
	void Stack<T>::push(const T data)
	{
		insert(data, count() + 1);
	}

	template <class T>
	T* Stack<T>::pop()
	{
		if (count() < 1)
		{
			return nullptr;
		}

		T* data = this->getLast();
		removeAt(count());
		return data;
	}

	template <class T>
	int Stack<T>::count()
	{
		return List<T>::count();
	}

	template <class T>
	void Stack<T>::clear()
	{
		List<T>::clear();
	}
}
#endif
