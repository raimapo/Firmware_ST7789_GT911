################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/extra/widgets/calendar/lv_calendar.c \
../Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
../Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c 

C_DEPS += \
./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar.d \
./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.d \
./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.d 

OBJS += \
./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar.o \
./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.o \
./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/extra/widgets/calendar/%.o Drivers/lvgl/src/extra/widgets/calendar/%.su Drivers/lvgl/src/extra/widgets/calendar/%.cyclo: ../Drivers/lvgl/src/extra/widgets/calendar/%.c Drivers/lvgl/src/extra/widgets/calendar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/UI -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/lvgl -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-calendar

clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-calendar:
	-$(RM) ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar.cyclo ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar.d ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar.o ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar.su ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.cyclo ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.d ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.o ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.su ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.cyclo ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.d ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.o ./Drivers/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-calendar

