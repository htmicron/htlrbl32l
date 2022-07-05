################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/HT_push_button.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/bluenrg_lp_it.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/gpio.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/lorawan_setup.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/main.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/rtc.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/spi.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/syscalls.c \
C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/uart.c 

OBJS += \
./Application/HT_push_button.o \
./Application/bluenrg_lp_it.o \
./Application/gpio.o \
./Application/lorawan_setup.o \
./Application/main.o \
./Application/rtc.o \
./Application/spi.o \
./Application/syscalls.o \
./Application/uart.o 

C_DEPS += \
./Application/HT_push_button.d \
./Application/bluenrg_lp_it.d \
./Application/gpio.d \
./Application/lorawan_setup.d \
./Application/main.d \
./Application/rtc.d \
./Application/spi.d \
./Application/syscalls.d \
./Application/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/HT_push_button.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/HT_push_button.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/bluenrg_lp_it.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/bluenrg_lp_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/gpio.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/lorawan_setup.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/lorawan_setup.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/main.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/rtc.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/spi.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/syscalls.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/syscalls.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/uart.o: C:/Users/hendrick.goncalves/Documents/EVB_Project/Repository/work_hendrick/HTLRBL32L_Applications/Applications/PushButton_LoRaWAN/Src/uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -ffunction-sections -fdata-sections -g3 -std=gnu99 -DDEFAULT_REGION=5 -DPUSH_BUTTON_APP -DUSE_FULL_LL_DRIVER -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_LS_RO -I../../Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Core/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Crypto/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/lorawan_specifics/Mac/Region/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/SX126X/Inc -I../../../../HTLRBL32L-SDK/LoRaWAN/Utils/Inc -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Device/ST/BlueNRG_LP/Include -I../../../../HTLRBL32L-SDK/Drivers/CMSIS/Include -I../../../../HTLRBL32L-SDK/Drivers/Peripherals_Drivers/Inc -I../../../../HTLRBL32L-SDK/Middlewares/ST/hal/Inc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


