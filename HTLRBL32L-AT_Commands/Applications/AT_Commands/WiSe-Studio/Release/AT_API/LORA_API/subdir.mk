################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/AT_API/LORA_API/Src/HT_atlora_api.c 

OBJS += \
./AT_API/LORA_API/HT_atlora_api.o 

C_DEPS += \
./AT_API/LORA_API/HT_atlora_api.d 


# Each subdirectory must supply rules for building sources it contributes
AT_API/LORA_API/HT_atlora_api.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/AT_API/LORA_API/Src/HT_atlora_api.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


