#ifndef _PROCESS_LOCK
#define _PROCESS_LOCK

#include <string>

namespace CoreLib
{
	class ProcessLock
	{
	public:
		ProcessLock();
		virtual ~ProcessLock();
		bool LockProcess(std::string &lockfileame);
		void GetLockFileName(std::string &lockfileame);
		void GetCurrentUserName(std::string &uName);
	private:
		void GetProcessName(std::string &processName);
		void GetTempDir(std::string &dirName);
		int _LockFile;
		std::string _LockFileName;
	};
}
#endif
