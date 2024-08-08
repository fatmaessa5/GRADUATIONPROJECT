#ifndef SPI_REGISTERS_H
#define SPI_REGISTERS_H



/********************************************** ****************
 *
 *    #####################  SPI_PRIVATE  #######################
 *   Description :
 *   Author      :
 *   Date        :
 * ****************** ********************  ********************/

/* SPCR SPI Control Register */
#define SPCR    (*(volatile unsigned char*)0x2D)

/* SPSR SPI Status Register */
#define SPSR    (*(volatile unsigned char *)0x2E)

/* SPDR SPI Data Register */
#define SPDR    (*(volatile unsigned char *)0x2F)





/**
 *  user                             date                                    update
 *
 *
 */



#endif /* SPI_REGISTERS_H */
