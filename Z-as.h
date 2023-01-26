/*
 * h_bridge.h - XvR 2020
 */

#ifndef _Z_AS_H_
#define _Z_AS_H_

// These pins are available on the shield via the header:
//
//		Mega	Uno
// digital 5	PE3	PD5
// digital 6	PH3	PD6
// digital 9	PH6	PB1
// analog 5	PF5	PC5

// The settings below are for the Mega, modify
// in case you want to use other pins

void init_Zas(void);
void Zas_set_percentage(signed char percentage);

#endif /* _H_BRIDGE_H_ */
