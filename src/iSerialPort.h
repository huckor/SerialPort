#ifndef _I_SERIAL_PORT_H_
#define _I_SERIAL_PORT_H_

#include <string>
#include <vector>

//Interface for Serial Port classes. Do not use it directly it's only for inheritance.
class iSerialPort
{
public:
	iSerialPort() {}
	virtual ~iSerialPort() {}
	virtual int Open() = 0;
	virtual void Close() = 0;
	virtual int Write(std::vector<unsigned char> Data) = 0;
	virtual int Read(unsigned char *Buffer, int Length) = 0;
	virtual void SetBaudRate(int BaudRate) = 0;
	virtual void SetParity(int Parity) = 0;
	virtual void SetCharacterSize(int ByteSize) = 0;
	virtual void SetComPortName(std::string ComPortName) = 0;
	virtual void SetReadTimeout(int TimeoutSec) = 0;
};

#endif
