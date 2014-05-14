/**************************init.c*********************************************
Auteur : Julien MAURAT
Date : 3 janv. 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
void init_global()
{
// Initialize the system
	Initialize();
	initBlinkled();
	initES_cod();
	resetCodeurs();
	InitTimer1();
	enableIRQ();
	initES_PWM();
	initFunction_PWM();
	initPWM();
	initIntel();
	CANinit_HW();
}
