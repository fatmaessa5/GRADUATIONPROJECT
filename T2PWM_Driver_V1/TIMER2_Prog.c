/*
 * TIMER2_Prog.c
 *
 *  Created on: Jul 5, 2023
 *      Author: musta
 */

/********************************************* Includes *************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "./TIMER2_Error.h"
#include "./TIMER2_Private.h"
#include "./TIMER2_Config.h"
#include "./TIMER2_Interface.h"
/********************************************************************************************************/

/****************************************** Declarations ************************************************/
static TIMER2_CLOCK_SOURCE_t TIMER2_CLOCK_SOURCE = TIMER2_CLOCK_SOURCE_t_SystemClock_With_No_Prescaler;
/********************************************************************************************************/

/*********************************** Functions Implementations ******************************************/

/********************************************************************************************************/
/*
 * Use this function to initialize the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER2_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_Init(void)
{
	TIMER2_ERROR_t Local_ErrorStatus = TIMER2_ERROR_t_RT_OK;

#if TIMER2_MODE == FAST_PWM_MODE
	//Set the Fast PWM mode
	SET_BIT(TIMER2_TCCR2,6);
	SET_BIT(TIMER2_TCCR2,3);
#else
	Local_ErrorStatus = TIMER2_ERROR_t_RT_NOK;
#error "Wrong Mode Option"

#endif

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the compare match output Mode of the fast PWM mode.
 * it takes:
 * 			- the Output Compare, Fast_Pwm option (TIMER2_FASTPWM_OCMODE_t)
 * it returns:
 * 			- The error status (TIMER2_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_FastPWM_SetOCMode(TIMER2_FASTPWM_OCMODE_t Copy_PWM_OCMode)
{
	TIMER2_ERROR_t Local_ErrorStatus = TIMER2_ERROR_t_RT_OK;

	if((Copy_PWM_OCMode >= TIMER2_FASTPWM_OCMODE_t_OC0_Disconnected) && (Copy_PWM_OCMode <= TIMER2_FASTPWM_OCMODE_t_Set_On_Compare_Match_And_Clear_At_Top))
	{
		//Set the compare match output mode

		TIMER2_TCCR2 &= (~(0b11<<4));				//clear bits 4 and 5 in the TCCR0 register
		TIMER2_TCCR2 |= (Copy_PWM_OCMode<<4);		//set the mode

		if(Copy_PWM_OCMode != TIMER2_FASTPWM_OCMODE_t_OC0_Disconnected)
		{
			//Set OC0 direction as output
			SET_BIT(TIMER2_DDRD,7);
		}
	}
	else
	{
		Local_ErrorStatus = TIMER2_ERROR_t_RT_NOK;
	}

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the timer clock source.
 * it takes:
 * 			- The clock source (TIMER2_CLOCK_SOURCE_t)
 * it returns:
 * 			- The error status (TIMER2_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_SetClockSource(TIMER2_CLOCK_SOURCE_t Copy_ClockSource)
{
	TIMER2_ERROR_t Local_ErrorStatus = TIMER2_ERROR_t_RT_OK;

	if((Copy_ClockSource >= TIMER2_CLOCK_SOURCE_t_SystemClock_With_No_Prescaler)
			&& (Copy_ClockSource <= TIMER2_CLOCK_SOURCE_t_External_On_Rising_Edge))
	{
		//Store the clock source in a global variable
		TIMER2_CLOCK_SOURCE = Copy_ClockSource;
	}
	else
	{
		Local_ErrorStatus = TIMER2_ERROR_t_RT_NOK;
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
 * 			- The error status (TIMER2_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_StartTimer(void)
{
	TIMER2_ERROR_t Local_ErrorStatus = TIMER2_ERROR_t_RT_OK;

	//Set the clock source of TIMER2 and start the timer
	TIMER2_TCCR2 &= (~(0b111<<0));					//clear the bits 0, 1 and 2
	TIMER2_TCCR2 |= (TIMER2_CLOCK_SOURCE<<0);		//set the clock source


	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to stop the timer.
 * it takes:
 * 			- void
 * it returns:
 * 			- The error status (TIMER2_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_StopTimer(void)
{
	TIMER2_ERROR_t Local_ErrorStatus = TIMER2_ERROR_t_RT_OK;

	//Stop the timer by setting no clock source
	TIMER2_TCCR2 &= (~(0b111<<0));					//clear the bits 0, 1 and 2

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/
/*
 * Use this function to set the duty cycle.
 *	it takes:
 *			- the duty cycle (u8)
 *	it returns:
 *	  		- The error status (TIMER2_ERROR_t)
 */
TIMER2_ERROR_t TIMER2_FastPWM_SetDutyCycle(u8 Copy_u8_DutyCycle)
{
	TIMER2_ERROR_t Local_ErrorStatus = TIMER2_ERROR_t_RT_OK;

	u8 Local_u8_DutyCycleTicks = 0;

	u8 Local_u8_OCMode = ((TIMER2_TCCR2>>4) & (0b11));   //Get the OC0 mode

	if((Copy_u8_DutyCycle >= 0) && (Copy_u8_DutyCycle <= 100))
	{
		Local_u8_DutyCycleTicks = (Copy_u8_DutyCycle * 255) / 100;

		//Check the OC0 mode
		if((Local_u8_OCMode == TIMER2_FASTPWM_OCMODE_t_OC0_Disconnected) || (Local_u8_OCMode == TIMER2_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top))
		{
			//The OC0 is disconnected or Non_Inverted mode
			TIMER2_OCR2 = Local_u8_DutyCycleTicks;
		}
		else if(Local_u8_OCMode == TIMER2_FASTPWM_OCMODE_t_Set_On_Compare_Match_And_Clear_At_Top)
		{
			//Inverted mode
			TIMER2_OCR2 = 255 - Local_u8_DutyCycleTicks;
		}
		else
		{
			Local_ErrorStatus = TIMER2_ERROR_t_RT_NOK;
		}

	}
	else
	{
		Local_ErrorStatus = TIMER2_ERROR_t_RT_NOK;
	}

	return Local_ErrorStatus;
}
/********************************************************************************************************/

/********************************************************************************************************/

