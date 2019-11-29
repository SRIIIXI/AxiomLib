/*
BSD 2-Clause License

Copyright (c) 2017, SRIIIXI (subratoroy@hotmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
