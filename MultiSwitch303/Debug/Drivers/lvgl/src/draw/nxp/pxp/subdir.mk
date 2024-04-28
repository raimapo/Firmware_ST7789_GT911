################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.c \
../Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
../Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
../Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c 

C_DEPS += \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.d \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d 

OBJS += \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.o \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/draw/nxp/pxp/%.o Drivers/lvgl/src/draw/nxp/pxp/%.su Drivers/lvgl/src/draw/nxp/pxp/%.cyclo: ../Drivers/lvgl/src/draw/nxp/pxp/%.c Drivers/lvgl/src/draw/nxp/pxp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/UI -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/lvgl -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp:
	-$(RM) ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.su ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.su ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.su ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

