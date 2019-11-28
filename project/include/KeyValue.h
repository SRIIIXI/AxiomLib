#ifndef _KEY_VALUE_C
#define _KEY_VALUE_C

#include "Node.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct KeyValue
{
    Node*	Key;
    Node*	Value;
}KeyValue;

extern void keyvalue_copy(KeyValue* dest, KeyValue* orig);

extern bool keyvalue_is_equal(KeyValue* first, KeyValue* second);

extern bool keyvalue_is_greater(KeyValue* first, KeyValue* second);

extern bool keyvalue_is_less(KeyValue* first, KeyValue* second);

#endif
