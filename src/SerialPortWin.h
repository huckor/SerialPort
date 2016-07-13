#ifndef _SERIAL_PORT_WIN_H_
#define _SERIAL_PORT_WIN_H_

#include <windows.h>
#include "iSerialPort.h"

#define NO_PARITY			NOPARITY
#define ODD_PARITY			ODDPARITY
#define EVEN_PARITY			EVENPARITY
#define SPACE_PARITY		SPACEPARITY

class SerialPortWin: public iSerialPort 
{
public:
	SerialPortWin();
	virtual ~SerialPortWin();
	virtual int Open();
	virtual void Close();
	virtual int Write(std::vector<unsigned char> Data);
	virtual int Read(unsigned char *Buffer, int Length);
	virtual void SetBaudRate(int BaudRate);
	virtual void SetParity(int Parity);
	virtual void SetCharacterSize(int ByteSize);
	virtual void SetComPortName(std::string ComPortName);
	virtual void SetReadTimeout(int TimeoutSec);

private:
	HANDLE _SerialPort;
	std::string _ComPortName;
	int _ReadTimeout;
	int _Parity;
	int _CharacterSize;
	int _BaudRate;
};

#endif //SERIAL_PORT_WIN_H_
