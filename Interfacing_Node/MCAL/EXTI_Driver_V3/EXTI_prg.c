/*
 * EXTI_prg.c
 *
 *  Created on: Sep 30, 2021
 *      Author: Mostafa
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include "avr/interrupt.h"

#include "../EXTI_Driver_V3/EXTI_int.h"
#include "../EXTI_Driver_V3/EXTI_Private.h"
#include "../EXTI_Driver_V3/EXTI_reg.h"

static void (*INT0_Cbf_ptr)(void) = NULL;
static void (*INT1_Cbf_ptr)(void) = NULL;
static void (*INT2_Cbf_ptr)(void) = NULL;

//this function sets the interrupt source, it takes the external interrupt number and event;
u8 EXTI_u8SetSource(u8 Copy_u8INTx, u8 Copy_u8Source){
	u8 Local_u8Status = 0;
	switch(Copy_u8INTx){
	case EXTI_INT_0:
		CLR_BIT(EXTI_DDRD_REG, EXTI_PIN_2);  // make pd2 => input
		SET_BIT(EXTI_PORTD_REG, EXTI_PIN_2);  //pull_up
		switch(Copy_u8Source){
		case EXTI_LOW_LEVEL:
			CLR_BIT(EXTI_MCUCR_REG, EXTI_PIN_0);
			CLR_BIT(EXTI_MCUCR_REG, EXTI_PIN_1);
			break;
		case EXTI_ANY_CHANGE:
			SET_BIT(EXTI_MCUCR_REG,  EXTI_PIN_0);
			CLR_BIT(EXTI_MCUCR_REG, EXTI_PIN_1);
			break;
		case EXTI_FALLING_EDGE:
			CLR_BIT(EXTI_MCUCR_REG,  EXTI_PIN_0);
			SET_BIT(EXTI_MCUCR_REG, EXTI_PIN_1);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(EXTI_MCUCR_REG,  EXTI_PIN_0);
			SET_BIT(EXTI_MCUCR_REG, EXTI_PIN_1);
			break;
		default:Local_u8Status = 1;
		}
		break;

	case EXTI_INT_1:
		CLR_BIT(EXTI_DDRD_REG, EXTI_PIN_3);  // make pd2 => input
		SET_BIT(EXTI_PORTD_REG, EXTI_PIN_3);  //pull_up
		switch(Copy_u8Source){
		case EXTI_LOW_LEVEL:
			CLR_BIT(EXTI_MCUCR_REG, EXTI_PIN_2);
			CLR_BIT(EXTI_MCUCR_REG, EXTI_PIN_3);
			break;
		case EXTI_ANY_CHANGE:
			SET_BIT(EXTI_MCUCR_REG,  EXTI_PIN_2);
			CLR_BIT(EXTI_MCUCR_REG, EXTI_PIN_3);
			break;
		case EXTI_FALLING_EDGE:
			CLR_BIT(EXTI_MCUCR_REG,  EXTI_PIN_2);
			SET_BIT(EXTI_MCUCR_REG, EXTI_PIN_3);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(EXTI_MCUCR_REG,  EXTI_PIN_2);
			SET_BIT(EXTI_MCUCR_REG, EXTI_PIN_3);
			break;
		default:Local_u8Status = 1;
		}
		break;

	case EXTI_INT_2:
		CLR_BIT(EXTI_DDRB_REG, EXTI_PIN_2);  // make pd2 => input
		SET_BIT(EXTI_PORTB_REG, EXTI_PIN_2);  //pull_up
		switch(Copy_u8Source){
		case EXTI_FALLING_EDGE:
			CLR_BIT(EXTI_MCUCSR_REG,  EXTI_PIN_6);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(EXTI_MCUCSR_REG, EXTI_PIN_6);
			break;
		default:Local_u8Status = 1;
		}
		break;
		default: Local_u8Status = 1;

	}
	/*}else if(Copy_u8INTx == INT_2){
			switch(Copy_u8Source){
			case FALLING_EDGE:
				CLR_BIT(MCUCSR, PIN_6);
				break;
			case RISING_EDGE:
				SET_BIT(MCUCSR, PIN_6);
				break;
			default: Local_u8Status = 1;
			}
		}*/
	return Local_u8Status;
}

/*
	this function used to enable the PIE (set the corresponding bit in GICR to 1),
	it takes the external interrupt number;
 */
u8 EXTI_u8EnablePIE(u8 Copy_u8INTx){
	u8 Local_u8Status = 0;
	switch(Copy_u8INTx){
	case EXTI_INT_0:
		SET_BIT(EXTI_GICR_REG, EXTI_PIN_6);
		break;
	case EXTI_INT_1:
		SET_BIT(EXTI_GICR_REG, EXTI_PIN_7);
		break;
	case EXTI_INT_2:
		SET_BIT(EXTI_GICR_REG, EXTI_PIN_5);
		break;
	default: Local_u8Status = 1;
	}
	return Local_u8Status;
}

/*
	this function used to enable the PIE (set the corresponding bit in GICR to 1),
	it takes the external interrupt number;
 */
u8 EXTI_u8DisablePIE(u8 Copy_u8INTx){
	u8 Local_u8Status = 0;
	switch(Copy_u8INTx){
	case EXTI_INT_0:
		CLR_BIT(EXTI_GICR_REG, EXTI_PIN_6);
		break;
	case EXTI_INT_1:
		CLR_BIT(EXTI_GICR_REG, EXTI_PIN_7);
		break;
	case EXTI_INT_2:
		CLR_BIT(EXTI_GICR_REG, EXTI_PIN_5);
		break;
	default: Local_u8Status = 1;
	}
	return Local_u8Status;
}

//this function used to enable the GIE (set the I_bit in SREG to 1)
void EXTI_voidEnableGIE(){
	SET_BIT(EXTI_SREG_REG, EXTI_PIN_7);
}

//this function used to disable the GIE (set the I_bit in SREG to 0)
void EXTI_voidDisableGIE(){
	CLR_BIT(EXTI_SREG_REG, EXTI_PIN_7);
}

//This function used to set INT0 call back function.
void EXTI_voidSet_INT0_Cbf(void (*fptr)(void)){
	if(fptr != NULL){
		INT0_Cbf_ptr = fptr;
	}
}

//This function used to set INT1 call back function.
void EXTI_voidSet_INT1_Cbf(void (*fptr)(void))
{
	if(fptr != NULL)
	{
		INT1_Cbf_ptr = fptr;
	}
}

//This function used to set INT1 call back function.
void EXTI_voidSet_INT2_Cbf(void (*fptr)(void))
{
	if(fptr != NULL)
	{
		INT2_Cbf_ptr = fptr;
	}
}

ISR(INT0_vect){
	if(INT0_Cbf_ptr != NULL){
		INT0_Cbf_ptr();
	}
}

ISR(INT1_vect){
	if(INT1_Cbf_ptr != NULL)
	{
		INT1_Cbf_ptr();
	}
}

ISR(INT2_vect){
	if(INT2_Cbf_ptr != NULL)
	{
		INT2_Cbf_ptr();
	}
}
