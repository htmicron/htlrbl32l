################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/blue_unit_conversion.s \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/context_switch.s \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal_memcpy.s 

C_SRCS += \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/clock.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/fifo.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/gp_timer.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/hal_miscutil.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/miscutil.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal.c 

OBJS += \
./Middlewares/HAL/blue_unit_conversion.o \
./Middlewares/HAL/clock.o \
./Middlewares/HAL/context_switch.o \
./Middlewares/HAL/fifo.o \
./Middlewares/HAL/gp_timer.o \
./Middlewares/HAL/hal_miscutil.o \
./Middlewares/HAL/miscutil.o \
./Middlewares/HAL/osal.o \
./Middlewares/HAL/osal_memcpy.o 

S_DEPS += \
./Middlewares/HAL/blue_unit_conversion.d \
./Middlewares/HAL/context_switch.d \
./Middlewares/HAL/osal_memcpy.d 

C_DEPS += \
./Middlewares/HAL/clock.d \
./Middlewares/HAL/fifo.d \
./Middlewares/HAL/gp_timer.d \
./Middlewares/HAL/hal_miscutil.d \
./Middlewares/HAL/miscutil.d \
./Middlewares/HAL/osal.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/HAL/blue_unit_conversion.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/blue_unit_conversion.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/clock.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/context_switch.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/context_switch.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/fifo.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/fifo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/gp_timer.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/gp_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/hal_miscutil.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/hal_miscutil.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/miscutil.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/miscutil.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/osal.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DBLE_STACK_BASIC_CONF -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../HT_BLE_API/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/RNGMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/PKAMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/AESMGR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLECNTR/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/NVMDB/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/AES -I../../../../HTLRBL32L-SDK/Middlewares/ST/cryptolib/inc/Common -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/layers_inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/BLE_Application/Profiles/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/Bluetooth_LE/inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/osal_memcpy.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal_memcpy.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


