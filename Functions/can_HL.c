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
		case ID_MSG_CAN_AX12_R :
			/*POS_AX12[0]=(Message_Ax_12.dataL)&0xFF;
			POS_AX12[1]=(Message_Ax_12.dataL>>8)&0xFF;
			POS_AX12[2]=(Message_Ax_12.dataL>>16)&0xFF;
			POS_AX12[3]=(Message_Ax_12.dataL>>24)&0xFF;
			POS_AX12[4]=(Message_Ax_12.dataH)&0xFF;
			POS_AX12[5]=(Message_Ax_12.dataH>>8)&0xFF;
			POS_AX12[6]=(Message_Ax_12.dataH>>16)&0xFF;
			POS_AX12[7]=(Message_Ax_12.dataH>>24)&0xFF;*/
			break;
		}
	}
}
void Envoi_POS_AX12()
{
	 Message_Ax_12.dataL=(long)(AX12[3]<<24)+(long)(AX12[2]<<16)+(long)(AX12[1]<<8)+(long)AX12[0];
	 Message_Ax_12.dataH=(long)(AX12[7]<<24)+(long)(AX12[6]<<16)+(long)(AX12[5]<<8)+(long)AX12[4];
	 CANTransmitMessage(&Message_Ax_12);
}
void Envoi_Etat_Pompes()
{
	unsigned char buff=Pompe1+(Pompe2<<1)+(Pompe3<<2);
	Message_Pompes.dataL=buff;
	CANTransmitMessage(&Message_Pompes);
}
