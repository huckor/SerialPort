#include "Path.h"

std::string Path::GetPathToExecutableFolder()
{
	std::wstring TmpResult;
	std::string FinalResult;
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

	return FinalResult;
}