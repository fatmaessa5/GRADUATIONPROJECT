################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/USART_Driver_V1/subdir.mk
-include MCAL/Timer0_Driver_V5/subdir.mk
-include MCAL/SPI_driver/subdir.mk
-include MCAL/EXTI_Driver_V3/subdir.mk
-include MCAL/DIO_V2/subdir.mk
-include HAL/MCP2515_driver_V2/subdir.mk
-include HAL/LED_Handler_V1/subdir.mk
-include HAL/LCD_Handler_V2/subdir.mk
-include HAL/IR_Remote_V2/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Interfacing_Node.lss \

FLASH_IMAGE += \
Interfacing_Node.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Interfacing_Node.elf secondary-outputs

# Tool invocations
Interfacing_Node.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Interfacing_Node.map -mmcu=atmega32 -o "Interfacing_Node.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Interfacing_Node.lss: Interfacing_Node.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Interfacing_Node.elf  >"Interfacing_Node.lss"
	@echo 'Finished building: $@'
	@echo ' '

Interfacing_Node.hex: Interfacing_Node.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Interfacing_Node.elf  "Interfacing_Node.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Interfacing_Node.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Interfacing_Node.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Interfacing_Node.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
