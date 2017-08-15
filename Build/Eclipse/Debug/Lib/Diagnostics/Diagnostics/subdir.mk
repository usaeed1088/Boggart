################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Diagnostics/Diagnostics/Diagnsotics.cpp 

OBJS += \
./Lib/Diagnostics/Diagnostics/Diagnsotics.o 

CPP_DEPS += \
./Lib/Diagnostics/Diagnostics/Diagnsotics.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Diagnostics/Diagnostics/Diagnsotics.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Diagnostics/Diagnostics/Diagnsotics.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


