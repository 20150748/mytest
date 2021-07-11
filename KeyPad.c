/*

 * KeyPad.c
 *
 *  Created on: Dec 25, 2020
 *      Author: Mohamed Elshazly
 */


/************************************************************************/
/*			       			INCLUDES             	                    */
/************************************************************************/


#include "STD_Types.h"
#include "DIO_reg.h"
#include "DIO_config.h"
#include "DIO.h"
#include "KeyPad.h"


/************************************************************************/
/*				           Global & Extern Variables	                */
/************************************************************************/
uint8 arr_num[4][4]={{7,8,9,10},
		{4,5,6,11},
		{1,2,3,12},
		{15,0,14,13}};
//{{7,8,9},
//					{4,5,6},
//					{1,2,3},
//					{'F',0,14}}; // A=/ , B= * , C = - , D = + , E = = , F = ON
uint8 arr_Pins[8]={PORTD0,PORTD1,PORTD2,PORTD3,PORTD4,PORTD5,PORTD6,PORTD7};
int i,j;


uint8 KeyPad_GetPressedKey(void)
{
	uint8 check=0;
	uint8 result= Default ; // value returned  // go to main.c

	DIO_WritePort(PORT_D,255);

	/* Looping on columns of the Key Pad  */
	for(i=Coloums_Start;i<=Coloums_End;i++)
	{
		DIO_WriteChannel(arr_Pins[i],0);

		/* Loop on the rows of the Key Pad*/
		for(j=Rows_Start;j<=Rows_End;j++)
		{
			 /* Check the status of the switch  */
			check=DIO_ReadChannel(arr_Pins[j]);
			if(check==0)
			{
				result=arr_num[i][j-4];
			}
			 /* Wait until the switch is released (Single Press) */

			while(!(DIO_ReadChannel(arr_Pins[j])));
		}

		DIO_WriteChannel(arr_Pins[i],1);
		//	DIO_WritePort(PORT_D,255); // todo: delete
	}
	return result;
}
