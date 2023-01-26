
/*
 * h_bridge.c - XvR 2020
 *
 * Use 8-bit timer. Uses interrupts in order to be able
 * to use the pins on the multifunction shield
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "X-as.h"

ISR(TIMER0_OVF_vect)
{
	if (OCR0A == 0 && OCR0B == 0)
	{
		PORTB &= ~(1<<PB4);
		PORTF &= ~(1<<PF5);
	}
	else if (OCR0A != 0)
	{
		PORTF &= ~(1<<PF5);
		PORTB |= (1<<PB4);
	}
	else if (OCR0B != 0)
	{
		PORTB &= ~(1<<PB4);
		PORTF |= (1<<PF5);
	}
}

ISR(TIMER0_COMPA_vect)
{
	if (OCR0A != 255)
	{
		PORTB &= ~(1<<PB4);
	}
}

ISR(TIMER0_COMPB_vect)
{
	if (OCR0B != 255)
	{
		PORTF &= ~(1<<PF5);
	}
}

void init_Xas(void)
{
	// Config pins as output
	DDRB |= (1<<PB4);
	DDRF |= (1<<PF5);

	// Output low
	PORTB &= ~(1<<PB4);
	PORTF &= ~(1<<PF5);

	// Use mode 0, clkdiv = 64
	TCCR0A = 0;
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);

	// Disable PWM output
	OCR0A = 0;
	OCR0B = 0;

	// Interrupts on OCA, OCB and OVF
	TIMSK0 = (1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0);

	sei();
}

void Xas_set_percentage(signed char percentage)
{
	if (percentage >= -100 && percentage <= 100)
	{
		if (percentage >= 0)
		{
			// Disable LPWM, calculate RPWM
			OCR0B = 0;
			OCR0A = (255*percentage)/100;
		}
		else // percentage < 0
		{
			// Disable RPWM, calculate LPWM
			OCR0A = 0;
			OCR0B = (255*percentage)/-100;
		}
	}
}
