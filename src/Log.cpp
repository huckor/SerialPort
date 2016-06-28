#include "Log.h"
#include "Conv.h"
#include "Time.h"

Log::Log()
{
    _LogBit = 0xFFFF;
}

Log::~Log()
{
	if(_LogFile != NULL && _LogFile != stderr)
        fclose(_LogFile);
}

bool Log::Create(const char *FileName)
{
	if( strcmp(FileName, "stderr") == 0 )
		_LogFile = stderr;
	else
    {
		if((_LogFile = fopen( FileName, "at")) == NULL)
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
  unsigned long Found = Path.find_last_of("/\\");

  if(Found != -1)
  {
    Path = Path.substr(Found + 1);
    Path += ":" + Conv::IntToStr(Line);
  }

  return Path;
}
