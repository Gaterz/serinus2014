/////////////////////////////////////////////////////////////////////
// Nom du fichier : pwm.c
// Fonction : Contient toutes les fonctions de bas niveau de gestion
// des PWM et des moteurs.
//
// Cree par : Valentin VERGEZ
// Date de creation : novembre 2011
//
// Adapte par : Julien MAURAT
//
// Modifie par : --
// Date de derniere modification : 18/12/2013
//
// Etat du fichier (REDACTION/VALIDATION/VALIDE)
// Etat : VALIDE
/////////////////////////////////////////////////////////////////////


/*Constantes*/
   // #include "../Constantes/constantes.h"


#include "../all_head.h"
//#include "../basNiveau/fonctionsPerso.h"

//רררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררר
//------------------------------------------------------------------------------------------------------------
	//Fonctions de bas niveau pour la gestion de la PWM	//רררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררר
//------------------------------------------------------------------------------------------------------------
//רררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררררר


/**
  * @use : modifie les valeurs de IN1 et IN2 (commande du pont en H) pour le moteur2
  *
  * @param :
  *     - unsigned char : in1 = valeur souhaitee pour IN1_U2
  *     - unsigned char : in2 = valeur souhaitee pour IN2_U2
  *
  * @retun : void
  *
  */
void in_Mot2(unsigned char in1, unsigned char in2)
{
    /*
        IN1_U2 = P0.7
        IN2_U2 = P0.6
    */
	IO0CLR = 3 << 6 ;                   //Clear de P0.6:7
    IO0SET = (in1 << 7 | in2 << 6) ;    //Ecriture de IN1_U2 et IN2_U2 sur P0.6:7
}


/**
  * @use : modifie les valeurs de IN1 et IN2 (commande du pont en H) pour le moteur1
  *
  * @param :
  *     - unsigned char : in1 = valeur souhaitee pour IN1_U1
  *     - unsigned char : in2 = valeur souhaitee pour IN2_U1
  *
  * @retun : void
  *
  */
void in_Mot1(unsigned char in1, unsigned char in2)
{
    /*
        IN1_U1 = P0.5
        IN2_U1 = P0.4
    */
    IO0CLR = 3 << 4 ;                   //Clear de P0.4:5
    IO0SET = (in1 << 5 | in2 << 4) ;    //Ecriture de IN1_U2 et IN2_U2 sur P0.4:5
}


/**
  * @use : fixe le rapport cyclique de la PWM U1 pour Fpwm = 5900Hz
  *
  * @param :
  *     - unsigned int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  * @retun : void
  *
  */
void pwmU1(unsigned int dutyCycle)
{
    if (dutyCycle > 10000) dutyCycle = 10000;

    PWM_MR4 = (unsigned long) dutyCycle ;

    PWM_LER |= 0x00000010 ; //Changement sur MR4 effectif au prochain front pclk
}



/**
  * @use : fixe le rapport cyclique de la PWM U2 pour Fpwm = 5900Hz
  *
  * @param :
  *     - unsigned int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  * @retun : void
  *
  */
void pwmU2(unsigned int dutyCycle)
{
	if (dutyCycle > 10000) dutyCycle = 10000;

    PWM_MR6 = (unsigned long) dutyCycle ;

    PWM_LER |= 0x00000040 ; //Changement sur MR6 effectif au prochain front pclk
}



/**
  * @use : fixe le rapport cyclique de la PWM U1 pour Fpwm != 5900Hz
  *         nיcessite des calculs supplיmentaires par rapport א pwmU1
  *
  * @param :
  *     - unsigned int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  * @retun : void
  *
  */
void pwmU1var(unsigned int dutyCycle)
{
    if (dutyCycle > 10000) dutyCycle = 10000;

    PWM_MR4 = (unsigned long)((PWM_MR0 * dutyCycle) / 10000);

    PWM_LER |= 0x00000010 ; //Changement sur MR4 effectif au prochain front pclk
}



