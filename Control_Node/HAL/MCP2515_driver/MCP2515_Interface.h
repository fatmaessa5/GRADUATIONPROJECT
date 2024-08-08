/*
 * MCP2515_Interface.h
 *
 *  Created on: Ù Ù¡â€�/Ù¡Ù¡â€�/Ù¢Ù Ù¢Ù¢
 *      Author: DELL
 */

#ifndef MCP2515_INTERFACE_H_
#define MCP2515_INTERFACE_H_


//#include "../../LIB/BIT_MATH.h"
//
//#include "../../MCAL/DIO_V1/DIO_reg.h"
//#include "../../MCAL/DIO_V1/DIO_init.h"
//
//#include "../../MCAL/SPI_driver/SPI_Registers.h"
//#include "../../MCAL/SPI_driver/SPI_Interface.h"
///* _____________________ */
//
//#include "MCP2515_Programe.h"
//#include "MP2515_Private.h"


/***********************************************************************************
 *         --------------------- Declaration Section -------------------        *
 ***********************************************************************************/

void HMCP2515_voidWriteReg(    u8 Copy_u8RegAddress , u8 Copy_u8Data);
u8 HMCP2515_U8ReadReg(         u8 Copy_u8RegAddress);
void HMCP2515_voidResetInst(void);
void  HMCP2515_voidBitModify(  u8 Copy_RegAddress ,u8 Copy_u8Mask    ,u8 Copy_U8Data   );
void HMCP2515_voidSetBitTiming(u8 Copy_U8CNFVAL1  ,u8 Copy_U8CNFVAL2 ,u8 Copy_U8CNFVAL3);
void HMCP2515_voidSetMode(     u8 Copy_U8Mode);
void HMCP2515_voidInitTransimiter(void);
void HMCP2515_VidSendCAN_Msg(  u8 Copy_u8Address , u32 Copy_u8MsgID   ,u8 Copy_u8DataLen_DLC , u8*Copy_u8data);
void HMCP2515_voidRecieveMess(u8 Copy_u8REC_Buff_addres) ;
void HMCP2515_voidRecievInit(void);
void HMCP2515_voidSetMask(u8 Copy_u8address_mask_Reg ,u32 Copy_u32Mask_Value ,u8 Copy_u8Extended);
void HMCP2515_voidRollOver(u8 BUKT);
/****************************************************************************
 *                            SPI INTERFACE
 ****************************************************************************/
/*  SPI INSTRUCTION SET */

#define MCP2515_RESET_INST                   0XC0
#define MCP2515_READ_INST                    0X03
#define MCP2515_WRITE_INST                   0x02
#define MCP2515_MREG2SENDTXB1_INST           0x82
#define MCP2515_MREG2SENDTXB0_INST           0x81
#define MCP2515_MREG2SENDTXB2_INST           0x84
#define MCP2515_BITMODIFY_INST               0x05
#define MCP2515_RXSTATUS_INST                0xB0
#define MCP2515_READSTATUS_INST              0xA0

/***************************************************************************
 *                         MODES OF CAN CONTROLER OPERATION
 ***************************************************************************/
#define NORMAL_MODE      0x0
#define CONFIG_MODE      0x4
#define SLEEP_MODE       0x1
#define lOOPBACK_MODE    0x2
#define LISTENONLY_MODE  0x3

/***
 *
 */
/**************************************************************************
 *                      Bit Timing Configuration
                               Registers
 **************************************************************************/
 /*  CNF1: CONFIGURATION REGISTER 1 */
/*
 * SJW[1:0]: Synchronization Jump Width Length bits
11 = Length = 4 x TQ(TQ IS QUANTA TIME)
10 = Length = 3 x TQ
01 = Length = 2 x TQ
00 = Length = 1 x TQ
 */
#define SJW1   7
#define SJW0   6

/*
 * BRP[5:0]: Baud Rate Prescaler bits (TQ ==SYNCH SEGMENT)
TQ = 2 x (BRP[5:0] + 1)/FOSC FOSC is Micro FREq.
 */
#define BRP5   5
#define BRP4   4
#define BRP3   3
#define BRP2   2
#define BRP1   1
#define BRP0   0

/* CNF2: CONFIGURATION REGISTER 2 */
/*
 * BTLMODE: PS2 Bit Time Length bit
1 = Length of PS2 is determined by the PHSEG2[2:0] bits of CNF3
0 = Length of PS2 is the greater of PS1 and IPT (2 TQs) (DEtermine Automatic )
 */
