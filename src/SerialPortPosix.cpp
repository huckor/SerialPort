#include "SerialPortPosix.h"
#include "Global.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

SerialPortPosix::SerialPortPosix()
{
	_SerialPort = -1;
	_ReadTimeout = 10;
	_BaudRate = B9600;
	_CharacterSize = CS8;
	_Parity = ODD_PARITY;
	_ComPortName = "dev/tty0";
}

SerialPortPosix::~SerialPortPosix()
{
	Close();
}

int SerialPortPosix::Write(std::vector<unsigned char> Data)
{
	int Ret = - 1;

	Ret = write(_SerialPort, &Data[0], Data.size());
	if (Ret < 0)
	{
		LOG("Error - Cannot write to serial port.", SERIAL_LOG_BIT);
		return FAIL;
	}

	return OK;
}

int SerialPortPosix::Read(unsigned char *Buffer, int Length)
{
	int Ret = -1;
	fd_set FdSet;
	struct timeval Timeout;

	FD_ZERO(&FdSet);
	FD_SET(_SerialPort, &FdSet);
	Timeout.tv_sec = _ReadTimeout;
	Timeout.tv_usec = 0;

	//Wait till data arrived or timeout happened
	Ret = select(_SerialPort + 1, &FdSet, NULL, NULL, &Timeout);
	if(Ret < 0)
	{
		LOG("Error during wait for data on serial port.", SERIAL_LOG_BIT);
		return FAIL;
	}
	else if(Ret == 0)
	{
		LOG("Timeout during wait for data on serial port.", SERIAL_LOG_BIT);
		return TIMEOUT;
	}
	else
	{
		//If data arrived, read them
		Ret = read(_SerialPort, Buffer, Length);
		if (Ret < 0)
		{
			LOG("Error - Cannot read from serial port.", SERIAL_LOG_BIT);
			return FAIL;
		}
	}

	return OK;
}

int SerialPortPosix::Open()
{
	struct termios Options;

	//Get the current options for the port
	tcgetattr(_SerialPort, &Options);

	//Set the baud rates
	cfsetispeed(&Options, _BaudRate);
	cfsetospeed(&Options, _BaudRate);

	//Set character size
	Options.c_cflag &= ~CSIZE; // Mask the character size bits
	Options.c_cflag |= _CharacterSize;

	//Set parity
	if(_Parity == NO_PARITY)
	{
		Options.c_cflag &= ~PARENB;
		Options.c_cflag &= ~CSTOPB;
		Options.c_cflag &= ~CSIZE;
		Options.c_cflag |= CS8;
	}
	else if(_Parity == EVEN_PARITY)
	{
		Options.c_cflag |= PARENB;
		Options.c_cflag &= ~PARODD;
		Options.c_cflag &= ~CSTOPB;
		Options.c_cflag &= ~CSIZE;
		Options.c_cflag |= CS7;
	}
	else if(_Parity == ODD_PARITY)
	{
		Options.c_cflag |= PARENB;
		Options.c_cflag |= PARODD;
		Options.c_cflag &= ~CSTOPB;
		Options.c_cflag &= ~CSIZE;
		Options.c_cflag |= CS7;
	}
	else if(_Parity == SPACE_PARITY)
	{
		Options.c_cflag &= ~PARENB;
		Options.c_cflag &= ~CSTOPB;
		Options.c_cflag &= ~CSIZE;
		Options.c_cflag |= CS8;
	}

	//Enable the receiver and set local mode
	Options.c_cflag |= (CLOCAL | CREAD);

	//Set the new options for the port
	tcsetattr(_SerialPort, TCSANOW, &Options);

	//Open serial port
	_SerialPort = open(_ComPortName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (_SerialPort == -1)
	{
		LOG("Error - Cannot open serial port " + _ComPortName, SERIAL_LOG_BIT);
		return FAIL;
	}

	//Set port to block (wait) until characters come in, an interval timer expires, or an error occurs
	fcntl(_SerialPort, F_SETFL, 0);

	LOG("Serial port " + _ComPortName + " opened.", SERIAL_LOG_BIT);

	return OK;
}

void SerialPortPosix::Close()
{
	if(_SerialPort != -1)
	{
		close(_SerialPort);
		_SerialPort = -1;
	}
}

void SerialPortPosix::SetComPortName(std::string ComPortName)
{
	_ComPortName = ComPortName;
}

void SerialPortPosix::SetReadTimeout(int TimeoutSec)
{
	_ReadTimeout = TimeoutSec;
}

void SerialPortPosix::SetBaudRate(int BaudRate)
{
	switch(BaudRate)
	{
		case 9600: _BaudRate = B9600; break;
		case 19200: _BaudRate = B19200; break;
		case 57600: _BaudRate = B57600; break;
		case 115200: _BaudRate = B115200; break;
		default: _BaudRate = B9600; break;
	}
}

void SerialPortPosix::SetParity(int Parity)
{
	_Parity = Parity;
}

void SerialPortPosix::SetCharacterSize(int ByteSize)
{
	switch(ByteSize)
	{
		case 5: _CharacterSize = CS5; break;
		case 6: _CharacterSize = CS6; break;
		case 7: _CharacterSize = CS7; break;
		case 8: _CharacterSize = CS8; break;
		default: _CharacterSize = CS8; break;
	}
}
