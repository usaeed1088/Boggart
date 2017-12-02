################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/boggart/Boggart/Lib/IPC/Messages/IPCMessage.cpp \
/home/developer/Clones/boggart/Boggart/Lib/IPC/Messages/Subtypes.cpp 

OBJS += \
./Lib/IPC/Messages/IPCMessage.o \
./Lib/IPC/Messages/Subtypes.o 

CPP_DEPS += \
./Lib/IPC/Messages/IPCMessage.d \
./Lib/IPC/Messages/Subtypes.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/IPC/Messages/IPCMessage.o: /home/developer/Clones/boggart/Boggart/Lib/IPC/Messages/IPCMessage.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../ -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Lib/IPC/Messages/Subtypes.o: /home/developer/Clones/boggart/Boggart/Lib/IPC/Messages/Subtypes.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../ -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


