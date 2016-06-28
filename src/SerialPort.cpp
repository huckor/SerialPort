#include "SerialPort.h"
#include "Global.h"
#include "Conv.h"
#include "Log.h"

SerialPort::SerialPort()
{
	_BaudRate = 9600;
	_Parity = NO_PARITY;
	_StopBit = ONE_STOP_BIT;
	_ByteSize = 8;
	_ReadTimeout = 1000;
	_WriteTimeout = 1000;
	_ComPortName = "COM1";
}

SerialPort::~SerialPort()
{
	Close();
}

std::vector<unsigned char> SerialPort::Read(int Length)
{
	unsigned long BytesRead = 0;
	std::vector<unsigned char> Buffer(Length);

	//Read data and check if error appeared
	if(!ReadFile(_SerialPort, &Buffer[0], Length, &BytesRead, NULL))
	{
		LOG("Error - read from COM port.", SERIAL_LOG_BIT);
		return std::vector<unsigned char>();
	}
	//Timeout
	else if(BytesRead <= 0)
		return std::vector<unsigned char>();
	//We have data !
	else 
		return Buffer;
}

bool SerialPort::Write(std::vector<unsigned char> Data)
{
	unsigned long BytesWritten = 0;

	if(!WriteFile(_SerialPort, &Data.front(), Data.size(), &BytesWritten, NULL))
	{
		LOG("Error write to COM port", SERIAL_LOG_BIT);
		return false;
	}
	else return true;
}

bool SerialPort::Open()
{
	std::wstring PortName = Conv::StringToWstring(_ComPortName) + L":";
	COMMTIMEOUTS Timeouts;
	DCB SerialPortParams;

	//Initialize parameters and timeouts structures
	SecureZeroMemory(&SerialPortParams, sizeof(DCB));
	SerialPortParams.DCBlength = sizeof(DCB);	
	SerialPortParams.BaudRate = _BaudRate;
	SerialPortParams.ByteSize = _ByteSize;
	SerialPortParams.StopBits = _StopBit;
	SerialPortParams.Parity = _Parity;
		
	Timeouts.ReadIntervalTimeout = MAXDWORD;
	Timeouts.ReadTotalTimeoutConstant = _ReadTimeout;
	Timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
	Timeouts.WriteTotalTimeoutConstant = _WriteTimeout;
	Timeouts.WriteTotalTimeoutMultiplier = MAXDWORD;

	//Open port
	_SerialPort = CreateFile(PortName.c_str(),
							GENERIC_READ | GENERIC_WRITE,
							0,
							NULL,
							OPEN_EXISTING,
							0,
							NULL);
	
	if(_SerialPort == INVALID_HANDLE_VALUE)
	{
		LOG("Error - Cannot open serial port communication.", SERIAL_LOG_BIT); 
		return false;
	}

	if(!SetCommState(_SerialPort, &SerialPortParams))
	{
		LOG("Error - Cannot set comm state.", SERIAL_LOG_BIT); 
		return false;
	}

	if(!SetCommTimeouts(_SerialPort, &Timeouts))
	{
		LOG("Error - Cannot set comm timeouts.", SERIAL_LOG_BIT); 
		return false;
	}

	return true;
}

void SerialPort::Close()
{
	if(_SerialPort != NULL && _SerialPort != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_SerialPort);
		_SerialPort = NULL;
	}
}

void SerialPort::SetBaudRate(int BaudRate)
{
	_BaudRate = BaudRate;
}

void SerialPort::SetByteSize(int ByteSize)
{
	_ByteSize = ByteSize;
}

void SerialPort::SetComPortName(std::string ComPortName)
{
	_ComPortName = ComPortName;
}

void SerialPort::SetParity(int Parity)
{
	_Parity = Parity;
}

void SerialPort::SetStopBit(int StopBit)
{
	_StopBit = StopBit;
}

void SerialPort::SetReadTimeout(int TimeoutSec)
{
	_ReadTimeout = TimeoutSec * 1000;
}

void SerialPort::SetWriteTimeout(int TimeoutSec)
{
	_WriteTimeout = TimeoutSec * 1000;
}

