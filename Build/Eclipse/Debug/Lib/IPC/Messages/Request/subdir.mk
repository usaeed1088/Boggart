################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Messages/Request/Request.cpp \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Messages/Request/Response.cpp \
/home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Messages/Request/Subtypes.cpp 

OBJS += \
./Lib/IPC/Messages/Request/Request.o \
./Lib/IPC/Messages/Request/Response.o \
./Lib/IPC/Messages/Request/Subtypes.o 

CPP_DEPS += \
./Lib/IPC/Messages/Request/Request.d \
./Lib/IPC/Messages/Request/Response.d \
./Lib/IPC/Messages/Request/Subtypes.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/IPC/Messages/Request/Request.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Messages/Request/Request.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Lib/IPC/Messages/Request/Response.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Messages/Request/Response.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Lib/IPC/Messages/Request/Subtypes.o: /home/developer/Clones/Boggart/linux-makefiles/Boggart/Lib/IPC/Messages/Request/Subtypes.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../../Lib -I../../../../PAL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


