#ifndef F_CPU
#define F_CPU 16000000ul
#endif
#include <util/delay.h>
#include "X-as.h"
#include "Y-as.h"
#include "Z-as.h"
#include <avr/io.h>


void init_Pinnen(void)
{
    //input knop pinnen
	DDRD &= ~(1<<PD0);
	DDRD &= ~(1<<PD1);
    DDRD &= ~(1<<PD2);
    DDRD &= ~(1<<PD3);
    DDRH &= ~(1<<PH0);
    DDRH &= ~(1<<PH1);
    DDRA &= ~(1<<PA0);
    DDRA &= ~(1<<PA2);
    DDRE |= (1<<PE0);
    DDRB |= (1<<PB7);

    PORTB |= (1<<PB7);
    PORTB ^= (1<<PB7);
}

void init(void)
{
	init_Xas();
	init_Yas();
	init_Zas();
	init_Pinnen();
}

int main(void)
{
	init();
    int x = 0;
    int y = 0;
    int z = 0;
    int tongepakt = 0;
    int noodstand = 0;
    int ZasGebruikt = 0;
    int stopGebruikt = 0;
    int knop1ingedrukt = 0;
    int knop2ingedrukt = 0;
    int knop3ingedrukt = 0;
    int knop4ingedrukt = 0;
    int knop5ingedrukt = 0;
    int knop6ingedrukt = 0;
	while (1)
	{
	    //noodstop ingedrukt
	    if ((PINJ & (1<<PJ0)) !=0)
        {
            _delay_ms(20);
            //assen stoppen
            x = 0;
            Xas_set_percentage(x);
            y = 0;
            Yas_set_percentage(y);
            z = 0;
            Zas_set_percentage(x);
            //noodstand veranderen
            noodstand = 1;
            stopGebruikt = 1;
        }
        if ((PINJ & (1<<PJ0)) ==0)
        {
            _delay_ms(20);
            noodstand = 0;
            if (stopGebruikt == 1)
            {
                if (ZasGebruikt == 1)
                {
                    x = -100;
                    Xas_set_percentage(x);
                    _delay_ms(5000);
                    x = 0;
                    Xas_set_percentage(x);
                    ZasGebruikt = 0;
                }
                stopGebruikt = 0;
            }
        }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	    //Z-as ton oppakken
	    if ((PIND &(1<<PD1)) !=0)
        {
            x = 0;
            Xas_set_percentage(x);
            PORTB ^= (1<<PB7);
            _delay_ms(2000);
            x = -100;
            Xas_set_percentage(x);
            _delay_ms(5000);
            x = 0;
            Xas_set_percentage(x);
        }
	    if ((PIND & (1<<PD0)) !=0)
        {
            ZasGebruikt = 1;
            _delay_ms(20);
            x = 100;
            Xas_set_percentage(x);
        }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	    //Assen bewegen
	    if (PINA & (1<<PA0))
        {
            if (knop1ingedrukt == 0)
            {
                 _delay_ms(20);
                x = -100;
                knop1ingedrukt = 1;
                Xas_set_percentage(x);
            }
        }
	    if(PINA & (1<<PA2))
        {
            if (knop2ingedrukt == 0)
            {
                _delay_ms(20);
                x = 100;
                knop2ingedrukt = 1;
                Xas_set_percentage(x);
            }
        }
		if ((PINA & (1<<PA0)) ==0)
        {
            if (knop1ingedrukt != 0)
            {
                _delay_ms(20);
                x = 0;
                knop1ingedrukt = 0;
                Xas_set_percentage(x);
            }
        }
        if ((PINA & (1<<PA2)) ==0)
        {
            if (knop2ingedrukt != 0)
            {
                _delay_ms(20);
                x = 0;
                knop2ingedrukt = 0;
                Xas_set_percentage(x);
            }
        }
        if(PIND & (1<<PD2))
        {
            if (knop3ingedrukt == 0)
            {
                _delay_ms(20);
                y = 100;
                knop3ingedrukt = 1;
                Yas_set_percentage(y);
            }
        }
        if(PIND & (1<<PD3))
        {
            if (knop4ingedrukt == 0)
            {
                _delay_ms(20);
                y = -100;
                knop4ingedrukt = 1;
                Yas_set_percentage(y);
            }
        }

        if ((PIND & (1<<PD2)) ==0)
        {
            if (knop3ingedrukt != 0)
            {
                _delay_ms(20);
                y = 0;
                knop3ingedrukt = 0;
                Yas_set_percentage(y);
            }
        }
        if ((PIND & (1<<PD3)) ==0)
        {
            if (knop4ingedrukt != 0)
            {
                _delay_ms(20);
                y = 0;
                knop4ingedrukt = 0;
                Yas_set_percentage(y);
            }
        }
        if(PINH & (1<<PH0))
        {
            if (knop5ingedrukt == 0)
            {
                _delay_ms(20);
                z = 100;
                knop5ingedrukt = 1;
                Zas_set_percentage(z);
            }
        }
        if(PINH & (1<<PH1))
        {
            if (knop6ingedrukt == 0)
            {
                _delay_ms(20);
                z = -100;
                knop6ingedrukt = 1;
                Zas_set_percentage(z);
            }
        }

        if ((PINH & (1<<PH0)) ==0)
        {
            if (knop5ingedrukt != 0)
            {
                _delay_ms(20);
                z = 0;
                knop5ingedrukt = 0;
                Zas_set_percentage(z);
            }
        }
        if ((PINH & (1<<PH1)) ==0)
        {
            if (knop6ingedrukt != 0)
            {
                _delay_ms(20);
                z = 0;
                knop6ingedrukt = 0;
                Zas_set_percentage(z);
            }
        }
	}
	return 0;
}


