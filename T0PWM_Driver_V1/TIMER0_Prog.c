/*
 * TIMER0_Prog.c
 *
 *  Created on: Dec 21, 2022
 *      Author: musta
 */

/********************************************* Includes *************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "./TIMER0_Error_.h"
#include "./TIMER0_Private.h"
#include "./TIMER0_Config.h"
#include "./TIMER0_Interface.h"
/********************************************************************************************************/

/****************************************** Declarations ************************************************/
static TIMER0_CLOCK_SOURCE_t TIMER0_CLOCK_SOURCE = TIMER0_CLOCK_SOURCE_t_SystemClock_With_No_Prescaler;
/********************************************************************************************************/

/*********************************** Functions Implementations ******************************************/

/********************************************************************************************************/
/*
 * Use this function to initialize the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_Init(void)
{
	TIMER0_ERROR_t Local_ErrorStatus = TIMER0_ERROR_t_RT_OK;

#if TIMER0_MODE == FAST_PWM_MODE
	//Set the Fast PWM mode
	SET_BIT(TIMER0_TCCR0,6);
	SET_BIT(TIMER0_TCCR0,3);
#else
	Local_ErrorStatus = TIMER0_ERROR_t_RT_NOK;
#error "Wrong Mode Option"

#endif

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the compare match output Mode of the fast PWM mode.
 * it takes:
 * 			- the Output Compare, Fast_Pwm option (TIMER0_FASTPWM_OCMODE_t)
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_FastPWM_SetOCMode(TIMER0_FASTPWM_OCMODE_t Copy_PWM_OCMode)
{
	TIMER0_ERROR_t Local_ErrorStatus = TIMER0_ERROR_t_RT_OK;

	if((Copy_PWM_OCMode >= TIMER0_FASTPWM_OCMODE_t_OC0_Disconnected) && (Copy_PWM_OCMode <= TIMER0_FASTPWM_OCMODE_t_Set_On_Compare_Match_And_Clear_At_Top))
	{
		//Set the compare match output mode

		TIMER0_TCCR0 &= (~(0b11<<4));				//clear bits 4 and 5 in the TCCR0 register
		TIMER0_TCCR0 |= (Copy_PWM_OCMode<<4);		//set the mode

		if(Copy_PWM_OCMode != TIMER0_FASTPWM_OCMODE_t_OC0_Disconnected)
		{
			//Set OC0 direction as output
			SET_BIT(TIMER0_DDRB,3);
		}
	}
	else
	{
		Local_ErrorStatus = TIMER0_ERROR_t_RT_NOK;
	}

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the timer clock source.
 * it takes:
 * 			- The clock source (TIMER0_CLOCK_SOURCE_t)
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_SetClockSource(TIMER0_CLOCK_SOURCE_t Copy_ClockSource)
{
	TIMER0_ERROR_t Local_ErrorStatus = TIMER0_ERROR_t_RT_OK;

	if((Copy_ClockSource >= TIMER0_CLOCK_SOURCE_t_SystemClock_With_No_Prescaler)
			&& (Copy_ClockSource <= TIMER0_CLOCK_SOURCE_t_External_On_Rising_Edge))
	{
		//Store the clock source in a global variable
		TIMER0_CLOCK_SOURCE = Copy_ClockSource;
	}
	else
	{
		Local_ErrorStatus = TIMER0_ERROR_t_RT_NOK;
	}

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to start the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_StartTimer(void)
{
	TIMER0_ERROR_t Local_ErrorStatus = TIMER0_ERROR_t_RT_OK;

	//Set the clock source of TIMER0 and start the timer
	TIMER0_TCCR0 &= (~(0b111<<0));					//clear the bits 0, 1 and 2
	TIMER0_TCCR0 |= (TIMER0_CLOCK_SOURCE<<0);		//set the clock source


	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to stop the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_StopTimer(void)
{
	TIMER0_ERROR_t Local_ErrorStatus = TIMER0_ERROR_t_RT_OK;

	//Stop the timer by setting no clock source
	TIMER0_TCCR0 &= (~(0b111<<0));					//clear the bits 0, 1 and 2

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the duty cycle.
 *	it takes:
 *			- the duty cycle (u8)
 *	it returns:
 *	  		- The error status (TIMER0_ERROR_t)
 */
TIMER0_ERROR_t TIMER0_FastPWM_SetDutyCycle(u8 Copy_u8_DutyCycle)
{
	TIMER0_ERROR_t Local_ErrorStatus = TIMER0_ERROR_t_RT_OK;

	u8 Local_u8_DutyCycleTicks = 0;

	u8 Local_u8_OCMode = ((TIMER0_TCCR0>>4) & (0b11));   //Get the OC0 mode

	if((Copy_u8_DutyCycle >= 0) && (Copy_u8_DutyCycle <= 100))
	{
		Local_u8_DutyCycleTicks = (Copy_u8_DutyCycle * 255) / 100;

		//Check the OC0 mode
		if((Local_u8_OCMode == TIMER0_FASTPWM_OCMODE_t_OC0_Disconnected) || (Local_u8_OCMode == TIMER0_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top))
		{
			//The OC0 is disconnected or Non_Inverted mode
			TIMER0_OCR0 = Local_u8_DutyCycleTicks;
		}
		else if(Local_u8_OCMode == TIMER0_FASTPWM_OCMODE_t_Set_On_Compare_Match_And_Clear_At_Top)
		{
			//Inverted mode
			TIMER0_OCR0 = 255 - Local_u8_DutyCycleTicks;
		}
		else
		{
			Local_ErrorStatus = TIMER0_ERROR_t_RT_NOK;
		}

	}
	else
	{
		Local_ErrorStatus = TIMER0_ERROR_t_RT_NOK;
	}

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
