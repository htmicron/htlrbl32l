################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/trace/subdir.mk
-include Utilities/timer/subdir.mk
-include Utilities/sequencer/subdir.mk
-include Utilities/misc/subdir.mk
-include Utilities/lpm/subdir.mk
-include Middlewares/Third_Party/SubGHz_Phy/sx126x/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/Utilities/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/Mac/Region/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/LmHandler/Packages/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/LmHandler/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/Crypto/subdir.mk
-include Middlewares/Third_Party/FullSDK/src/subdir.mk
-include HTLRBL32L-SDK/Drivers/Peripherals_Drivers/src/subdir.mk
-include HTLRBL32L-Acklio/SX1261DVK1BAS/subdir.mk
-include HTLRBL32L-Acklio/LoRaWAN/Target/subdir.mk
-include HTLRBL32L-Acklio/LoRaWAN/App/subdir.mk
-include HTLRBL32L-Acklio/Core/Src/subdir.mk
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
HTLRBL32L-ACKLIO.hex \

POST_BUILD_PRINT_SIZE += \
elf-size \


# All Target
all: HTLRBL32L-ACKLIO.elf secondary-outputs

# Tool invocations
HTLRBL32L-ACKLIO.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Wl,--gc-sections -Wl,-Map="HTLRBL32L-ACKLIO.map" -T"C:/Users/christian.lehmen/Documents/HTLRBL32L-ACKLIO/wise-project/LinkerScript.ld" -o "HTLRBL32L-ACKLIO.elf"  -Wl,--start-group @"objects.list" $(USER_OBJS) $(LIBS) -lm -lc  -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

HTLRBL32L-ACKLIO.hex: HTLRBL32L-ACKLIO.elf
	@echo 'Invoking: Generate binary'
	arm-none-eabi-objcopy -O ihex "HTLRBL32L-ACKLIO.elf"  "HTLRBL32L-ACKLIO.hex"
	@echo 'Finished building: $@'
	@echo ' '

elf-size: HTLRBL32L-ACKLIO.elf
	@echo 'Invoking: Print Size'
	arm-none-eabi-size -B "HTLRBL32L-ACKLIO.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(POST_BUILD_OBJCOPY)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(POST_BUILD_PRINT_SIZE)$(C_DEPS) HTLRBL32L-ACKLIO.elf HTLRBL32L-ACKLIO.bin *.map
	-@echo ' '

secondary-outputs: $(POST_BUILD_OBJCOPY) $(POST_BUILD_PRINT_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
