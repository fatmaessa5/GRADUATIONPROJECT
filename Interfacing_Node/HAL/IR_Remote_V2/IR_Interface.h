/*
 * IR_Remote.h
 *
 *  Created on: Jul 3, 2023
 *      Author: musta
 */

#ifndef HAL_IR_REMOTE_V2_IR_REMOTE_H_
#define HAL_IR_REMOTE_V2_IR_REMOTE_H_

void IR_Init(void);
static void IR_vidGetFrame(void);
static void IR_vidtakeAction(void);
static void IR_vidSetSinglePeriod(u16 ticks, void (*callback)(void));
static u16 IR_u16GetElapsedTime(void);

extern volatile u16 ir_signal  ; // variable to store received IR signal
extern volatile u8 ir_edge_count ; // counter for number of bits received
extern volatile u8 ir_start_flag  ; // flag to indicate whether data is ready
extern volatile u8 ir_frame[50] ;
extern volatile u8 ready;
#endif /* HAL_IR_REMOTE_V2_IR_REMOTE_H_ */
