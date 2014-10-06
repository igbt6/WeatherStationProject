################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/usb/ring_buffer.c \
../Sources/usb/usb.c \
../Sources/usb/usb_cdc.c \
../Sources/usb/usb_reg.c 

OBJS += \
./Sources/usb/ring_buffer.o \
./Sources/usb/usb.o \
./Sources/usb/usb_cdc.o \
./Sources/usb/usb_reg.o 

C_DEPS += \
./Sources/usb/ring_buffer.d \
./Sources/usb/usb.d \
./Sources/usb/usb_cdc.d \
./Sources/usb/usb_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/usb/%.o: ../Sources/usb/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Sources" -I"C:/Users/lukasz/workspace.kds/WeatherStation/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


