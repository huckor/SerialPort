### Serial port demo.



Programming language: C++

OS Usage: Windows systems, POSIX systems

Projects: Visual Studio 2010, Eclipse

**Notes**

Before run, set correct serial port name. Find line with SerialPort->SetComPortName in main.cpp file.  

**What is this**

This simple demo demonstrate how to use serial port for communication between two devices.


**In nutshell this application doing this**

After successful build and run, this application open serial port and start waiting for data. After every received byte this application send ACK. When application receive byte 0x31 then application close serial port and terminate itself. 
