#include "Log.h"
#include "Global.h"
#include "Conv.h"
#ifndef WIN32
#include "SerialPortPosix.h"
#else
#include "SerialPortWin.h"
#endif

Log *__LOG;

int main(int argc, const char * argv[])
{
    //Create log class !importand to do it before anything else
    __LOG = new Log();
    __LOG->Create("stderr");
    
    
    std::vector<unsigned char> Data;
    iSerialPort *SerialPort;
    int Ret = -1;

#ifndef WIN32
    SerialPort = new SerialPortPosix();
    SerialPort->SetComPortName("/dev/pts/6");
#else
    SerialPort = new SerialPortWin();
    SerialPort->SetComPortName("COM1");
#endif

	//Set serial port parameters
	SerialPort->SetBaudRate(9600);
	SerialPort->SetCharacterSize(8);
	SerialPort->SetParity(ODD_PARITY);
	SerialPort->SetReadTimeout(10);
	
	//Initialize and open serial port
	if(SerialPort->Open() == OK)
	{
		//Read data till receive 0x31 ('1')
		while(true)
		{
			Data.clear();
			Data.push_back(0x00);
			Ret = SerialPort->Read(&Data[0], 1);
			if(Ret == OK)
			{
				if(Data[0] == 0x31)
					break;
				else
				{
					LOG("Read: " + Conv::BinToAscii(Data, false), MAIN_LOG_BIT);

					//Write ACK
					Data.clear();
					Data.push_back(0x06);
					if(SerialPort->Write(Data))
						LOG("ACK were written to serial port successfully", MAIN_LOG_BIT);
					else
						LOG("Write to serial port failed", MAIN_LOG_BIT);
				}
			}
			else
				LOG("Read timeout", MAIN_LOG_BIT);
		}

		SerialPort->Close();
	}

#ifndef WIN32
	delete (SerialPortPosix *)SerialPort;
#else
	delete (SerialPortWin *)SerialPort;
#endif
    
    
    //Delete log class !important to do it as last thing
    delete __LOG;
    
    return 0;
}
