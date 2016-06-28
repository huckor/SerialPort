#ifndef TIME_H_
#define TIME_H_

#include <string>
#include <vector>

/**
* This class provide basic time operations.
*/
class Time
{
public:
  Time() {}
  ~Time() {}
  static std::string GetFormatedDateTime();
  static unsigned long GetSecondsSinceEpoch();  
  static bool CalculateRemainingTimeout(unsigned long StartTime, int *RemainingTimeout);
  static bool CheckIfTimeoutElapsed(unsigned long StartTime, int Timeout);
};

#endif /* TIME_H_ */
