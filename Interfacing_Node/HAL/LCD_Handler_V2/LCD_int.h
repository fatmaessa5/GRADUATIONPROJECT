/*
 * LCD_int.h
 *
 *  Created on: Apr 1, 2022
 *      Author: Mostafa
 */

#ifndef HAL_LCD_HANDLER_V2_LCD_INT_H_
#define HAL_LCD_HANDLER_V2_LCD_INT_H_

/*
 * Use these macros in the configuration file for the LCD_MODE
 */
#define FOUR_BITS			0
#define EIGHT_BITS			1

/*
 * Use these macros in the configuration file for the NO_OF_LINES
 */
#define ONE_LINE			0
#define TWO_LINES			1

/*
 * Use these macros in the configuration file for the DESPLAY_STATE, CURSOR_STATE, CURSOR_BLINKING and DISPLAY_SHIFT_OPERATION.
 */
#define	OFF					0
#define	ON					1

/*
 * Use these macros in the configuration file for the DISPLAY_STATE, CURSOR_STATE and CURSOR_BLINKIN.
 */
#define	INCREMENT			1
#define DECREMENT			0

/*
 * Description:
 * 				Use this function to initialize the LCD
 * Parameters:
 *				- void
 * Return:
 * 				- void
 */
void LCD_vidInit(void);

/*
 * Description:
 * 				Use this function to send command.
 * Parameters:
 *				- (u8) Command
 * Return:
 * 				- void
 */
void LCD_vidSendCmd(u8 Copy_u8Cmd);

/*
 * Description:
 * 				Use this function to send data.
 * Parameters:
 *				- (u8) data
 * Return:
 * 				- void
 */
void LCD_vidWriteChar(u8 Copy_u8Char);

/*
 * Description:
 * 				Use this function to shift the entire display right
 * Parameters:
 *				- void
 * Return:
 * 				- void
 */
void LCD_vidShiftDisplayRight(void);

/*
 * Description:
 * 				Use This function to shift the entire display left
 * Parameters:
 *				- void
 * Return:
 * 				- void
 */
void LCD_vidShiftDisplayLeft(void);

/*
 * Description:
 * 				Use This function to shift the cursor left
 * Parameters:
 *				- void
 * Return:
 * 				- void
 */
void LCD_vidShiftCursorLeft(void);

/*
 * Description:
 * 				Use This function to shift the cursor right
 * Parameters:
 *				- void
 * Return:
 * 				- void
 */
void LCD_vidShiftCursorRight(void);

/*
 * Description:
 * 				Use This function to go to a specific segment
 * Parameters:
 *				1- (u8) row_number  (1 or 2)
 *				2- (u8) column number:
 *									if row = 1 	==>     then column can be from 1 to 64
 *									if row = 2	==>		then column can be from 1 to 16
 *
 * Return:
 * 				- RT_OK or
 * 				- RT_WRONG_COLUMN_NUMBER or
 * 				- RT_WRONG_ROW_NUMBER
 */
u8 LCD_u8Goto(u8 Copy_u8Row, u8 Copy_u8Col);

/*
 * Description:
 * 				Use This function to display integer number
 * Parameters:
 *				- (u32) number
 * Return:
 * 				- void
 */
void LCD_vidSendInt(u32 Copy_u32IntNumber);

/*
 * Description:
 * 				Use This function to send a string
 * Parameters:
 *				- Pointer to u8 (pointer to the first character in a string)
 * Return:
 * 				- void
 */
void LCD_vidSendString(u8 * Copy_u8CharPtr);

/*
 * Description:
 * 				Use This function to clear the display
 * Parameters:
 *				- void
 * Return:
 * 				- void
 */
void LCD_vidClear(void);

#endif /* HAL_LCD_HANDLER_V2_LCD_INT_H_ */
