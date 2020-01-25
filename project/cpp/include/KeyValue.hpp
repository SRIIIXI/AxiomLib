#ifndef _KEY_VALUE
#define _KEY_VALUE

namespace CoreLibrary
{
	template <class K, class V>
	class KeyValue
	{
	public:
		KeyValue();
		KeyValue(const K key, const V value);
		~KeyValue();
		void operator=(const KeyValue& other);
		bool operator!=(const KeyValue& other);
		bool operator==(const KeyValue& other);
		bool operator>(const KeyValue& other);
		bool operator<(const KeyValue& other);
		K Key;
		V Value;
	};

	template <class K, class V>
	KeyValue<K, V>::KeyValue()
	{
	}

	template <class K, class V>
	KeyValue<K, V>::KeyValue(const K key, const V value)
	{
		Value = value;
		Key = key;
	}

	template <class K, class V>
	KeyValue<K, V>::~KeyValue()
	{
	}

	template <class K, class V>
	void KeyValue<K, V>::operator=(const KeyValue& other)
	{
		Key = other.Key;
		Value = other.Value;
	}

	template <class K, class V>
	bool KeyValue<K, V>::operator!=(const KeyValue& other)
	{
		return(Key != other.Key);
	}

	template <class K, class V>
	bool KeyValue<K, V>::operator==(const KeyValue& other)
	{
		return(Key == other.Key);
	}

	template <class K, class V>
	bool KeyValue<K, V>::operator>(const KeyValue& other)
	{
		return (Key > other.Key);
	}

	template <class K, class V>
	bool KeyValue<K, V>::operator<(const KeyValue& other)
	{
		return (Key < other.Key);
	}
}
#endif
