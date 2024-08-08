
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// Include HAL
#include "../HAL/MCP2515_driver/MCP2515_Interface.h"
#include "../HAL/MCP2515_driver/MP2515_Private.h"


/* Include MCAL */
#include "../MCAL/DIO_V1/DIO_init.h"
#include "../MCAL/SPI_driver/SPI_Interface.h"
#include "../MCAL/EXTI_Driver_V2/EXTI_int.h"
#include "../MCAL/UART/USART_ErrorTypes.h"
#include "../MCAL/UART/USART_Init.h"

#include "../HAL/LCD_Handler_V2/LCD_err.h"
#include "../HAL/LCD_Handler_V2/LCD_int.h"

#include"../HAL/LED_Handler_V1/LED_int.h"

#include "string.h"
#include "avr/delay.h"

// End character :
#define		_END_CHAR_ 				'#'
// Signs bits :
#define  	_SIGN_BIT_ 				'S'
#define  	_SIGN_BUMP_BIT_			'b'
#define 	_SIGN_SPEED_BIT_		's'
#define 	_SIGN_TURN_LEFT_BIT_	'l'
#define 	_SIGN_TURN_RIGHT_BIT_	'r'
// Distance :
#define 	_DISTANCE_BIT_			'D'
// Lane :
#define 	_GO_RIGHT_BIT_			'R'
#define 	_GO_LEFT_BIT_			'L'
#define 	_IN_CENTER_BIT_			'C'

#define BUFFER_SIZE					5

u8 Received_Message[BUFFER_SIZE] ;
u8 Transmit_Message[BUFFER_SIZE] ;
volatile u8 Filter_Enable_Bit;
static u8 counter = 0 ;

/* CAN */
volatile u8 App_CANRecMessage ;
extern u8  REC_Message[16] ;

USART_Config_t  UART =
{
		.usart_circuit_enable 	= USART_Enable_t_TXAndRXEnable ,  // rx and tx.
		.usart_parity 			= USART_ParityMode_t_Disable ,	  // no parity.
		.usart_charSize_slct 	= USART_CharcterSize_t_8 ,		  // frame size 8-bit.
		.usart_stopBits_slct 	= USART_StopBitSlct_t_OneBit ,	  // one bit stop bit.
		.usart_speed_slct 		= USART_Speed_t_NormalSpeed		  // 9600
};

static void vUartReceive_Callback( u8 bit );
static void vFilter(u8 *ptdata);
static void vEXT_INT_Receive_Callback(void);
static void vPrintData(void);

int main ()
{
	LED_e LED_ARR[] = {LED_e_1};

	/* UART Interrupt */
	USART_init( &UART );
	USART_ReceiveData_interrupt(vUartReceive_Callback);

	/* External Interrupt */
	EXTI_voidSet_INT0_Cbf(&vEXT_INT_Receive_Callback);
	EXTI_u8SetSource( EXTI_INT_0,EXTI_FALLING_EDGE);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();
	/*  CAN  Init  */
	//	HMCP2515_voidInitTransimiter() ;
	//	HMCP2515_voidRecievInit()      ;

	LCD_vidInit();
	LED_vidInit(LED_ARR,1);

	Filter_Enable_Bit = 0;

	counter = 0;

	while(1)
	{
		if (Filter_Enable_Bit == 1)
		{
			vPrintData();
			counter = 0;
			vFilter(Received_Message);
			Filter_Enable_Bit = 0;
		}
	}
}


void vUartReceive_Callback( u8 bit )
{
	if ( bit != '#'){

		Received_Message[counter] = bit;
	}
	else
	{
		Received_Message[counter] = bit;
		// start action.
		Filter_Enable_Bit = 1 ;
	}
	counter++;

}

void vPrintData(void)
{
	u8 Local_u8Counter = 0;

	LCD_vidClear();

	while(Received_Message[Local_u8Counter] != '#')
	{
		LCD_vidWriteChar(Received_Message[Local_u8Counter]);
		Local_u8Counter++;
	}
	LCD_vidWriteChar(Received_Message[Local_u8Counter]);
}


