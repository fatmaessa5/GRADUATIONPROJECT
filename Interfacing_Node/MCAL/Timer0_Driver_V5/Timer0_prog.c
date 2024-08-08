/*
 * Timer0_prog.c
 *
 *  Created on: Feb 8, 2022
 *      Author: Mostafa
 */

#include "avr/interrupt.h"
#include "../../LIB/STD_Types.h"
//#include "../../LIB/PUBLIC_MACROS.h"
#include "../../LIB/BIT_MATH.h"
#include "../Timer0_Driver_V5/Timer0_cfg.h"
#include "../Timer0_Driver_V5/Timer0_int.h"
#include "../Timer0_Driver_V5/Timer0_reg.h"

#define TIMER0_CLK_CLR_MSK 				(u8)0b11111000
#define TIMER0_WG_CLR_MSK 				(u8)0b11001111
#define TIMER0_WG_Offset 				(u8)4
#define Timer0_WG_PWM_Reserved_Option   (u8)1

static void (*Timer0_Tovf_cbk_Fptr)(void) = NULL;
static void (*Timer0_Ctc_cbk_Fptr)(void) = NULL;

ISR(TIMER0_OVF_vect){
	if(Timer0_Tovf_cbk_Fptr != NULL){
		Timer0_Tovf_cbk_Fptr();
	}
}

ISR(TIMER0_COMP_vect){
	if(Timer0_Ctc_cbk_Fptr != NULL){
		Timer0_Ctc_cbk_Fptr();
	}
}

static Timer0_Prescaller_e TIMER0_CLK_SLCT = Timer0_Prescaller_e_No;

void Timer0_vidinit(void){
#if TIMER0_MODE == NORMAL_MODE
	CLR_BIT(TCCR0_REG, 3);
	CLR_BIT(TCCR0_REG, 6);
#elif TIMER0_MODE == PHASE_CORRECT_MODE
	CLR_BIT(TCCR0_REG, 3);
	SET_BIT(TCCR0_REG, 6);
#elif TIMER0_MODE == CTC_MODE
	SET_BIT(TCCR0_REG, 3);
	CLR_BIT(TCCR0_REG, 6);
#elif TIMER0_MODE == FAST_PWM_MODE
	SET_BIT(TCCR0_REG, 3);
	SET_BIT(TCCR0_REG, 6);
#endif

#if TIMER0_COMPARE_OUTPUT_MODE == NORMAL_PORT_OPERATION_MODE
	CLR_BIT(TCCR0_REG, 4);
	CLR_BIT(TCCR0_REG, 5);
#elif TIMER0_COMPARE_OUTPUT_MODE == TOGGLE_ON_CM_MODE
	SET_BIT(TCCR0_REG, 4);
	CLR_BIT(TCCR0_REG, 5);
#elif TIMER0_COMPARE_OUTPUT_MODE == CLEAR_ON_CM_MODE || TIMER0_COMPARE_OUTPUT_MODE == INVERTED_MODE
	CLR_BIT(TCCR0_REG, 4);
	SET_BIT(TCCR0_REG, 5);
#elif TIMER0_COMPARE_OUTPUT_MODE == SET_ON_CM_MODE || TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTED_MODE
	SET_BIT(TCCR0_REG, 5);
	SET_BIT(TCCR0_REG, 5);
#endif
}

void Timer0_vidSlctPrescaller(Timer0_Prescaller_e Copy_Timer0_Prescaller_e_value){
	if(Copy_Timer0_Prescaller_e_value >= Timer0_Prescaller_e_No &&
			Copy_Timer0_Prescaller_e_value <= Timer0_Prescaller_e_Ext_Rising_Edge ){
		TIMER0_CLK_SLCT = Copy_Timer0_Prescaller_e_value;
	}
}

void Timer0_vidSetPreloadVlaue(u8 Copy_u8PreloadValue){
	TCNT0_REG = Copy_u8PreloadValue;
}

void Timer0_vidSetCTCValue(u8 Copy_u8CtcValue){
	OCR0_REG = Copy_u8CtcValue;
}

