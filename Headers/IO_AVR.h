/*
 * IO_AVR.h
 *
 *  Created on: 19 mai 2014
 *      Author: Julien
 */

#ifndef IO_AVR_H_
#define IO_AVR_H_

//ARM->AVR
extern unsigned char Pompe1;
extern unsigned char Pompe2;
extern unsigned char Pompe3;
extern unsigned char Pompe4;
extern unsigned char Pompe5;
extern unsigned char AX12[8];
extern unsigned char EN_SONARS;
extern unsigned char EN_AX12;
extern unsigned char EN_POMPES;
//AVR->ARM
extern unsigned int Dist_Sonard0;
extern unsigned int Dist_Sonard1;
extern unsigned int Dist_Sonard2;
extern unsigned int Dist_Sonard3;
extern unsigned char POS_AX12[8];
extern unsigned char INTERUPTEUR_ROUGE;
extern unsigned char INTERUPTEUR_JAUNE;
extern unsigned char INTERUPTEUR_JACK;
#endif /* IO_AVR_H_ */
