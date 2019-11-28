#include "KeyValue.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

void keyvalue_copy(KeyValue* dest, KeyValue* orig)
{
	node_copy(dest->Key, orig->Key);
	node_copy(dest->Value, orig->Value);
}

bool keyvalue_is_equal(KeyValue* first, KeyValue* second)
{
    return node_is_equal(first->Key, second->Key);
}

bool keyvalue_is_greater(KeyValue* first, KeyValue* second)
{
    return node_is_greater(first->Key, second->Key);
}

bool keyvalue_is_less(KeyValue* first, KeyValue* second)
{
    return node_is_less(first->Key, second->Key);
}
