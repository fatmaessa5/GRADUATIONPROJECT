/*
 * DIO_prg.c
 *
 *  Created on: Mar 24, 2022
 *      Author: Mostafa
 */

#include "../../LIB/STD_TYPES.h"
#include "DIO_reg.h"
#include "DIO_int.h"
#include "DIO_err.h"
#include "../../LIB/BIT_MATH.h"

u8 DIO_u8SetPortDir(u8 Copy_u8Port, u8 Copy_u8Dir){
	u8 Local_error_status = RT_OK;			//it contains the error number
	switch(Copy_u8Port){
	case PORTA: DDRA_REG = Copy_u8Dir; break;
	case PORTB: DDRB_REG = Copy_u8Dir; break;
	case PORTC: DDRC_REG = Copy_u8Dir; break;
	case PORTD: DDRD_REG = Copy_u8Dir; break;
	default: Local_error_status = RT_WRONG_PORT_NO;
	}
	return Local_error_status;
}

u8 DIO_u8SetPortVal(u8 Copy_u8Port, u8 Copy_u8val){
	u8 Local_error_status = RT_OK;
	switch(Copy_u8Port){
	case PORTA: PORTA_REG = Copy_u8val; break;
	case PORTB: PORTB_REG = Copy_u8val; break;
	case PORTC: PORTC_REG = Copy_u8val; break;
	case PORTD: PORTD_REG = Copy_u8val; break;
	default: Local_error_status = RT_WRONG_PORT_NO;
	}
	return Local_error_status;
}

u8 DIO_u8GetPortVal(u8 Copy_u8Port, u8 * Copy_u8Ptr){
	u8 Local_error_status = RT_OK;
	switch(Copy_u8Port){
	case PORTA: * Copy_u8Ptr = PINA_REG; break;			//to store the port value in the given address
	case PORTB: * Copy_u8Ptr = PINB_REG; break;
	case PORTC: * Copy_u8Ptr = PINC_REG; break;
	case PORTD: * Copy_u8Ptr = PIND_REG; break;
	default: Local_error_status = RT_WRONG_PORT_NO;
	}
	return Local_error_status;
}

u8 DIO_u8SetPinDir(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Dir){
	u8 Local_error_status = RT_OK;
	if(Copy_u8Pin >= PIN0 && Copy_u8Pin <= PIN7){
		switch(Copy_u8Port){
		case PORTA:
			if(Copy_u8Dir == INPUT){
				CLR_BIT(DDRA_REG, Copy_u8Pin);  //to set this pin as input
			}else if(Copy_u8Dir == OUTPUT){
				SET_BIT(DDRA_REG, Copy_u8Pin);	//to set this pin as output
			}else{
				Local_error_status = RT_WRONG_PIN_DIRECTION;
			}
			break;
		case PORTB:
			if(Copy_u8Dir == INPUT){
				CLR_BIT(DDRB_REG, Copy_u8Pin);
			}else if(Copy_u8Dir == OUTPUT){
				SET_BIT(DDRB_REG, Copy_u8Pin);
			}else{
				Local_error_status = RT_WRONG_PIN_DIRECTION;
			}
			break;
		case PORTC:
			if(Copy_u8Dir == INPUT){
				CLR_BIT(DDRC_REG, Copy_u8Pin);
			}else if(Copy_u8Dir == OUTPUT){
				SET_BIT(DDRC_REG, Copy_u8Pin);
			}else{
				Local_error_status = RT_WRONG_PIN_DIRECTION;
			}
			break;
		case PORTD:
			if(Copy_u8Dir == INPUT){
				CLR_BIT(DDRD_REG, Copy_u8Pin);
			}else if(Copy_u8Dir == OUTPUT){
				SET_BIT(DDRD_REG, Copy_u8Pin);
			}else{
				Local_error_status = RT_WRONG_PIN_DIRECTION;
			}
			break;
		default: Local_error_status= RT_WRONG_PORT_NO;
		}
	}else{
		Local_error_status = RT_WRONG_PIN_NO;
	}
	return Local_error_status;
}

u8 DIO_u8SetPinVal(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Val){
	u8 Local_error_status = RT_OK;
	if(Copy_u8Pin >= PIN0 && Copy_u8Pin <= PIN7){
		switch(Copy_u8Port){
		case PORTA:
			if(Copy_u8Val == LOW){
				CLR_BIT(PORTA_REG, Copy_u8Pin);		//to make this pin low
			}else if(Copy_u8Val == HIGH){
				SET_BIT(PORTA_REG, Copy_u8Pin);		//to make this pin high
			}else{
				Local_error_status = RT_WRONG_PIN_VALUE;
			}
			break;
		case PORTB:
			if(Copy_u8Val == LOW){
				CLR_BIT(PORTB_REG, Copy_u8Pin);
			}else if(Copy_u8Val == HIGH){
				SET_BIT(PORTB_REG, Copy_u8Pin);
			}else{
				Local_error_status = RT_WRONG_PIN_VALUE;
			}
			break;
		case PORTC:
			if(Copy_u8Val == LOW){
				CLR_BIT(PORTC_REG, Copy_u8Pin);
			}else if(Copy_u8Val == HIGH){
				SET_BIT(PORTC_REG, Copy_u8Pin);
			}else{
				Local_error_status = RT_WRONG_PIN_VALUE;
			}
			break;
		case PORTD:
			if(Copy_u8Val == LOW){
				CLR_BIT(PORTD_REG, Copy_u8Pin);
			}else if(Copy_u8Val == HIGH){
				SET_BIT(PORTD_REG, Copy_u8Pin);
			}else{
				Local_error_status = RT_WRONG_PIN_VALUE;
			}
			break;
		default: Local_error_status= RT_WRONG_PORT_NO;
		}
	}else{
		Local_error_status = RT_WRONG_PIN_NO;
	}
	return Local_error_status;
}

u8 DIO_u8GetPinVal(u8 Copy_u8Port, u8 Copy_u8Pin, u8 * Copy_u8Ptr){
	u8 Local_error_status = RT_OK;
	if(Copy_u8Pin >= PIN0 && Copy_u8Pin <= PIN7){
		switch(Copy_u8Port){
		case PORTA: * Copy_u8Ptr = GET_BIT(PINA_REG, Copy_u8Pin); break;		//to store the pin value in the given address
		case PORTB: * Copy_u8Ptr = GET_BIT(PINB_REG, Copy_u8Pin); break;
		case PORTC: * Copy_u8Ptr = GET_BIT(PINC_REG, Copy_u8Pin); break;
		case PORTD: * Copy_u8Ptr = GET_BIT(PIND_REG, Copy_u8Pin); break;
		default: Local_error_status = RT_WRONG_PORT_NO;
		}
	}else{
		Local_error_status = RT_WRONG_PIN_NO;
	}
	return Local_error_status;
}
