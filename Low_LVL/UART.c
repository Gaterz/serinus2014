/**************************UART.c*********************************************
Auteur : Julien MAURAT
Date : 14 déc. 2013
Description : Initialisation de la PLL de l'ARM et de ces périphériques
Constantes : N/A
Fonctions :
void init_UART0(void) : Configuration de la liason série 0(redirigée vers USB)
**************************************************************************************/
#include "../all_head.h"
#include <math.h>
void init_UART0(void)
{
	PINSEL0 |= 0x00000005;
	//UART0_LCR|=0x80;//Enable latch
	UART0_FCR=0b00000111;
	UART0_LCR=0b10000011;//Enable latch
	UART0_DLL=32;//96  /// 0x80
	UART0_DLM=0;//   1
	//Enable FIFO
	UART0_LCR=0b00000011;//8-bit no control 1 stop
	//UART0_LCR&=0b01111111;//clear latch
	UART0_THR='E';
}
void UART0_Sendchar(char C)
{
	while ((UART0_LSR & (1<<5)) == 0);
	if(C == '\n') UART0_Sendchar(0xD);
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
void printLongVal(signed long value)
{
	char val_send[10];
	int i=0;
	if(value == 0)
	{
		UART0_Sendchar('0');
		return;
	}
	if(value <0)
	{
		UART0_Sendchar('-');
		value =abs(value);
	}
	/*for(i=0;i<10;i++)
	{
		val_send[9-i] = (value % 10)+'0';
		value /= 10;
	}
	for(i=0;i<10;i++)
	{
		UART0_Sendchar(val_send[i]);
	}
	*/
	do
	{
			val_send[i] = (value % 10)+'0';
			value /= 10;
			i++;
	}while(value >0);
	i--;
	do
	{
		UART0_Sendchar(val_send[i]);
		i--;
	}while(i>=0);

}
