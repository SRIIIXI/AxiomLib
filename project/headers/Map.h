#ifndef _MAP_C
#define _MAP_C

#include "KeyValue.h"
#include "Node.h"

typedef struct Map
{
	unsigned long Count;
	unsigned long MapMemorySize;
	KeyValue* MapMemory;
	long IteratorPosition;
}Map;

extern void mapClear(Map* mptr);
extern void mapAllocate(Map* mptr);

extern void mapInsert(Map* mptr, Node key, const Node data);
extern void mapRemove(Map* mptr, const Node key);

extern size_t mapItemCount();
extern size_t mapIndexOf(const Node key);

extern Node* mapGetkey(Map* mptr, const Node data);
extern Node* mapGetvalue(Map* mptr, const Node key);
extern KeyValue* mapGetAt(Map* mptr, unsigned int atpos);

extern KeyValue* mapGetFirst(Map* mptr);
extern KeyValue* mapGetLast(Map* mptr);
extern KeyValue* mapGetNext(Map* mptr);
extern KeyValue* mapGetPrevious(Map* mptr);


#endif
