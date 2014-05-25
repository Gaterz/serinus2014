/**************************IO_AVR.c*********************************************
Auteur : Julien MAURAT
Date : 19 mai 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
//ARM->AVR
unsigned char Pompe1=0;
unsigned char Pompe2=0;
unsigned char Pompe3=0;
unsigned char Pompe4=0;
unsigned char Pompe5=0;
unsigned char LED_ROUGE=0;
unsigned char LED_JAUNE=0;
unsigned char AX12[8]={0}; /*
				+---+    +---+
				| 3 |    | 4 |
				+---+----+---+
				|            |
				| +--------> |
				|            |
				++---+       +---+   +---+
				|| 5 |       | 7 |   | 8 |
				++---+       +---+   +---+
				|            |
				|        +---+
				|        | 6 |
				+---+--------+
				| 2 |    | 1 |
				+---+    +---+
*/

unsigned char EN_SONARS=0;
unsigned char EN_AX12=0;
unsigned char EN_POMPES=0;
//AVR->ARM
unsigned int Dist_Sonard0=0;
unsigned int Dist_Sonard1=0;
unsigned int Dist_Sonard2=0;
unsigned int Dist_Sonard3=0;
unsigned char POS_AX12[8]={0};
/*unsigned char POS_AX12_2=0;
unsigned char POS_AX12_3=0;
unsigned char POS_AX12_4=0;
unsigned char POS_AX12_5=0;
unsigned char POS_AX12_6=0;
unsigned char POS_AX12_7=0;
unsigned char POS_AX12_8=0;*/
unsigned char INTERUPTEUR_ROUGE=0;
unsigned char INTERUPTEUR_JAUNE=0;
unsigned char INTERUPTEUR_JACK=0;
unsigned char F_course1=0;
unsigned char F_course2=0;
unsigned char F_course3=0;
unsigned char F_course4=0;
unsigned char F_course5=0;
