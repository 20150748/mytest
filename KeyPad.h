/*

* KeyPad.h
 *
 *  Created on: Dec 25, 2020
 *      Author: Mohamed Elshazly
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/************************************************************************/
/*			       			INCLUDES             	                    */
/************************************************************************/

#include "STD_Types.h"

/************************************************************************/
/*			       			 Macros            	                */
/************************************************************************/

#define Coloums_Start  0
#define Coloums_End    3
#define Rows_Start     4
#define Rows_End       7

#define Default   16

/************************************************************************/
/*				           FUNCTION PROTOTYPES	                        */
/************************************************************************/
uint8 KeyPad_GetPressedKey(void);


#endif /* KEYPAD_H_ */
