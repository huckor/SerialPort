#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#ifdef WIN32
#include <windows.h>
#define NO_PARITY			NOPARITY
#define ODD_PARITY			ODDPARITY
#define EVEN_PARITY			EVENPARITY
#define MARK_PARITY			MARKPARITY
#define SPACE_PARITY		SPACEPARITY

#define ONE_STOP_BIT		ONESTOPBIT
#define ONE_5_STOP_BITS		ONE5STOPBITS
#define TWO_STOP_BITS		TWOSTOPBITS
#endif
#include <string>
#include <vector>

class SerialPort
{
public:
	SerialPort();
	~SerialPort();
	bool Open();
	void Close();
	bool Write(std::vector<unsigned char> Data);
	std::vector<unsigned char> Read(int Length);
	void SetBaudRate(int BaudRate);
	void SetParity(int Parity);
	void SetStopBit(int StopBit);
	void SetByteSize(int ByteSize);
	void SetComPortName(std::string ComPortName);
	void SetReadTimeout(int TimeoutSec);
	void SetWriteTimeout(int TimeoutSec);

private:
	HANDLE _SerialPort;
	std::string _ComPortName;
	int _ReadTimeout;
	int _WriteTimeout;
	int _Parity;
	int _StopBit;
	int _ByteSize;
	int _BaudRate;
};

#endif //SERIAL_PORT_H_
