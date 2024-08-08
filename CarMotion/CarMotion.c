/*
 * CarMotion.c
 *
 *  Created on: Jul 5, 2023
 *      Author: musta
 */

#include "../../LIB/STD_TYPES.h"

#include "../CarMotion/CarMotion_Private.h"
#include "../CarMotion/CarMotion_Config.h"
#include "CarMotion.h"

#include "../../MCAL/T0PWM_Driver_V1/TIMER0_Error_.h"
#include "../../MCAL/T0PWM_Driver_V1/TIMER0_Interface.h"

#include "../../MCAL/T2PWM_Driver_V1/TIMER2_Error.h"
#include "../../MCAL/T2PWM_Driver_V1/TIMER2_Interface.h"

#include "../../MCAL/DIO_V2/DIO_init.h"

void Car_Init(void)
{

#if MOTOR_1_STATE == ENABLE

#if MOTOR_1_TIMER == TIMER0
	TIMER0_Init();
	TIMER0_SetClockSource(TIMER2_CLOCK_SOURCE_t_SystemClock_With_256_Prescaler);
	TIMER0_FastPWM_SetOCMode(TIMER2_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top);
	TIMER0_FastPWM_SetDutyCycle(90);
	TIMER0_StartTimer();
#elif MOTOR_1_TIMER == TIMER2
	TIMER2_Init();
	TIMER2_SetClockSource(TIMER2_CLOCK_SOURCE_t_SystemClock_With_256_Prescaler);
	TIMER2_FastPWM_SetOCMode(TIMER2_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top);
	TIMER2_FastPWM_SetDutyCycle(90);
	TIMER2_StartTimer();
#else
#error	"Configuration Error: Wrong Timer Selection"
#endif

	DIO_u8setPinDir(MOTOR_1_PORT, MOTOR_1_FIRST_PIN, DIO_OUTPUT);
	DIO_u8setPinDir(MOTOR_1_PORT, MOTOR_1_SECOND_PIN, DIO_OUTPUT);

#endif

#if MOTOR_2_STATE == ENABLE
#if MOTOR_2_TIMER == TIMER0
	TIMER0_Init();
	TIMER0_SetClockSource(TIMER2_CLOCK_SOURCE_t_SystemClock_With_256_Prescaler);
	TIMER0_FastPWM_SetOCMode(TIMER2_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top);
	TIMER0_FastPWM_SetDutyCycle(90);
	TIMER0_StartTimer();
#elif MOTOR_2_TIMER == TIMER2
	TIMER2_Init();
	TIMER2_SetClockSource(TIMER2_CLOCK_SOURCE_t_SystemClock_With_256_Prescaler);
	TIMER2_FastPWM_SetOCMode(TIMER2_FASTPWM_OCMODE_t_Clear_On_Compare_Match_And_Set_At_Top);
	TIMER2_FastPWM_SetDutyCycle(90);
	TIMER2_StartTimer();
#else
#error	"Configuration Error: Wrong Timer Selection"
#endif

	DIO_u8setPinDir(MOTOR_2_PORT, MOTOR_2_FIRST_PIN, DIO_OUTPUT);
	DIO_u8setPinDir(MOTOR_2_PORT, MOTOR_2_SECOND_PIN, DIO_OUTPUT);

#endif



}

void Car_Go_Forword(void)
{
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_FIRST_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_SECOND_PIN, DIO_HIGH);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_FIRST_PIN, DIO_HIGH);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_SECOND_PIN, DIO_LOW);
}

void Car_Go_Backword(void)
{
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_FIRST_PIN, DIO_HIGH);
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_SECOND_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_FIRST_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_SECOND_PIN, DIO_HIGH);
}
void Car_Go_Left(void)
{
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_FIRST_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_SECOND_PIN, DIO_HIGH);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_FIRST_PIN, DIO_HIGH);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_SECOND_PIN, DIO_LOW);
}
void Car_Go_Right(void)
{
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_FIRST_PIN, DIO_HIGH);
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_SECOND_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_FIRST_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_SECOND_PIN, DIO_HIGH);
}
void Car_Stop(void)
{
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_FIRST_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_1_PORT, MOTOR_1_SECOND_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_FIRST_PIN, DIO_LOW);
	DIO_u8setPinVal(MOTOR_2_PORT, MOTOR_2_SECOND_PIN, DIO_LOW);
}
void Car_Set_Speed(u8 MOTOR, u8 Copy_u8SpeedValue)
{
	switch (MOTOR) {
	case MOTOR_1:
		if(MOTOR_1_TIMER == TIMER0)
		{
			TIMER0_FastPWM_SetDutyCycle(Copy_u8SpeedValue);
		}else if(MOTOR_1_TIMER == TIMER2)
		{
			TIMER2_FastPWM_SetDutyCycle(Copy_u8SpeedValue);
		}else{

		}
		break;
	case MOTOR_2:
		if(MOTOR_2_TIMER == TIMER0)
		{
			TIMER0_FastPWM_SetDutyCycle(Copy_u8SpeedValue);
		}else if(MOTOR_2_TIMER == TIMER2)
		{
			TIMER2_FastPWM_SetDutyCycle(Copy_u8SpeedValue);
		}else{

		}
		break;
	default:
		break;
	}
}
