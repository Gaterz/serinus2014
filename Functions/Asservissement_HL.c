/**************************Asservissement_HL.c*********************************************
Auteur : Julien MAURAT
Date : 14 déc. 2013
Description : Fonctions abstraites de gestion de l'asservissement
L'asservissement sur le robot est gérer de la manierre suivante :
                     +-----------------------------------------------------------------------+
                     |                                                                       |
                   +-v-+             +---+                                                   |
                   | - |   +---+     |   |            +-------------+          +-------+     |
Consigne distance-->+  +--->PID+--+-->+  +------------> Roue droite +---+------>Moyenne+-----+
                   |   |   +-+-+  |  | + |            +-------------+   |      +---^---+
                   +---+          |  +-^-+                              |          |
                                  |    |                                +-------+  |
                                  |    |     +---+                              |  |
                                  |    |     |   |    +-------------+           |  |
                                  +---------->+  +----> Roue gauche +-+---------|--+
                                       |     | - |    +-------------+ |         |
                   +---+               |     +-^-+                    |         |(+)
                   |   |   +---+       |       |                      |       +-v--------+
Consigne angle----->+  +--->PID+-------+-------+                      +------->Différence+---+
                   | - |   +-+-+                                           (-)+----------+   |
                   +-^-+                                                                     |
                     |                                                                       |
                     +-----------------------------------------------------------------------+
Constantes : P,I et D du PID de distance et de celui d'angle
Fonctions : void Gestion_Asserv_HL(...) : Renvoi en sortie les consignes en fonction des
valeurs de codeuses envoyées
**************************************************************************************/
#include "all_head.h"
///////////coefficients////////////////////////////////////////////////////
#define P_PID_DISTANCE 1
#define I_PID_DISTANCE 0
#define D_PID_DISTANCE 0
#define P_PID_ANGLE 1
#define I_PID_ANGLE 0
#define D_PID_ANGLE 0
///////////gloabl_vars/////////////////////////////////////////////////////
signed long Asserv_Cons_distance = 10;
signed long Asserv_Cons_angle = 10;
signed long Asserv_Integrale_Distance = 10;
signed long Asserv_Integrale_angle = 10;
signed long Asserv_Derivee_Distance = 10;
signed long Asserv_Derivee_angle = 10;
///////////////////////////////////////////////////////////////////////////
void Gestion_Asserv_HL(signed long Tick_droit,signed long Tick_gauche,signed long* Cons_droite,signed long* Cons_gauche)
{
	//Moyennage////////////////////////////////////////////////////////////
	signed long Moyenne = (Tick_droit+Tick_gauche)/2;

	//Différence///////////////////////////////////////////////////////////
	signed long Difference = Tick_droit-Tick_gauche;

	//Calcul d'erreur//////////////////////////////////////////////////////
	signed long Erreur_distance 	=Asserv_Cons_distance	-	Moyenne;
	signed long Erreur_angle 		=Asserv_Cons_angle		-	Difference;

	//Intégration//////////////////////////////////////////////////////////
	Asserv_Integrale_Distance	+=Erreur_distance;
	Asserv_Integrale_angle		+=Erreur_angle;

	//Dérivation///////////////////////////////////////////////////////////
	//..distance//
	signed long delta_distance		=Erreur_distance	-	Asserv_Derivee_Distance;
	Asserv_Derivee_Distance	=Erreur_distance;
	//..angle//
	signed long delta_angle		=Erreur_angle		-	Asserv_Derivee_angle;
	Asserv_Derivee_angle	=Erreur_angle;

	//Application des coefficients/////////////////////////////////////////
	signed long ordre_distance	=	Erreur_distance	* P_PID_DISTANCE			+
							Asserv_Integrale_Distance * I_PID_DISTANCE 	+
							delta_distance * D_PID_DISTANCE;

	signed long ordre_angle	=	Erreur_angle * P_PID_ANGLE				+
							Asserv_Integrale_angle * I_PID_ANGLE 	+
							delta_angle * D_PID_ANGLE;

	//Calcul des consignes/////////////////////////////////////////////////
	*Cons_droite=ordre_distance+ordre_angle;
	*Cons_gauche=ordre_distance-ordre_angle;
}
