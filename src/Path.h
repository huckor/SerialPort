#ifndef _PATH_
#define _PATH_

#ifndef WIN32

#else
#include <windows.h>
#include <winbase.h>
#endif
#include <string>

class Path
{
public:
	Path() {}
	~Path() {}
	static std::string GetPathToExecutableFolder();
};

#endif //_PATH_