################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Sources/uart/subdir.mk
-include Sources/timeout/subdir.mk
-include Sources/sensors/subdir.mk
-include Sources/lcd/subdir.mk
-include Sources/i2c/subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include MQXLITE/psp/cortex_m/core/M0/subdir.mk
-include MQXLITE/psp/cortex_m/subdir.mk
-include MQXLITE/kernel/subdir.mk
-include MQXLITE/config/subdir.mk
-include Generated_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: WeatherStation.elf secondary-outputs

# Tool invocations
WeatherStation.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "C:/Users/lukasz/workspace.kds/WeatherStation/Project_Settings/Linker_Files/ProcessorExpert.ld" -Xlinker --gc-sections -L"C:/Users/lukasz/workspace.kds/WeatherStation/Project_Settings/Linker_Files" -Wl,-Map,"WeatherStation.map" -nanolibc -o "WeatherStation.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) WeatherStation.elf
	-@echo ' '

post-build:
	-"C:\Freescale\KDS_1.1.1\toolchain\bin\arm-none-eabi-size"  --format=berkeley WeatherStation.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
