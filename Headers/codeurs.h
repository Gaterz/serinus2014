#ifndef _Codeurs_Header_
#define _Codeurs_Header_

//������������������������������������������������������������������������������������������������������������
//------------------------------------------------------------------------------------------------------------
	//Fonctions de bas niveau pour la gestion des codeurs	//������������������������������������������������������������������������������������������������������������
//------------------------------------------------------------------------------------------------------------
//������������������������������������������������������������������������������������������������������������

/**
  * @use : Recupere la valeur des compteurs codeur en signe
  *
  * @param : void
  *
  * @retun : void
  *
  */
void lectureCodeursSigned(signed long* regCodeurX, signed long* regCodeurY);

/**
  * @use : Affiche les quatre octets des compteurs codeur
  *
  * @param : void
  *
  * @retun : void
  *
  */
void lectureCodeursTest(unsigned long* regCodeurX, unsigned long* regCodeurY);


/**
  * @use : Initialise correctement la direction des pins codeurs
  *         Perd son utilit� si l'on utilise un initES() global (m�thode � pr�f�rer)
  *
  * @param : void
  *
  * @retun : void
  *
  */
void initES_cod();

/**
  * @use : Reset nos deux codeurs
  *
  * @param : void
  *
  * @retun : void
  *
  */
void resetCodeurs();

//------------------------------------------------------------------------------------------------------------

/*--------------------------------------Define de confort----------------------------------------------------*/
    //Permet d'appeler la fonction plus simplement
        //NB : je ne renomme pas directement la fonction car il en existe plusieurs formes
        //      legerement differentes dans les codes plus anciens
        #define codeurs(x,y); lectureCodeursSigned(x,y);

#endif
