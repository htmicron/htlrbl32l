################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/aes.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/cmac.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/soft-se.c 

OBJS += \
./Middlewares/LoRaWAN/Crypto/aes.o \
./Middlewares/LoRaWAN/Crypto/cmac.o \
./Middlewares/LoRaWAN/Crypto/soft-se.o 

C_DEPS += \
./Middlewares/LoRaWAN/Crypto/aes.d \
./Middlewares/LoRaWAN/Crypto/cmac.d \
./Middlewares/LoRaWAN/Crypto/soft-se.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/LoRaWAN/Crypto/aes.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/aes.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Crypto/cmac.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/cmac.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/Crypto/soft-se.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Src/soft-se.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


