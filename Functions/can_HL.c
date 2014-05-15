/**************************can_HL.c*********************************************
Auteur : Julien MAURAT
Date : 17 mars 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
void Routine_CAN()
{
	if(CANReceiveMessage(&Message_R)==1)
			{
				if(Message_R.stdIdf==1)
				{
					Dist_Sonard0=Message_R.dataL<<8+Message_R.dataL;
					Dist_Sonard1=Message_R.dataL<<8+Message_R.dataL;
					Dist_Sonard2=Message_R.dataH<<8+Message_R.dataH;
					Dist_Sonard3=Message_R.dataH<<8+Message_R.dataH;
				}
			}
}
