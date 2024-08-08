#ifndef USART_INIT_H
#define USART_INIT_H

/********************************************** Declarations ************************************************/

typedef enum {
	USART_Enable_t_TransmitterEnable = 1			,
	USART_Enable_t_ReceiverEnable					,
	USART_Enable_t_TXAndRXEnable
}USART_Enable_t;

typedef enum {
	USART_CharcterSize_t_5 							,
	USART_CharcterSize_t_6							,
	USART_CharcterSize_t_7							,
	USART_CharcterSize_t_8							,
	USART_CharcterSize_t_9
}USART_CharcterSize_t;

typedef enum {
	USART_ParityMode_t_Disable 						=0,
	USART_ParityMode_t_EvenParity 					=2,
	USART_ParityMode_t_OddParity  					=3
}USART_ParityMode_t;

typedef enum {
	USART_Speed_t_NormalSpeed 						,
	USART_Speed_t_DoubleSpeed 										
}USART_Speed_t;

typedef enum {
	USART_StopBitSlct_t_OneBit 						,
	USART_StopBitSlct_t_TwoBits
}USART_StopBitSlct_t;



typedef struct
{
	USART_Enable_t 				usart_circuit_enable;
	USART_CharcterSize_t 		usart_charSize_slct;
	USART_ParityMode_t			usart_parity;
	USART_StopBitSlct_t			usart_stopBits_slct;
	USART_Speed_t				usart_speed_slct;
} USART_Config_t;

/********************************************** Functions Prototypes ************************************************/

/*
	use this function to initiate the USART.
	It takes:
		- Pointer to USART_Config_t struct
	It returns:
		- USART Error State (USART_Error_t)
 */
USART_Error_t USART_init(USART_Config_t * Copy_StrPtr);

/*
	use this function to send data.
	It takes:
		- data to to be sent (s16 variable)
	It returns:
		- USART Error State (USART_Error_t)
 */
USART_Error_t USART_SendData(s16 Copy_s16Data);

/*
	use this function to receive data.
	It takes:
		- pointer to u16 to store the received data
	It returns:
		- USART Error State (USART_Error_t)
 */
USART_Error_t USART_ReceiveData(s16 * Copy_Ps16Data);

/*
	use this function to receive data using interrupt.
	It takes:
		- pointer to function to be executed after data reception.
	It returns:
		- USART Error State (USART_Error_t)
 */
USART_Error_t USART_ReceiveData_interrupt(void(* Local_Fptr)(u8));
#endif
