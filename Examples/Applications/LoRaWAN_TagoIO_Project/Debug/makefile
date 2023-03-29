################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include HTLRBL32L-SDK/Middlewares/ST/hal/Src/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/sx126x/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/region/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/subdir.mk
-include HTLRBL32L-SDK/LoRaWAN/Utils/subdir.mk
-include HTLRBL32L-SDK/Drivers/Peripherals_Drivers/src/subdir.mk
-include HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Source/subdir.mk
-include HTLRBL32L-SDK/Drivers/BSP/STEVAL-IDB011V1/Src/subdir.mk
-include HTLRBL32L-SDK/Drivers/BSP/Components/lsm6dsox_STdC/driver/subdir.mk
-include HTLRBL32L-SDK/Drivers/BSP/Components/lps22hh_STdC/driver/subdir.mk
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
LoRaWAN_TagoIO_Project.bin \

POST_BUILD_PRINT_SIZE += \
elf-size \


# All Target
all: LoRaWAN_TagoIO_Project.elf secondary-outputs

# Tool invocations
LoRaWAN_TagoIO_Project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Wl,--gc-sections -Wl,-Map="LoRaWAN_TagoIO_Project.map" -T"../HTLRBL32L.ld" -L"C:\Users\christian.lehmen\Desktop\git\public\htlrbl32l\Examples\HTLRBL32L-SDK\Libraries" -o "LoRaWAN_TagoIO_Project.elf"  -Wl,--start-group @"objects.list" $(USER_OBJS) $(LIBS) -lm -lc  -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

LoRaWAN_TagoIO_Project.bin: LoRaWAN_TagoIO_Project.elf
	@echo 'Invoking: Generate binary'
	arm-none-eabi-objcopy -O binary "LoRaWAN_TagoIO_Project.elf"  "LoRaWAN_TagoIO_Project.bin"
	@echo 'Finished building: $@'
	@echo ' '

elf-size: LoRaWAN_TagoIO_Project.elf
	@echo 'Invoking: Print Size'
	arm-none-eabi-size -B "LoRaWAN_TagoIO_Project.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(POST_BUILD_OBJCOPY)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(POST_BUILD_PRINT_SIZE)$(C_DEPS) LoRaWAN_TagoIO_Project.elf LoRaWAN_TagoIO_Project.bin *.map
	-@echo ' '

secondary-outputs: $(POST_BUILD_OBJCOPY) $(POST_BUILD_PRINT_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
