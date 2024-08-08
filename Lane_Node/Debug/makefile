################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/Timer0_Driver_V4/subdir.mk
-include MCAL/SPI_driver/subdir.mk
-include MCAL/EXTI_Driver_V2/subdir.mk
-include MCAL/DIO_V1/subdir.mk
-include HAL/MCP2515_driver/subdir.mk
-include HAL/LED_Handler_V1/subdir.mk
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
Lane_Node.lss \

FLASH_IMAGE += \
Lane_Node.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Lane_Node.elf secondary-outputs

# Tool invocations
Lane_Node.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Lane_Node.map -mmcu=atmega32 -o "Lane_Node.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Lane_Node.lss: Lane_Node.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Lane_Node.elf  >"Lane_Node.lss"
	@echo 'Finished building: $@'
	@echo ' '

Lane_Node.hex: Lane_Node.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Lane_Node.elf  "Lane_Node.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Lane_Node.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Lane_Node.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Lane_Node.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
