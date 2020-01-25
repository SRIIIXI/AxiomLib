#include "Logger.hpp"
#include "StringEx.hpp"

#include <filesystem>
namespace fs = std::filesystem;

#include <thread>
#include <chrono>

Logger objLogger;

Logger*  Logger::GetInstance()
{
    return &objLogger;
}

Logger::Logger()
{
    logDirectory = "";
    logFileSize = 1024;

    logLevelMap.clear();

	std::string ph = fs::current_path().generic_string();
	logDirectory = ph + "/logs/";
	fs::create_directory(logDirectory);

    logLevelMap[LOG_INFO]       ="Information";
    logLevelMap[LOG_WARNING]    ="Warning    ";
    logLevelMap[LOG_ERROR]      ="Error      ";
    logLevelMap[LOG_CRITICAL]   ="Critical   ";
    logLevelMap[LOG_PANIC]      ="Panic      ";
}

Logger::~Logger()
{
    StopLogging();
    logLevelMap.clear();
}

void Logger::StopLogging()
{
	if (logFile.is_open())
	{
		logFile.flush();
		logFile.close();
	}
}

void Logger::StartLogging()
{
	if (moduleName.length() < 1)
	{
		return;
	}

    if(logDirectory.empty() || logDirectory.length()<1)
    {
		std::string ph = fs::current_path().generic_string();
		logDirectory = ph + "/logs/";
		fs::create_directory(logDirectory);
    }

    logFilename = logDirectory + moduleName + ".log";

	logFile.open(logFilename);
}

void Logger::Write(std::string logEntry, LogLevel llevel, const char* func, const char* file, int line)
{
    if(logFile.is_open() && logFile.good())
    {
        size_t sz = fs::file_size(logFilename);

        if(sz >= (logFileSize * 1024))
        {
			std::string backupfile;

			auto timenow = std::chrono::system_clock::now();
			std::time_t t = std::chrono::system_clock::to_time_t(timenow);
			std::string ts = std::ctime(&t);
			ts.resize(ts.size() - 1);

			backupfile += moduleName;
			backupfile += "_";
			backupfile += ts;
			backupfile += ".log";

            StopLogging();
            int res = rename(logFilename.c_str(), backupfile.c_str());
            StartLogging();
        }

		std::string sourcefile = fs::path(std::string(file)).filename().generic_string();

		std::string lvel = logLevelMap[llevel];

		auto timenow = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(timenow);
		std::string ts = std::ctime(&t);
		ts.resize(ts.size() - 1);

		std::string fname;
        fname = func;
        #if defined(_WIN32) || defined(WIN32)
        #else
        int pos = strcharacterpos(fname,'(');
        fname[pos]=0;
        #endif

		std::string left, right;

        strsplit(fname, "::", left, right);

        if(right.length() > 1)
        {
            fname = right;
        }

        strsplit(fname, " ", left, right);

        if(right.length() > 1)
        {
            fname = right;
        }

		char temp[1024] = { 0 };
        sprintf(temp,"%s|%s|%05d|%s|%s| ", ts.c_str() , lvel.c_str(), line, fname.c_str(), sourcefile.c_str());

        logEntry = temp + logEntry;
		logEntry += "\n";
		logFile.write(logEntry.c_str(), logEntry.length());
		logFile.flush();
    }
}

void Logger::SetModuleName(const std::string& mname)
{
    moduleName = mname;
	
	size_t pos = 0;

    pos = strcharacterpos(mname, '/');

	if (pos < 0)
	{
		pos = strcharacterpos(mname, '\\');
	}

	if (pos > -1)
	{
		moduleName = moduleName.erase(0, pos);
	}

    strreplace(moduleName, ".exe", "");
    strreplace(moduleName, ".EXE", "");
}

void Logger::SetLogFileSize(int flsz)
{
    logFileSize = flsz;
}

void Logger::SetLogDirectory(const std::string &dirpath)
{
    logDirectory = dirpath;
	fs::create_directory(logDirectory);
}



