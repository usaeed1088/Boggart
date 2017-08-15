################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Lib/Transport/TCP/Server/subdir.mk
-include Lib/Transport/TCP/Client/subdir.mk
-include Lib/Transport/IncomingBuffer/subdir.mk
-include Lib/Transport/InProcess/subdir.mk
-include Lib/Transport/Helper/subdir.mk
-include Lib/Transport/Definition/subdir.mk
-include Lib/Transport/subdir.mk
-include Lib/Timer/Manager/SoftTimerManager/subdir.mk
-include Lib/Timer/Manager/subdir.mk
-include Lib/Timer/Device/SoftTimerDevice/subdir.mk
-include Lib/Timer/Device/subdir.mk
-include Lib/Message/subdir.mk
-include Lib/Logger/Console/subdir.mk
-include Lib/Logger/subdir.mk
-include Lib/IPC/Subscribable/subdir.mk
-include Lib/IPC/Messages/Response/subdir.mk
-include Lib/IPC/Messages/Request/subdir.mk
-include Lib/IPC/Messages/subdir.mk
-include Lib/IPC/Asynchronous/subdir.mk
-include Lib/IPC/subdir.mk
-include Lib/Diagnostics/Diagnostics/subdir.mk
-include Lib/Diagnostics/subdir.mk
-include Lib/Common/Patterns/DependencyInjection/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libBoggart.a

# Tool invocations
libBoggart.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Archiver'
	ar -r  "libBoggart.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(ARCHIVES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) libBoggart.a
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
