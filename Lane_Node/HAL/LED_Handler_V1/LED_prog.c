/*
 * LED_prog.c
 *
 *  Created on: Feb 6, 2022
 *      Author: Mostafa
 */

#include "../../LIB/STD_Types.h"
#include "../LED_Handler_V1/LED_int.h"
#include "../LED_Handler_V1/LED_cfg.h"

#include "../../MCAL/DIO_V1/DIO_init.h"


u8 LED_NUMBER_STATUS = 0;
u8 LED_PORT = 0;
u8 LED_PIN =  0;

/*
 *This function takes the led number, and returns the port and pin of that specific led;
 * it also return 1 if the led exist(between 1 and 8), 0 Otherwise;
 */
static u8 LED_u8Mapping(u8 Copy_u8LedNumber, u8 *Copy_u8PortPtr, u8 *Copy_u8PinPtr){
	u8 Local_u8LedNumberStatus = 1;
	switch(Copy_u8LedNumber){
			case LED_e_1:
				*Copy_u8PortPtr = LED_1_PORT;
				*Copy_u8PinPtr = LED_1_PIN;
				break;
			case LED_e_2:
				*Copy_u8PortPtr = LED_2_PORT;
				*Copy_u8PinPtr = LED_2_PIN;
				break;
			case LED_e_3:
				*Copy_u8PortPtr = LED_3_PORT;
				*Copy_u8PinPtr = LED_3_PIN;
				break;
			case LED_e_4:
				*Copy_u8PortPtr = LED_4_PORT;
				*Copy_u8PinPtr = LED_4_PIN;
				break;
			case LED_e_5:
				*Copy_u8PortPtr = LED_5_PORT;
				*Copy_u8PinPtr = LED_5_PIN;
				break;
			case LED_e_6:
				*Copy_u8PortPtr = LED_6_PORT;
				*Copy_u8PinPtr = LED_6_PIN;
				break;
			case LED_e_7:
				*Copy_u8PortPtr = LED_7_PORT;
				*Copy_u8PinPtr = LED_7_PIN;
				break;
			case LED_e_8:
				*Copy_u8PortPtr = LED_8_PORT;
				*Copy_u8PinPtr = LED_8_PIN;
				break;
			default:
				Local_u8LedNumberStatus = 0;
		}
	return Local_u8LedNumberStatus;
}

/*This function used to initialize the LEDs,
 * it takes:
 * 			1-the array address of type LED_e (this array contains the LEDs you want to initialize).
 * 			2-and the array size.
*/
void LED_vidInit(LED_e *arr_ptr, u8 Copy_u8LedsNumber){
	for(u8 i=0; i < Copy_u8LedsNumber; i++){
		LED_NUMBER_STATUS = LED_u8Mapping(arr_ptr[i], &LED_PORT, &LED_PIN);
		if(LED_NUMBER_STATUS){
			DIO_u8setPinDir(LED_PORT, LED_PIN, DIO_OUTPUT);
		}
	}
}

//This function used to toggle the led, it takes the led number;
void LED_vidToggleLed(u8 Copy_u8LedNumber){
	u8 Local_u8LedStatus;

	LED_NUMBER_STATUS = LED_u8Mapping(Copy_u8LedNumber, &LED_PORT, &LED_PIN);
	if(LED_NUMBER_STATUS){
		DIO_u8getPinVal(LED_PORT, LED_PIN, &Local_u8LedStatus);
		if(Local_u8LedStatus){
			DIO_u8setPinVal(LED_PORT, LED_PIN, DIO_LOW);
		}else{
			DIO_u8setPinVal(LED_PORT, LED_PIN, DIO_HIGH);
		}
	}

}

//This function used to turn on the led, it takes the led number;
void LED_vidTurnOnLed(u8 Copy_u8LedNumber){
#if LEDS_Configuration == COMMON_CATHODE
	LED_NUMBER_STATUS = LED_u8Mapping(Copy_u8LedNumber, &LED_PORT, &LED_PIN);
	if(LED_NUMBER_STATUS){
		DIO_u8setPinVal(LED_PORT, LED_PIN, HIGH);
	}
#elif LEDS_Configuration == COMMON_ANODE
	LED_NUMBER_STATUS = LED_u8Mapping(Copy_u8LedNumber, &LED_PORT, &LED_PIN);
	if(LED_NUMBER_STATUS){
		DIO_u8setPinVal(LED_PORT, LED_PIN, DIO_LOW);
	}
#endif
}


//This function used to turn off the led, it takes the led number;
void LED_vidTurnOffLed(u8 Copy_u8LedNumber){
#if LEDS_Configuration == COMMON_CATHODE
	LED_NUMBER_STATUS = LED_u8Mapping(Copy_u8LedNumber, &LED_PORT, &LED_PIN);
	if(LED_NUMBER_STATUS){
		DIO_u8setPinVal(LED_PORT, LED_PIN, LOW);
	}
#elif LEDS_Configuration == COMMON_ANODE
	LED_NUMBER_STATUS = LED_u8Mapping(Copy_u8LedNumber, &LED_PORT, &LED_PIN);
	if(LED_NUMBER_STATUS){
		DIO_u8setPinVal(LED_PORT, LED_PIN, DIO_HIGH);
	}
#endif
}

