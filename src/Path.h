#ifndef _PATH_
#define _PATH_

#include <string>

class Path
{
public:
  Path() {}
  ~Path() {}
  static std::string GetPathToExecutableFolder();
};

#endif //_PATH_