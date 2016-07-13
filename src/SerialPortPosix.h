#ifndef _SERIAL_PORT_POSIX_H_
#define _SERIAL_PORT_POSIX_H_

#include "iSerialPort.h"

#define NO_PARITY			1
#define ODD_PARITY			2
#define EVEN_PARITY			3
#define SPACE_PARITY		4


class SerialPortPosix: public iSerialPort
{
public:
	SerialPortPosix();
	virtual ~SerialPortPosix();
	virtual int Open();
	virtual void Close();
	virtual int Write(std::vector<unsigned char> Data);
	virtual int Read(unsigned char *Buffer, int Length);
	virtual void SetBaudRate(int BaudRate);
	virtual void SetParity(int Parity);
	virtual void SetCharacterSize(int CharacterSize);
	virtual void SetComPortName(std::string ComPortName);
	virtual void SetReadTimeout(int TimeoutSec);

private:
	int _SerialPort;
	std::string _ComPortName;
	int _ReadTimeout;
	int _Parity;
	unsigned int _CharacterSize;
	unsigned int _BaudRate;
};

#endif //_SERIAL_PORT_POSIX_H_
