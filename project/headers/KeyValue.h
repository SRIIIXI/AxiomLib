#ifndef _KEY_VALUE_C
#define _KEY_VALUE_C

#include "Node.h"

typedef struct KeyValue
{
    Node*	Key;
    Node*	Value;
}KeyValue;

extern void keyValueCopy(KeyValue* dest, KeyValue* orig);

extern int keyValueAreEqual(KeyValue* first, KeyValue* second);

extern int keyValueIsGreater(KeyValue* first, KeyValue* second);

extern int keyValueIsLess(KeyValue* first, KeyValue* second);

#endif
