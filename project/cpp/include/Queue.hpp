#ifndef _QUEUE
#define _QUEUE

#include "List.hpp"

namespace CoreLibrary
{
	template <class T>
	class Queue : protected List<T>
	{
	public:
		Queue();
		virtual ~Queue();

		void enqueue(const T data);
		T* dequeue();

		int count();
		void clear();
	};

	template <class T>
	Queue<T>::Queue()
	{
	}

	template <class T>
	Queue<T>::~Queue()
	{
		List<T>::clear();
	}

	template <class T>
	void Queue<T>::enqueue(const T data)
	{
		insert(data, count() + 1);
	}

	template <class T>
	T* Queue<T>::dequeue()
	{
		if (count() < 1)
		{
			return nullptr;
		}

		T* data = this->getFirst();
		this->remove(0);
		return data;
	}

	template <class T>
	int Queue<T>::count()
	{
		return List<T>::count();
	}

	template <class T>
	void Queue<T>::clear()
	{
		List<T>::clear();
	}
}
#endif
