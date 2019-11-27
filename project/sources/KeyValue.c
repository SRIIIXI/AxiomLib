#include "KeyValue.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

void keyValueCopy(KeyValue* dest, KeyValue* orig)
{
    nodeCopy(dest->Key, orig->Key);
    nodeCopy(dest->Value, orig->Value);
}

int keyValueAreEqual(KeyValue* first, KeyValue* second)
{
    return nodeAreEqual(first->Key, second->Key);
}

int keyValueIsGreater(KeyValue* first, KeyValue* second)
{
    return nodeIsGreater(first->Key, second->Key);
}

int keyValueIsLess(KeyValue* first, KeyValue* second)
{
    return nodeIsLess(first->Key, second->Key);
}
