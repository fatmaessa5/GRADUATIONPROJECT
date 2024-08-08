
/*********************************************** LIB Includes **************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/********************************************** USART Includes ************************************************/
#include "USART_Private.h"
#include "USART_Config.h"
#include "USART_ErrorTypes.h"
#include "USART_Init.h"

#include "avr/interrupt.h"

/********************************************* Global Declarations **************************************/
typedef void (* PointerToFunction)(u8);
static PointerToFunction USART_FPTR = NULL;

/********************************************* Functions Implementations **************************************/

/*********************************************************************************************/
USART_Error_t USART_init(USART_Config_t * Copy_StrPtr)
{
	USART_Error_t Local_ErrorState = USART_Error_t_RT_OK;
	if(NULL == Copy_StrPtr)
	{
		Local_ErrorState = USART_Error_t_RT_NULL_PTR;
	}
	else 
	{

#if USART_MODE == USART_OperMode_t_Sync

		// set the Synchronous operation mode
		USART_UBRRH_UCSRC |= ((1<<7) | (1<<6));			//set the two bits USREL and UMSEL

#elif USART_MODE == USART_OperMode_t_Async
		//set the Asynchronous operation mode --> doNothing (because we can't set the USREL bit and clear the UMSEL bit at the same instruction)

		// set the speed mode
		USART_UCSRA &= (~(1<<1));
		USART_UCSRA |= ((Copy_StrPtr->usart_speed_slct)<<1);

		//set Baud rate to 9600
		if(USART_Speed_t_NormalSpeed == Copy_StrPtr->usart_speed_slct)
		{
			USART_UBRRH_UCSRC = 0;
			USART_UBRRL = 51;

		}
		else if(USART_Speed_t_DoubleSpeed == Copy_StrPtr->usart_speed_slct)
		{
			USART_UBRRH_UCSRC = 0;
			USART_UBRRL = 103;
		}
		else{
			Local_ErrorState = USART_Error_t_RT_WRONG_CONFIG;
		}

#else
		Local_ErrorState = USART_Error_t_RT_WRONG_CONFIG;
#error "Wrong Operation Mode"
#endif

		// set the data size
		if(Copy_StrPtr->usart_charSize_slct == USART_CharcterSize_t_5)
		{
			//DoNothing --> Because we can't set URSEL and clear  UCSZ1 and UCSZ0 at the same time.
		}
		else if(Copy_StrPtr->usart_charSize_slct == USART_CharcterSize_t_9)
		{
			USART_UCSRB |= (1<<2);
			USART_UBRRH_UCSRC |= ((1<<7) | (0b11<<1));
		}
		else
		{
			USART_UBRRH_UCSRC |= ((1<<7) | (Copy_StrPtr->usart_charSize_slct << 1));
		}


		//set the parity mode
		if(Copy_StrPtr->usart_parity == USART_ParityMode_t_Disable)
		{
			//DoNothing --> Because we can't set URSEL and clear UPM1 and UPM0 at the same time.
		}
		else
		{
			USART_UBRRH_UCSRC |= ((1<<7) | (Copy_StrPtr->usart_parity << 4));
		}

		// set the stop bit
		if(Copy_StrPtr->usart_stopBits_slct == USART_StopBitSlct_t_OneBit)
		{
			//DoNothing --> Because we can't set URSEL and clear USBS at the same time.
		}
		else
		{
			USART_UBRRH_UCSRC |= ((1 << 7) | (1 << 3));
		}

		// enable the usart
		USART_UCSRB &= (~(0b11<<3));			//to clear bit3 and bit4
		USART_UCSRB |= (Copy_StrPtr->usart_circuit_enable << 3);
	}

	return Local_ErrorState;
}
/*********************************************************************************************/

/*********************************************************************************************/
USART_Error_t USART_SendData(s16 Copy_s16Data)
{
	USART_Error_t Local_ErrorState = USART_Error_t_RT_OK;

	while(!GET_BIT(USART_UCSRA,5));

	USART_UDR = Copy_s16Data;

	return Local_ErrorState;

}
/*********************************************************************************************/

/*********************************************************************************************/
USART_Error_t USART_ReceiveData(s16 * Copy_Ps16Data)
{
	USART_Error_t Local_ErrorState = USART_Error_t_RT_OK;

	if(NULL == Copy_Ps16Data)
	{
		Local_ErrorState = USART_Error_t_RT_NULL_PTR;
	}
	else
	{
		while(!GET_BIT(USART_UCSRA, 7));

		*Copy_Ps16Data = (u16)USART_UDR;
	}

	return Local_ErrorState;
}
/*********************************************************************************************/

/*********************************************************************************************/
USART_Error_t USART_ReceiveData_interrupt(void(* Local_Fptr)(u8))
{
	USART_Error_t Local_ErrorState = USART_Error_t_RT_OK;

	if(NULL != Local_Fptr)
	{
		USART_FPTR = Local_Fptr;

		//Enable The Global Interrupt
		LIB_SREG |= (1<<7);

		//Enable RX Complete Interrupt
		USART_UCSRB |= (1<<7);
	}
	else
	{
		Local_ErrorState = USART_Error_t_RT_NULL_PTR;
	}


	return Local_ErrorState;
}
/*********************************************************************************************/

ISR(USART_RXC_vect)
{
	u8 Local_u8_Received_Data = USART_UDR;

	if(NULL != USART_FPTR)
	{
		USART_FPTR(Local_u8_Received_Data);
	}

}

/************************************************************************************************************/
