################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Logger/Console/Console.cpp 

OBJS += \
./Lib/Logger/Console/Console.o 

CPP_DEPS += \
./Lib/Logger/Console/Console.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Logger/Console/Console.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Logger/Console/Console.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