#define BTLMODE       7
/*
 * SAM: Sample Point Configuration bit
1 = Bus line is sampled three times at the sample point
0 = Bus line is sampled once at the sample point
 */
#define SAM           6
/*
 * PHSEG1[2:0]: PS1 Length bits
(PHSEG1[2:0] + 1) x TQ
 */
#define PHSEG2        5
#define PHSEG1        4
#define PHSEG0        3
/*
 * PRSEG[2:0]: Propagation Segment Length bits
(PRSEG[2:0] + 1) x TQ
 */
#define PRSEG2        2
#define PRSEG1        1
#define PRSEG0        0

/* CNF3: CONFIGURATION REGISTER 3 */
/*
 * SOF: Start-of-Frame signal bit
If CLKEN (CANCTRL[2]) = 1:
1 = CLKOUT pin is enabled for SOF signal
0 = CLKOUT pin is enabled for clock out function
If CLKEN (CANCTRL[2]) = 0:
Bit is donâ€™t care.
 */
#define SOF           7
/*
 * WAKFIL: Wake-up Filter bit
1 = Wake-up filter is enabled
0 = Wake-up filter is disabled
 */
#define WAKFIL        6
/* Unimplemented: Reads as â€˜0â€™*/
//#define U_0           5
//#define U_0           4
//#define U_0           3
/*
 * PHSEG2[2:0]: PS2 Length bits
(PHSEG2[2:0] + 1) x TQ. Minimum valid setting for PS2 is 2 TQs
 */
#define PHSEG2_2      2
#define PHSEG2_1      1
#define PHSEG2_0      0
/***************************************************************************
 *                              TXBnCTRL REG BITS                          *
 **************************************************************************/

/*
 * TXP[1:0]: Transmit Buffer Priority bits
11 = Highest message priority
10 = High intermediate message priority
01 = Low intermediate message priority
00 = Lowest message priorit
Message ins_ide MCP2515 CONtroler (Any message will send first inside MCP2515)
 */
#define TXP0    0
#define TXP1    1
/* Unimplemented Bit : Read as â€˜0â€™ */
//#define U_0     2
/*
 * ABTF: Message Aborted Flag bit
1 = Message was aborted
0 = Message completed transmission successfully
*/
#define ABTF    3
/*
 * MLOA: Message Lost Arbitration bit
1 = Message lost arbitration while being sent
0 = Message did not lose arbitration while being sent
*/
#define MLOA    4
/*
 * TXERR: Transmission Error Detected bit
1 = A bus error occurred while the message was being transmitted
0 = No bus error occurred while the message was being transmitted
TXREQ: Message Transmit Request bit
1 = Buffer is currently pending transmission
(MCU sets this bit to request message be transmitted â€“ bit is automatically cleared when the
message is sent)
0 = Buffer is not currently pending transmission
(MCU can clear this bit to request a message abort)
 */
#define TXERR    5
#define TXREQ    6
/* Unimplemented Bit : Read as â€˜0â€™ */
//#define U_0     7
/***************************************************************************
 *                              TXRTSCTRL REG BITS
 *                      TXnRTS PIN CONTROL AND STATUS REGISTER                         *
 **************************************************************************/
/*
 * BIT 6 ,BIT 7  are Reserved
 *
 */
/*********88
 TXnRTS Pin State bit n=1,2,3
- Reads state of TX2RTS pin when in Digital Input mode
- Reads as â€˜0â€™ when pin is in Request-to-Send mode
 */
#define B2RTS    5
#define B1RTS    4
#define B0RTS    3
/*
 * TXnRTS Pin mode bit (n=0,1,2)
1 = Pin is used to request message transmission of TXB0 buffer (on falling edge)
0 = Digital input
 *
 */
#define B2RTSM   2
#define B1RTSM   1
#define B0RTSM   0
/*************************************************************************
 *                        CANCTRL REG BITS
 *************************************************************************/
/*
 * REQOP[2:0]: Request Operation Mode bits
000 = Sets Normal Operation mode (MOndatory )
001 = Sets Sleep mode (CAN_FD Send DAta At network AND there classic CAN  )
010 = Sets Loopback mode
011 = Sets Listen-Only mode
100 = Sets Configuration mode (used when we configure BIT TIMING )
All other values for the REQOPn bits are invalid and should not be used. On power-up, REQOP[2:0] = bâ€™100â€™
 */
