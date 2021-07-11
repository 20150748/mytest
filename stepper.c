/*
 * stepper.c
 *
 *  Created on: Feb 1, 2021
 *      Author: DELL
 */
/*
 * main.c
 *
 *  Created on: Dec 26, 2020
 *      Author: Mohamed Elshazly
 */
/************************************************************************/
/*			       			INCLUDES             	                    */
/************************************************************************/

#include <util/delay.h>
#include "DIO.h"
#include "DIO_config.h"
#include "BIT_MATH.h"
#include "STD_Types.h"
#include "DIO_reg.h"
#include "stepper.h"



void Stepper_RotateClock(void)
{

	DIO_WriteChannel(PORTC0,1);
	DIO_WriteChannel(PORTC1,0);
	DIO_WriteChannel(PORTC2,0);
	DIO_WriteChannel(PORTC3,0);
	_delay_ms(10);

	DIO_WriteChannel(PORTC0,0);
	DIO_WriteChannel(PORTC1,1);
	DIO_WriteChannel(PORTC2,0);
	DIO_WriteChannel(PORTC3,0);
	_delay_ms(10);

	DIO_WriteChannel(PORTC0,0);
	DIO_WriteChannel(PORTC1,0);
	DIO_WriteChannel(PORTC2,1);
	DIO_WriteChannel(PORTC3,0);

	_delay_ms(10);

	DIO_WriteChannel(PORTC0,0);
	DIO_WriteChannel(PORTC1,0);
	DIO_WriteChannel(PORTC2,0);
	DIO_WriteChannel(PORTC3,1);

	_delay_ms(10);

}
void Stepper_Rotate_anticlock(void)
{

	DIO_WriteChannel(PORTC0,0);
	DIO_WriteChannel(PORTC1,0);
	DIO_WriteChannel(PORTC2,0);
	DIO_WriteChannel(PORTC3,1);
	_delay_ms(10);


	DIO_WriteChannel(PORTC0,0);
	DIO_WriteChannel(PORTC1,0);
	DIO_WriteChannel(PORTC2,1);
	DIO_WriteChannel(PORTC3,0);

	_delay_ms(10);

	DIO_WriteChannel(PORTC0,0);
	DIO_WriteChannel(PORTC1,1);
	DIO_WriteChannel(PORTC2,0);
	DIO_WriteChannel(PORTC3,0);
	_delay_ms(10);

	DIO_WriteChannel(PORTC0,1);
	DIO_WriteChannel(PORTC1,0);
	DIO_WriteChannel(PORTC2,0);
	DIO_WriteChannel(PORTC3,0);

	_delay_ms(10);


}