void vFilter(u8 *ptdata)
{

	u32 _CAN_Msg_ID_ ;
	// start Filter
	u8 Local_u8Counter = 0;

	switch (ptdata[0]) {
	case _DISTANCE_BIT_ : // 'D'
	{

		// send this character and the next one to the [Adaptive Cruise Node] ,then add '$' Using "CAN" , so the final message.
		while(ptdata[Local_u8Counter] != '#'){
			Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
			Local_u8Counter++;
		}
		Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
		Local_u8Counter++;
		// ID FOR Adaptive
		//MASK for Adaptive   0x3
		//Filter ( 1 )  0xff01
		//Filter ( 2 )  0xff12
		//		_CAN_Msg_ID_ =0xff01 ;
		//		HMCP2515_VidSendCAN_Msg(TXB0CTRL , _CAN_Msg_ID_ , Local_u8Counter ,Transmit_Message) ;
		// send this message.

		break;
	}

	case _SIGN_BIT_ :
	{
		if (ptdata[1] == _SIGN_BUMP_BIT_ )
		{
			// send this character and the next one to the [Adaptive Cruise Node] and [InterFace Node] ,then add '$' Using "CAN" , so the final message.
			while(ptdata[Local_u8Counter] != '#'){
				Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
				Local_u8Counter++;
			}
			Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
			Local_u8Counter++;

			// ID FOR Int and Adative is 0Xff02
			//MASK  for interface  0x2
			//Filter ( 1 )  0xff02
			//filter (2)
			//			_CAN_Msg_ID_ =0Xff02 ;
			//			HMCP2515_VidSendCAN_Msg(TXB0CTRL ,_CAN_Msg_ID_ ,Local_u8Counter ,Transmit_Message) ;
			// send this message.

		}
		else if (ptdata[1] == _SIGN_SPEED_BIT_ )
		{
			// send this character and the next one to the [Adaptive Cruise Node] and [InterFace Node] ,then add '$' Using "CAN" , so the final message.
			while(ptdata[Local_u8Counter] != '#'){
				Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
				Local_u8Counter++;
			}
			Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
			Local_u8Counter++;
			//MASK   0x12
			//Filter ( 1 )  0xff02
			//ID  For  Intf and Adative
			//			_CAN_Msg_ID_ =0Xff12  ;
			//			HMCP2515_VidSendCAN_Msg(TXB0CTRL , _CAN_Msg_ID_ ,Local_u8Counter ,Transmit_Message) ;

		}
		else if((ptdata[1] == _SIGN_TURN_LEFT_BIT_ ) || (ptdata[1] == _SIGN_TURN_RIGHT_BIT_))
		{
			// send this character and the next one to the [InterFace Node] and ,then add '$' Using "CAN" , so the final message.
			while(ptdata[Local_u8Counter] != '#'){
				Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
				Local_u8Counter++;
			}
			Transmit_Message[Local_u8Counter] = ptdata[Local_u8Counter];
			Local_u8Counter++;
			//ID  For  Int and Adative
			//Mask   0x10
			//filter[2]    0Xff10
			//			_CAN_Msg_ID_ =0Xff10  ;
			//			HMCP2515_VidSendCAN_Msg(TXB0CTRL , _CAN_Msg_ID_ ,Local_u8Counter ,Transmit_Message) ;

		}
		else{
			LCD_vidClear();
			LCD_vidSendString("Wrong Frame");
		}

		break;
	}

	case _GO_RIGHT_BIT_ :
	case _GO_LEFT_BIT_ :
	case _IN_CENTER_BIT_ :
	{
		// send this character and the next one to the [LANE Node] ,then add '$' Using "CAN" , so the final message.
		Transmit_Message[0] = ptdata[0];
		Local_u8Counter++;

		//ID for Lane Node
		//Mask 0x4
		//filter [1 ] 0X4
		//		_CAN_Msg_ID_ =0X4  ;
		//		HMCP2515_VidSendCAN_Msg(TXB0CTRL , _CAN_Msg_ID_ ,Local_u8Counter ,Transmit_Message) ;
		break;
	}


	default :
		LCD_vidClear();
		LCD_vidSendString("Wrong Frame");
		break;


	}
}

void vEXT_INT_Receive_Callback(void)
{
	HMCP2515_voidRecieveMess(RXB0CTRL) ;
	App_CANRecMessage = REC_Message[6] ;
}