#define REQOP2  7
#define REQOP1  6
#define REQOP0  5
/*
 * ABAT: Abort All Pending Transmissions bit (SOMETIME USED)
1 = Requests abort of all pending transmit buffers
0 = Terminates request to abort all transmissions
 */
#define ABAT    4
/*
 * OSM: One-Shot Mode bit
1 = Enabled; messages will only attempt to transmit one time
0 = Disabled; messages will reattempt transmission if required
 */
#define OSM     3
/*
 * CLKEN: CLKOUT Pin Enable bit (Must enable AT Init)
1 = CLKOUT pin is enabled
0 = CLKOUT pin is disabled (pin is in high-impedance state)
 */
#define CLKEN    2

/*
 * CLKPRE[1:0]: CLKOUT Pin Prescaler bits
00 =FCLKOUT = System Clock/1
01 =FCLKOUT = System Clock/2
10 =FCLKOUT = System Clock/4
11 =FCLKOUT = System Clock/8
 *
 */
#define CLKPRE1   1
#define CLKPRE0   0

/**************************************************************************
 *                         CANSTAT REG BITS
 ***************************************************************************/
/*
 * CANSTAT Used to Know Operation Mode of Control=er
 * OPMOD[2:0]: Operation Mode bits
000 = Device is in Normal Operation mode
001 = Device is in Sleep mode
010 = Device is in Loopback mode
011 = Device is in Listen-Only mode
100 = Device is in Configuration mode
 */
#define OPMOD2   7
#define OPMOD1   6
#define OPMOD0   5
/*
 *  Unimplemented: Read as â€˜0â€™
 */
//#define U_0      4
/*
 ICOD[2:0]: Interrupt Flag Code bits
000 = No interrupt
001 = Error interrupt
010 = Wake-up interrupt
011 = TXB0 interrupt
100 = TXB1 interrupt
101 = TXB2 interrupt
110 = RXB0 interrupt
111 = RXB1 interrupt
 */
#define ICOD2    3
#define ICOD1    2
#define ICOD0    1
/*
 *  Unimplemented: Read as â€˜0â€™
 */
//#define U_0      0
/**************************************************************************
 *                            TXBnSIDH REG BITS
 **************************************************************************/
/* SID[10:3]: Standard Identifier bits */
#define SID3  0
#define SID4  1
#define SID5  2
#define SID6  3
#define SID7  4
#define SID8  5
#define SID9  6
#define SID10 7
/***************************************************************************
 *                            TXBnSIDL REG BITS
 ***************************************************************************/
/*
 * SID[2:0]: Standard Identifier bits
 */
#define SID2  7
#define SID1  6
#define SID0  5
/* Unimplemented: Read as â€˜0â€™ */
//#define U_0   4
/*
 * EXIDE: Extended Identifier Enable bit
1 = Message will transmit Extended Identifier
0 = Message will transmit Standard Identifier
 */
#define EXIDE 3
/* Unimplemented: Read as â€˜0â€™ */
//#define U_0   2
/* EID[17:16]: Extended Identifier bits */
#define EID17 1
#define EID16 0
/***************************************************************************
 *                            TXBnEID8 REG BITS
 ***************************************************************************/
/*  EID[15:8]: Extended Identifier bits  */

#define EID15   7
#define EID14   6
#define EID13   5
#define EID12   4
#define EID11   3
#define EID10   2
#define EID9    1
#define EID8    0

/***************************************************************************
 *                            TXBnEID0 REG BITS
 ***************************************************************************/
/* EID[7:0]: Extended Identifier bits */
#define EID7     7
#define EID6     6
#define EID5     5
#define EID4     4
#define EID3     3
#define EID2     2
#define EID1     1
#define EID0     0
/****************************************************************************
 *                            TXBnDLC REG BITS
 *****************************************************************************/
/* Unimplemented: Read as â€˜0â€™ */
//#define U_0  7
/*
 * RTR: Remote Transmission Request bit
1 = Transmitted message will be a remote transmit request
0 = Transmitted message will be a data frame
 */
