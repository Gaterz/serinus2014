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
		switch(Message_R.stdIdf)
		{
		case ID_MSG_CAN_SONARS :
			Dist_Sonard0=(Message_R.dataL&0xFF)+(Message_R.dataL&0xFF00);
			Dist_Sonard1=(Message_R.dataL>>16&0xFF)+(Message_R.dataL>>16&0xFF00);
			Dist_Sonard2=(Message_R.dataH&0xFF)+(Message_R.dataH&0xFF00);
			Dist_Sonard3=(Message_R.dataH>>16&0xFF)+(Message_R.dataH>>16&0xFF00);
			//Message_R.stdIdf=2;
			//CANTransmitMessage(&Message_R);
			break;
		case ID_MSG_CAN_BUTTON :

			break;
		}
	}
}
void Envoi_POS_AX12()
{
	 Message_Ax_12.dataL=(long)(POS_AX12[3]<<24)+(long)(POS_AX12[2]<<16)+(long)(POS_AX12[1]<<8)+(long)POS_AX12[0];
	 Message_Ax_12.dataH=(long)(POS_AX12[7]<<24)+(long)(POS_AX12[6]<<16)+(long)(POS_AX12[5]<<8)+(long)POS_AX12[4];
	 CANTransmitMessage(&Message_Ax_12);
}
