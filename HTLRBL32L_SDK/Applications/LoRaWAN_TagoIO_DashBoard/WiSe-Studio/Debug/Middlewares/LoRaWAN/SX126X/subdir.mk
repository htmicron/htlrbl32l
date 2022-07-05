################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/SX126X/Src/radio.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/SX126X/Src/sx1262_interface.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/SX126X/Src/sx126x.c 

OBJS += \
./Middlewares/LoRaWAN/SX126X/radio.o \
./Middlewares/LoRaWAN/SX126X/sx1262_interface.o \
./Middlewares/LoRaWAN/SX126X/sx126x.o 

C_DEPS += \
./Middlewares/LoRaWAN/SX126X/radio.d \
./Middlewares/LoRaWAN/SX126X/sx1262_interface.d \
./Middlewares/LoRaWAN/SX126X/sx126x.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/LoRaWAN/SX126X/radio.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/SX126X/Src/radio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DLORAWAN_TAGOIO -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/SX126X/sx1262_interface.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/SX126X/Src/sx1262_interface.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DLORAWAN_TAGOIO -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/LoRaWAN/SX126X/sx126x.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/HTLRBL32L-SDK/LoRaWAN/SX126X/Src/sx126x.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DLORAWAN_TAGOIO -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