#define RTR  6
/* Unimplemented: Read as â€˜0â€™ */
//#define U_0  5
//#define U_0  4
/*
 * DLC[3:0]: Data Length Code bits(1)
Sets the number of data bytes to be transmitted (0 to 8 bytes)
 */
#define DLC3 3
#define DLC2 2
#define DLC1 1
#define DLC0 0

/****************************************************************************
 *                              TXBnDm REG BITS
 ***************************************************************************/
/*
 * TXBnDm[7:0]: Transmit Buffer n Data Field Byte m bits
 *
 */
/****************************************************************************
 *                               Receive Register
 ***************************************************************************/

/********** ********* ************** RXB0CTRL Reg  ********* ****** ******* *********/
/*
 *  RXB0CTRL: RECEIVE BUFFER 0 CONTROL REGISTER
 */
/* bit 7 Unimplemented: Read as â€˜0â€™ */
#define U_0     7
#define U_0     4
/*
 * RXM[1:0]: Receive Buffer Operating mode bits
11 = Turns mask/filters off; receives any message
10 = Reserved
01 = Reserved
00 = Receives all valid messages using either Standard or Extended Identifiers that meet filter criteria;
Extended ID Filter registers, RXFnEID8:RXFnEID0, are applied to the first two bytes of data in
the messages with standard IDs
 */
#define  RXM0   6
#define  RXM0   5
/*
 * RXRTR: Received Remote Transfer Request bit
1 = Remote Transfer Request received
0 = No Remote Transfer Request received
 */
#define RXRTR   3
/*
 * BUKT: Rollover Enable bit
1 = RXB0 message will roll over and be written to RXB1 if RXB0 is full
0 = Rollover is disabled
 */
#define BUKT    2
/*
 * BUKT1: Read-Only Copy of BUKT bit (used internally by the MCP2515)
 */
#define BUKT1   1
/*
 * FILHIT0: Filter Hit bit (indicates which acceptance filter enabled reception of message)(1)
1 = Acceptance Filter 1 (RXF1)
0 = Acceptance Filter 0 (RXF0)

( Note 1: If a rollover from RXB0 to RXB1 occurs, the FILHIT0 bit will reflect the filter that accepted the message
that rolled over )
 */
#define FILHIT0 0

/********** ********* ************** RXB1CTRL Reg  ********* ****** ******* *********/
/*
 *  RXB1CTRL: RECEIVE BUFFER 1 CONTROL REGISTER
 */
/* bit 7 Unimplemented: Read as â€˜0â€™ */
#define U_1     7
#define U_1     4
/*
 * RXM[1:0]: Receive Buffer Operating mode bits
11 = Turns mask/filters off; receives any message
10 = Reserved
01 = Reserved
00 = Receives all valid messages using either Standard or Extended Identifiers that meet filter criteria;
Extended ID Filter registers, RXFnEID8:RXFnEID0, are applied to the first two bytes of data in
the messages with standard IDs
 */
#define  RXM1   6
#define  RXM1   5
/*
 * RXRTR: Received Remote Transfer Request bit
1 = Remote Transfer Request received
0 = No Remote Transfer Request received
 */
#define RXRTR   3
/*
 * FILHIT[2:0]: Filter Hit bits (indicates which acceptance filter enabled reception of message)
101 = Acceptance Filter 5 (RXF5)
100 = Acceptance Filter 4 (RXF4)
011 = Acceptance Filter 3 (RXF3)
010 = Acceptance Filter 2 (RXF2)
001 = Acceptance Filter 1 (RXF1) (only if the BUKT bit is set in RXB0CTRL)
000 = Acceptance Filter 0 (RXF0) (only if the BUKT bit is set in RXB0CTRL)
 *
*/
#define FLIGHT2  2
#define FLIGHT1  1
#define FLIGHT0  0

/*********************************** RXBnSIDH ************************************/
/*
 * RXBnSIDH: RECEIVE BUFFER n STANDARD IDENTIFIER REGISTER HIGH
 */
/* SID[10:3]: Standard Identifier bits
These bits contain the eight Most Significant bits of the Standard Identifier for the received message.
*/

/********************************** RXBnSIDL **********************************/

/*
 * RXBnSIDL: RECEIVE BUFFER n STANDARD IDENTIFIER REGISTER LOW
 */
/*
 * SID[2:0]: Standard Identifier bits
These bits contain the three Least Significant bits of the Standard Identifier for the received message
 */
