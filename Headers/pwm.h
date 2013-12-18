#ifndef _PWN_HEADER_
#define _PWM_HEADER_


/*--------------------------------------Define de confort----------------------------------------------------*/
    //Permet d'appeler la fonction plus simplement
        //NB : je ne renomme pas directement la fonction car il en existe plusieurs formes
        //      legerement differentes
        #define controlMoteurGauche(x); controlMotor2_invert(x);
        #define controlMoteurDroit(x); controlMotor1_invert(x);

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
void in_Mot2(unsigned char in1, unsigned char in2);


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
void in_Mot1(unsigned char in1, unsigned char in2);


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
void pwmU1(unsigned int dutyCycle);



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
void pwmU2(unsigned int dutyCycle);



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
void pwmU1var(unsigned int dutyCycle);



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
void pwmU2var(unsigned int dutyCycle);



/**
  * @use : Modifie la frיquence de la PWM
  *
  * @param :
  *        - unsigned long : freq = la Frיquence pwm en Hz
  *
  * @retun : void
  *
  */
void modifPWM(unsigned long freq);


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
void controlMotor1(int dutyCycle);


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
void controlMotor2(int dutyCycle);


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
void controlMotor1_invert(int dutyCycle);


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
void controlMotor2_invert(int dutyCycle);


/**
  * @use : Initialise les PWM avec leur timer associe, Fpwm = 5900Hz
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initPWM();



/**
  * @use : Initialise correctement la direction des pins PWM
  *         Perd son utilite si l'on utilise un initES() global (methode a preferer)
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initES_PWM();



/**
  * @use : Configure correctement les pins pour une utilisation en mode PWM
  *         Perd son utilite si l'on utilise un initFunction() global (methode a preferer)
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initFunction_PWM();

//------------------------------------------------------------------------------------------------------------



#endif