void Timer0_vidStartTimer(void){
	TCCR0_REG &= TIMER0_CLK_CLR_MSK;
	TCCR0_REG |= TIMER0_CLK_SLCT;
}

void Timer0_vidStopTimer(void){
	TCCR0_REG &= TIMER0_CLK_CLR_MSK;
}

void Timer0_vidTovfIrqEnable(void){
	SET_BIT(TIMSK_REG, 0);
}

void Timer0_vidTovfIrqDisable(void){
	CLR_BIT(TIMSK_REG, 0);
}

void Timer0_vidCtcIrqEnable(void){
	SET_BIT(TIMSK_REG, 1);
}

void Timer0_vidCtcIrqDisable(void){
	CLR_BIT(TIMSK_REG, 1);
}

u8 Timer0_u8GetElepsedTime(void){

	return TCNT0_REG;

}

void Timer0_vidResetTimer(void){

	TCNT0_REG = 0;

}

/*
void Timer0_vidSlctNonPwmWG(Timer0_NonPwm_WG_e Copy_Timer0_NonPwm_WG_e_Option){

	if(Copy_Timer0_NonPwm_WG_e_Option >= Timer0_NonPwm_WG_e_Normal_Port_Op &&
			Copy_Timer0_NonPwm_WG_e_Option <= Timer0_NonPwm_WG_e_Set_Pin_On_Cm){

		TCCR0_REG &= TIMER0_WG_CLR_MSK;
		TCCR0_REG |= (Copy_Timer0_NonPwm_WG_e_Option << TIMER0_WG_Offset);

	}

}
*/
/*
void Timer0_vidSlctFastPwmWG(Timer0_FastPwm_WG_e Copy_Timer0_FastPwm_WG_e_Option){
	if(Copy_Timer0_FastPwm_WG_e_Option >= Timer0_FastPwm_WG_e_Normal_Port_Op &&
			Copy_Timer0_FastPwm_WG_e_Option <= Timer0_FastPwm_WG_e_Set_On_Cm_Clear_At_Top&&
			Copy_Timer0_FastPwm_WG_e_Option != Timer0_WG_PWM_Reserved_Option){
		TCCR0_REG &= TIMER0_WG_CLR_MSK;
		TCCR0_REG |= (Copy_Timer0_FastPwm_WG_e_Option << TIMER0_WG_Offset);
	}
}
void Timer0_vidSlctPhCorrPwmWG(Timer0_PhCorrPwm_WG_e Copy_Timer0_PhCorrPwm_WG_e_Option){
	if(Copy_Timer0_PhCorrPwm_WG_e_Option >= Timer0_PhCorrPwm_WG_e_Normal_Port_Op &&
			Copy_Timer0_PhCorrPwm_WG_e_Option <= Timer0_PhCorrPwm_WG_e_Set_On_Cm_UpCount_Clear_On_Cm_DownCount &&
			Copy_Timer0_PhCorrPwm_WG_e_Option != Timer0_WG_PWM_Reserved_Option){
		TCCR0_REG &= TIMER0_WG_CLR_MSK;
		TCCR0_REG |= (Copy_Timer0_PhCorrPwm_WG_e_Option << TIMER0_WG_Offset);
	}
}
*/

//To set the call back function of the Normal mode.
void Timer0_vidSet_Tovf_Call_Back(void (*fptr)(void)){
	if(fptr != NULL){
		Timer0_Tovf_cbk_Fptr = fptr;
	}
}

//To set the call back function of the CTC mode.
void Timer0_vidSet_CTC_Call_Back(void (*fptr)(void)){
	if(fptr != NULL){
		Timer0_Ctc_cbk_Fptr = fptr;
	}
}

void Timer0_vidSetPwmDutyCycle(u8 Copy_u8DutyCycle){
	u8 DutyTicks;
	DutyTicks = 256 * ((f32)Copy_u8DutyCycle / 100);
#if TIMER0_COMPARE_OUTPUT_MODE == INVERTED_MODE
	OCR0_REG = DutyTicks;
#elif TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTED_MODE
	OCR0_REG = 255-DutyTicks;
#endif
}
