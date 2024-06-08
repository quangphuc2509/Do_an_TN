################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib_user/Src/begin.c \
../Lib_user/Src/body.c \
../Lib_user/Src/calculate_ARR.c \
../Lib_user/Src/convert_position.c \
../Lib_user/Src/define.c \
../Lib_user/Src/director.c \
../Lib_user/Src/exti_interrupt.c \
../Lib_user/Src/timer_interrupt.c \
../Lib_user/Src/uart_interrupt.c \
../Lib_user/Src/var.c 

OBJS += \
./Lib_user/Src/begin.o \
./Lib_user/Src/body.o \
./Lib_user/Src/calculate_ARR.o \
./Lib_user/Src/convert_position.o \
./Lib_user/Src/define.o \
./Lib_user/Src/director.o \
./Lib_user/Src/exti_interrupt.o \
./Lib_user/Src/timer_interrupt.o \
./Lib_user/Src/uart_interrupt.o \
./Lib_user/Src/var.o 

C_DEPS += \
./Lib_user/Src/begin.d \
./Lib_user/Src/body.d \
./Lib_user/Src/calculate_ARR.d \
./Lib_user/Src/convert_position.d \
./Lib_user/Src/define.d \
./Lib_user/Src/director.d \
./Lib_user/Src/exti_interrupt.d \
./Lib_user/Src/timer_interrupt.d \
./Lib_user/Src/uart_interrupt.d \
./Lib_user/Src/var.d 


# Each subdirectory must supply rules for building sources it contributes
Lib_user/Src/%.o Lib_user/Src/%.su: ../Lib_user/Src/%.c Lib_user/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"F:/STM32/testuart/Lib_user/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Lib_user-2f-Src

clean-Lib_user-2f-Src:
	-$(RM) ./Lib_user/Src/begin.d ./Lib_user/Src/begin.o ./Lib_user/Src/begin.su ./Lib_user/Src/body.d ./Lib_user/Src/body.o ./Lib_user/Src/body.su ./Lib_user/Src/calculate_ARR.d ./Lib_user/Src/calculate_ARR.o ./Lib_user/Src/calculate_ARR.su ./Lib_user/Src/convert_position.d ./Lib_user/Src/convert_position.o ./Lib_user/Src/convert_position.su ./Lib_user/Src/define.d ./Lib_user/Src/define.o ./Lib_user/Src/define.su ./Lib_user/Src/director.d ./Lib_user/Src/director.o ./Lib_user/Src/director.su ./Lib_user/Src/exti_interrupt.d ./Lib_user/Src/exti_interrupt.o ./Lib_user/Src/exti_interrupt.su ./Lib_user/Src/timer_interrupt.d ./Lib_user/Src/timer_interrupt.o ./Lib_user/Src/timer_interrupt.su ./Lib_user/Src/uart_interrupt.d ./Lib_user/Src/uart_interrupt.o ./Lib_user/Src/uart_interrupt.su ./Lib_user/Src/var.d ./Lib_user/Src/var.o ./Lib_user/Src/var.su

.PHONY: clean-Lib_user-2f-Src

