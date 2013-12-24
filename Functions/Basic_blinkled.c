/**************************Basic_blikled.c*********************************************
Auteur : Julien MAURAT
Date : 14 déc. 2013
Description : fonction basique de blink de la led de la carte olimex
Constantes : N/A
Fonctions :
void blinkled(void) : fonction bloquante avec temporisation a la barbare
qui execute un clignotement de led

void initBlinkled(void) : initialise la broche de sortie connectée a la led
**************************************************************************************/

#include "../all_head.h"
void blinkled(void)
{
	int	j;
	{
					IO0CLR |= 0x40000000;
					for (j = 0; j < 500000; j++ );
					IO0SET |= 0x40000000;
					for (j = 0; j < 2000000; j++ );
					//UART0_THR='7';
				}
}
void initBlinkled(void)
{
	// set io pins for led P0.30
		PINSEL1 &= 0xC0FFFFFF;  // configure pin as GPIO (default is analogue input)
		IO0DIR = 0x40000000;	// pin P0.30 is an output, everything else is input after reset
}