/**
  * @use : fixe le rapport cyclique de la PWM U2 pour Fpwm != 5900Hz
  *         nיcessite des calculs supplיmentaires par rapport א pwmU2
  *
  * @param :
  *     - unsigned int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  * @retun : void
  *
  */
void pwmU2var(unsigned int dutyCycle)
{
	if (dutyCycle > 10000) dutyCycle = 10000;

    PWM_MR6 = (unsigned long)((PWM_MR0 * dutyCycle) / 10000);

    PWM_LER |= 0x00000040 ; //Changement sur MR6 effectif au prochain front pclk
}



/**
  * @use : Modifie la frיquence de la PWM
  *
  * @param :
  *        - unsigned long : freq = la Frיquence pwm en Hz
  *
  * @retun : void
  *
  */
void modifPWM(unsigned long freq)
{

    PWM_MR0 = 58823529 / freq  ;

    PWM_LER |= 0x00000001 ;  //Changement sur MR0 effectif au prochain front pclk
}


/**
  * @use : Configure les valeurs de IN1 et IN2 et la PWM pour le moteur 1
  *
  * @param :
  *		   - int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  *             VALEUR SIGNEE => Indique le sens de la rotation /!\
  *
  * @retun : void
  *
  */
void controlMotor1(int dutyCycle)
{
	if(dutyCycle<0)
	{
        //Recul
		in_Mot1(1,0); 					// Commande du pont en H
		dutyCycle = -dutyCycle;			// Passage du rapport cyclique en positif
		pwmU1((unsigned int)(dutyCycle)); // Gיnיration de la PWM
	}
	else
	{
	    //Avance
		in_Mot1(0,1); 					// Commande du pont en H
		pwmU1((unsigned int)(dutyCycle)); // Gיnיration de la PWM
	}
}


/**
  * @use : Configure les valeurs de IN1 et IN2 et la PWM pour le moteur 2
  *
  * @param :
  *		   - int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  *             VALEUR SIGNEE => Indique le sens de la rotation /!\
  *
  * @retun : void
  *
  */
void controlMotor2(int dutyCycle)
{
	if(dutyCycle<0)
	{
	    //Recule
		in_Mot2(1,0); 					// Commande du pont en H
		dutyCycle = -dutyCycle;			// Passage du rapport cyclique en positif
		pwmU2((unsigned int)(dutyCycle)); // Gיnיration de la PWM
	}
	else
	{
	    //Avance
		in_Mot2(0,1); 					// Commande du pont en H
		pwmU2((unsigned int)(dutyCycle)); // Gיnיration de la PWM
	}
}


/**
  * @use : Configure les valeurs de IN1 et IN2 et la PWM pour le moteur 1
  *         Prend en compte les inverseurs presents sur le shield
  *
  * @param :
  *		   - int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  *             VALEUR SIGNEE => Indique le sens de la rotation /!\
  *
  * @retun : void
  *
  */
void controlMotor1_invert(int dutyCycle)
{
	if(dutyCycle<0)
	{
        //Recul
		in_Mot1(1,0); 					// Commande du pont en H
		dutyCycle = -dutyCycle;			// Passage du rapport cyclique en positif
		pwmU1((unsigned int)(1000 - dutyCycle)); // Gיnיration de la PWM
	}
	else if (dutyCycle>0)
	{
	    //Avance
		in_Mot1(0,1); 					// Commande du pont en H
		pwmU1((unsigned int)(1000 - dutyCycle)); // Gיnיration de la PWM
	}
  else
  {
      //Arrךt
    in_Mot1(1,1);           // Commande du pont en H
    pwmU1(0); // Gיnיration de la PWM
  }
}


/**
  * @use : Configure les valeurs de IN1 et IN2 et la PWM pour le moteur 2
  *         Prend en compte les inverseurs presents sur le shield
  *
  * @param :
  *		   - int : dutyCycle = le rapport cyclique de la PWM en /10 000
  *             10 000 => 100%, 5 000 => 50%, 5 => 0,05%
  *
  *             VALEUR SIGNEE => Indique le sens de la rotation /!\
  *
  * @retun : void
  *
  */
