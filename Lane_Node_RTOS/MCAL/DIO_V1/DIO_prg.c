/*
 * DIO_prg.c
 *
 *  Created on: Sep 15, 2021
 *      Author: Mostafa
 */

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"DIO_reg.h"
#include"DIO_init.h"


//PORT Functions
//set PORT direction
u8 DIO_u8setPortDir(u8 Copy_u8port, u8 Copy_u8dir){
	u8 Local_u8statues = 0;
	switch (Copy_u8port){
	case DIO_PORT_A:	DDRA_REG = Copy_u8dir;  break;
	case DIO_PORT_B:	DDRB_REG = Copy_u8dir;  break;
	case DIO_PORT_C:	DDRC_REG = Copy_u8dir;  break;
	case DIO_PORT_D:	DDRD_REG = Copy_u8dir;  break;

	default: Local_u8statues = 1;
	}

	return Local_u8statues;
}

//set PORT value
u8 DIO_u8setPortVal(u8 Copy_u8port, u8 Copy_u8val)
{
	u8 Local_u8statues = 0;
	switch (Copy_u8port){
	case DIO_PORT_A:	PORTA_REG = Copy_u8val;  break;
	case DIO_PORT_B:	PORTB_REG = Copy_u8val;  break;
	case DIO_PORT_C:	PORTC_REG = Copy_u8val;  break;
	case DIO_PORT_D:	PORTD_REG = Copy_u8val;  break;
	default: Local_u8statues = 1;
	}

	return Local_u8statues;
}
//get PORT value
u8 DIO_u8getPortVal(u8 Copy_u8port, u8 *Copy_u8valuePtr){
	u8 Local_u8statues = 0;
	switch (Copy_u8port){
	case DIO_PORT_A:	*Copy_u8valuePtr = PINA_REG;  break;
	case DIO_PORT_B:	*Copy_u8valuePtr = PINB_REG;  break;
	case DIO_PORT_C:	*Copy_u8valuePtr = PINC_REG;  break;
	case DIO_PORT_D:	*Copy_u8valuePtr = PIND_REG;  break;

	default: Local_u8statues = 1;
	}

	return Local_u8statues;
}

//PIN Functions
//set PIN direction
u8 DIO_u8setPinDir(u8 Copy_u8port, u8 Copy_u8pin, u8 Copy_u8dir){
	u8 Local_u8statues = 0;
	if(Copy_u8pin >= 0 && Copy_u8pin <= 7){
		if(Copy_u8dir == DIO_INPUT){
			switch(Copy_u8port){
			case DIO_PORT_A:	CLR_BIT(DDRA_REG, Copy_u8pin);  break;
			case DIO_PORT_B:	CLR_BIT(DDRB_REG, Copy_u8pin);  break;
			case DIO_PORT_C:	CLR_BIT(DDRC_REG, Copy_u8pin);  break;
			case DIO_PORT_D:	CLR_BIT(DDRD_REG, Copy_u8pin);  break;

			default: Local_u8statues = 1;
			}
		}else if(Copy_u8dir == DIO_OUTPUT){
			switch(Copy_u8port){
			case DIO_PORT_A:	SET_BIT(DDRA_REG, Copy_u8pin);  break;
			case DIO_PORT_B:	SET_BIT(DDRB_REG, Copy_u8pin);  break;
			case DIO_PORT_C:	SET_BIT(DDRC_REG, Copy_u8pin);  break;
			case DIO_PORT_D:	SET_BIT(DDRD_REG, Copy_u8pin);  break;

			default: Local_u8statues = 1;
			}
		}else{
			Local_u8statues=1;
		}

	}else{
		Local_u8statues=1;
	}

	return Local_u8statues;
}
//set PIN value
u8 DIO_u8setPinVal(u8 Copy_u8port, u8 Copy_u8pin, u8 Copy_u8val){
	u8 Local_u8statues = 0;
	if(Copy_u8pin >= 0 && Copy_u8pin <=7){
		if(Copy_u8val == DIO_HIGH){
			switch(Copy_u8port){
			case DIO_PORT_A:	SET_BIT(PORTA_REG, Copy_u8pin);  break;
			case DIO_PORT_B:	SET_BIT(PORTB_REG, Copy_u8pin);  break;
			case DIO_PORT_C:	SET_BIT(PORTC_REG, Copy_u8pin);  break;
			case DIO_PORT_D:	SET_BIT(PORTD_REG, Copy_u8pin);  break;

			default: Local_u8statues = 1;
			}
		}else if(Copy_u8val == DIO_LOW){
			switch(Copy_u8port){
			case DIO_PORT_A:	CLR_BIT(PORTA_REG, Copy_u8pin);  break;
			case DIO_PORT_B:	CLR_BIT(PORTB_REG, Copy_u8pin);  break;
			case DIO_PORT_C:	CLR_BIT(PORTC_REG, Copy_u8pin);  break;
			case DIO_PORT_D:	CLR_BIT(PORTD_REG, Copy_u8pin);  break;

			default: Local_u8statues = 1;
			}
		}else{
			Local_u8statues=1;
		}
	}else{
		Local_u8statues=1;
	}

	return Local_u8statues;
}

//get PIN value
u8 DIO_u8getPinVal(u8 Copy_u8port, u8 Copy_u8pin, u8 *Copy_u8valuePtr){
	u8 Local_u8statues = 0;
	if(Copy_u8pin >= 0 && Copy_u8pin <=7){
		switch(Copy_u8port){
		case DIO_PORT_A: *Copy_u8valuePtr = GET_BIT(PINA_REG, Copy_u8pin); break;
		case DIO_PORT_B: *Copy_u8valuePtr = GET_BIT(PINB_REG, Copy_u8pin); break;
		case DIO_PORT_C: *Copy_u8valuePtr = GET_BIT(PINC_REG, Copy_u8pin); break;
		case DIO_PORT_D: *Copy_u8valuePtr = GET_BIT(PIND_REG, Copy_u8pin); break;

		default: Local_u8statues = 1;
		}
	}else{
		Local_u8statues=1;
	}
	return Local_u8statues;
}
