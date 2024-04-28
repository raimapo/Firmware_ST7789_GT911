################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/examples/others/msg/lv_example_msg_1.c \
../Drivers/lvgl/examples/others/msg/lv_example_msg_2.c \
../Drivers/lvgl/examples/others/msg/lv_example_msg_3.c 

C_DEPS += \
./Drivers/lvgl/examples/others/msg/lv_example_msg_1.d \
./Drivers/lvgl/examples/others/msg/lv_example_msg_2.d \
./Drivers/lvgl/examples/others/msg/lv_example_msg_3.d 

OBJS += \
./Drivers/lvgl/examples/others/msg/lv_example_msg_1.o \
./Drivers/lvgl/examples/others/msg/lv_example_msg_2.o \
./Drivers/lvgl/examples/others/msg/lv_example_msg_3.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/examples/others/msg/%.o Drivers/lvgl/examples/others/msg/%.su Drivers/lvgl/examples/others/msg/%.cyclo: ../Drivers/lvgl/examples/others/msg/%.c Drivers/lvgl/examples/others/msg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/UI -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/lvgl -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-examples-2f-others-2f-msg

clean-Drivers-2f-lvgl-2f-examples-2f-others-2f-msg:
	-$(RM) ./Drivers/lvgl/examples/others/msg/lv_example_msg_1.cyclo ./Drivers/lvgl/examples/others/msg/lv_example_msg_1.d ./Drivers/lvgl/examples/others/msg/lv_example_msg_1.o ./Drivers/lvgl/examples/others/msg/lv_example_msg_1.su ./Drivers/lvgl/examples/others/msg/lv_example_msg_2.cyclo ./Drivers/lvgl/examples/others/msg/lv_example_msg_2.d ./Drivers/lvgl/examples/others/msg/lv_example_msg_2.o ./Drivers/lvgl/examples/others/msg/lv_example_msg_2.su ./Drivers/lvgl/examples/others/msg/lv_example_msg_3.cyclo ./Drivers/lvgl/examples/others/msg/lv_example_msg_3.d ./Drivers/lvgl/examples/others/msg/lv_example_msg_3.o ./Drivers/lvgl/examples/others/msg/lv_example_msg_3.su

.PHONY: clean-Drivers-2f-lvgl-2f-examples-2f-others-2f-msg

