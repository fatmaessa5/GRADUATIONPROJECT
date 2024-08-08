################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/USART_Driver_V1/subdir.mk
-include MCAL/SPI_driver/subdir.mk
-include MCAL/EXTI_Driver_V3/subdir.mk
-include MCAL/DIO_V2/subdir.mk
-include HAL/MCP2515_driver/subdir.mk
-include HAL/LCD_Handler_V2/subdir.mk
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
Control_Node.lss \

FLASH_IMAGE += \
Control_Node.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Control_Node.elf secondary-outputs

# Tool invocations
Control_Node.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Control_Node.map -mmcu=atmega32 -o "Control_Node.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Control_Node.lss: Control_Node.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Control_Node.elf  >"Control_Node.lss"
	@echo 'Finished building: $@'
	@echo ' '

Control_Node.hex: Control_Node.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Control_Node.elf  "Control_Node.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Control_Node.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Control_Node.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Control_Node.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
