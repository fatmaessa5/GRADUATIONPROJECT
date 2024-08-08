/*
 * TIMER0_Private.h
 *
 *  Created on: Dec 21, 2022
 *      Author: musta
 */

#ifndef MCAL_T0PWM_DRIVER_V1_TIMER0_PRIVATE_H_
#define MCAL_T0PWM_DRIVER_V1_TIMER0_PRIVATE_H_

/*
 * Use these configurations in the configuration file to set the mode of the timer
 */
#define NORMAL_MODE						0
#define PHASE_CORRECT_PWM_MODE			1
#define CTC_MODE						2
#define FAST_PWM_MODE					3

/*
 * TIMER0 Registers
 */
#define TIMER0_TCCR0					(*(volatile u8 *)(0x53))
#define TIMER0_TCNT0					(*(volatile u8 *)(0x52))
#define TIMER0_OCR0						(*(volatile u8 *)(0x5C))
#define TIMER0_DDRB						(*(volatile u8 *)(0x37))
#define TIMER0_TCNT0					(*(volatile u8 *)(0x52))

#endif /* MCAL_T0PWM_DRIVER_V1_TIMER0_PRIVATE_H_ */
