#ifndef Global_h
#define Global_h

#include "Log.h"

extern Log *__LOG;

#define MAIN_LOG_BIT            0x00000001
#define LUA_LOG_BIT             0x00000002
#define SERIAL_LOG_BIT			0x00000004

#define OK                       1
#define FAIL					-1
#define LUA_INIT_FAILED         -2
#define LUA_SET_PATH_FAILED     -3
#define LUA_DO_FILE_FAILED      -4
#define TIMEOUT					-5

#endif /* Global_h */
