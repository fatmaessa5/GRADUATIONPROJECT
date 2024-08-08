/*
 * TIMER2_Interface.h
 *
 *  Created on: Jul 5, 2023
 *      Author: musta
 */

#ifndef MCAL_T2PWM_DRIVER_V1_TIMER2_INTERFACE_H_
#define MCAL_T2PWM_DRIVER_V1_TIMER2_INTERFACE_H_

/*********************************************** Declarations *******************************************/

/*
 * This enumerator contains the Output Compare, fast_PWM options.
 */
typedef enum{
	TIMER2_FASTPWM_OCMODE_t_OC0_Disconnected								= 0,
	TIMER2_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top			= 2,
	TIMER2_FASTPWM_OCMODE_t_Set_On_Compare_Match_And_Clear_At_Top			= 3
}TIMER2_FASTPWM_OCMODE_t;

/*
 * This enumerator contains the Prescaler options.
 */
typedef enum{
	TIMER2_CLOCK_SOURCE_t_SystemClock_With_No_Prescaler								= 1,
	TIMER2_CLOCK_SOURCE_t_SystemClock_With_8_Prescaler								,
	TIMER2_CLOCK_SOURCE_t_SystemClock_With_64_Prescaler								,
	TIMER2_CLOCK_SOURCE_t_SystemClock_With_256_Prescaler							,
	TIMER2_CLOCK_SOURCE_t_SystemClock_With_1024_Prescaler							,
	TIMER2_CLOCK_SOURCE_t_External_On_Falling_Edge									,
	TIMER2_CLOCK_SOURCE_t_External_On_Rising_Edge
}TIMER2_CLOCK_SOURCE_t;
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
TIMER2_ERROR_t TIMER2_Init(void);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the compare match output Mode of the fast PWM mode.
 * it takes:
 * 			- the Output Compare, Fast_Pwm option (TIMER0_FASTPWM_OCMODE_t)
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_FastPWM_SetOCMode(TIMER2_FASTPWM_OCMODE_t Copy_PWM_OCMode);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the timer clock source.
 * it takes:
 * 			- The clock source (TIMER0_CLOCK_SOURCE_t)
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_SetClockSource(TIMER2_CLOCK_SOURCE_t Copy_ClockSource);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to start the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER2_ERROR_t TIMER0_StartTimer(void);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to stop the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_StopTimer(void);
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the duty cycle.
 *	it takes:
 *			- the duty cycle (u8)
 *	it returns:
 *	  		- The error status (TIMER0_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_FastPWM_SetDutyCycle(u8 Copy_u8_DutyCycle);
/********************************************************************************************************/

/********************************************************************************************************/


#endif /* MCAL_T2PWM_DRIVER_V1_TIMER2_INTERFACE_H_ */
