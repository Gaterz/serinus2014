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
					Dist_Sonard0=(Message_R.dataH>>16&0xFF)+(Message_R.dataH>>16&0xFF00);
					Dist_Sonard1=(Message_R.dataH&0xFF)+(Message_R.dataH&0xFF00);
					Dist_Sonard2=(Message_R.dataL>>16&0xFF)+(Message_R.dataL>>16&0xFF00);
					Dist_Sonard3=(Message_R.dataL&0xFF)+(Message_R.dataL&0xFF00);
//					Dist_Sonard0=(Message_R.dataL>>8&0xFF)+(Message_R.dataL<<8&0xFF00);
//					Dist_Sonard1=(Message_R.dataL>>24&0xFF)+(Message_R.dataL>>8&0xFF00);
//					Dist_Sonard2=(Message_R.dataH>>8&0xFF)+(Message_R.dataH<<8&0xFF00);
//					Dist_Sonard3=(Message_R.dataH>>24&0xFF)+(Message_R.dataH>>8&0xFF00);
					Message_R.stdIdf=2;
					CANTransmitMessage(&Message_R);
				}

			}
}
