################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/DIO_V1/DIO_prg.c 

OBJS += \
./MCAL/DIO_V1/DIO_prg.o 

C_DEPS += \
./MCAL/DIO_V1/DIO_prg.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/DIO_V1/%.o: ../MCAL/DIO_V1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"F:\Educational\Graduation Project\AVR_Workspace\Lane_Node_RTOS\FreeRTOS\Inc" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


