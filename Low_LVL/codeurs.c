/////////////////////////////////////////////////////////////////////
// Nom du fichier : codeurs.c
// Fonction : Permet la lecture des registres des HCTL (composants qui
// comptent le nombre de ticks sur les roues codeuses)
//
// Cree par : Valentin VERGEZ
// Date de creation : novembre 2011
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

/**
  * @use : Recupere la valeur des compteurs codeur en signe
  *
  * @param : void
  *
  * @retun : void
  *
  */
void lectureCodeursSigned(signed long* regCodeurX, signed long* regCodeurY) //(Validé sans delays)
{
/*Environnement*/

    //RAZ des variablesid lectureCodeursSigned(signed
    *regCodeurX = *regCodeurY = 0;
/*Algo*/
	//printf("X0: %.3ld ; Y0: %.3ld \n",*regCodeurX,*regCodeurY);

    //On enregistre la valeur des deux compteurs dans des bascules (OE = 0)
    //P3.24 = 0
    IO3CLR = 0x01000000 ; //=> 0"0001" 00 00 00, P3.24 = 0


    //Selection de l'octet de poids fort (SEL1 = 0, SEL2 = 1)
    //P0.29 et P1.24 = 0
    //P0.28 et P1.25 = 1
    IO0CLR = 0x01000000 ; //=> 0"0010" 00 00 00, P0.24 = 0 //=> "0010"0 00 00 00, P0.29 = 0
    IO1CLR = 0x01000000 ; //=> 0"0001" 00 00 00, P1.24 = 0
    IO0SET = 0x02000000 ; //=> 0"0001" 00 00 00, P0.25 = 1 //=> "0001"0 00 00 00, P0.28 = 1
    IO1SET = 0x02000000 ; //=> 0"0010" 00 00 00, P1.25 = 1


    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX = (IO1PIN & 0x00FF0000) << 8;
        //Codeur Y  //P0.23:16
        *regCodeurY = (IO0PIN & 0x00FF0000) << 8;

	//printf("X.3: %x ; Y.3: %x \n",(IOPIN1 & 0x00FF0000) >>16,(IOPIN0 & 0x00FF0000) >>16);

    //Selection du deuxieme octet  (SEL1 = 1, SEL2 = 1)
    //P0.29 et P1.24 = 1
    //P0.28 et P1.25 = 1
    IO0SET = 0x03000000 ; //=> 0"0011" 00 00 00, P0.25:24 = 1 //=> "0011"0 00 00 00, P0.29:28 = 1
    IO1SET = 0x03000000 ; //=> 0"0011" 00 00 00, P1.25:24 = 1


    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX |= (IO1PIN & 0x00FF0000);
        //Codeur Y  //P0.23:16
        *regCodeurY |= (IO0PIN & 0x00FF0000);

	//printf("X.2: %x ; Y.2: %x \n",(IOPIN1 & 0x00FF0000)>>16,(IOPIN0 & 0x00FF0000)>>16);


    //Selection du troisieme octet  (SEL1 = 0, SEL2 = 0)
    //P0.29 et P1.24 = 0
    //P0.28 et P1.25 = 0
    IO0CLR = 0x03000000 ; //=> "0011"0 00 00 00, P0.25:24 = 0
    IO1CLR = 0x03000000 ; //=> 0"0011" 00 00 00, P1.25:24 = 0


    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX |= (IO1PIN & 0x00FF0000) >> 8;
        //Codeur Y  //P0.23:16
        *regCodeurY |= (IO0PIN & 0x00FF0000) >> 8;

	//printf("X.1: %x ; Y.1: %x \n",(IOPIN1 & 0x00FF0000)>>16,(IOPIN0 & 0x00FF0000)>>16);


    //Selection de l'octet de poids faible  (SEL1 = 1, SEL2 = 0)
    //P0.29 et P1.24 = 1
    //P0.28 et P1.25 = 0
    IO0SET = 0x01000000 ; //=> 0"0001" 00 00 00, P0.24 = 1
    IO1SET = 0x01000000 ; //=> 0"0001" 00 00 00, P1.24 = 1
    IO0CLR = 0x02000000 ; //=> 0"0010" 00 00 00, P0.25 = 0
    IO1CLR = 0x02000000 ; //=> 0"0010" 00 00 00, P1.25 = 0


    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX |= (IO1PIN & 0x00FF0000) >> 16;
        //Codeur Y  //P0.23:16
        *regCodeurY |= (IO0PIN & 0x00FF0000) >> 16;

	//printf("X.0: %x ; Y.0: %x \n",(IOPIN1 & 0x00FF0000) >> 16,(IOPIN0 & 0x00FF0000) >> 16);


    //On deverouille l'ecriture sur le bus (OE = 1)
    //P3.24 = 1
    IO3SET = 0x01000000 ; //=> 0"0001" 00 00 00, P3.24 = 1


    //La roue X compte en inverse
        *regCodeurX = -*regCodeurX ;

	//printf("X1: %.3ld ; Y1: %.3ld \n",*regCodeurX,*regCodeurY);
}


/**
  * @use : Affiche les quatre octets des compteurs codeur
  *
  * @param : void
  *
  * @retun : void
  *
  */
