/*
 *

APP.c
 *
 *  Created on: Jan 30, 2021
 *      Author: Mohamed Elshazly
 */


/************************************************************************/
/*			       			INCLUDES             	                    */
/************************************************************************/

#include <util/delay.h>
#include "KeyPad.h"
#include "LCD.h"
#include "APP.h"
#include "DIO.h"
#include "stepper.h"
#include "State_M.h"

/************************************************************************/
/*				           Global  Variables	                */
/************************************************************************/
uint8 key;


uint8 flag0,flag1,i;

/************************************************************************/
/*				           FUNCTION IMPLEMENTATION	                    */
/************************************************************************/

/**state of entering a new password for the safe**/
void Enter_New_Pssword(void)
{
	/**clear the screen**/
	LCD_Clear();

	/**move the cursor in the first row , first col**/
	LCD_GotoXY(0,1);

	/**display message**/
	LCD_writestring("Enter New Pass");
	_delay_ms(200);

}

void confrim(void)
{
	/**clear the screen**/
	LCD_Clear();

	/**move the cursor in the first row , first col**/
	LCD_GotoXY(0,1);

	/**display message**/
	LCD_writestring("confirm the New Pass");
	_delay_ms(200);

}

/*****************************************************************************************/
/*  Input:  None                                                                         */
/*  Output: ERROR_STATUS                                        	                     */
/*  In/Out: pointer of the array that the password will save in it                       */
/*          pointer to uint8 to detect if the user press the # button or not			 */
/*  Description:take the password from the user  and notify if the user                  */
/*              press the new password button                                            */
/*****************************************************************************************/

void input_num(uint16* pass)
{
	uint8 i;
	(*pass)=0;
	for (i=0;i<4;)
	{
		key=KeyPad_GetPressedKey();

		if(key>=0 && key<10)
		{
			_delay_ms(10);
			LCD_GotoXY(1,1+i);
			LCD_WriteData('*');
			//LCD_WriteNumber(key);
			(*pass) *= 10;
			(*pass) += key;
			i++;
		}
		else if(key==15)
		{
			*pass=1;
			LCD_Clear();

			_delay_ms(200);

			break;
		}
	}
}

/**************************************************************************************	**/
/*  Input:  None                                                                         */
/*  Output: ERROR_STATUS                                        	                     */
/*  In/Out: None																	     */
/*  Description: enable the motor to open the safe                                      */
/*****************************************************************************************/

void open_safe(void)
{

	DIO_Init();
	uint8 i;

	/**clear the screen**/
	LCD_Clear();

	/**move the cursor in the first row , first col**/
	LCD_GotoXY(0,1);

	/**display message**/
	LCD_writestring("Welcome");
	_delay_ms(200);

	/**clear the screen**/
	LCD_Clear();

	/**move the cursor in the first row , first col**/
	LCD_GotoXY(0,1);

	/**display message**/
	LCD_writestring("Accessed");

	for (i=0;i<50;i++)
	{
		Stepper_RotateClock();
	}
}

/**************************************************************************************	**/
/*  Input:  None                                                                         */
/*  Output: ERROR_STATUS                                        	                     */
/*  In/Out: None																	     */
/*  Description: enable the motor to close the safe                                      */
/*****************************************************************************************/

void close_safe(void)
{
	/**clear the screen**/
	LCD_Clear();

	/**move the cursor in the first row , first col**/
	LCD_GotoXY(0,1);

	/**display message**/
	LCD_writestring("close safe");

	_delay_ms(200);

	/* Rotate anti clock wise for 5 seconds */

	for (i=0;i<50;i++)
	{
		Stepper_Rotate_anticlock();
	}
}


void Master_key(void)
{

	/**clear the screen**/
	LCD_Clear();

	/**move the cursor in the first row , first col**/
	LCD_GotoXY(0,1);

	/**display message**/
	LCD_writestring("Enter Master key");

	_delay_ms(200);
}






