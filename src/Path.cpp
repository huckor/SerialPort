#include "Path.h"
#ifdef __APPLE__
#include <mach-o/dyld.h>
#elif WIN32
#include <windows.h>
#include <winbase.h>
#endif

std::string Path::GetPathToExecutableFolder()
{
  std::string FinalResult;
    
#ifdef __APPLE__
  char path[2048];
  uint32_t size = sizeof(path);
  if (_NSGetExecutablePath(path, &size) == 0)
    FinalResult = std::string(path);
  else
    FinalResult = "";
    
#elif WIN32
  std::wstring TmpResult;
  char ConvertBuffer[MAX_PATH];
  WCHAR PathWhithFileName[MAX_PATH];
  int Position;
    
  HMODULE Module = GetModuleHandleW(NULL);
  GetModuleFileNameW(Module, PathWhithFileName, MAX_PATH);
    
  TmpResult = std::wstring(PathWhithFileName);
  Position = TmpResult.find_last_of(L"/\\");
    
  if(Position != -1)
    TmpResult = TmpResult.substr(0, Position + 1);
    
  wcstombs(ConvertBuffer, TmpResult.c_str(), MAX_PATH);
  FinalResult = std::string(ConvertBuffer);
    
#endif
    
  return FinalResult;
}