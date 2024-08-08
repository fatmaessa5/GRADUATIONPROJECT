/*
 * DIO_init.h
 *
 *  Created on: Sep 15, 2021
 *      Author: Mostafa
 */


#ifndef MCAL_DIO_V1_DIO_INIT_H_
#define MCAL_DIO_V1_DIO_INIT_H_

#define DIO_PORT_A  0
#define DIO_PORT_B  1
#define DIO_PORT_C  2
#define DIO_PORT_D  3

#define DIO_PIN_0 0
#define DIO_PIN_1 1
#define DIO_PIN_2 2
#define DIO_PIN_3 3
#define DIO_PIN_4 4
#define DIO_PIN_5 5
#define DIO_PIN_6 6
#define DIO_PIN_7 7

#define DIO_LOW 0
#define DIO_HIGH 1

#define DIO_INPUT 0
#define DIO_OUTPUT 1

#define DIO_FULL_INPUT  0x00
#define DIO_FULL_OUTPUT 0xff

#define DIO_FULL_HIGH      0xff
#define DIO_FULL_LOW       0x00

//PORT Functions
//set PORT direction
u8 DIO_u8setPortDir(u8 Copy_u8port, u8 Copy_u8dir);

//set PORT value
u8 DIO_u8setPortVal(u8 Copy_u8port, u8 Copy_u8val);

//get PORT value
u8 DIO_u8getPortVal(u8 Copy_u8port, u8 *Copy_u8valuePtr);


//PIN Functions
//set PIN direction
u8 DIO_u8setPinDir(u8 Copy_u8port, u8 Copy_u8pin, u8 Copy_u8dir);

//set PIN value
u8 DIO_u8setPinVal(u8 Copy_u8port, u8 Copy_u8pin, u8 Copy_u8val);

//get PIN value
u8 DIO_u8getPinVal(u8 Copy_u8port, u8 Copy_u8pin, u8 *Copy_u8valuePtr);

#endif /* MCAL_DIO_V1_DIO_INIT_H_ */

