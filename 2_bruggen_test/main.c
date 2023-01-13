#ifndef F_CPU
#define F_CPU 16000000ul
#endif
#include <util/delay.h>
#include "h_bridge.h"
#include "h_bridge1.h"
#include "X-as.h"
#include <avr/io.h>

void init(void)
{
	init_h_bridge();
//s	init_h_bridge_1();
	init_Xas();
	init_Pinnen();
}

void init_Pinnen(void)
{
    //input knop pinnen
	DDRD &= ~(1<<PD0);
	DDRD &= ~(1<<PD1);
    DDRD &= ~(1<<PD2);
    DDRD &= ~(1<<PD3);
    DDRH &= ~(1<<PH0);
    DDRH &= ~(1<<PH1);
}

int main(void)
{
	init();
    int z = 0;
    int y = 0;
    int x = 0;
    int knop1ingedrukt = 0;
    int knop2ingedrukt = 0;
    int knop3ingedrukt = 0;
    int knop4ingedrukt = 0;
    int knop5ingedrukt = 0;
    int knop6ingedrukt = 0;
	while (1)
	{
		if(PIND & (1<<PD0))
        {
            if (knop1ingedrukt == 0)
            {
                _delay_ms(20);
                z = 100;
                knop1ingedrukt = 1;
                h_bridge_set_percentage(z);
            }
        }
        if(PIND & (1<<PD1))
        {
            if (knop2ingedrukt == 0)
            {
                _delay_ms(20);
                z = -100;
                knop2ingedrukt = 1;
                h_bridge_set_percentage(z);
            }
        }

        if ((PIND & (1<<PD0)) ==0)
        {
            if (knop1ingedrukt != 0)
            {
                _delay_ms(20);
                z = 0;
                knop1ingedrukt = 0;
                h_bridge_set_percentage(z);
            }
        }
        if ((PIND & (1<<PD1)) ==0)
        {
            if (knop2ingedrukt != 0)
            {
                _delay_ms(20);
                z = 0;
                knop2ingedrukt = 0;
                h_bridge_set_percentage(z);
            }
        }/*
        if(PIND & (1<<PD2))
        {
            if (knop3ingedrukt == 0)
            {
                _delay_ms(20);
                y = 100;
                knop3ingedrukt = 1;
                h_bridge_set_percentage_1(y);
            }
        }
        if(PIND & (1<<PD3))
        {
            if (knop4ingedrukt == 0)
            {
                _delay_ms(20);
                y = -100;
                knop4ingedrukt = 1;
                h_bridge_set_percentage_1(y);
            }
        }

        if ((PIND & (1<<PD2)) ==0)
        {
            if (knop3ingedrukt != 0)
            {
                _delay_ms(20);
                y = 0;
                knop3ingedrukt = 0;
                h_bridge_set_percentage_1(y);
            }
        }
        if ((PIND & (1<<PD3)) ==0)
        {
            if (knop4ingedrukt != 0)
            {
                _delay_ms(20);
                y = 0;
                knop4ingedrukt = 0;
                h_bridge_set_percentage_1(y);
            }
        }*/
        if(PIND & (1<<PD2))
        {
            if (knop5ingedrukt == 0)
            {
                _delay_ms(20);
                x = 100;
                knop5ingedrukt = 1;
                Xas_set_percentage(x);
            }
        }
        if(PIND & (1<<PD3))
        {
            if (knop6ingedrukt == 0)
            {
                _delay_ms(20);
                x = -100;
                knop6ingedrukt = 1;
                Xas_set_percentage(x);
            }
        }

        if ((PIND & (1<<PD2)) ==0)
        {
            if (knop5ingedrukt != 0)
            {
                _delay_ms(20);
                x = 0;
                knop5ingedrukt = 0;
                Xas_set_percentage(x);
            }
        }
        if ((PIND & (1<<PD3)) ==0)
        {
            if (knop6ingedrukt != 0)
            {
                _delay_ms(20);
                x = 0;
                knop6ingedrukt = 0;
                Xas_set_percentage(x);
            }
        }
	}
	return 0;
}


