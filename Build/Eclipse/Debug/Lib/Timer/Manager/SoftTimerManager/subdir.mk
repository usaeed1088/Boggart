################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Timer/Manager/SoftTimerManager/SoftTimerManager.cpp 

OBJS += \
./Lib/Timer/Manager/SoftTimerManager/SoftTimerManager.o 

CPP_DEPS += \
./Lib/Timer/Manager/SoftTimerManager/SoftTimerManager.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Timer/Manager/SoftTimerManager/SoftTimerManager.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Timer/Manager/SoftTimerManager/SoftTimerManager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


