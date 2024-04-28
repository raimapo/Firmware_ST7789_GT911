################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STemWin/GUIConf.c \
../Drivers/STemWin/GUIDRV_Template.c \
../Drivers/STemWin/GUI_X.c \
../Drivers/STemWin/LCDConf.c 

OBJS += \
./Drivers/STemWin/GUIConf.o \
./Drivers/STemWin/GUIDRV_Template.o \
./Drivers/STemWin/GUI_X.o \
./Drivers/STemWin/LCDConf.o 

C_DEPS += \
./Drivers/STemWin/GUIConf.d \
./Drivers/STemWin/GUIDRV_Template.d \
./Drivers/STemWin/GUI_X.d \
./Drivers/STemWin/LCDConf.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STemWin/%.o Drivers/STemWin/%.su Drivers/STemWin/%.cyclo: ../Drivers/STemWin/%.c Drivers/STemWin/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Raimondas/Desktop/STM32CubeMX_and_STemWin-master/emWin/STemWin" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-STemWin

clean-Drivers-2f-STemWin:
	-$(RM) ./Drivers/STemWin/GUIConf.cyclo ./Drivers/STemWin/GUIConf.d ./Drivers/STemWin/GUIConf.o ./Drivers/STemWin/GUIConf.su ./Drivers/STemWin/GUIDRV_Template.cyclo ./Drivers/STemWin/GUIDRV_Template.d ./Drivers/STemWin/GUIDRV_Template.o ./Drivers/STemWin/GUIDRV_Template.su ./Drivers/STemWin/GUI_X.cyclo ./Drivers/STemWin/GUI_X.d ./Drivers/STemWin/GUI_X.o ./Drivers/STemWin/GUI_X.su ./Drivers/STemWin/LCDConf.cyclo ./Drivers/STemWin/LCDConf.d ./Drivers/STemWin/LCDConf.o ./Drivers/STemWin/LCDConf.su

.PHONY: clean-Drivers-2f-STemWin