#define SID2   7
#define SID1   6
#define SID0   5
/*
 * SRR: Standard Frame Remote Transmit Request bit (valid only if IDE bit = 0)
1 = Standard frame Remote Transmit Request received
0 = Standard data frame received
 */
#define SRR    4
/*
 *IDE: Extended Identifier Flag bit
This bit indicates whether the received message was a standard or an extended frame.
1 = Received message was an extended frame
0 = Received message was a standard frame
 */
#define IDE    3

/*
 * Unimplemented: Read as â€˜0â€™
 */
#define U_2    2
/*
 * EID[17:16]: Extended Identifier bits
These bits contain the two Most Significant bits of the Extended Identifier for the received message
 */
#define EID17  1
#define EID16  0

/******************************* RXBnEID8 ********************************/
/* RXBnEID8: RECEIVE BUFFER n EXTENDED IDENTIFIER REGISTER HIGH */

/*
 * EID[15:8]: Extended Identifier bits
These bits hold bits 15 through 8 of the Extended Identifier for the received message
 */

/******************************  RXBnEID0 *******************************/
/* RXBnEID0: RECEIVE BUFFER n EXTENDED IDENTIFIER REGISTER LOW */

/*EID[7:0]: Extended Identifier bits
These bits hold the Least Significant eight bits of the Extended Identifier for the received message
*/
/****************************** RXBnDLC: *********************************/
/* Unimplemented: Read as â€˜0â€™ */
#define U_3   7
/*
 *RTR: Extended Frame Remote Transmission Request bit (valid only when IDE (RXBnSIDL[3]) = 1)
1 = Extended frame Remote Transmit Request received
0 = Extended data frame received
 */
#define RTR   6

/*
 * bit 5 RB1: Reserved Bit 1
   bit 4 RB0: Reserved Bit 0
 */

/*
 * bit 3-0 DLC[3:0]: Data Length Code bits
Indicates the number of data bytes that were received.
 */
#define DLC3   3
#define DLC2   2
#define DLC1   1
#define DLC0   0

/******************************  RXBnDm **************************/
/* RXBnDm: RECEIVE BUFFER n DATA BYTE m REGISTER */
/*
 *bit 7-0 RBnD[7:0]: Receive Buffer n Data Field Bytes m bits
Eight bytes containing the data bytes for the received message
 *
 */
/*********************************************************************************
 *                               FILTER
**********************************************************************************/
/** RXFnSIDH: FILTER n STANDARD IDENTIFIER REGISTER HIGH */
/*
 * SID[10:3]: Standard Identifier Filter bits
These bits hold the filter bits to be applied to bits[10:3] of the Standard Identifier portion of a received
message
*/

/** RXFnSIDL: FILTER n STANDARD IDENTIFIER REGISTER LOW */
/*
 * SID[2:0]: Standard Identifier Filter bits
These bits hold the filter bits to be applied to bits[2:0] of the Standard Identifier portion of a received
message.
 */
#define SID2   7
#define SID1   6
#define SID0   5
/*
 * EXIDE: Extended Identifier Enable bit
1 = Filter is applied only to extended frames
0 = Filter is applied only to standard frames
 */
#define EXIDE  3

/*
 * EID[17:16]: Extended Identifier Filter bits
These bits hold the filter bits to be applied to bits[17:16] of the Extended Identifier portion of a received
message
 */
#define EID17     1
#define EID16     0
/*
 * Unimplemented: Read as â€˜0â€™
 */

/** RXFnEID8: FILTER n EXTENDED IDENTIFIER REGISTER HIGH */
/*
 * EID[15:8]: Extended Identifier bits
These bits hold the filter bits to be applied to bits[15:8] of the Extended Identifier portion of a received
message or to Byte 0 in received data if the corresponding RXM[1:0] bits = 00 and EXIDE = 0.
 */
/** RXFnEID0: FILTER n EXTENDED 1 REGISTER LOW */
/*
 * EID[7:0]: Extended Identifier bits
These bits hold the filter bits to be applied to bits[7:0] of the Extended Identifier portion of a received
message or to Byte 1 in received data if the corresponding RXM[1:0] bits = 00 and EXIDE = 0
 */
/*********************************************************************************
 *                                 MASK
**********************************************************************************/
/** RXMnSIDH: MASK n STANDARD IDENTIFIER REGISTER HIGH */
/*
 * SID[10:3]: Standard Identifier Mask bits
These bits hold the mask bits to be applied to bits[10:3] of the Standard Identifier portion of a received
message
 */

