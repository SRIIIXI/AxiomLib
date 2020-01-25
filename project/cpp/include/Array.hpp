#ifndef _ARRAY
#define _ARRAY

#if defined(_WIN32) || defined(WIN32) || defined (_WIN64) || defined (WIN64)
#include <memory.h>
#else
#include <string.h>
#endif

namespace CoreLibrary
{
	#ifndef ARRAY_RESIZE_FACTOR
	#define ARRAY_RESIZE_FACTOR 8
	#endif

	template <class T>
	class Array
	{
	public:
		Array();
		virtual ~Array();

		void insert(const T data);
		void remove(const T data);

		unsigned long count();
		unsigned long indexOf(const T data);
		void clear();
		void sort();

		T* getAt(unsigned int atpos);
		T* getFirst();
		T* getLast();
		T* getNext();
		T* getPrevious();

		T& operator[](unsigned long index);
	private:
		unsigned long _Count;
		unsigned long _ArraySize;
		T* _Array;
		long _IteratorPosition;
		bool _IsSorted;
	};

	template <class T>
	Array<T>::Array()
	{
		_IsSorted = false;
		_Count = 0;
		_IteratorPosition = 1;
		_ArraySize = ARRAY_RESIZE_FACTOR;
		_Array = new T[_ArraySize * sizeof(T)];
		memset((void*)_Array, 0, _ArraySize * sizeof(T));
	}

	template <class T>
	Array<T>::~Array()
	{
		clear();
	}

	template <class T>
	void Array<T>::insert(const T data)
	{
		T newitem(data);

		//Special case for first entry
		if (_Count == 0)
		{
			_Array[_Count] = newitem;
			_Count++;
			return;
		}

		//Check whether we have reached the end of array already or not
		if (_Count == _ArraySize)
		{
			// Double the array size
			unsigned long newsz = _ArraySize + ARRAY_RESIZE_FACTOR;
			T* temparray = new T[newsz * sizeof(T)];
			memset((void*)temparray, 0, newsz * sizeof(T));
			memcpy((void*)temparray, (void*)_Array, _ArraySize * sizeof(T));
			delete[] _Array;
			_Array = temparray;
			_ArraySize = newsz;
		}

		if (_IsSorted)
		{
			int lowerbound = 0;
			int upperbound = _Count - 1;
			int middle = -1;

			while (lowerbound <= upperbound)
			{
				//Middle element
				middle = (lowerbound + upperbound) / 2;

				//If the search key on the left half
				if (data < _Array[middle])
				{
					//Update right index
					upperbound = middle - 1;
				}
				//If the search key on the right half
				else
				{
					if (data > _Array[middle])
					{
						//Update the left index
						lowerbound = middle + 1;
					}
					//We found the key
					else
					{
						break;
					}
				}
			}

			memcpy((void*)&_Array[lowerbound + 1], (void*)&_Array[lowerbound], (_Count - lowerbound) * sizeof(T));
			_Array[lowerbound] = newitem;
			_Count++;
		}
		else
		{
			_Array[_Count] = newitem;
			_Count++;
		}
	}

	template <class T>
	void Array<T>::remove(const T data)
	{
		unsigned long idx = indexOf(data);
		if (idx != -1)
		{
			memcpy((void*)&_Array[idx], (void*)&_Array[idx + 1], (_Count - idx) * sizeof(T));
			memset((void*)&_Array[_Count - 1], 0, sizeof(T));
			_Count--;
		}
	}

	template <class T>
	void Array<T>::clear()
	{
		if (_Array != nullptr && _ArraySize != 0)
		{
			delete[] _Array;
		}
		_Array = nullptr;
		_ArraySize = 0;
		_Count = 0;
		_IteratorPosition = -1;
	}

	template <class T>
	unsigned long Array<T>::count()
	{
		return _Count;
	}

	template <class T>
	void Array<T>::sort()
	{
		for (unsigned long i = 0; i < _Count; ++i)
		{
			for (unsigned long j = i + 1; j < _Count; ++j)
			{
				if (_Array[i] > _Array[j])
				{
					T temp = _Array[i];
					_Array[i] = _Array[j];
					_Array[j] = temp;
				}
			}
		}
		_IsSorted = true;
	}

	template <class T>
	unsigned long Array<T>::indexOf(const T data)
	{
		if (_IsSorted)
		{
			int lowerbound = 0;
			int upperbound = _Count - 1;
			int middle = -1;

			while (lowerbound <= upperbound)
			{
				//Middle element
				middle = (lowerbound + upperbound) / 2;

				//If the search key on the left half
				if (data < _Array[middle])
				{
					//Update right index
					upperbound = middle - 1;
				}
				//If the search key on the right half
				else
				{
					if (data > _Array[middle])
					{
						//Update the left index
						lowerbound = middle + 1;
					}
					//We found the key
					else
					{
						return middle;
					}
				}
			}

			return -1;
		}
		else
		{
			for (unsigned long ctr = 0; ctr < _Count; ctr++)
			{
				if (_Array[ctr] == data)
				{
					return ctr;
				}
			}
		}

		return -1;
	}

	template <class T>
	T *Array<T>::getAt(unsigned int atpos)
	{
		if (atpos > _Count)
		{
			return nullptr;
		}

		return &_Array[atpos];
	}

	template <class T>
	T *Array<T>::getFirst()
	{
		_IteratorPosition = 0;

		return &_Array[_IteratorPosition];
	}

	template <class T>
	T *Array<T>::getLast()
	{
		_IteratorPosition = _Count - 1;

		return &_Array[_IteratorPosition];
	}

	template <class T>
	T *Array<T>::getNext()
	{
		_IteratorPosition++;

		return &_Array[_IteratorPosition];
	}

	template <class T>
	T *Array<T>::getPrevious()
	{
		_IteratorPosition--;

		return *_Array[_IteratorPosition];
	}

	template <class T>
	T& Array<T>::operator[](unsigned long index)
	{
		if (index > _Count)
		{
			throw;
		}

		return _Array[index];
	}
}
#endif
