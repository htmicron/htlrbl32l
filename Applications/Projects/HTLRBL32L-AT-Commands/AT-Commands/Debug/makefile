################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/sx126x/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/region/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/Utils/subdir.mk
-include HTLRBL32L-SDK/Drivers/Peripherals_Drivers/src/subdir.mk
-include HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Source/subdir.mk
-include AT_API/UART_API/Src/subdir.mk
-include AT_API/LORA_API/Src/subdir.mk
-include AT_API/AT_App/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
POST_BUILD_OBJCOPY += \
AT-Commands-WiSE.hex \

POST_BUILD_PRINT_SIZE += \
elf-size \


# All Target
all: AT-Commands-WiSE.elf secondary-outputs

# Tool invocations
AT-Commands-WiSE.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -nostartfiles -nodefaultlibs -Wl,--gc-sections -Wl,-Map="AT-Commands-WiSE.map" -T"../HTLRBL32L.ld" -Wl,--cref --specs=nano.specs -o "AT-Commands-WiSE.elf"  -Wl,--start-group @"objects.list" $(USER_OBJS) $(LIBS) -lm -lc  -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

AT-Commands-WiSE.hex: AT-Commands-WiSE.elf
	@echo 'Invoking: Generate binary'
	arm-none-eabi-objcopy -O ihex "AT-Commands-WiSE.elf"  "AT-Commands-WiSE.hex"
	@echo 'Finished building: $@'
	@echo ' '

elf-size: AT-Commands-WiSE.elf
	@echo 'Invoking: Print Size'
	arm-none-eabi-size -B "AT-Commands-WiSE.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(POST_BUILD_OBJCOPY)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(POST_BUILD_PRINT_SIZE)$(C_DEPS) AT-Commands-WiSE.elf AT-Commands-WiSE.bin *.map
	-@echo ' '

secondary-outputs: $(POST_BUILD_OBJCOPY) $(POST_BUILD_PRINT_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
