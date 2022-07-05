################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/blue_unit_conversion.s \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/context_switch.s \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal_memcpy.s 

C_SRCS += \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/clock.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/fifo.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/gp_timer.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/hal_miscutil.c \
C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal.c 

OBJS += \
./Middlewares/HAL/blue_unit_conversion.o \
./Middlewares/HAL/clock.o \
./Middlewares/HAL/context_switch.o \
./Middlewares/HAL/fifo.o \
./Middlewares/HAL/gp_timer.o \
./Middlewares/HAL/hal_miscutil.o \
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
./Middlewares/HAL/osal.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/HAL/blue_unit_conversion.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/blue_unit_conversion.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/clock.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/context_switch.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/context_switch.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/fifo.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/fifo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/gp_timer.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/gp_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/hal_miscutil.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/hal_miscutil.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/osal.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -Os -g -DCONFIG_DEVICE_BLUENRG_LP -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/HAL/osal_memcpy.o: C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/HTLRBL32L-SDK/Middlewares/ST/hal/Src/osal_memcpy.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -I"C:/Users/rodrigo.madruga/Documents/LORA_BLE/HTLRBL32L_AT_WISE/HTLRBL32L_Applications/Applications/AT_Commands/WiSe-Studio/inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


