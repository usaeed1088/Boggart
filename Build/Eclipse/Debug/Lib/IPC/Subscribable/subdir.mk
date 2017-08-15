################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Subscribable/Subscribable.cpp 

OBJS += \
./Lib/IPC/Subscribable/Subscribable.o 

CPP_DEPS += \
./Lib/IPC/Subscribable/Subscribable.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/IPC/Subscribable/Subscribable.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Subscribable/Subscribable.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


