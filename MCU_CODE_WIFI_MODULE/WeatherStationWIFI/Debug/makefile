################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/TI/Energia/energia-0101E0014/hardware/tools/lm4f

ORDERED_OBJS += \
"./aJson/utility/stringbuffer.o" \
"./CC3000/utility/board.o" \
"./CC3000/utility/cc3000_common.o" \
"./CC3000/utility/evnt_handler.o" \
"./CC3000/utility/hci.o" \
"./CC3000/utility/netapp.o" \
"./CC3000/utility/nvmem.o" \
"./CC3000/utility/patch.o" \
"./CC3000/utility/security.o" \
"./CC3000/utility/SimplelinkWifi.o" \
"./CC3000/utility/socket.o" \
"./CC3000/utility/tcp.o" \
"./CC3000/utility/wlan.o" \
"./aJson/aJSON.o" \
"./CC3000/TCPclient.o" \
"./CC3000/TCPserver.o" \
"./CC3000/utility/spi.o" \
"./CC3000/WiFi.o" \
"./CC3000/WiFiUdp.o" \
"./dataParser.o" \
"./RF22/RF22.o" \
"./RF22/RF22Datagram.o" \
"./RF22/RF22ReliableDatagram.o" \
"./SPI/HardwareSPI.o" \
"./SPI/SPI.o" \
"./WeatherStationWIFI.o" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-Wl,-T"C:/TI/Energia/energia-0101E0014/hardware/lm4f/cores/lm4f/lm4fcpp_blizzard.ld" \
-l"c" \
-l"lplm4f120h5qr_core" \
-l"m" \
-l"gcc" \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include aJson/utility/subdir_vars.mk
-include aJson/subdir_vars.mk
-include SPI/subdir_vars.mk
-include RF22/subdir_vars.mk
-include CC3000/utility/subdir_vars.mk
-include CC3000/subdir_vars.mk
-include subdir_rules.mk
-include aJson/utility/subdir_rules.mk
-include aJson/subdir_rules.mk
-include SPI/subdir_rules.mk
-include RF22/subdir_rules.mk
-include CC3000/utility/subdir_rules.mk
-include CC3000/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
WeatherStationWIFI.out \

EXE_OUTPUTS__QUOTED += \
"WeatherStationWIFI.out" \

BIN_OUTPUTS += \
WeatherStationWIFI.hex \

BIN_OUTPUTS__QUOTED += \
"WeatherStationWIFI.hex" \


# All Target
all: WeatherStationWIFI.out

dependents:
	-cd C:/TI/Energia/energiaWorkspace/lplm4f120h5qr_core/Debug && $(MAKE) clean all

# Tool invocations
WeatherStationWIFI.out: $(OBJS) $(GEN_CMDS) C:/TI/Energia/energiaWorkspace/lplm4f120h5qr_core/Debug/liblplm4f120h5qr_core.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Linker'
	"C:/TI/Energia/energia-0101E0014/hardware/tools/lm4f/bin/arm-none-eabi-gcc.exe" -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-rtti -fno-exceptions -DF_CPU=80000000L -DARDUINO=101 -DENERGIA=12 -Os -ffunction-sections -fdata-sections -fsingle-precision-constant -g -gstrict-dwarf -Wall -Wl,-Map,"WeatherStationWIFI.map" --entry ResetISR -nostartfiles -Wl,--gc-sections -L"C:/TI/Energia/energiaWorkspace/lplm4f120h5qr_core/Debug" -o"WeatherStationWIFI.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

WeatherStationWIFI.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: GNU Objcopy Utility'
	"C:/TI/Energia/energia-0101E0014/hardware/tools/lm4f/bin/arm-none-eabi-objcopy.exe"  $(EXE_OUTPUTS__QUOTED) "WeatherStationWIFI.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "WeatherStationWIFI.d" "dataParser.d" "aJson\aJSON.d" "SPI\HardwareSPI.d" "SPI\SPI.d" "RF22\RF22.d" "RF22\RF22Datagram.d" "RF22\RF22ReliableDatagram.d" "CC3000\utility\spi.d" "CC3000\TCPclient.d" "CC3000\TCPserver.d" "CC3000\WiFi.d" "CC3000\WiFiUdp.d" 
	-$(RM) "aJson\utility\stringbuffer.d" "CC3000\utility\SimplelinkWifi.d" "CC3000\utility\board.d" "CC3000\utility\cc3000_common.d" "CC3000\utility\evnt_handler.d" "CC3000\utility\hci.d" "CC3000\utility\netapp.d" "CC3000\utility\nvmem.d" "CC3000\utility\patch.d" "CC3000\utility\security.d" "CC3000\utility\socket.d" "CC3000\utility\tcp.d" "CC3000\utility\wlan.d" 
	-$(RM) "WeatherStationWIFI.o" "dataParser.o" "aJson\utility\stringbuffer.o" "aJson\aJSON.o" "SPI\HardwareSPI.o" "SPI\SPI.o" "RF22\RF22.o" "RF22\RF22Datagram.o" "RF22\RF22ReliableDatagram.o" "CC3000\utility\SimplelinkWifi.o" "CC3000\utility\board.o" "CC3000\utility\cc3000_common.o" "CC3000\utility\evnt_handler.o" "CC3000\utility\hci.o" "CC3000\utility\netapp.o" "CC3000\utility\nvmem.o" "CC3000\utility\patch.o" "CC3000\utility\security.o" "CC3000\utility\socket.o" "CC3000\utility\spi.o" "CC3000\utility\tcp.o" "CC3000\utility\wlan.o" "CC3000\TCPclient.o" "CC3000\TCPserver.o" "CC3000\WiFi.o" "CC3000\WiFiUdp.o" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/TI/Energia/energia-0101E0014/hardware/tools/lm4f/bin/arm-none-eabi-objcopy -O binary WeatherStationWIFI.out WeatherStationWIFI.bin
	-C:/TI/Energia/energia-0101E0014/hardware/tools/lm4f/bin/arm-none-eabi-size.exe  WeatherStationWIFI.out
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/TI/Energia/energiaWorkspace/lplm4f120h5qr_core/Debug/liblplm4f120h5qr_core.a:

-include ../makefile.targets

