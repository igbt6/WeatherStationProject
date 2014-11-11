################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/sensors/BMP180.c \
../Sources/sensors/DHT22.c \
../Sources/sensors/adt7410.c \
../Sources/sensors/max9611.c 

OBJS += \
./Sources/sensors/BMP180.o \
./Sources/sensors/DHT22.o \
./Sources/sensors/adt7410.o \
./Sources/sensors/max9611.o 

C_DEPS += \
./Sources/sensors/BMP180.d \
./Sources/sensors/DHT22.d \
./Sources/sensors/adt7410.d \
./Sources/sensors/max9611.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/sensors/%.o: ../Sources/sensors/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Sources" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Generated_Code" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/include" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/config" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/kernel" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m/core/M0" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


