################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/extra/layouts/flex/lv_flex.c 

C_DEPS += \
./Drivers/lvgl/src/extra/layouts/flex/lv_flex.d 

OBJS += \
./Drivers/lvgl/src/extra/layouts/flex/lv_flex.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/extra/layouts/flex/%.o Drivers/lvgl/src/extra/layouts/flex/%.su Drivers/lvgl/src/extra/layouts/flex/%.cyclo: ../Drivers/lvgl/src/extra/layouts/flex/%.c Drivers/lvgl/src/extra/layouts/flex/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/UI -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/lvgl -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-layouts-2f-flex

clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-layouts-2f-flex:
	-$(RM) ./Drivers/lvgl/src/extra/layouts/flex/lv_flex.cyclo ./Drivers/lvgl/src/extra/layouts/flex/lv_flex.d ./Drivers/lvgl/src/extra/layouts/flex/lv_flex.o ./Drivers/lvgl/src/extra/layouts/flex/lv_flex.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-layouts-2f-flex

