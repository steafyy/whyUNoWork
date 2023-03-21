################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/ft6x06/ls016b8uy/ls016b8uy.c 

OBJS += \
./Drivers/Components/ft6x06/ls016b8uy/ls016b8uy.o 

C_DEPS += \
./Drivers/Components/ft6x06/ls016b8uy/ls016b8uy.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/ft6x06/ls016b8uy/%.o Drivers/Components/ft6x06/ls016b8uy/%.su: ../Drivers/Components/ft6x06/ls016b8uy/%.c Drivers/Components/ft6x06/ls016b8uy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP -I../Drivers/Fonts -I../Drivers/Components -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-ft6x06-2f-ls016b8uy

clean-Drivers-2f-Components-2f-ft6x06-2f-ls016b8uy:
	-$(RM) ./Drivers/Components/ft6x06/ls016b8uy/ls016b8uy.d ./Drivers/Components/ft6x06/ls016b8uy/ls016b8uy.o ./Drivers/Components/ft6x06/ls016b8uy/ls016b8uy.su

.PHONY: clean-Drivers-2f-Components-2f-ft6x06-2f-ls016b8uy

