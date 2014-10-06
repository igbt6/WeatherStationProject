################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/I2C/hal_dev_mag3110.c \
../Sources/I2C/hal_dev_mma8451.c \
../Sources/I2C/hal_i2c.c 

OBJS += \
./Sources/I2C/hal_dev_mag3110.o \
./Sources/I2C/hal_dev_mma8451.o \
./Sources/I2C/hal_i2c.o 

C_DEPS += \
./Sources/I2C/hal_dev_mag3110.d \
./Sources/I2C/hal_dev_mma8451.d \
./Sources/I2C/hal_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/I2C/%.o: ../Sources/I2C/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Sources" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Generated_Code" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/include" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/config" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/kernel" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m/core/M0" -I"C:/Users/lukasz/workspace.kds/WeatherStation/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


