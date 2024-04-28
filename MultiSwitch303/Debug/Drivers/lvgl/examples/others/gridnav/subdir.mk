################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_1.c \
../Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_2.c \
../Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_3.c \
../Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_4.c 

C_DEPS += \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_1.d \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_2.d \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_3.d \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_4.d 

OBJS += \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_1.o \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_2.o \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_3.o \
./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_4.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/examples/others/gridnav/%.o Drivers/lvgl/examples/others/gridnav/%.su Drivers/lvgl/examples/others/gridnav/%.cyclo: ../Drivers/lvgl/examples/others/gridnav/%.c Drivers/lvgl/examples/others/gridnav/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/UI -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/lvgl -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-examples-2f-others-2f-gridnav

clean-Drivers-2f-lvgl-2f-examples-2f-others-2f-gridnav:
	-$(RM) ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_1.cyclo ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_1.d ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_1.o ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_1.su ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_2.cyclo ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_2.d ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_2.o ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_2.su ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_3.cyclo ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_3.d ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_3.o ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_3.su ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_4.cyclo ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_4.d ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_4.o ./Drivers/lvgl/examples/others/gridnav/lv_example_gridnav_4.su

.PHONY: clean-Drivers-2f-lvgl-2f-examples-2f-others-2f-gridnav

