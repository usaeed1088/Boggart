################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/boggart/Boggart/Lib/IPC/Messages/Factory/Factory.cpp 

OBJS += \
./Lib/IPC/Messages/Factory/Factory.o 

CPP_DEPS += \
./Lib/IPC/Messages/Factory/Factory.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/IPC/Messages/Factory/Factory.o: /home/developer/Clones/boggart/Boggart/Lib/IPC/Messages/Factory/Factory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../ -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


