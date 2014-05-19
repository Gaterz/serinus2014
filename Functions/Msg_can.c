/**************************Msg_can.c*********************************************
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

////////////////////////////////////////////////////////////
//////////////////////////Pompes////////////////////////////
//bit 7-0 : 0: pompe off 1: pompe on
canMsgType Message_Pompes ={
			ID_MSG_CAN_POMPES,
			1,
			0,
			0
};
////////////////////////////////////////////////////////////
//////////////////////////AX-12/////////////////////////////
//octet 7-0 : pos 0-255 ax12
canMsgType Message_Ax_12 ={
			ID_MSG_CAN_AX12_T,
			8,
			0,
			0
};
////////////////////////////////////////////////////////////
//////////////////////////Activate/////////////////////////////
//bit 0:ax-12 0:off 1:on
//bit 1: pompes on/off
//bit 3: sonars on/off

canMsgType Message_Activate ={
			ID_MSG_CAN_ACTIVATE,
			1,
			0,
			0
};
