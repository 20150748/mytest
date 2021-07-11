/*
 * stepper.h
 *
 *  Created on: Feb 1, 2021
 *      Author: DELL
 */

#ifndef STEPPER_H_
#define STEPPER_H_


#define Coil_Blue     0
#define Coil_Pink     1
#define Coil_Yellow   2
#define Coil_Orange   3

void Stepper_Rotate_anticlock(void);
void Stepper_RotateClock(void);

#endif /* STEPPER_H_ */
