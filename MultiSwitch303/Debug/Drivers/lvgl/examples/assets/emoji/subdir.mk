################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/examples/assets/emoji/img_emoji_F617.c 

C_DEPS += \
./Drivers/lvgl/examples/assets/emoji/img_emoji_F617.d 

OBJS += \
./Drivers/lvgl/examples/assets/emoji/img_emoji_F617.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/examples/assets/emoji/%.o Drivers/lvgl/examples/assets/emoji/%.su Drivers/lvgl/examples/assets/emoji/%.cyclo: ../Drivers/lvgl/examples/assets/emoji/%.c Drivers/lvgl/examples/assets/emoji/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/UI -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/lvgl -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-examples-2f-assets-2f-emoji

clean-Drivers-2f-lvgl-2f-examples-2f-assets-2f-emoji:
	-$(RM) ./Drivers/lvgl/examples/assets/emoji/img_emoji_F617.cyclo ./Drivers/lvgl/examples/assets/emoji/img_emoji_F617.d ./Drivers/lvgl/examples/assets/emoji/img_emoji_F617.o ./Drivers/lvgl/examples/assets/emoji/img_emoji_F617.su

.PHONY: clean-Drivers-2f-lvgl-2f-examples-2f-assets-2f-emoji

