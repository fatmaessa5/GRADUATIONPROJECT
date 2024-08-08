/*
 * LCD_cfg.h
 *
 *  Created on: Apr 1, 2022
 *      Author: Mostafa
 */

#ifndef HAL_LCD_HANDLER_V2_LCD_CFG_H_
#define HAL_LCD_HANDLER_V2_LCD_CFG_H_

/*
 * LCD_MODE takes:
 * 					- EIGHT_BITS
 * 					- FOUR_BITS
 */
#define LCD_MODE		EIGHT_BITS

/*
 * NO_OF_LINES takes:
 * 					- ONE_LINE
 * 					- TWO_LINES
 */
#define NO_OF_LINES		TWO_LINES


/*
 * DISPLAY_STATE, CURSOR_STATE, CURSOR_BLINKING AND DISPLAY_SHIFT_OPERATION take:
 * 																				- ON
 * 																				- OFF
 */
#define DISPLAY_STATE				ON
#define CURSOR_STATE				ON
#define CURSOR_BLINKING				OFF
#define DISPLAY_SHIFT_OPERATION		OFF

/*
 * CURSOR_MOVE_DIRECTION takes:
 * 					- INCREMENT
 * 					- DECREMENT
 */
#define CURSOR_MOVE_DIRECTION		INCREMENT

/*
 * LCD_DATA_PORT, RS_PORT, RW_PORT and E_PORT take:
 * 					- DIO_PORT_A
 * 					- DIO_PORT_B
 * 					- DIO_PORT_C
 * 					- DIO_PORT_D
 */
#define LCD_DATA_PORT				DIO_PORT_C
#define RS_PORT						DIO_PORT_B
#define RW_PORT						DIO_PORT_B
#define E_PORT						DIO_PORT_B



/*
 * DB4_PIN, RS_PIN, RW_PIN and E_PIN take:
 * 					- DIO_PIN_0
 * 					- DIO_PIN_1
 * 						.
 * 						.
 * 					- DIO_PIN_7
 */
#define RS_PIN						DIO_PIN_2
#define RW_PIN						DIO_PIN_1
#define E_PIN						DIO_PIN_0

//Use this configuration in case of 4bits mode to specify the pin of DB4
#define DB4_PIN						DIO_PIN_0

#endif /* HAL_LCD_HANDLER_V2_LCD_CFG_H_ */
