################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/I2C1.c \
../Generated_Code/MQX1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/SegLCD1.c \
../Generated_Code/SystemTimer1.c \
../Generated_Code/TU1.c \
../Generated_Code/USART0_DEBUG.c \
../Generated_Code/Vectors.c \
../Generated_Code/WDog1.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/I2C1.o \
./Generated_Code/MQX1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SegLCD1.o \
./Generated_Code/SystemTimer1.o \
./Generated_Code/TU1.o \
./Generated_Code/USART0_DEBUG.o \
./Generated_Code/Vectors.o \
./Generated_Code/WDog1.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/I2C1.d \
./Generated_Code/MQX1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/SegLCD1.d \
./Generated_Code/SystemTimer1.d \
./Generated_Code/TU1.d \
./Generated_Code/USART0_DEBUG.d \
./Generated_Code/Vectors.d \
./Generated_Code/WDog1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Sources" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Generated_Code" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/include" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/config" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/kernel" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m/core/M0" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


