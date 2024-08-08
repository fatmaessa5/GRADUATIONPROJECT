/*
 * Main.c
 *
 *  Created on: Jun 20, 2023
 *      Author: musta
 */

#include "../LIB/STD_TYPES.h"

#include "../HAL/MCP2515_driver/MP2515_Private.h"
#include "../HAL/MCP2515_driver/MCP2515_Interface.h"

#include "../MCAL/Timer0_Driver_V4/Timer0_int.h"
#include "avr/interrupt.h"
#include "../MCAL/EXTI_Driver_V2/EXTI_int.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

//Preprocessor macros
#define LEFT_MOTOR_SPEED	((u8)70)
#define RIGHT_MOTOR_SPEED	((u8)100)

//Function Prototypes
void systemInit(void);
void EXTI_CallBackFUNC(void);
void Send_SpeedTask(void);

//External variables
extern u8 REC_Message[];

//Global Objects
static u8 Global_Turn_Left_[2] =  {70  , 100} ;
static u8 Global_Turn_Right_[2] =  {100 , 70 } ;

QueueHandle_t xQueue;

void main()
{
	//System Initialization
	systemInit();

	//Queue Creation (By default taken).
	xQueue = xQueueCreate(2, 1);

	/* Create Tasks */
	xTaskCreate(Send_SpeedTask, "Send_SpeedTask", 120, NULL, 1, NULL);

	/* Start OS */
	vTaskStartScheduler();

	while(1);

}

void systemInit(void)
{

	//EXTI Initialization
	EXTI_voidSet_INT0_Cbf(&EXTI_CallBackFUNC);
	EXTI_u8SetSource( EXTI_INT_0,EXTI_FALLING_EDGE);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();

	//CAN Initialization
	HMCP2515_voidRecievInit();
	HMCP2515_voidInitTransimiter();

}

void EXTI_CallBackFUNC(void)
{
	u8 Local_u8Data;

	//Receive CAN message
	HMCP2515_voidRecieveMess(RXB0CTRL);

	//Store the data.
	Local_u8Data =  REC_Message[6];

	//Push the data into the queue.
	xQueueSendFromISR(xQueue, &Local_u8Data, NULL);

}

void Send_SpeedTask(void){

	u8 Local_u8RX_Data = 0;

	while(1){

		//Receive data from the queue.
		if(xQueueReceive(xQueue, &Local_u8RX_Data, portMAX_DELAY)){

			if(Local_u8RX_Data == 'l'){

				// speed of the motors
				HMCP2515_VidSendCAN_Msg(TXB0CTRL, 0x7E1, 2, Global_Turn_Left_);

			}
			else if(Local_u8RX_Data == 'r'){

				// speed of the motors
				HMCP2515_VidSendCAN_Msg(TXB0CTRL, 0x7E1, 2 , Global_Turn_Right_);
			}
			else{
				//wrong message
			}

			Local_u8RX_Data = 0;

		}
	}

}
