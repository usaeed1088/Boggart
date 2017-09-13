################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/boggart/Boggart/Lib/Message/Utility/Utility.cpp 

OBJS += \
./Lib/Message/Utility/Utility.o 

CPP_DEPS += \
./Lib/Message/Utility/Utility.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Message/Utility/Utility.o: /home/developer/Clones/boggart/Boggart/Lib/Message/Utility/Utility.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../ -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


