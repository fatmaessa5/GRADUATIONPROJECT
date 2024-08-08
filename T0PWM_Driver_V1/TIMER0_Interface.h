/*
 * TIMER0_Init.h
 *
 *  Created on: Dec 21, 2022
 *      Author: musta
 */

#ifndef MCAL_T0PWM_DRIVER_V1_TIMER0_INTERFACE_H_
#define MCAL_T0PWM_DRIVER_V1_TIMER0_INTERFACE_H_

/*********************************************** Declarations *******************************************/

/*
 * This enumerator contains the Output Compare, fast_PWM options.
 */
typedef enum{
	TIMER0_FASTPWM_OCMODE_t_OC0_Disconnected								= 0,
	TIMER0_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top			= 2,
	TIMER0_FASTPWM_OCMODE_t_Set_On_Compare_Match_And_Clear_At_Top			= 3
}TIMER0_FASTPWM_OCMODE_t;

/*
 * This enumerator contains the Prescaler options.
 */
typedef enum{
	TIMER0_CLOCK_SOURCE_t_SystemClock_With_No_Prescaler								= 1,
	TIMER0_CLOCK_SOURCE_t_SystemClock_With_8_Prescaler								,
	TIMER0_CLOCK_SOURCE_t_SystemClock_With_64_Prescaler								,
	TIMER0_CLOCK_SOURCE_t_SystemClock_With_256_Prescaler							,
	TIMER0_CLOCK_SOURCE_t_SystemClock_With_1024_Prescaler							,
	TIMER0_CLOCK_SOURCE_t_External_On_Falling_Edge									,
	TIMER0_CLOCK_SOURCE_t_External_On_Rising_Edge
}TIMER0_CLOCK_SOURCE_t;
/********************************************************************************************************/

/******************************************* Functions Prototypes ***************************************/

/********************************************************************************************************/
/*
 * Use this function to initialize the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_Init(void);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the compare match output Mode of the fast PWM mode.
 * it takes:
 * 			- the Output Compare, Fast_Pwm option (TIMER0_FASTPWM_OCMODE_t)
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_FastPWM_SetOCMode(TIMER0_FASTPWM_OCMODE_t Copy_PWM_OCMode);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the timer clock source.
 * it takes:
 * 			- The clock source (TIMER0_CLOCK_SOURCE_t)
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_SetClockSource(TIMER0_CLOCK_SOURCE_t Copy_ClockSource);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to start the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_StartTimer(void);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to stop the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_StopTimer(void);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the duty cycle.
 *	it takes:
 *			- the duty cycle (u8)
 *	it returns:
 *	  		- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_FastPWM_SetDutyCycle(u8 Copy_u8_DutyCycle);
/********************************************************************************************************/

/********************************************************************************************************/

#endif /* MCAL_T0PWM_DRIVER_V1_TIMER0_INTERFACE_H_ */
