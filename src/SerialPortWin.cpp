#include "SerialPortWin.h"
#include "Global.h"
#include "Conv.h"
#include "Log.h"

SerialPortWin::SerialPortWin()
{
	_BaudRate = 9600;
	_Parity = NO_PARITY;
	_CharacterSize = 8;
	_ReadTimeout = 10000;
	_ComPortName = "COM1";
}

SerialPortWin::~SerialPortWin()
{
	Close();
}

int SerialPortWin::Read(unsigned char *Buffer, int Length)
{
	unsigned long BytesRead = 0;

	//Read data and check if error appeared
	if(!ReadFile(_SerialPort, Buffer, Length, &BytesRead, NULL))
	{
		LOG("Error - on serial port during read", SERIAL_LOG_BIT);
		return FAIL;
	}
	//Timeout
	else if(BytesRead <= 0)
	{
		LOG("Timeout on serial port during read", SERIAL_LOG_BIT);
		return FAIL;
	}
	//We have data !
	else 
		return OK;
}

int SerialPortWin::Write(std::vector<unsigned char> Data)
{
	unsigned long BytesWritten = 0;

	if(!WriteFile(_SerialPort, &Data.front(), Data.size(), &BytesWritten, NULL))
	{
		LOG("Error on serial port during write", SERIAL_LOG_BIT);
		return FAIL;
	}
	else 
		return OK;
}

int SerialPortWin::Open()
{
	std::wstring PortName = Conv::StringToWstring(_ComPortName) + L":";
	COMMTIMEOUTS Timeouts;
	DCB SerialPortParams;

	//Initialize parameters and timeouts structures
	SecureZeroMemory(&SerialPortParams, sizeof(DCB));
	SerialPortParams.DCBlength = sizeof(DCB);	
	SerialPortParams.BaudRate = _BaudRate;
	SerialPortParams.ByteSize = _CharacterSize;
	SerialPortParams.StopBits = ONESTOPBIT;
	SerialPortParams.Parity = _Parity;
		
	Timeouts.ReadIntervalTimeout = MAXDWORD;
	Timeouts.ReadTotalTimeoutConstant = _ReadTimeout;
	Timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
	Timeouts.WriteTotalTimeoutConstant = 1;
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
		LOG("Error - Cannot open serial port on " + _ComPortName, SERIAL_LOG_BIT); 
		return false;
	}

	if(!SetCommState(_SerialPort, &SerialPortParams))
	{
		LOG("Error - Cannot set serial port state.", SERIAL_LOG_BIT); 
		return false;
	}

	if(!SetCommTimeouts(_SerialPort, &Timeouts))
	{
		LOG("Error - Cannot set serial port timeouts.", SERIAL_LOG_BIT); 
		return false;
	}

	LOG("Serial port opened", SERIAL_LOG_BIT); 

	return true;
}

void SerialPortWin::Close()
{
	if(_SerialPort != NULL && _SerialPort != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_SerialPort);
		_SerialPort = NULL;
	}
}

void SerialPortWin::SetBaudRate(int BaudRate)
{
	_BaudRate = BaudRate;
}

void SerialPortWin::SetCharacterSize(int ByteSize)
{
	_CharacterSize = ByteSize;
}

void SerialPortWin::SetComPortName(std::string ComPortName)
{
	_ComPortName = ComPortName;
}

void SerialPortWin::SetParity(int Parity)
{
	_Parity = Parity;
}

void SerialPortWin::SetReadTimeout(int TimeoutSec)
{
	_ReadTimeout = TimeoutSec * 1000;
}

