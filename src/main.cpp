#include "Log.h"
#include "Global.h"
#include "SerialPort.h"
#include "Conv.h"

Log *__LOG;

int main(int argc, const char * argv[])
{
    //Create log class !importand to do it before anything else
    __LOG = new Log();
    __LOG->Create("stderr");
    
    
	std::vector<unsigned char> Data;
    SerialPort _SerialPort;

	//Set serial port parameters
	_SerialPort.SetBaudRate(9600);
	_SerialPort.SetByteSize(8);
	_SerialPort.SetComPortName("COM1");
	_SerialPort.SetParity(ODD_PARITY);
	_SerialPort.SetReadTimeout(10);
	
	//Initialize and open serial port
	if(_SerialPort.Open())
	{
		//Read data till receive 0x03 (EOT)
		while(true)
		{
			Data = _SerialPort.Read(1);
			if(Data.size() > 0)
			{
				if(Data[0] == 0x03)
					break;
				else
				{
					LOG("Readed: " + Conv::BinToAscii(Data, false), MAIN_LOG_BIT);

					//Write ACK
					Data.clear();
					Data.push_back(0x06);
					if(_SerialPort.Write(Data))
						LOG("ACK were written to serial port sucesfully", MAIN_LOG_BIT);
					else
						LOG("Write to serial port failed", MAIN_LOG_BIT);
				}
			}
			else
				LOG("Read timeouted", MAIN_LOG_BIT);
		}

		_SerialPort.Close();
	}
    
    
    //Delete log class !important to do it as last thing
    delete __LOG;
    
    return 0;
}
