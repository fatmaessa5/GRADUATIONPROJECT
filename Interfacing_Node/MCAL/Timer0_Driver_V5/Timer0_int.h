/*
 * Timer0_int.h
 *
 *  Created on: Feb 8, 2022
 *      Author: Mostafa
 */

#ifndef MCAL_TIMER0_DRIVER_V5_TIMER0_INT_H_
#define MCAL_TIMER0_DRIVER_V5_TIMER0_INT_H_

/*
 * use these options in configuration file in TIMER0_MODE
 */
#define NORMAL_MODE      		1
#define FAST_PWM_MODE         	2
#define CTC_MODE         		3
#define PHASE_CORRECT_MODE		4

/*
 * use these options in configuration file in TIMER0_COMPARE_OUTPUT_MODE
*/

//The following option works with all modes.
#define NORMAL_PORT_OPERATION_MODE     	1

//These three options is related to the CTC_MODE.
#define TOGGLE_ON_CM_MODE              	2
#define CLEAR_ON_CM_MODE               	3
#define SET_ON_CM_MODE               	4

//These two options is related to the PWM_MODES.
#define INVERTED_MODE                  5
#define NON_INVERTED_MODE              6


typedef enum {
	Timer0_Prescaller_e_No    				=  1,
	Timer0_Prescaller_e_8     				=  2,
	Timer0_Prescaller_e_64    				=  3,
	Timer0_Prescaller_e_256   			   	=  4,
	Timer0_Prescaller_e_1024              	=  5,
	Timer0_Prescaller_e_Ext_Falling_Edge  	=  6,
	Timer0_Prescaller_e_Ext_Rising_Edge   	=  7,

} Timer0_Prescaller_e;

//typedef enum {
//	Timer0_NonPwm_WG_e_Normal_Port_Op			= 0,
//	Timer0_NonPwm_WG_e_Toggle_Pin_On_Cm    		= 1,
//	Timer0_NonPwm_WG_e_Clear_Pin_On_Cm     		= 2,
//	Timer0_NonPwm_WG_e_Set_Pin_On_Cm			= 3
//}Timer0_NonPwm_WG_e;

//typedef enum {
//	Timer0_FastPwm_WG_e_Normal_Port_Op					= 0,
//	Timer0_FastPwm_WG_e_Clear_On_Cm_Set_At_Top    		= 2,
//	Timer0_FastPwm_WG_e_Set_On_Cm_Clear_At_Top			= 3
//}Timer0_FastPwm_WG_e;

//typedef enum {
//	Timer0_PhCorrPwm_WG_e_Normal_Port_Op									= 0,
//	Timer0_PhCorrPwm_WG_e_Clear_On_Cm_UpCount_Set_On_Cm_DownCount    		= 2,
//	Timer0_PhCorrPwm_WG_e_Set_On_Cm_UpCount_Clear_On_Cm_DownCount			= 3
//}Timer0_PhCorrPwm_WG_e;

//This function is to initialize the timer by setting the desired mode;
void Timer0_vidinit(void);

//This function sets the desired Prescaller, it takes a timer0_Prescaller_e value;
void Timer0_vidSlctPrescaller(Timer0_Prescaller_e Copy_Timer0_Prescaller_e_value);

//This function used to set the Preload value(number of Ticks), it takes u8 value;
void Timer0_vidSetPreloadVlaue(u8 Copy_u8PreloadValue);

//This function used to set the CTC value(number of ticks), it takes u8 value;
void Timer0_vidSetCTCValue(u8 Copy_u8CtcValue);

//Used to start the timer;
void Timer0_vidStartTimer(void);

//Used To stop The timer;
void Timer0_vidStopTimer(void);

//Enables the Timer Overflow Interrupt;
void Timer0_vidTovfIrqEnable(void);

//Disables the Timer Overflow Interrupt;
void Timer0_vidTovfIrqDisable(void);

//Enables the Timer CTC Interrupt;
void Timer0_vidCtcIrqEnable(void);

//Disables the Timer CTC Interrupt;
void Timer0_vidCtcIrqDisable(void);

//Get the Elapsed Time
u8 Timer0_u8GetElepsedTime(void);

//Reset Timer0
void Timer0_vidResetTimer(void);

//To choose the output waveform of the Non_pwm modes(Normal and CTC modes).
//void Timer0_vidSlctNonPwmWG(Timer0_NonPwm_WG_e Copy_Timer0_NonPwm_WG_e_Option);

//To choose the output waveform of the Fast_Pwm mode.
//void Timer0_vidSlctFastPwmWG(Timer0_FastPwm_WG_e Copy_Timer0_FastPwm_WG_e_Option);

//To choose the output waveform of the Phase Correct PWM mode.
//void Timer0_vidSlctPhCorrPwmWG(Timer0_PhCorrPwm_WG_e Copy_Timer0_PhCorrPwm_WG_e_Option);

//To set the call back function of the Normal mode.
void Timer0_vidSet_Tovf_Call_Back(void (*fptr)(void));

//To set the call back function of the CTC mode.
void Timer0_vidSet_CTC_Call_Back(void (*fptr)(void));

void Timer0_vidSetPwmDutyCycle(u8 Copy_u8DutyCycle);


#endif /* MCAL_TIMER0_DRIVER_V5_TIMER0_INT_H_ */