void controlMotor2_invert(int dutyCycle)
{
	if(dutyCycle<0)
	{
	    //Recul
		in_Mot2(1,0); 					// Commande du pont en H
		dutyCycle = -dutyCycle;			// Passage du rapport cyclique en positif
		pwmU2((unsigned int)(1000 - dutyCycle)); // Gיnיration de la PWM
	}
	else if(dutyCycle>0)
	{
	    //Avance
		in_Mot2(0,1); 					// Commande du pont en H
		pwmU2((unsigned int)(1000 - dutyCycle)); // Gיnיration de la PWM
	}
  else
  {
      //Arrךt
    in_Mot2(1,1);           // Commande du pont en H
    pwmU2(0); // Gיnיration de la PWM
  }
}


/**
  * @use : Initialise les PWM avec leur timer associe, Fpwm = 5900Hz
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initPWM()
{
    //Note : l'horloge est de 59MHz
    //Soit T=17ns

    /*
        0xFFFFAF7C = FF FF "1010"F "0111""1100" => '&', RAZ de PCR.12, 14 et 6:2
        0x00005000 = 00 00 "0101"0 00 => '|', RAZ de PCR.12 et 14
        PWMENA4 = PCR.12    (Output Enable)
        PWMENA6 = PCR.14
        PCR.2:6 = 0         (Single Edge)
    */
    PWM_PCR = (PWM_PCR & 0xFFFFAF7C) | 0x00005000 ;       //Pin de PWM4 et PWM6 enables, mode single edge

    /*
        0x00000002 = 00 00 00 0"0010", fonction reset sur MR0
    */
    PWM_MCR = 0x00000002;    //Reset de PWMTC sur MR0

    PWM_MR0 = 1000 ;        //Pיriode de PWMTC de 10 000 * 17 ns = 170 us, soit Fpwm = 5900 Hz
                            //(On laisse PWMPR א 0, ainsi PWMTC compte tout les fronts pclk)

    /*
        0x00000009 = 00 00 00 0"1001"
        1: Counter Enable
        2: Reset
        3: NA
        4: Enable pwm
    */
    PWM_TCR |= 0x00000009 ;   //Autorisation de PWM et de Timer
}



/**
  * @use : Initialise correctement la direction des pins PWM
  *         Perd son utilite si l'on utilise un initES() global (methode a preferer)
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initES_PWM()
{
    /*
        0xFFFFFC0F = FF FF F"1100" "0000"F => '&', RAZ de DIR.9:4
        0x000003F0 = 00 00 0"0011" "1111"0 => '|', SET de DIR.9:4 א '1' (sortie)

        P0.4 => IN2_U1
        P0.5 => IN1_U1
        P0.6 => IN2_U2
        P0.7 => IN1_U2
        P0.8 => ENABLE_U1
        P0.9 => ENABLE_U2
    */
    IO0DIR = (IO0DIR & 0xFFFFFC0F)| 0x000003F0 ; //P0.9:4 en sortie
}



/**
  * @use : Configure correctement les pins pour une utilisation en mode PWM
  *         Perd son utilite si l'on utilise un initFunction() global (methode a preferer)
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initFunction_PWM()
{
    /*
        PWM4 => PINSEL0.17:16 = "10"
        PWM6 => PINSEL0.19:18 = "10"
        0xFFF0FFFF = FF "1111""0000" FF FF => '&', RAZ des PINSEL0.19:16
        0x000A0000 = 00 "0000""1010" 00 00 => '|', SET des PINSEL0.19:16
    */
    PINSEL0 = (PINSEL0 & 0xFFF0FFFF) | 0x000A0000 ;  //Utilisation des PWM4 et PWM6
}

//------------------------------------------------------------------------------------------------------------


