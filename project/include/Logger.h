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

#ifndef _LOGGER_C
#define _LOGGER_C

#if defined(_WIN32) || defined(WIN32)
#define __FUNCTIONNAME__ __FUNCTION__
#else
#define __FUNCTIONNAME__ __PRETTY_FUNCTION__
#endif

#include <stddef.h>

typedef enum LogLevel
{
	LOG_INFO = 0,
	LOG_ERROR = 1,
	LOG_WARNING = 2,
	LOG_CRITICAL = 3,
	LOG_PANIC = 4
}LogLevel;

size_t	logger_start_logging();
void    logger_stop_logging(size_t loggerid);
void    logger_write(size_t loggerid, const char* logentry, LogLevel llevel, const char* func, const char* file, int line);
void    logger_set_logfilesize(size_t loggerid, int flsz);
void    logger_set_logdirectory(size_t loggerid, const char* dirpath);
void    logger_set_modulename(size_t loggerid, const char* mname);
size_t  logger_get_instance();

#define writeLog(loggerid, str, level) logger_write(loggerid, str, level, __FUNCTIONNAME__, __FILE__, __LINE__);
#define writeLogNormal(loggerid, str) logger_write(loggerid, str, LOG_INFO, __FUNCTIONNAME__, __FILE__, __LINE__);

#endif