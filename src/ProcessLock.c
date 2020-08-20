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

#include "ProcessLock.h"
#include "StringEx.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/*
	ProcessLock::ProcessLock()
	{
		_LockFile = 0;
	}

	bool ProcessLock::LockProcess(std::string &lockfileame)
	{
		GetLockFileName(_LockFileName);
		if (_LockFile != 0 && _LockFile != -1)
		{
			//File is already open
			return false;
		}

		#if !defined(_WIN32) || !defined(WIN32)
		_LockFile = open(_LockFileName.c_str(), O_CREAT | O_RDWR, 0666);
		if (_LockFile != -1)
		{
			off_t sz = 0;
			int rc = lockf(_LockFile, F_TLOCK, sz);
			if (rc == -1)
			{
				close(_LockFile);
				_LockFile = 0;
				if (EAGAIN == errno || EACCES == errno)
				{
				}
				else
				{
				}
				return false;
			}

			// Okay! We got a lock
			lockfileame = _LockFileName;
			return true;
		}
		else
		{
			_LockFile = 0;
			return false;
		}
		#endif

		return true;
	}

	void ProcessLock::GetLockFileName(std::string &lockfileame)
	{
		std::string procname, uname, tmpdir;
		GetProcessName(procname);
		GetCurrentUserName(uname);
		GetTempDir(tmpdir);

		lockfileame = tmpdir;

		lockfileame += "/";
		lockfileame += procname;
		lockfileame += ".";
		lockfileame += uname;
		lockfileame += ".lock";
	}

	ProcessLock::~ProcessLock()
	{
		#if !defined(_WIN32) || !defined(WIN32)
		close(_LockFile);
		#endif
	}


	void ProcessLock::GetProcessName(std::string &processName)
	{
		FILE *pipein_fp;
		char readbuf[80] = { 0 };

		int ownpid = getpid();

		char cmdbuffer[256] = { 0 };
		sprintf(cmdbuffer, "ps aux | tr -s ' ' | cut -d ' ' -f2,11 | grep %d", ownpid);

		// Create one way pipe line with call to popen()
		if ((pipein_fp = popen(cmdbuffer, "r")) == NULL)
		{
			return;
		}


		bool found = false;

		// Processing loop
		while (true)
		{
			memset((void*)&readbuf, 0, sizeof(readbuf));
			char *ptr = fgets(readbuf, 80, pipein_fp);
			if (ptr == NULL)
			{
				break;
			}

			for (int idx = 0; idx < 80; idx++)
			{
				if (readbuf[idx] == '\r' || readbuf[idx] == '\n')
				{
					readbuf[idx] = 0;
				}
			}

			if (strlen(readbuf) < 1)
			{
				continue;
			}

			// Check for zombie processes
			if (strstr(readbuf, "<defunct>") != NULL)
			{
				continue;
			}

			std::vector<std::string> strlist;

			std::string tempreadbuf(readbuf);

			strsplit(tempreadbuf, strlist, ' ');

			if (strlist.size() < 2)
			{
				continue;
			}

			processName = strlist[1];
			strremove(processName, '.');
			strremove(processName, '&');
			strremove(processName, '/');

		}
		// Close the pipes
		pclose(pipein_fp);
	}

	void ProcessLock::GetCurrentUserName(std::string &uName)
	{
		uName = getenv("USER");
	}

	void ProcessLock::GetTempDir(std::string &dirName)
	{
		dirName = "/tmp";
	}
*/
