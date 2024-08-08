/*
 * TIMER2_Private.h
 *
 *  Created on: Jul 5, 2023
 *      Author: musta
 */

#ifndef MCAL_T2PWM_DRIVER_V1_TIMER2_PRIVATE_H_
#define MCAL_T2PWM_DRIVER_V1_TIMER2_PRIVATE_H_


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
#define TIMER2_TCCR2					(*(volatile u8 *)(0x45))
#define TIMER2_TCNT2					(*(volatile u8 *)(0x44))
#define TIMER2_OCR2						(*(volatile u8 *)(0x43))
#define TIMER2_DDRD						(*(volatile u8 *)(0x31))

#endif /* MCAL_T2PWM_DRIVER_V1_TIMER2_PRIVATE_H_ */
