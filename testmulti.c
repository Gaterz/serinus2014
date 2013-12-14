/*
 * testmulti.c
 *
 *  Created on: 11 déc. 2013
 *      Author: Julien
 */
#include "LPC22xx.h"
void blinkled(void)
{
	int		j;
	{
					IO0CLR |= 0x40000000;
					for (j = 0; j < 500000; j++ );
					IO0SET |= 0x40000000;
					for (j = 0; j < 2000000; j++ );
					UART0_THR='6';
				}
}
