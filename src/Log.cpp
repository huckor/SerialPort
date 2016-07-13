#include "Log.h"
#include "Conv.h"
#include "Time.h"

Log::Log()
{
    _LogBit = 0xFFFF;
    _LogFile = NULL;
}

Log::~Log()
{
	if(_LogFile != NULL && _LogFile != stderr)
        fclose(_LogFile);
}

bool Log::Create(std::string FileName)
{
	if(FileName.compare("stderr") == 0)
		_LogFile = stderr;
	else
    {
		if((_LogFile = fopen( FileName.c_str(), "at")) == NULL)
			return false;
	}
    
	return true;
}

void Log::Write(unsigned int LogLevel, std::string Text, std::string CppFile, int CppLine)
{
    if(_LogBit & LogLevel)
    {
        fprintf( _LogFile, "%s (%s) - %s\n",Time::GetFormatedDateTime().c_str(), GetFileAndLine(CppFile, CppLine).c_str(), Text.c_str() );
        fflush( _LogFile );
    }
}

void Log::SetLogBit(unsigned int LogBit)
{
	_LogBit = LogBit;
}

std::string Log::GetFileAndLine(std::string Path, int Line)
{
  std::string Result;
  size_t Found = Path.find_last_of("/\\");

  if(Found != std::string::npos)
  {
    Path = Path.substr(Found + 1);
    Path += ":" + Conv::IntToStr(Line);
  }

  return Path;
}
