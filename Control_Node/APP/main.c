#include "../LIB/STD_TYPES.h"
#include "../MCAL/EXTI_Driver_V3/EXTI_int.h"
#include "../HAL/MCP2515_driver/MP2515_Private.h"
#include "../HAL/MCP2515_driver/MCP2515_Interface.h"
#include "../MCAL/USART_Driver_V1/USART_ErrorTypes.h"
#include "../MCAL/DIO_V2/DIO_init.h"
#include "../MCAL/USART_Driver_V1/USART_Init.h"
***************************************************************************
#define APP_GO_FORWORD		(u8)70
#define APP_GO_BACKWORD		(u8)80
#define APP_GO_LEFT			(u8)69
#define APP_GO_RIGHT		(u8)50
#define APP_STOP_CAR		(u8)66
***************************************************************************
void RX_CanMsg(void);
void Go_Forword(void);
void Go_Backword(void);
void Go_Left(void);
void Go_Right(void);
void Car_Stop(void);
void Set_Speed(u8 Copy_u8SpeedValue);
void Rx_Data_CallBack_USART(u8 Speed);

extern u8 REC_Message[16];
static u8 App_CANRecMessage[16];
static u8 Old_Speed;
static u8 SpeedFrame[3];
int main()
{
	
	//USART Configurations.
	USART_Config_t Local_Usart_STR = {.usart_charSize_slct = USART_CharcterSize_t_8,
			.usart_circuit_enable = USART_Enable_t_TXAndRXEnable,
			.usart_parity = USART_ParityMode_t_Disable,
			.usart_speed_slct = USART_Speed_t_DoubleSpeed,
			.usart_stopBits_slct = USART_StopBitSlct_t_OneBit
	};

	u8 Local_u8CharCounter = 0;
	EXTI_u8SetSource(EXTI_INT_0, EXTI_FALLING_EDGE);
	EXTI_voidSet_INT0_Cbf(RX_CanMsg);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();

	USART_init(&Local_Usart_STR);
	USART_ReceiveData_interrupt(&Rx_Data_CallBack_USART);

	HMCP2515_voidInitTransimiter();
	HMCP2515_voidRecievInit();
	SpeedFrame[0] = 'V';
	SpeedFrame[2] = '#';
	SpeedFrame[1] = Old_Speed;
    while(SpeedFrame[Local_u8CharCounter] != '#')
	{
		USART_SendData(SpeedFrame[Local_u8CharCounter]);
		Local_u8CharCounter++;

	}
	USART_SendData(SpeedFrame[Local_u8CharCounter]);

	while(1)
	{
	   switch (App_CANRecMessage[0]) {
		case 'I':
			switch(App_CANRecMessage[1]){
			case 'f':
				Go_Forword();
				break;
			case 'b':
				Go_Backword();
			break;
			case 'l':
				Go_Left();
				break;
			case 'r':
				Go_Right();
				break;
			case 's':
				Car_Stop();
				break;
			default:
				break;
			}
			break;
			case 'r':
				if(App_CANRecMessage[1] > App_CANRecMessage[2])
				{
					Go_Right();
				}else if(App_CANRecMessage[1] < App_CANRecMessage[2])
				{
					Go_Left();
				}else{
					Go_Forword();
				}
				break;
			case 'D':
			case 'S':
            while(App_CANRecMessage[Local_u8CharCounter] != '#')
				{
					USART_SendData(App_CANRecMessage[Local_u8CharCounter]);
					Local_u8CharCounter++;
				}
				USART_SendData(App_CANRecMessage[Local_u8CharCounter]);
				break;

			default:
				break;
		}
	}
}

void RX_CanMsg(void)
{
	HMCP2515_voidRecieveMess(RXB0CTRL) ;
	u8 i = 0;
	while(REC_Message[6+i] != '#')
	{
		App_CANRecMessage[i] = REC_Message[6+i] ;
		i++;

	}
	App_CANRecMessage[i] = REC_Message[6+i];

}

void Go_Forword(void)
{

}

void Go_Backword(void)
{

}
void Go_Left(void)
{

}
void Go_Right(void)
{

}
void Car_Stop(void)
{

}
void Set_Speed(u8 Copy_u8SpeedValue)
{

}

void Rx_Data_CallBack_USART(u8 Copy_u8NewSpeed)
{
	if(Copy_u8NewSpeed != Old_Speed)
	{
		Set_Speed(Copy_u8NewSpeed);
		Old_Speed = Copy_u8NewSpeed;
	}
	else{

	}
}

