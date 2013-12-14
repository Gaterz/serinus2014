#include "all_head.h"
void blinkled(void)
{
	int	j;
	{
					IO0CLR |= 0x40000000;
					for (j = 0; j < 500000; j++ );
					IO0SET |= 0x40000000;
					for (j = 0; j < 2000000; j++ );
					UART0_THR='9';
				}
}
void initBlinkled(void)
{
	// set io pins for led P0.30
		PINSEL1 &= 0xC0FFFFFF;  // configure pin as GPIO (default is analogue input)
		IO0DIR = 0x40000000;	// pin P0.30 is an output, everything else is input after reset
}
