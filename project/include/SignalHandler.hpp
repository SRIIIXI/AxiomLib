#ifndef _SIGNAL_HANDLER
#define _SIGNAL_HANDLER

namespace CoreLib
{
	class SignalCallback
	{
	public:
		SignalCallback() {}
        virtual ~SignalCallback() {}
		virtual void Suspend() = 0;
		virtual void Resume() = 0;
		virtual void Shutdown() = 0;
		virtual void Alarm() = 0;
		virtual void Reset() = 0;
		virtual void ChildExit() = 0;
		virtual void Userdefined1() = 0;
		virtual void Userdefined2() = 0;
	};

	class SignalHandler
	{
	public:
		SignalHandler();
		~SignalHandler();
		void RegisterCallbackClient(SignalCallback *clientptr);
		void RegisterSignalHandlers();
		bool IsShutdownSignal(const int signum);
	};
}
#endif
