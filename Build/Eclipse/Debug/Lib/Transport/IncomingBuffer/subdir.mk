################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/boggart/Boggart/Lib/Transport/IncomingBuffer/IncomingBuffer.cpp 

OBJS += \
./Lib/Transport/IncomingBuffer/IncomingBuffer.o 

CPP_DEPS += \
./Lib/Transport/IncomingBuffer/IncomingBuffer.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Transport/IncomingBuffer/IncomingBuffer.o: /home/developer/Clones/boggart/Boggart/Lib/Transport/IncomingBuffer/IncomingBuffer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../ -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


