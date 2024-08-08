/*
 * EXTI_reg.h
 *
 *  Created on: Sep 30, 2021
 *      Author: Mostafa
 */

#ifndef MCAL_EXTI_DRIVER_V3_EXTI_REG_H_
#define MCAL_EXTI_DRIVER_V3_EXTI_REG_H_

#define EXTI_SREG_REG     *((volatile u8 *)0x5f)
#define EXTI_GICR_REG     *((volatile u8 *)0x5B)
#define EXTI_GIFR_REG     *((volatile u8 *)0x5A)
#define EXTI_MCUCR_REG    *((volatile u8 *)0x55)
#define EXTI_MCUCSR_REG   *((volatile u8 *)0x54)

//PORTB REGS
#define EXTI_DDRB_REG *(volatile u8 *)0x37
#define EXTI_PORTB_REG *(volatile u8 *)0x38
#define EXTI_PINB_REG *(volatile u8 *)0x36

//PORTD REGS
#define EXTI_DDRD_REG *(volatile u8 *)0x31
#define EXTI_PORTD_REG *(volatile u8 *)0x32
#define EXTI_PIND_REG *(volatile u8 *)0x30


#endif /* MCAL_EXTI_DRIVER_V3_EXTI_REG_H_ */
