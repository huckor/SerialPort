#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <stdio.h>

/**
* Clas used for logging.
*/
class Log
{
public:
    Log();
    ~Log();
    bool Create(const char *FileName);
    void Write(unsigned int LogLevel, std::string Text, std::string CppFile, int CppLine);
    void SetLogBit(unsigned int LogBit);

private:
    FILE *_LogFile;
    unsigned long _LogBit;

    std::string GetFileAndLine(std::string Path, int Line);
    std::string GetMemory();
};

//Macro definition for log. Use this macro instead of above class.
#define LOG(Msg, LogBit) __LOG->Write(LogBit, Msg, std::string(__FILE__), __LINE__)

#endif /* LOGFILE_H_ */
