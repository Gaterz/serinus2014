/**************************can_HL.c*********************************************
Auteur : Julien MAURAT
Date : 17 mars 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
canMsgType Message_R ={
			0,
			0,
			0,
			0
};
void Routine_CAN()
{
	if(CANReceiveMessage(&Message_R)==1)
			{

			}
}
