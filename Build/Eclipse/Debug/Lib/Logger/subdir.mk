################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Logger/Level.cpp \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Logger/LoggerBase.cpp 

OBJS += \
./Lib/Logger/Level.o \
./Lib/Logger/LoggerBase.o 

CPP_DEPS += \
./Lib/Logger/Level.d \
./Lib/Logger/LoggerBase.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Logger/Level.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Logger/Level.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Lib/Logger/LoggerBase.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/Logger/LoggerBase.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