void lectureCodeursTest(unsigned long* regCodeurX, unsigned long* regCodeurY)  //(Validé sans delays)
{
    //RAZ des variables
    *regCodeurX = *regCodeurY = 0;

    //On enregistre la valeur des deux compteurs dans des bascules (OE = 0)
    //P3.24 = 0
    IO3CLR = 0x01000000 ; //=> 0"0001" 00 00 00, P3.24 = 0

    //Selection de l'octet de poids fort (SEL1 = 0, SEL2 = 1)
    //P0.29 et P1.24 = 0
    //P0.28 et P1.25 = 1
    IO0CLR = 0x20000000 ; //=> "0010"0 00 00 00, P0.29 = 0
    IO1CLR = 0x01000000 ; //=> 0"0001" 00 00 00, P1.24 = 0
    IO0SET = 0x10000000 ; //=> "0001"0 00 00 00, P0.28 = 1
    IO1SET = 0x02000000 ; //=> 0"0010" 00 00 00, P1.25 = 1

    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX = (IO1PIN & 0x00FF0000) >> 16;
        //Codeur Y  //P0.23:16
        *regCodeurY = (IO0PIN & 0x00FF0000) >> 16;
    //printf("\nOct1 | X : %.3lu - Y : %.3lu\n",*regCodeurX, *regCodeurY);

    //Selection du deuxieme octet  (SEL1 = 1, SEL2 = 1)
    //P0.29 et P1.24 = 1
    //P0.28 et P1.25 = 1
    IO0SET = 0x30000000 ; //=> "0011"0 00 00 00, P0.29:28 = 1
    IO1SET = 0x03000000 ; //=> 0"0011" 00 00 00, P1.24:25 = 1

    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX = (IO1PIN & 0x00FF0000)>>16;
        //Codeur Y  //P0.23:16
        *regCodeurY = (IO0PIN & 0x00FF0000)>>16;
    printf("Oct2 | X : %.3lu - Y : %.3lu\n",*regCodeurX, *regCodeurY);

    //Selection ddu troisieme octet  (SEL1 = 0, SEL2 = 0)
    //P0.29 et P1.24 = 0
    //P0.28 et P1.25 = 0
    IO0CLR = 0x30000000 ; //=> "0011"0 00 00 00, P0.28:29 = 0
    IO1CLR = 0x03000000 ; //=> 0"0011" 00 00 00, P1.25:24 = 0

    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX = (IO1PIN & 0x00FF0000) >> 16;
        //Codeur Y  //P0.23:16
        *regCodeurY = (IO0PIN & 0x00FF0000) >> 16;
    printf("Oct3 | X : %.3lu - Y : %.3lu\n",*regCodeurX, *regCodeurY);

    //Selection de l'octet de poids faible  (SEL1 = 1, SEL2 = 0)
    //P0.29 et P1.24 = 1
    //P0.28 et P1.25 = 0
    IO0SET = 0x20000000 ; //=> "0010"0 00 00 00, P0.29 = 1
    IO1SET = 0x01000000 ; //=> 0"0001" 00 00 00, P1.24 = 1
    IO0CLR = 0x10000000 ; //=> "0001"0 00 00 00, P0.28 = 0
    IO1CLR = 0x02000000 ; //=> 0"0010" 00 00 00, P1.25 = 0

    //Recuperation des donnees
        //Codeur X  //P1.23:16
        *regCodeurX = (IO1PIN & 0x00FF0000) >> 16;
        //Codeur Y  //P0.23:16
        *regCodeurY = (IO0PIN & 0x00FF0000) >> 16;
    printf("Oct4 | X : %.3lu - Y : %.3lu\n",*regCodeurX, *regCodeurY);

    //On deverouille l'ecriture sur le bus (OE = 1)
    //P3.24 = 1
    IO3SET = 0x01000000 ; //=> 0"0001" 00 00 00, P3.24 = 1
}

/**
  * @use : Initialise correctement la direction des pins codeurs
  *         Perd son utilite si l'on utilise un initES() global (methode a preferer)
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initES_cod()
{


    //PINSEL2.17:14 = 0 (GPIO P3.25:24) /!\ Devrait etre effectif en reset µC, meme si l'experience montre le contraire
    PINSEL2 &= ~(0xF << 14);

    /*
    Entrée:
     - P0.23:16
     - P1.23:16
    Sortie :
     - P0.28:29
     - P1.24:25
     - P3.25:24
    */


    //P0.16:23 en entrée (8bits)
    IO0DIR = IO0DIR & ~(0xFF << 16);

    //P1.16:23 en entrée (8bits)
    IO1DIR = IO1DIR & ~(0xFF << 16);

    //P0.28:29 en sortie (2bits)
    IO0DIR = IO0DIR | (0x03 << 24); // 3 << 28

    //P1.24:25 en sortie (2bits)
    IO1DIR = IO1DIR | (0x03 << 24);

    //P3.24:25 en sortie (2bits)
    IO3DIR = IO3DIR | (0x03 << 24);
}


/**
  * @use : Reset nos deux codeurs
  *
  * @param : void
  *
  * @retun : void
  *
  */
void resetCodeurs()
{
    //RST
        //P3.25 = 0
        IO3CLR = 0x02000000 ; //0"0010" 00 00 00 (.25 = 0)
        //P3.25 = 1
        IO3SET = 0x02000000 ; //0"0010" 00 00 00 (.25 = 1)
}
