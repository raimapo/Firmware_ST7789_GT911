################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/examples/widgets/animimg/lv_example_animimg_1.c 

C_DEPS += \
./Drivers/lvgl/examples/widgets/animimg/lv_example_animimg_1.d 

OBJS += \
./Drivers/lvgl/examples/widgets/animimg/lv_example_animimg_1.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/examples/widgets/animimg/%.o Drivers/lvgl/examples/widgets/animimg/%.su Drivers/lvgl/examples/widgets/animimg/%.cyclo: ../Drivers/lvgl/examples/widgets/animimg/%.c Drivers/lvgl/examples/widgets/animimg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/UI -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/lvgl -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-examples-2f-widgets-2f-animimg

clean-Drivers-2f-lvgl-2f-examples-2f-widgets-2f-animimg:
	-$(RM) ./Drivers/lvgl/examples/widgets/animimg/lv_example_animimg_1.cyclo ./Drivers/lvgl/examples/widgets/animimg/lv_example_animimg_1.d ./Drivers/lvgl/examples/widgets/animimg/lv_example_animimg_1.o ./Drivers/lvgl/examples/widgets/animimg/lv_example_animimg_1.su

.PHONY: clean-Drivers-2f-lvgl-2f-examples-2f-widgets-2f-animimg

