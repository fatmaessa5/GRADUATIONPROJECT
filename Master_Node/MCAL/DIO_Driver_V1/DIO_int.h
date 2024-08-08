/*
 * DIO_int.h
 *
 *  Created on: Mar 24, 2022
 *      Author: Mostafa
 */

#ifndef MCAL_DIO_INT_H_
#define MCAL_DIO_INT_H_

/*
 * Use these macros as port numbers
 * it used with all functions
 */
#define PORTA	1
#define PORTB	2
#define PORTC	3
#define PORTD	4

/*
 * Use these macros as pin numbers, with the following functions:
 * 															1- DIO_u8SetPinDir
 * 															2- DIO_u8SetPinVal
 * 															3- DIO_u8GetPinVal
*/
#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

/*
 * if you want to set the whole port as input or output use these macros.
 * they used with the following functions:
 * 										1- DIO_u8SetPortDir
*/
#define FULL_INPUT	(u8)(0b00000000)
#define FULL_OUTPUT	(u8)(0b11111111)

/*
 * if you want to set the whole port high or low use these macros.
 * they used with the following functions:
 * 										1- DIO_u8SetPortVal
*/
#define FULL_HIGH	(u8)(0XFF)
#define FULL_LOW	(u8)(0X00)

/*
 * use these macros as the pin direction.
 * they used with the following functions:
 * 										1- DIO_u8SetPinDir
 */
#define INPUT	1
#define OUTPUT	2

/*
 * use these macros as the pin value
 * they used with the following functions:
 * 										1- DIO_u8SetPinVal
 */
#define	LOW		1
#define HIGH	2


//function to set port direction
/*
 * description:
 * 				Use this function to set the port direction.
 *
 * parameters:
 * 			 	1- (u8) port number (PORTA, PORTB, PORTC, PORTD)
				2- (u8) direction of the whole port
 * return:
 *				1- RT_OK  (there are no errors)
 *				2- RT_WRONG_PORT (port number is wrong)
 */
u8 DIO_u8SetPortDir(u8 Copy_u8Port, u8 Copy_u8Dir);

//function to set port value
/*
 * description:
 * 				Use this function to set the port value.
 *
 * parameters:
 * 			 	1- (u8) port number (PORTA, PORTB, PORTC, PORTD)
				2- (u8) value of the whole port
 * return:
 *				1- RT_OK  (there are no errors)
 *				2- RT_WRONG_PORT (port number is wrong)
 */
u8 DIO_u8SetPortVal(u8 Copy_u8Port, u8 Copy_u8val);

//function to get port value
/*
 * description:
 * 				Use this function to read the port value.
 *
 * parameters:
 * 			 	1- (u8) port number (PORTA, PORTB, PORTC, PORTD)
				2- Address of u8 variable (pointer to u8)
 * return:
 *				1- RT_OK  			(there are no errors)
 *				2- RT_WRONG_PORT 	(port number is wrong)
 */
u8 DIO_u8GetPortVal(u8 Copy_u8Port, u8 * Copy_u8Ptr);

//function to set pin direction
/*
 * description:
 * 				Use this function to set the pin direction.
 *
 * parameters:
 * 			 	1- (u8) port number (PORTA, PORTB, PORTC, PORTD)
 * 			 	2- (u8) pin number  (PIN0, PIN1, ...., PIN7)
				3- (u8) direction of the pin (OUTPUT, INPUT)
 * return:
 *				1- RT_OK  (there are no errors)
 *				2- RT_WRONG_PORT 		(port number is wrong)
 *				3- RT_WRONG_PIN  		(pin number is wrong)
 *				4- RT_WRONG_DIRECTION	(pin direction is wrong)
 */
u8 DIO_u8SetPinDir(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Dir);

//function to set pin value
/*
 * description:
 * 				Use this function to set the pin value.
 *
 * parameters:
 * 			 	1- (u8) port number (PORTA, PORTB, PORTC, PORTD)
 * 			 	2- (u8) pin number  (PIN0, PIN1, ...., PIN7)
 *				3- (u8) value of the pin (HIGH, LOW)
 * return:
 *				1- RT_OK  (there are no errors)
 *				2- RT_WRONG_PORT 		(port number is wrong)
 *				3- RT_WRONG_PIN  		(pin number is wrong)
 *				4- RT_WRONG_VALUE		(pin value is wrong)
 */
u8 DIO_u8SetPinVal(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Val);

//function to get pin value
/*
 * description:
 * 				Use this function to get the pin value.
 *
 * parameters:
 * 			 	1- (u8) port number (PORTA, PORTB, PORTC, PORTD)
 * 			 	2- (u8) pin number  (PIN0, PIN1, ...., PIN7)
				2- Address of u8 variable (pointer to u8)
 * return:
 *				1- RT_OK  			(there are no errors)
 *				2- RT_WRONG_PORT 	(port number is wrong)
 *				3- RT_WRONG_PIN  		(pin number is wrong)
 */
u8 DIO_u8GetPinVal(u8 Copy_u8Port, u8 Copy_u8Pin, u8 * Copy_u8Ptr);
#endif /* MCAL_DIO_INT_H_ */
