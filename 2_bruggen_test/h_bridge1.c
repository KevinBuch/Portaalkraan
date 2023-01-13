
/*
 * h_bridge.c - XvR 2020
 *
 * Use 8-bit timer. Uses interrupts in order to be able
 * to use the pins on the multifunction shield
 */
/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include "h_bridge1.h"

ISR(TIMER2_OVF_vect)
{
	if (OCR2A == 0 && OCR2B == 0)
	{
		PORTH &= ~(1<<PH6);
		PORTF &= ~(1<<PF6);
	}
	else if (OCR2A != 0)
	{
		PORTF &= ~(1<<PF6);
		PORTH |= (1<<PH6);
	}
	else if (OCR2B != 0)
	{
		PORTH &= ~(1<<PH6);
		PORTF |= (1<<PF6);
	}
}

ISR(TIMER2_COMPA_vect)
{
	if (OCR2A != 255)
	{
		PORTH &= ~(1<<PH6);
	}
}

ISR(TIMER2_COMPB_vect)
{
	if (OCR2B != 255)
	{
		PORTF &= ~(1<<PF6);
	}
}

void init_h_bridge_1(void)
{
	// Config pins as output
	DDRH |= (1<<PH6);
	DDRF |= (1<<PF6);

	// Output low
	PORTH &= ~(1<<PH6);
	PORTF &= ~(1<<PF6);

	// Use mode 0, clkdiv = 64
    TCCR2A = 0;
	TCCR2B = (0<<CS22) | (1<<CS21) | (1<<CS20);


	// Disable PWM output
	OCR2A = 0;
	OCR2B = 0;

	// Interrupts on OCA, OCB and OVF
	TIMSK2 = (1<<OCIE2B) | (1<<OCIE2A) | (1<<TOIE2);

	sei();
}

void h_bridge_set_percentage_1(signed char percentage)
{
	if (percentage >= -100 && percentage <= 100)
	{
		if (percentage >= 0)
		{
			// Disable LPWM, calculate RPWM
			OCR2B = 0;
			OCR2A = (255*percentage)/100;
		}
		else // percentage < 0
		{
			// Disable RPWM, calculate LPWM
			OCR2A = 0;
			OCR2B = (255*percentage)/-100;
		}
	}
}
*/
