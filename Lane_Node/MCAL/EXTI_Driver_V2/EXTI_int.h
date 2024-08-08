/*
 * EXTI_int.h
 *
 *  Created on: Sep 30, 2021
 *      Author: Mostafa
 */

#ifndef MCAL_EXTI_DRIVER_V2_EXTI_INT_H_
#define MCAL_EXTI_DRIVER_V2_EXTI_INT_H_

#define EXTI_INT_0     0
#define EXTI_INT_1     1
#define EXTI_INT_2     2

#define EXTI_LOW_LEVEL    0
#define EXTI_ANY_CHANGE   1
#define EXTI_FALLING_EDGE 2
#define EXTI_RISING_EDGE  3

//this function used to enable the GIE (set the I_bit in SREG to 1)
void EXTI_voidEnableGIE();

//this function used to disable the GIE (set the I_bit in SREG to 0)
void EXTI_voidDisableGIE();

/*this function used to enable the PIE (set the bit in GICR to 1),
it takes the external interrupt number(INT_0, INT_1, INT_2)
it returns 0 if it succeeded, and 1 if there is an error
*/
u8 EXTI_u8EnablePIE(u8 Copy_u8INTx);

/*this function used to disable the PIE (set the bit in GICR to 0),
it takes the external interrupt number(INT_0, INT_1, INT_2)
it returns 0 if it succeeded, and 1 if there is an error
*/
u8 EXTI_u8DisablePIE(u8 Copy_u8INTx);

/*this function sets the interrupt source
 it takes the external interrupt number(INT_0, INT_1, INT_2)
 for(INT_0, INT_1) the source can be (LOW_LEVEL, FALLING_EDGE, RISING_EDGE, ANY_CHANGE)
 for(INT_2) the source can be (FALLING_EDGE OR RISING_EDGE)
 it returns 0 if it succeeded, and 1 if there is an error
*/
u8 EXTI_u8SetSource(u8 Copy_u8INTx, u8 Copy_u8Source);

void EXTI_voidSet_INT0_Cbf(void (*fptr)(void));

void EXTI_voidSet_INT1_Cbf(void (*fptr)(void));

#endif /* MCAL_EXTI_DRIVER_V2_EXTI_INT_H_ */
