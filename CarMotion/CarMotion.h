/*
 * CarMotion.h
 *
 *  Created on: Jul 5, 2023
 *      Author: musta
 */

#ifndef HAL_CARMOTION_CARMOTION_H_
#define HAL_CARMOTION_CARMOTION_H_

#define MOTOR_1		(u8)1
#define MOTOR_2		(u8)2

void Car_Init(void);
void Car_Go_Forword(void);
void Car_Go_Backword(void);
void Car_Go_Left(void);
void Car_Go_Right(void);
void Car_Stop(void);
void Car_Set_Speed(u8 MOTOR, u8 Copy_u8SpeedValue);

#endif /* HAL_CARMOTION_CARMOTION_H_ */
