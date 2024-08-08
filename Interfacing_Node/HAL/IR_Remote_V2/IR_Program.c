#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "IR_private.h"
#include "IR_config.h"
#include "IR_Interface.h"

#include "../../MCAL/EXTI_Driver_V3/EXTI_int.h"
#include "../../MCAL/DIO_V2/DIO_init.h"
#include "../LED_Handler_V1/LED_int.h"

volatile u16 ir_signal = 0; // variable to store received IR signal
volatile u8 ir_edge_count = 0; // counter for number of bits received
volatile u8 ir_start_flag = 0; // flag to indicate whether data is ready
volatile u8 ir_frame[50] = {0};

void (*isr_timer1_callback)(void) = NULL;

void IR_Init(void){

#if IR_PORT == DIO_PORT_B
#if IR_PIN == DIO_PIN_2
	EXTI_u8SetSource(EXTI_INT_2, EXTI_FALLING_EDGE);
	EXTI_voidSet_INT2_Cbf(&IR_vidGetFrame);
	EXTI_u8EnablePIE(EXTI_INT_2);
	EXTI_voidEnableGIE();
#else
#error "Configuration error : IR pin selection error"
#endif

#elif IR_PORT == DIO_PORT_D
#if IR_PIN == DIO_PIN_2
	EXTI_u8SetSource(EXTI_INT_0, EXTI_FALLING_EDGE);
	EXTI_voidSet_INT0_Cbf(&IR_vidGetFrame);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();
#elif IR_PIN == DIO_PIN_3
	EXTI_u8SetSource(EXTI_INT_1, EXTI_FALLING_EDGE);
	EXTI_voidSet_INT1_Cbf(&IR_vidGetFrame);
	EXTI_u8EnablePIE(EXTI_INT_1);
	EXTI_voidEnableGIE();
#else
#error "Configuration error : IR pin selection error"
#endif
#else
#error "Configuration error : IR port selection error"
#endif
}

static void IR_vidGetFrame(void){
	LED_vidToggleLed(LED_e_7);
	if(ir_start_flag == 0)
	{
		IR_vidSetSinglePeriod(1000, &IR_vidtakeAction);
		ir_start_flag = 1;
	}else{
		ir_frame[ir_edge_count] = IR_u16GetElapsedTime();
		IR_vidSetSinglePeriod(1000,&IR_vidtakeAction);
		ir_edge_count++;
	}
}
static void IR_vidtakeAction(void)
{

	u8 i =0;

	//	LED_vidToggleLed(LED_e_1);
	ir_signal = 0;
	if((ir_frame[0] > 100) && (ir_frame[0] < 110)){
		for(i = 0; i < DATA_BITS ; i++){
			if(ir_frame[17+i] > MIN_OFF_PERIOD && ir_frame[17+i] < MAX_OFF_PERIOD)
			{
				SET_BIT(ir_signal,i);
			}else{
				CLR_BIT(ir_signal,i);
			}
		}
	}

	ir_frame[0] = 0;
	ir_start_flag = 0;
	ir_edge_count = 0;

}

static void IR_vidSetSinglePeriod(u16 ticks, void (*callback)(void)) {
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	// Reset Timer1 counter
	TCNT1 = 0;

	// Set Timer1 to CTC mode with prescaler = 1024
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	// Set compare match value to ticks
	OCR1A = ticks;
	// Enable compare match interrupt
	TIMSK |= (1 << OCIE1A);
	// Set callback function to be called on interrupt
	if(callback != NULL){

		isr_timer1_callback = callback;
	}
}
static u16 IR_u16GetElapsedTime(void)
{
	return TCNT1;
}
// Interrupt service routine for Timer1 compare match
ISR(TIMER1_COMPA_vect) {
	// Call the callback function provided to setup_timer1()
	if(isr_timer1_callback != NULL){
		isr_timer1_callback();
	}
}
