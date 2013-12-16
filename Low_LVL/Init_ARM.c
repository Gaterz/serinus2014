/**************************Init_ARM.c*********************************************
Auteur : Julien MAURAT
Date : 14 d�c. 2013
Description : Initialisation de la PLL de l'ARM et de ces p�riph�riques
Constantes :
PLOCK : reglage de la fr�quence de la PLL

Fonctions :
void Initialize(void) : configure et initialise la PLL

void feed(void) : "confirmation" des param�tres de la PLL
**************************************************************************************/
#include "../all_head.h"
#define PLOCK 0x400

void Initialize(void)
{

	// Setting Multiplier and Divider values
  	PLLCFG=0x23;
  	feed();

	// Enabling the PLL */
	PLLCON=0x1;
	feed();

	// Wait for the PLL to lock to set frequency
	while(!(PLLSTAT & PLOCK)) ;

	// Connect the PLL as the clock source
	PLLCON=0x3;
	feed();

	// Enabling MAM and setting number of clocks used for Flash memory fetch (4 cclks in this case)
	MAMCR=0x2;
	MAMTIM=0x4;

	// Setting peripheral Clock (pclk) to System Clock (cclk)
	VPBDIV=0x1;

	init_UART0();
}

void feed(void)
{
  PLLFEED=0xAA;
  PLLFEED=0x55;
}
