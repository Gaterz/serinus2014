/**************************UART.c*********************************************
Auteur : Julien MAURAT
Date : 14 déc. 2013
Description : Initialisation de la PLL de l'ARM et de ces périphériques
Constantes : N/A
Fonctions :
void init_UART0(void) : Configuration de la liason série 0(redirigée vers USB)
**************************************************************************************/
#include "all_head.h"
void init_UART0(void)
{
	PINSEL0 |= 0x00000005;
	//UART0_LCR|=0x80;//Enable latch
	UART0_FCR=0b00000111;
	UART0_LCR=0b10000011;//Enable latch
	UART0_DLL=96;
	UART0_DLM=0;
	//Enable FIFO
	UART0_LCR=0b00000011;//8-bit no control 1 stop
	//UART0_LCR&=0b01111111;//clear latch
	UART0_THR='E';
}
void UART0_Sendchar(char C)
{
	while ((UART0_LSR & (1<<5)) == 0);
	UART0_THR = C;
}

void printString(char *Str)
{
unsigned int i = 0;
	while(Str[i] != '\0')
		{
			UART0_Sendchar(Str[i]);
			i++;
		}
}
