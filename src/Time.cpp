#include "Time.h"
#ifndef WIN32
#include <cstdio>
#include <cstring>
#else
#include <windows.h>
#include <winbase.h>
#include <time.h>
#endif
#include <ctime>

/**
* This method return current formated Date and Time.
* Foramt is: [day.month.year hour:minute:second]
*/
std::string Time::GetFormatedDateTime()
{
  char Result[50];

#ifndef WIN32
  struct tm tm_time;
  time_t tm;

  time(&tm);
  memcpy(&tm_time, localtime(&tm), sizeof(tm_time));

  snprintf(Result, 50, "[%02i.%02i.%02i %02i:%02i:%02i]", tm_time.tm_mday, tm_time.tm_mon + 1,
      tm_time.tm_year + 1900, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
#else
  //Structure represents a date and time
  SYSTEMTIME SysTime;
  //Retrieves the current system date and time
  GetLocalTime(&SysTime);

  _snprintf(Result, 50, "[%02i.%02i.%02i %02i:%02i:%02i]", SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
#endif

  return std::string(Result);
}

/**
* returns the time as the number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
*/
unsigned long Time::GetSecondsSinceEpoch()
{
#ifndef WIN32
  return time(NULL);
#else
  SYSTEMTIME SysTime;
  FILETIME FileTime;
  LARGE_INTEGER LargeInteger;

  //Get systime
  GetSystemTime(&SysTime);
  //Convert systime to file time
  SystemTimeToFileTime(&SysTime, &FileTime);

  //Convert filetime to large integer (int64)
  LargeInteger.LowPart = FileTime.dwLowDateTime;
  LargeInteger.HighPart = FileTime.dwHighDateTime;

  //Convert to seconds
  return (unsigned long)LargeInteger.QuadPart / 10000000;
#endif
}

/**
* Calculate remaining time in seconds between StartTime and actual time.
* Result is stored in out parameter named RemainingTimeout.
* @param StartTime - begining time in seconds since epoch
* @param RemainingTimeout [IN/OUT] remaining timeout in seconds
* @return If remaining timeout is less or equal than 1 sec this method return false and set RemainingTimeout variable to 0
*/
bool Time::CalculateRemainingTimeout(unsigned long StartTime, int *RemainingTimeout)
{
  //Get actual time in seconds
  unsigned long ActualTime = GetSecondsSinceEpoch();
  //Calculate difference in seconds
  unsigned long Difference = ActualTime - StartTime;

  //If difference is less or equal than 0
  if(Difference <= 0) Difference = 1;

  //Calculate remaining timeout
  *RemainingTimeout -= (Difference * 1000);

  //If timeout is less than 1 sec return false
  if(*RemainingTimeout <= 1)
  {
    *RemainingTimeout = 0;
    return false;
  }
  else
      return true;
}

/**
* Check if timeout elapsed from StartTime.
* @param StartTime - begining time in seconds since epoch
* @param Timeout, timeout in miliseconds
* @return True if timeout elapsed, else false
*/
bool Time::CheckIfTimeoutElapsed(unsigned long StartTime, int Timeout)
{
  //Get actual time in seconds
    unsigned long ActualTime = GetSecondsSinceEpoch();
    //Calculate difference in seconds
    unsigned long Difference = ActualTime - StartTime;

    if((Difference * 1000) >= (unsigned long)Timeout)
        return true;
    else
        return false;
}



