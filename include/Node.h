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

#ifndef NODE_C
#define NODE_C

#include <stddef.h>
#include <stdbool.h>
#include "Buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node
{
    Buffer* NodeData;
    struct Node* Next;
    struct Node* Previous;
}Node;

extern __attribute__((visibility("default"))) Node* node_allocate(void* data, size_t sz);

extern __attribute__((visibility("default"))) void node_free(Node* ptr);
extern __attribute__((visibility("default"))) void node_copy(Node* dest, Node* orig);

extern __attribute__((visibility("default"))) bool node_is_equal(Node* first, Node* second);
extern __attribute__((visibility("default"))) bool node_is_greater(Node* first, Node* second);
extern __attribute__((visibility("default"))) bool node_is_less(Node* first, Node* second);

#ifdef __cplusplus
}
#endif

#endif
