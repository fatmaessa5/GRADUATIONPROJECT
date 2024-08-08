/*
 * LED_int.h
 *
 *  Created on: Feb 6, 2022
 *      Author: Mostafa
 */

#ifndef HAL_LED_HANDLER_V1_LED_INT_H_
#define HAL_LED_HANDLER_V1_LED_INT_H_

#define COMMON_CATHODE	0
#define COMMON_ANODE	1

typedef enum{
	LED_e_1 = 1,
	LED_e_2 = 2,
	LED_e_3 = 3,
	LED_e_4 = 4,
	LED_e_5 = 5,
	LED_e_6 = 6,
	LED_e_7 = 7,
	LED_e_8 = 8,
}LED_e;

/*This function used to initialize the LEDs,
 * it takes:
 * 			1-the array address of type LED_e (this array contains the LEDs you want to initialize).
 * 			2-and the array size.
*/
void LED_vidInit(LED_e *arr_ptr, u8 Copy_u8LedsNumber);

//This function used to toggle the led, it takes the led number;
void LED_vidToggleLed(u8 Copy_u8LedNumber);

//This function used to turn on the led, it takes the led number;
void LED_vidTurnOnLed(u8 Copy_u8LedNumber);


//This function used to turn off the led, it takes the led number;
void LED_vidTurnOffLed(u8 Copy_u8LedNumber);

#endif /* HAL_LED_HANDLER_V1_LED_INT_H_ */
