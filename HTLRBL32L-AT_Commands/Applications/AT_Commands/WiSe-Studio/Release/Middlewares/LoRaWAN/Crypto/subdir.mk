################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/aes.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/cmac.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/soft-se.c 

OBJS += \
./Middlewares/LoRaWAN/Crypto/aes.o \
./Middlewares/LoRaWAN/Crypto/cmac.o \
./Middlewares/LoRaWAN/Crypto/soft-se.o 

C_DEPS += \
./Middlewares/LoRaWAN/Crypto/aes.d \
./Middlewares/LoRaWAN/Crypto/cmac.d \
./Middlewares/LoRaWAN/Crypto/soft-se.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/LoRaWAN/Crypto/aes.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/aes.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Crypto/cmac.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/cmac.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Crypto/soft-se.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/soft-se.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


