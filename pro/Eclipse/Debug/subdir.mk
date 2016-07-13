################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/robo/workspace/SerialPort/src/Conv.cpp \
/home/robo/workspace/SerialPort/src/Log.cpp \
/home/robo/workspace/SerialPort/src/Path.cpp \
/home/robo/workspace/SerialPort/src/SerialPortPosix.cpp \
/home/robo/workspace/SerialPort/src/Time.cpp \
/home/robo/workspace/SerialPort/src/main.cpp 

OBJS += \
./Conv.o \
./Log.o \
./Path.o \
./SerialPortPosix.o \
./Time.o \
./main.o 

CPP_DEPS += \
./Conv.d \
./Log.d \
./Path.d \
./SerialPortPosix.d \
./Time.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
Conv.o: /home/robo/workspace/SerialPort/src/Conv.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Log.o: /home/robo/workspace/SerialPort/src/Log.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Path.o: /home/robo/workspace/SerialPort/src/Path.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SerialPortPosix.o: /home/robo/workspace/SerialPort/src/SerialPortPosix.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Time.o: /home/robo/workspace/SerialPort/src/Time.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.o: /home/robo/workspace/SerialPort/src/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


