/*
 * MP2515_Private.h
 *
 *  Created on: ٠١‏/١١‏/٢٠٢٢
 *      Author: DELL
 */

#ifndef MP2515_PRIVATE_H_
#define MP2515_PRIVATE_H_

/*
 * Bit Timing Registers
 */
#define CNF1   0x2A
#define CNF2   0X29
#define CNF3   0X28

/*
 * BUFFER SEND REGISTER
 * Not make casting or volatile because Address JUst Data
 * TXBnCTRL ->TRANSMIT BUFFER n CONTROL REGISTER
 */
#define TXB0CTRL    0x30
#define TXB1CTRL    0x40
#define TXB2CTRL    0x50

/***********
 * TXRTSCTRL:
 * TXnRTS PIN CONTROL AND STATUS REGISTER
 */
#define TXRTSCTRL  0x0D

/*
 * STanderd Frame Format ID=11 BITS
 * Identifier Register
 * TXBnSIDH: TRANSMIT BUFFER n STANDARD IDENTIFIER REGISTER HIGH
 * TXBnSIDL: TRANSMIT BUFFER n STANDARD IDENTIFIER REGISTER LOW (Contain only 3bit from ID)
 */
#define TXB0SIDH    0x31
#define TXB1SIDH    0x41
#define TXB2SIDH    0x51

#define TXB0SIDL    0x32
#define TXB1SIDL    0x42
#define TXB2SIDL    0x52

/*
 * IF we Use Extra ID  ( ADD 18 BITS FROM it TWO Bits At TXBnSIDL and Enable to ADD extra BIT (EXIDE)  )
 *   TXBnEID8: TRANSMIT BUFFER n EXTENDED IDENTIFIER 8 REGISTER HIGH
 *   TXBnEID0: TRANSMIT BUFFER n EXTENDED IDENTIFIER 0 REGISTER LOW
 */
# define TXB0EID8   0x33
# define TXB1EID8   0x43
# define TXB2EID8   0x53

# define TXB0EID0   0x34
# define TXB1EID0   0x44
# define TXB2EID0   0x54

/*
 * TXBnDLC: TRANSMIT BUFFER n DATA LENGTH CODE REGISTER
 * 4Bits (0000 1000 if IF u write(1111 is =1000 (8 bytes (CLassical CAN)) )
 * RTR bit
 */
#define  TXB0DLC    0x35
#define  TXB1DLC    0x45
#define  TXB2DLC    0x55

/*
 *  TXBnDm: TRANSMIT BUFFER n DATA BYTE m REGISTER
 *  TXB0D0 to TXB0D8 FOR FIRST BUFFER
 *  TXB1D0 to TXB2D8 FOR SECOND BUFFER
 *  TXB2D0 t0 TXB2D8 For THIRD BUFFER
 *  n= 0 to 8 determine (DLC)
 */
#define TXB0D0   0x36
#define TXB0D1   0x37
#define TXB0D2   0x38
#define TXB0D3   0x39
#define TXB0D4   0x3A
#define TXB0D5   0x3B
#define TXB0D6   0x3C
#define TXB0D7   0x3D

#define TXB1D0   0x46
#define TXB1D1   0x47
#define TXB1D2   0x48
#define TXB1D3   0x49
#define TXB1D4   0x4A
#define TXB1D5   0x4B
#define TXB1D6   0x4C
#define TXB1D7   0x4D

#define TXB2D0   0x56
#define TXB2D1   0x57
#define TXB2D2   0x58
#define TXB2D3   0x59
#define TXB2D4   0x5A
#define TXB2D5   0x5B
#define TXB2D6   0x5C
#define TXB2D7   0x5D

/*
 * CANCTRL: CAN CONTROL REGISTER (ADDRESS: XFh)
 * CANSTAT: CAN STATUS REGISTER (ADDRESS: XEh)
 */
#define CANCTRL  0x0F
#define CANSTAT  0x0E
/******************************* RECIEVE PART ***************************/
/*
 * BUFFER RECIEVE REG
 * Not make casting or volatile because Address JUst Data
 */
#define RXB0CTRL  0x60
#define RXB1CTRL  0x70

/*
 * Filter Register
 * value want to mask on it
*/
#define RXF0SIDH 0x00
#define RXF1SIDH 0x04
#define RXF2SIDH 0x08
#define RXF3SIDH 0x10
#define RXF4SIDH 0x14
#define RXF5SIDH 0x18
/*
 * Mask Register
*/
#define RXM0SIDH 0x20
#define RXM1SIDH 0x24
/*
 * CAN Interrupt Enable buffer
*/
#define CANINTE  0x2B
/*
 * CAN Interrupt flag
*/
#define CANINTF  0x2C

#define BFPCTRL  0x0C
#endif /* MP2515_PRIVATE_H_ */