/** RXMnSIDL: MASK n STANDARD IDENTIFIER REGISTER LOW  */
/*
 * SID[2:0]: Standard Identifier Mask bits
These bits hold the mask bits to be applied to bits[2:0] of the Standard Identifier portion of a received
message
 */
#define SID2   7
#define SID1   6
#define SID0   5
/*
 * bit 4-2 Unimplemented: Reads as â€˜0â€™
 *
*/
/*
 * EID[17:16]: Extended Identifier Mask bits
These bits hold the mask bits to be applied to bits[17:16] of the Extended Identifier portion of a received
message
 */
#define EID17     1
#define EID16     0
/**RXMnEID8: MASK n EXTENDED IDENTIFIER REGISTER HIGH  */
/*
 * EID[15:8]: Extended Identifier bits
These bits hold the filter bits to be applied to bits[15:8] of the Extended Identifier portion of a received
message. If the corresponding RXM[1:0] bits = 00 and EXIDE = 0, these bits are applied to Byte 0 in
received data
 */
/** RXMnEID0: MASK n EXTENDED IDENTIFIER REGISTER LOW */
/*
 * EID[7:0]: Extended Identifier Mask bits
These bits hold the filter bits to be applied to bits[7:0] of the Extended Identifier portion of a received
message. If the corresponding RXM[1:0] bits = 00 and EXIDE = 0, these bits are applied to Byte 1 in
received data.
 */
/********************************** CANITE ***************************/
/** CANINTE: CAN INTERRUPT ENABLE REGISTER */
/*
 * bit 7 MERRE: Message Error Interrupt Enable bit
1 = Interrupt on error during message reception or transmission
0 = Disabled
bit 6 WAKIE: Wake-up Interrupt Enable bit
1 = Interrupt on CAN bus activity
0 = Disabled
bit 5 ERRIE: Error Interrupt Enable bit (multiple sources in EFLG register)
1 = Interrupt on EFLG error condition change
0 = Disabled
bit 4 TX2IE: Transmit Buffer 2 Empty Interrupt Enable bit
1 = Interrupt on TXB2 becoming empty
0 = Disabled
bit 3 TX1IE: Transmit Buffer 1 Empty Interrupt Enable bit
1 = Interrupt on TXB1 becoming empty
0 = Disabled
bit 2 TX0IE: Transmit Buffer 0 Empty Interrupt Enable bit
1 = Interrupt on TXB0 becoming empty
0 = Disabled
bit 1 RX1IE: Receive Buffer 1 Full Interrupt Enable bit
1 = Interrupt when message was received in RXB1
0 = Disabled
bit 0 RX0IE: Receive Buffer 0 Full Interrupt Enable bit
1 = Interrupt when message was received in RXB0
0 = Disabled
 *
 */
#define MERRE  7
#define WAKIE  6
#define ERRIE  5
#define TX2IE  4
#define TX1IE  3
#define TX0IE  2
#define RX1IE  1
#define RX0IE  0

/************************************ CANINTF *****************************/
/** CANINTF: CAN INTERRUPT FLAG REGISTER */
/*
 * bit 7 MERRF: Message Error Interrupt Flag bit
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
bit 6 WAKIF: Wake-up Interrupt Flag bit
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
bit 5 ERRIF: Error Interrupt Flag bit (multiple sources in EFLG register)
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
bit 4 TX2IF: Transmit Buffer 2 Empty Interrupt Flag bit
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
bit 3 TX1IF: Transmit Buffer 1 Empty Interrupt Flag bit
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
bit 2 TX0IF: Transmit Buffer 0 Empty Interrupt Flag bit
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
bit 1 RX1IF: Receive Buffer 1 Full Interrupt Flag bit
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
bit 0 RX0IF: Receive Buffer 0 Full Interrupt Flag bit
1 = Interrupt is pending (must be cleared by MCU to reset the interrupt condition)
0 = No interrupt is pending
 *
 */
#define MERRF  7
#define WAKIF  6
#define ERRIF  5
#define TX2IF  4
#define TX1IF  3
#define TX0IF  2
#define RX1IF  1
#define RX0IF  0
#endif /* MCP2515_INTERFACE_H_ */
