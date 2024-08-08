/*******************************************
	****   @File   : SPI_PROGRAME.c           **
	****   Author  : Mina Maher           ***
	****   Data    : 17/3/2023            ***
	****   Version : 1_0_1                ***
	****   Brief   :                      ***
 ********************************************/


/*_____________________________*/
/****Include LIB ***********/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/*** MCAL ***********/
#include "SPI_Registers.h"
#include  "../DIO_V2/DIO_reg.h"
#include "../DIO_V2/DIO_init.h"
/*_____________________________*/
/*______________________*/

/*********** User SPI_Init function Start **/
/*
 @Brief     :
 @Parameter :
 @Return    :
 */
void MSPI_voidSpiMasterInit(void)
{
	u8 temp_SPCR = 0;

	// Set MOSI pin direction output
	DIO_u8setPinDir(DIO_PORT_B,DIO_PIN_4,DIO_OUTPUT);
	DIO_u8setPinDir(DIO_PORT_B,DIO_PIN_5,DIO_OUTPUT);
	DIO_u8setPinDir(DIO_PORT_B,DIO_PIN_6,DIO_INPUT);
	DIO_u8setPinVal(DIO_PORT_B,DIO_PIN_6,DIO_HIGH);
	DIO_u8setPinDir(DIO_PORT_B,DIO_PIN_7,DIO_OUTPUT);
//	DIO_VidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_LOW);

	// enable SPI
	SET_BIT(temp_SPCR, 6);

	// data order >>>> transmit MSB first
	CLR_BIT(temp_SPCR, 5);

	// configure SS pin as output and choose master spi mode
	//DIO_VidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_OUTPUT);
	//DIO_VidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_HIGH);
	SET_BIT(temp_SPCR, 4);


	// clock polarity >>> leading rising edge
	CLR_BIT(temp_SPCR, 3);

	// clock phase >>>> sampling at rising edge
	CLR_BIT(temp_SPCR, 2);

	// clock oscillator >> F_CPU / 8
	SET_BIT(temp_SPCR, 0);
	CLR_BIT(temp_SPCR, 1);
	SET_BIT(SPSR, 0);

	SPCR = temp_SPCR;
}
/*********** User SPI_Init function END **/

/*********** User SET_PRESC function Start **/
/*
 @Brief     :
 @Parameter :
 @Return    :
 */
void MSPI_voidSetPreSca(u8 Copy_u8Presca_value)
{
	switch(Copy_u8Presca_value)
	{
		/************************ ***/
		case 0:
			CLR_BIT(SPCR, 0);
			CLR_BIT(SPCR, 1);
			CLR_BIT(SPSR, 0);
		break;
		/************************ ***/
		case 1:
			SET_BIT(SPCR, 0);
			CLR_BIT(SPCR, 1);
			CLR_BIT(SPSR, 0);
		break;
		/************************ ***/
		case 2:
			CLR_BIT(SPCR, 0);
			SET_BIT(SPCR, 1);
			CLR_BIT(SPSR, 0);
		break;
		/************************ ***/
		case 3:
			SET_BIT(SPCR, 0);
			SET_BIT(SPCR, 1);
			CLR_BIT(SPSR, 0);
		break;
		/************************ ***/
		case 4:
			CLR_BIT(SPCR, 0);
			CLR_BIT(SPCR, 1);
			SET_BIT(SPSR, 0);
		break;
		/************************ ***/
		case 5:
			SET_BIT(SPCR, 0);
			CLR_BIT(SPCR, 1);
			SET_BIT(SPSR, 0);
		break;
		/************************ ***/
		case 6:
			CLR_BIT(SPCR, 0);
			SET_BIT(SPCR, 1);
			SET_BIT(SPSR, 0);
		break;
		/************************ ***/
		default :
			CLR_BIT(SPCR, 0);
			CLR_BIT(SPCR, 1);
			CLR_BIT(SPSR, 0);

		break;
	}
}
/*********** User SET_PRESC function Start **/

/*********** User Chip SeLect(SS) function Start **/
/*
 @Brief     :
 @Parameter :
 @Return    :
 */
void MSPI_VidChipSelect(u8 state)
{
	if(state == 1)
	{
		//MCAL_DIO_voidSETBIT(PB,PB4,LOW);
		DIO_u8setPinVal(DIO_PORT_B,DIO_PIN_4,DIO_LOW);
	}
	else
	{
		DIO_u8setPinVal(DIO_PORT_B,DIO_PIN_4,DIO_HIGH);
	}
}
/*********** User Chip SeLect(SS) function End **/
/*********** User SPI Transmit function Start **/
/*
 @Brief     :
 @Parameter :
 @Return    :
 */
u8 MSPI_U8MasterTransmit(u8 Copy_u8SpiMessage)
{
	u8 dataRead=0;
	SPDR = Copy_u8SpiMessage;
	while(GET_BIT(SPSR, 7)==0);
	dataRead = SPDR;
	return dataRead;
}
/*********** User SPI Transmit function End **/
/****************************************************
   Name                    Date               Update
   MINA Maher              16/3/2023          Adding comment
  ***************************************************
 */

