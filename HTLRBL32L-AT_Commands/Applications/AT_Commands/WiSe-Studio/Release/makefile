################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/LoRaWAN/Utils/subdir.mk
-include Middlewares/LoRaWAN/SX126X/subdir.mk
-include Middlewares/LoRaWAN/Region/subdir.mk
-include Middlewares/LoRaWAN/MAC/subdir.mk
-include Middlewares/LoRaWAN/Crypto/subdir.mk
-include Middlewares/LoRaWAN/Core/subdir.mk
-include Middlewares/HAL/subdir.mk
-include Drivers/Peripheral_Drivers/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/subdir.mk
-include AT_API/UART_API/subdir.mk
-include AT_API/LORA_API/subdir.mk
-include AT_API/AT_App/subdir.mk
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
HTLRBL32L-AT_commands.hex \

POST_BUILD_PRINT_SIZE += \
elf-size \


# All Target
all: HTLRBL32L-AT_commands.elf secondary-outputs

# Tool invocations
HTLRBL32L-AT_commands.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Wl,--gc-sections -Wl,-Map="HTLRBL32L-AT_commands.map" -T"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/LinkerScript.ld" -o "HTLRBL32L-AT_commands.elf"  -Wl,--start-group @"objects.list" $(USER_OBJS) $(LIBS) -lm -lc  -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

HTLRBL32L-AT_commands.hex: HTLRBL32L-AT_commands.elf
	@echo 'Invoking: Generate binary'
	arm-none-eabi-objcopy -O ihex "HTLRBL32L-AT_commands.elf"  "HTLRBL32L-AT_commands.hex"
	@echo 'Finished building: $@'
	@echo ' '

elf-size: HTLRBL32L-AT_commands.elf
	@echo 'Invoking: Print Size'
	arm-none-eabi-size -B "HTLRBL32L-AT_commands.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(POST_BUILD_OBJCOPY)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(POST_BUILD_PRINT_SIZE)$(C_DEPS) HTLRBL32L-AT_commands.elf HTLRBL32L-AT_commands.bin *.map
	-@echo ' '

secondary-outputs: $(POST_BUILD_OBJCOPY) $(POST_BUILD_PRINT_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
