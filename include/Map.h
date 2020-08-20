/*
BSD 2-Clause License

Copyright (c) 2017, Subrato Roy (subratoroy@hotmail.com)
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

#ifndef MAP_C
#define MAP_C

#include "Buffer.h"
#include "Tree.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Map
{
    Tree data;
}Map;

extern __attribute__((visibility("default"))) void* map_allocate(void* mptr);
extern __attribute__((visibility("default"))) void map_clear(void* mptr);

extern __attribute__((visibility("default"))) void map_insert(void* mptr, void* key, const void* data);
extern __attribute__((visibility("default"))) void map_remove(void* mptr, const void* key);

extern __attribute__((visibility("default"))) size_t map_item_count();

extern __attribute__((visibility("default"))) void* map_get_key(void* mptr, const void* data);
extern __attribute__((visibility("default"))) void* map_get_value(void* mptr, const void* key);

#ifdef __cplusplus
}
#endif

#endif
