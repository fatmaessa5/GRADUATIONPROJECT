#include "../LIB/STD_TYPES.h"

#include "../MCAL/USART_Driver_V1/USART_ErrorTypes.h"
#include "../MCAL/USART_Driver_V1/USART_Init.h"

#include "../HAL/LCD_Handler_V2/LCD_err.h"
#include "../HAL/LCD_Handler_V2/LCD_int.h"

#include "../MCAL/EXTI_Driver_V3/EXTI_int.h"
#include "../MCAL/DIO_V2/DIO_init.h"
#include "../HAL/IR_Remote_V2/IR_Interface.h"
#include "../HAL/LED_Handler_V1/LED_int.h"
#include "avr/delay.h"
#include "../HAL/MCP2515_driver_V2/MCP2515_Interface.h"
#include "../HAL/MCP2515_driver_V2/MP2515_Private.h"

/*Definition Section */
#define _Data_Msg_Lentgh_  3
#define CAN_Msg_ID         (u32)0x03

#define APP_GO_FORWORD		(u16)3
#define APP_GO_BACKWORD		(u16)2
#define APP_GO_LEFT			(u16)14
#define APP_GO_RIGHT		(u16)26
#define APP_STOP_CAR		(u16)7

//Functions Prototypes
void APP_Recieve_Data_Usart(u8 data);
void APP_Recieve_Data_CAN(void);

//External Objects
extern u8 REC_Message[];

//Global Objects
static u8 Global_SignBuffer[3];
static u8 Global_SignFlag;


u8 CAN_Msg[] ={"B"}   ;
u8 CAN_MESSAGE_1 []= {'I','f','#'};
u8 CAN_MESSAGE_2 []= {'I','b','#'};
u8 CAN_MESSAGE_3 []= {'I','l','#'};
u8 CAN_MESSAGE_4 []= {'I','r','#'};
u8 CAN_MESSAGE_5 []= {'I','s','#'};

int main(){
	LED_e arr[] = {LED_e_1,LED_e_2,LED_e_3,LED_e_4,LED_e_5, LED_e_7};
	LED_vidInit(arr,6);
	//USART Configurations.
	USART_Config_t Local_Usart_STR = {.usart_charSize_slct = USART_CharcterSize_t_8,
			.usart_circuit_enable = USART_Enable_t_TXAndRXEnable,
			.usart_parity = USART_ParityMode_t_Disable,
			.usart_speed_slct = USART_Speed_t_NormalSpeed,
			.usart_stopBits_slct = USART_StopBitSlct_t_OneBit
	};

	//LCD Initialization.
	LCD_vidInit();
	IR_Init() ;



	//External Interrupt Configurations.
	EXTI_u8SetSource(EXTI_INT_0, EXTI_FALLING_EDGE);
	EXTI_voidSet_INT0_Cbf(APP_Recieve_Data_CAN);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();

	//CAN Initialization.
	//HMCP2515_voidInitTransimiter() ;
	//HMCP2515_voidRecievInit();

	//USART Initialization.
	USART_init(&Local_Usart_STR);
	USART_ReceiveData_interrupt(APP_Recieve_Data_Usart);


	while(1)
	{
		LCD_vidClear();
		LCD_vidSendInt(ir_signal);

		//IR Remote code
		switch(ir_signal)
		{
		case APP_GO_FORWORD://up
			LED_vidTurnOnLed(LED_e_1);
			//Send the direction to the adaptive node.
            //HMCP2515_VidSendCAN_Msg(TXB0CTRL , CAN_Msg_ID , _Data_Msg_Lentgh_, CAN_MESSAGE_1);

			break;
		case APP_GO_RIGHT://right
			LED_vidTurnOnLed(LED_e_2);
			//Send the direction to the adaptive node.
			//HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID , _Data_Msg_Lentgh_ , CAN_MESSAGE_4);

			break;
		case APP_GO_LEFT://left
			LED_vidTurnOnLed(LED_e_3);
			//Send the direction to the adaptive node.
			//HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID, _Data_Msg_Lentgh_, CAN_MESSAGE_3);

			break;
		case APP_GO_BACKWORD://down
			LED_vidTurnOnLed(LED_e_4);
			//Send the direction to the adaptive node.
			//HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID, _Data_Msg_Lentgh_, CAN_MESSAGE_2);

			break;
		case APP_STOP_CAR://ok
			LED_vidTurnOnLed(LED_e_5);
			//Send the direction to the adaptive node.
			//HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID, _Data_Msg_Lentgh_, CAN_MESSAGE_5);

			break;
		}

		//Check if data is received using the can
		if(Global_SignFlag == 1)
		{
			//Check if the data is sign data received from the master node.
			if(Global_SignBuffer[0] == 'S')
			{
				switch(Global_SignBuffer[1]){
				case 's':
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Speed Sign");
					LCD_u8Goto(2,1);
					LCD_vidSendString("Speed : ");
					LCD_vidSendInt(Global_SignBuffer[2]);
					break;
				case 'b':
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Bump");
					break;
				case 'l':
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Turn Left");
					break;
				case 'r':
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Turn right");
					break;

				}
			}
			//Check if the data is speed data received from the adaptive node.
			else if(Global_SignBuffer[0] == 'V')
			{
				LCD_vidClear();
				LCD_u8Goto(2,1);
				LCD_vidSendString("Speed = ");
				LCD_vidSendInt(Global_SignBuffer[1]);
			}

			Global_SignFlag = 0;
		}


	}

}


void APP_Recieve_Data_Usart(u8 data)
{
	//	LCD_vidWriteChar(data);
	if(data == 'B')
	{
		//Send B to the adaptive node by CAN
		HMCP2515_VidSendCAN_Msg(TXB0CTRL ,CAN_Msg_ID ,_Data_Msg_Lentgh_ ,CAN_Msg) ;
	}
}

void APP_Recieve_Data_CAN(void)
{
	//Receive data from the Routing and the adaptive nodes.
	HMCP2515_voidRecieveMess(RXB0CTRL) ;
	//the routing node should send the sign.
	//the adaptive node should send the current speed.
	u8 _Data_Lentgh_Rec_ = REC_Message[5] ;
	//Store the received data into the SignBuffer.

	for( u8 Index =0 ; Index < 3; Index++)
	{
		Global_SignBuffer [Index]= REC_Message[6 + Index] ;
	}

	//Set the flag to indicate that data is received.
	Global_SignFlag = 1;
}
