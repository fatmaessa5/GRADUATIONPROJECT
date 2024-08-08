
#include "../LIB/STD_TYPES.h"

#include "../MCAL/EXTI_Driver_V2/EXTI_int.h"

#include "../HAL/MCP2515_driver/MP2515_Private.h"
#include "../HAL/MCP2515_driver/MCP2515_Interface.h"

#include "avr/interrupt.h"

//Function Prototype.
void RX_Distance(void);

//External Objects
extern u8 REC_Message[];

//Global Objects
static u8 Global_App_CANMsgBuffer;
static u8 Global_Turn_Left_[] =  {'r', 70  , 100, '#'} ;
static u8 Global_Turn_Right_[] = {'r', 100 , 70 , '#'} ;

void main()
{
	//EXTI Configurations.
	EXTI_voidSet_INT0_Cbf(&RX_Distance);
	EXTI_u8SetSource( EXTI_INT_0,EXTI_FALLING_EDGE);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();

	//CAN initialization.
	HMCP2515_voidRecievInit();
	HMCP2515_voidInitTransimiter();

	while(1)
	{
		//Check the received data.
		if(Global_App_CANMsgBuffer == 'l'){
			// speed of the motors
			HMCP2515_VidSendCAN_Msg(TXB0CTRL, 0x7E1, 3, Global_Turn_Left_);
		}
		else if(Global_App_CANMsgBuffer == 'r'){
			// speed of the motors
			HMCP2515_VidSendCAN_Msg(TXB0CTRL, 0x7E1, 3 , Global_Turn_Right_);
		}
		else{
			//Wrong message
		}
		//Clear the data.
		Global_App_CANMsgBuffer =0 ;
	}
}

void RX_Distance(void){

	//RECEIVE MESSAGE FROM CAN
	HMCP2515_voidRecieveMess(RXB0CTRL);

	//Store the received data.
	Global_App_CANMsgBuffer =  REC_Message[6];

}
