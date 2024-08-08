#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

/*_____________________________*/

/***************************** Prototype Function start *****************************/
void MSPI_voidSpiMasterInit();

u8 MSPI_U8MasterTransmit(u8 Copy_u8SpiMessage);
//void MSPI_voidSpiMasterSendString( u8 *Copy_u8SpiMessage1);
void MSPI_VidChipSelect(u8 State);
/***************************** Prototype Function end *****************************/

/****************************************************************************************
 *		SPI Control Register
 * **************
 *
******************************/

/* INTERRUPT ENABLE BITS */
#define SPIE   7

/* SPI ENABLE BITS */
#define SPE    6

/* Data order bits */
#define DORD   5

/* MAster/SLave Select Bit */
#define MSTR   4

/* Clock Polarity bit */
#define CPOL   3

/* Clock Phase bit */
#define CPHA   2

/* clock rate select bits */
#define SPR1   1
#define SPR0   0

/****************************************************************************************
 *		SPI Status Register
 * **************
 *
******************************/


/* SPIF SPI Interrupt flag Bit */
#define SPIF   7

/* WCOL Write Collision Flag bit */
#define WCOL   6

/* Reserved bits */
/*
 * Bit from 5 to 1 is reserved
*/

/* SPI2X Double Speed Mode */
#define SPI2X  0


/*********************************
 * Pre scalar Values
 */
/*
 *  0 00 fosc/4
	0 01 fosc/16
	0 10 fosc/64
	0 11 fosc/128
	1 00 fosc/2
	1 01 fosc/8
	1 10 fosc/32
	1 11 fosc/64
 *
 */
#define _SPI_PRESCALLER_4     0b000
#define _SPI_PRESCALLER_16    0b001
#define _SPI_PRESCALLER_64    0b010
#define _SPI_PRESCALLER_128   0b011
#define _SPI_PRESCALLER_2     0b100
#define _SPI_PRESCALLER_8     0b101
#define _SPI_PRESCALLER_32    0b110

#endif /* MCAL_SPI_INTERFACE_H */

/**
 *  user                             date                                    update
 *
 *
 */


//#endif /* SPI_INTERFACE_H */
