################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/Region.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionAS923.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionAU915.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionCN470.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionCN779.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionCommon.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionEU433.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionEU868.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionIN865.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionKR920.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionRU864.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionUS915.c 

OBJS += \
./Middlewares/LoRaWAN/Region/Region.o \
./Middlewares/LoRaWAN/Region/RegionAS923.o \
./Middlewares/LoRaWAN/Region/RegionAU915.o \
./Middlewares/LoRaWAN/Region/RegionCN470.o \
./Middlewares/LoRaWAN/Region/RegionCN779.o \
./Middlewares/LoRaWAN/Region/RegionCommon.o \
./Middlewares/LoRaWAN/Region/RegionEU433.o \
./Middlewares/LoRaWAN/Region/RegionEU868.o \
./Middlewares/LoRaWAN/Region/RegionIN865.o \
./Middlewares/LoRaWAN/Region/RegionKR920.o \
./Middlewares/LoRaWAN/Region/RegionRU864.o \
./Middlewares/LoRaWAN/Region/RegionUS915.o 

C_DEPS += \
./Middlewares/LoRaWAN/Region/Region.d \
./Middlewares/LoRaWAN/Region/RegionAS923.d \
./Middlewares/LoRaWAN/Region/RegionAU915.d \
./Middlewares/LoRaWAN/Region/RegionCN470.d \
./Middlewares/LoRaWAN/Region/RegionCN779.d \
./Middlewares/LoRaWAN/Region/RegionCommon.d \
./Middlewares/LoRaWAN/Region/RegionEU433.d \
./Middlewares/LoRaWAN/Region/RegionEU868.d \
./Middlewares/LoRaWAN/Region/RegionIN865.d \
./Middlewares/LoRaWAN/Region/RegionKR920.d \
./Middlewares/LoRaWAN/Region/RegionRU864.d \
./Middlewares/LoRaWAN/Region/RegionUS915.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/LoRaWAN/Region/Region.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/Region.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionAS923.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionAS923.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionAU915.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionAU915.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionCN470.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionCN470.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionCN779.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionCN779.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionCommon.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionCommon.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionEU433.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionEU433.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionEU868.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionEU868.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionIN865.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionIN865.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionKR920.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionKR920.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionRU864.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionRU864.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Region/RegionUS915.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Src/RegionUS915.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


