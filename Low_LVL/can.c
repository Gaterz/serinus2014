/////////////////////////////////////////////////////////////////////
// Nom du fichier : can.c
// Fonction : Gestion de la communication CAN (envoi et reception 
// d'un message)
//
// Cree par : Mikael BRIDAY
// Date de creation : avril 2012
//
// Adapte par : --
//
// Modifie par : --
// Date de derniere modification : --
//
// Etat du fichier (REDACTION/VALIDATION/VALIDE)
// Etat : VALIDE
/////////////////////////////////////////////////////////////////////

#include "../all_head.h"

// DESCRIPTION: 
void CANinit_HW()
{
	//selection des broches du CAN4
	//P0.12 -> RXCAN -> bits 25:24 = 0b11
	//P0.13 -> TXCAN -> bits 27:26 = 0b11
	PINSEL0 |= 0xF << 24;

	// Enter Reset Mode 
	C4MOD = CAN_RESET_MODE;
    // Write into Bus Timing Register 
	// Freq = 58,9824 MHz
	// Objectif -> Freq bus CAN = 250 Kbits/s
	// on a 58982,4 / 250 = 235,92. En prenant un prescaler BTR = 26
	// alors chaque bit CAN fait 9,07 time quantum (tq). C'est pour
	// cette valeur qu'on est le plus proche d'un nombre entier.
	// On partage ces 9 time quantum en:
	// 1 tq pour la synchro
	// 5 pour Tseg1
	// 3 pour tseg2
	// Attention, les valeurs indiquee doivent etre minoree de 1:
	// TSEG1 = 4
	// TSEG2 = 2
	// BTR   = 25
	// => CAN Bps = Freq/((TSEG1+TSEG2+3)(BRP+1)) = 252,06 Kbps
	// SJW = 0
	C4BTR = 25      | //20//BTR =25
			0 << 14 | //SJW
		    4 << 16 | //TSEG1 =4
	        2 << 20;  //TSEG2 =2
    // Enter Operating Mode 
 	C4MOD = CAN_OPERATING_MODE;
	//on n'utilise pas le Global Acceptance Filter => on accepte tout en reception.
	AFMR = 3;
	
}

int CANTransmitMessage(canMsgType *msg)
{	
	const unsigned int dlc = msg->dlc;
	if(dlc > 8) return -1;


	//il y a 3 buffers de transmission.
	//Si les 3 buffers sont pleins (les transmissions ne sont pas 
	//effectuees, l'attente est blocante).
	char txBuffer = 5;
	char compt = 0;
	while(txBuffer == 5 && compt <= 250)
	{
		//pour chaque buffer, on teste si TBSx=1 et TCSx=1 (p.286, UM10114)
		// => la transmission precedente est OK. valeur identique au reset.
		if     ((C4SR & 0x0000000C) == 0x0000000C) txBuffer = 0;
		else if((C4SR & 0x00000C00) == 0x00000C00) txBuffer = 1;
		else if((C4SR & 0x000C0000) == 0x000C0000) txBuffer = 2;

		compt++;
	}

	//ok, on a un buffer de transmission vide.
	//on remplit
	const unsigned int txBufferAddressOffset = (txBuffer * 0x10);
	const unsigned int TFIAddress = (unsigned int)(&C4TFI1) + txBufferAddressOffset;
	OUTW(TFIAddress, dlc << 16);			//trame data, idf std, et valeur dlc.
	const unsigned int TIDAddress = (unsigned int)(&C4TID1) + txBufferAddressOffset;
	OUTW(TIDAddress, (msg->stdIdf) & 0x7FF);//valeur idf
	const unsigned int TDAaddress = (unsigned int)(&C4TDA1) + txBufferAddressOffset;
	OUTW(TDAaddress, msg->dataL);			//4 premiers octets
	const unsigned int TDBaddress = (unsigned int)(&C4TDB1) + txBufferAddressOffset;
	OUTW(TDBaddress, msg->dataH);			//4 octets suivants

	//on valide la transmission (Write only reg) du buffer precedemment rempli.
	C4CMR = ((1 << txBuffer) << 5) | 1;
	return 0;
}

int CANReceiveMessage(canMsgType *msg)
{
	if(C4GSR & 0x00000001) //un nouveau message est disponible
	{
		//on remplit
		msg->dlc = (C4RFS >> 16) & 0xF;
		msg->stdIdf = C4RID & 0x7FF;
		msg->dataL = C4RDA;
		msg->dataH = C4RDB;

		//relache le buffer de reception (write only reg)
		C4CMR = 0x04; //RRB
		return 1;
	}
	return 0;
}
