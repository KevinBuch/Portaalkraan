

/*
 * h_bridge.c - XvR 2020
 *
 * Use 8-bit timer. Uses interrupts in order to be able
 * to use the pins on the multifunction shield
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "X-as.h"

ISR(TIMER1_OVF_vect)
{
	if (OCR1A == 0 && OCR1B == 0)
	{
		PORTH &= ~(1<<PH5);
		PORTF &= ~(1<<PF7);
	}
	else if (OCR1A != 0)
	{
		PORTF &= ~(1<<PF7);
		PORTH |= (1<<PH5);
	}
	else if (OCR1B != 0)
	{
		PORTH &= ~(1<<PH5);
		PORTF |= (1<<PF7);
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (OCR1A != 255)
	{
		PORTH &= ~(1<<PH5);
	}
}

ISR(TIMER1_COMPB_vect)
{
	if (OCR2B != 255)
	{
		PORTF &= ~(1<<PF7);
	}
}

void init_Xas(void)
{
	// Config pins as output
	DDRH |= (1<<PH5);
	DDRF |= (1<<PF7);

	// Output low
	PORTH &= ~(1<<PH5);
	PORTF &= ~(1<<PF7);

	// Use mode 0, clkdiv = 64
    TCCR1A = 0;
	TCCR1B = (0<<CS22) | (0<<CS21) | (0<<CS20);


	// Disable PWM output
	OCR1A = 0;
	OCR1B = 0;

	// Interrupts on OCA, OCB and OVF
	TIMSK1 = (1<<OCIE2B) | (1<<OCIE2A) | (1<<TOIE2);

	sei();
}

void Xas_set_percentage(signed char percentage)
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

