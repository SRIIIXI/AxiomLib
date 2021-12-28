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

#ifndef DEFINES_C
#define DEFINES_C

	#ifdef __cplusplus
	extern "C" {
	#endif

	/*Common headers*/
	#include <stddef.h>
	#include <stdint.h>
	#include <stdbool.h>

	/*Operating system specific headers*/
	#if defined (_WIN32) || defined (_WIN64)
		#include <WinSock2.h>
		#include <ws2tcpip.h>
		#include <Windows.h>
		#include <process.h>
		#include <direct.h>
	#else
		#include <unistd.h>
		#include <pthread.h>
	#endif

	/*Symbol export directive*/
	#if defined (_WIN32) || defined (_WIN64)
		#define LIBRARY_EXPORT __declspec( dllexport )
	#else
		#define LIBRARY_EXPORT __attribute__((visibility("default")))
	#endif

	/*Object aliases*/
	#if defined (_WIN32) || defined (_WIN64)
		typedef unsigned __int64    ssize_t;
		#define thread_t HANDLE
		#define lock_t CRITICAL_SECTION
		#define socket_t SOCKET
		#define pid_t long
	#else
		#define lock_t pthread_mutex_t
		#define thread_t pthread_t
		#define socket_t int
		#define LPSOCKADDR sockaddr*
		#define INVALID_SOCKET (-1)
		#define SOCKET_ERROR	 (-1)
		#define closesocket(s) close(s)
	#endif

	/*Function aliases*/
	#if defined (_WIN32) || defined (_WIN64)
		#define lock_create(l) InitializeCriticalSection(&l)
		#define lock_destroy(l) DeleteCriticalSection(&l)
		#define lock_acquire(l) EnterCriticalSection(&l)
		#define lock_try_acquire(l) TryEnterCriticalSection(&l)
		#define lock_release(l) LeaveCriticalSection(&l)
		#define strtoull(str, endptr, base) _strtoui64(str, endptr, base)
		#define getpid() _getpid()
		#define mkdir(s) _mkdir(s)
		#define getcwd(p, l) _getcwd(p, l)
	#else
		#define lock_create(l) pthread_mutex_init(&l, NULL)
		#define lock_destroy(l) pthread_mutex_destroy(&l)
		#define lock_acquire(l) pthread_mutex_lock(&l)
		#define lock_try_acquire(l) pthread_mutex_trylock(&l)
		#define lock_release(l) pthread_mutex_unlock(&l)
	#endif

	#ifdef __cplusplus
	}
	#endif

#endif