################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Timer/Device/DeviceBase.cpp \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Timer/Device/Type.cpp 

OBJS += \
./Lib/Timer/Device/DeviceBase.o \
./Lib/Timer/Device/Type.o 

CPP_DEPS += \
./Lib/Timer/Device/DeviceBase.d \
./Lib/Timer/Device/Type.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Timer/Device/DeviceBase.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Timer/Device/DeviceBase.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Lib/Timer/Device/Type.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Timer/Device/Type.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


