/*
 *
 State_M.c
 *
 *  Created on: Feb 1, 2021
 *      Author: Mohamed Elshazly
 *
/*********************************************************************/

/************************************************************************/
/*			       			INCLUDES             	                    */
/************************************************************************/

#include <util/delay.h>
#include "APP.h"
#include "State_M.h"
#include "KeyPad.h"
#include "LCD.h"
#include "APP.h"
#include "DIO.h"

/************************************************************************/
/*				           Global Variables	                */
/************************************************************************/

/**global variable that hold the master key**/
uint8 master_pass=1991;
uint8 state = ENTER_NEW_PASS;
uint16 password = 0;
uint16  confirm_pass=0;
uint16  re_pass=0;
uint8 num_of_tries = 0;


/************************************************************************/
/*				           FUNCTION IMPLEMENTATION	                    */
/************************************************************************/


/**************************************************************************************	**/
/*  Input:  None                                                                         */
/*  Output: ERROR_STATUS                                        	                     */
/*  In/Out: None																	     */
/*  Description: manage the safe state                                       		     */
/*****************************************************************************************/


void state_machine(void)
{
	/**state machine of the safe **/

	switch(state)
	{

	/**new password state that ask  the user to enter anew password for the safe**/
	case ENTER_NEW_PASS:

		/**call the function to print the state messages**/
		Enter_New_Pssword();

		/**take the password from the user using the following API**/
		input_num(&password);

		/**change the state to CONFIRM_PASSWORD**/
		state=CONFIRAMTION;

		break;

		/**confirmation case which ask the user to confirm his/her password**/
	case CONFIRAMTION:

		/**call the function to print the state messages**/
		confrim();

		/**take the password from the user using the following API**/
		input_num(&confirm_pass);

		/**compare the confirmation password with the original password and **/

		/**in case of the matching  between 2 passwords**/
		if (confirm_pass==password)
		{
			/**change the state to SAFE_OPEN**/
			state=OPEN_SAFE;
		}

		/**in case of the mismatching  between  2 passwords**/

		else
		{
			/**change the state to NEW_PASSWORD**/
			state=ENTER_NEW_PASS;
		}
		break;

		/** open safe state**/
	case OPEN_SAFE:

		/**open the safe **/
		open_safe();

		/**clear the screen**/
		LCD_Clear();

		/**change the state to SAFE_CLOSE**/
		state=CLOSE_SAFE;

		/** intialize nu of tries =0 **/
		num_of_tries = 0;
		break;

		/** close safe state**/
	case CLOSE_SAFE:

		/**close the safe **/
		close_safe();

		_delay_ms(200);

		/**change the state to ENTER_PASSWORD**/
		state=ENTER_PASS;

		break;

	case ENTER_PASS:

		/**clear the screen**/
		LCD_Clear();
		LCD_GotoXY(0,1);

		/**display message**/
		LCD_writestring("Enter password");

		/**take the password from the user using the following API**/
		input_num(&re_pass);

		/**in case of the user press on the new password button**/
		if(re_pass==password )
		{
			/**change the state to SAFE_OPEN**/
			state=OPEN_SAFE;
			_delay_ms(200);

			/**clear the screen**/
			LCD_Clear();

			_delay_ms(200);

		}
		else if (re_pass==1)
		{
			/**change the state to OLD_PASSWORD**/
			state=OLD_PASS;

			/**clear the screen**/
			LCD_Clear();

			_delay_ms(200);
		}

		else
		{
			if( num_of_tries ==0)
			{

				/**display message**/
				LCD_writestring("1st failed");
				_delay_ms(1000);
				LCD_Clear();

				/**display message**/
				LCD_writestring("Enter your password");

				/**increment the num of tries**/
				num_of_tries++;

				state = ENTER_PASS;
			}
			else if( num_of_tries ==1)
			{

				/**display message**/
				LCD_writestring("2nd failed");

				_delay_ms(1000);

				/**clear the screen**/
				LCD_Clear();

				/**display message**/
				LCD_writestring("Enter your password");

				/**increment the num of tries**/
				num_of_tries++;

				state = ENTER_PASS;


			}
			else if( num_of_tries ==2)
			{

				/**display message**/
				LCD_writestring("3rd failed");
				_delay_ms(1000);

				/**clear the screen**/
				LCD_Clear();

				/**display message**/
				LCD_writestring("Enter your password");

				/**increment the num of tries**/
				num_of_tries++;

				state = ENTER_PASS;

			}


			else
			{
				/**ptint failed3 time**/
				LCD_writestring("Failed 3 time");

				/**change the state to MASTER_MODE**/
				state=MASTER_MODE;
			}

		}
		break;

		/**the old password state**/
	case OLD_PASS:

		/**clear the screen**/
		LCD_Clear();

		/**move the cursor in the first row , first col**/
		LCD_GotoXY(0,1);

		/**display message**/
		LCD_writestring("Enter old");

		/**take the  password  from the user using the following API**/
		input_num(&re_pass);

		/**compare the entered password with the original password and **/
		/**in case of the matching  between 2 passwords**/
		if(re_pass==password )
		{
			/**change the state to NEW_PASSWORD**/
			state=ENTER_NEW_PASS;
		}

		/**in case of the number of failed tries did not exceed the limit**/
		else
		{
			if( num_of_tries ==0)
			{
				/**display message**/
				LCD_writestring("1st failed");

				_delay_ms(1000);

				/**clear the screen**/
				LCD_Clear();

				/**display message**/
				LCD_writestring("Enter your password");

				/**increment the num of tries**/
				num_of_tries++;

				/**stay in  current state **/
				state = OLD_PASS;
			}
			else if( num_of_tries ==1)
			{
				/**display message**/
				LCD_writestring("2nd failed");
				_delay_ms(1000);

				/**clear the screen**/
				LCD_Clear();

				/**display message**/
				LCD_writestring("Enter your password");

				/**increment the num of tries**/
				num_of_tries++;

				/**stay in  current state **/
				state = OLD_PASS;
			}
			else if( num_of_tries ==2)
			{

				/**display message**/
				LCD_writestring("3rd failed");
				_delay_ms(1000);

				/**clear the screen**/
				LCD_Clear();

				/**display message**/
				LCD_writestring("Enter your password");

				/**increment the num of tries**/
				num_of_tries++;

				/**stay in  current state **/
				state = OLD_PASS;

			}

			/**in case of the  number of failed tries  exceed the limit**/
			else

			{
				/**ptint failed3 time**/
				LCD_writestring("Failed 3 time");

				/**change the state to MASTER_MODE**/
				state=MASTER_MODE;
			}
		}
		break;


	case MASTER_MODE:

		/**call the func to print the state messages**/
		Master_key();

		/**take the master password  from the user using the following API**/
		input_num(&re_pass);

		/**compare the master password with the original password and **/
		/**in case of the matching  between 2 passwords**/
		if( re_pass==master_pass )
		{
			/**change the state to NEW_PASSWORD**/
			state=ENTER_NEW_PASS;
		}
		/**in case of the mismatching  between  2 passwords**/
		else
		{
			/**stay in  current state **/
			state=MASTER_MODE;
		}

		break;
	default:break;
	}
}

