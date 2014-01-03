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
void Mode_Asserv(int mode) : Change le mode de l'asservissement entre P,PI,PD
	!!Toujours utiliser les define de MODE!!
void Asserv_Reset_Integrateur(void) : Reset des intégrateurs
void Asserv_Reset_Derivateur(void) : Reset des dérivateurs
**************************************************************************************/
#include "../all_head.h"
///////////coefficients////////////////////////////////////////////////////
#define P_PID_DISTANCE 1.0
#define I_PID_DISTANCE 0.1
#define D_PID_DISTANCE 0.0
#define P_PID_ANGLE 1.0
#define I_PID_ANGLE 0.1
#define D_PID_ANGLE 0.0
///////////global_vars/////////////////////////////////////////////////////
signed long Asserv_Cons_distance = 0;
signed long Asserv_Cons_angle = 0;
///////////static_vars/////////////////////////////////////////////////////
static int Asserv_mode=0;
static signed long Asserv_Integrale_Distance = 0;
static signed long Asserv_Integrale_angle = 0;
static signed long Asserv_Derivee_Distance = 0;
static signed long Asserv_Derivee_angle = 0;
///////////////////////////////////////////////////////////////////////////
void Gestion_Asserv_HL(signed long Tick_droit,signed long Tick_gauche,signed long* Cons_droite,signed long* Cons_gauche)
{
	//Vars/////////////////////////////////////////////////////////////////
	signed long delta_distance=0;
	signed long delta_angle=0;
	//Moyennage////////////////////////////////////////////////////////////
	signed long Moyenne = (Tick_droit+Tick_gauche)/2;

	//Différence///////////////////////////////////////////////////////////
	signed long Difference = Tick_droit-Tick_gauche;

	//Calcul d'erreur//////////////////////////////////////////////////////
	signed long Erreur_distance 	=Asserv_Cons_distance	-	Moyenne;
	signed long Erreur_angle 		=Asserv_Cons_angle		-	Difference;

	//Intégration//////////////////////////////////////////////////////////
	if(Asserv_mode==MODE_PI)
	{
		Asserv_Integrale_Distance	+=Erreur_distance;
		Asserv_Integrale_angle		+=Erreur_angle;
	}

	//Dérivation///////////////////////////////////////////////////////////
	if(Asserv_mode==MODE_PD)
	{
		//..distance//
		delta_distance	=Erreur_distance	-	Asserv_Derivee_Distance;
		Asserv_Derivee_Distance	=Erreur_distance;
		//..angle//
		delta_angle		=Erreur_angle		-	Asserv_Derivee_angle;
		Asserv_Derivee_angle	=Erreur_angle;
	}
	//Application des coefficients/////////////////////////////////////////
	signed long ordre_distance	=	Erreur_distance	* P_PID_DISTANCE	+
							Asserv_Integrale_Distance * I_PID_DISTANCE 	-
							delta_distance * D_PID_DISTANCE;

	signed long ordre_angle		=	Erreur_angle * P_PID_ANGLE			+
							Asserv_Integrale_angle * I_PID_ANGLE 		-
							delta_angle * D_PID_ANGLE;

	//Calcul des consignes/////////////////////////////////////////////////
	*Cons_droite=ordre_distance-ordre_angle;
	*Cons_gauche=ordre_distance+ordre_angle;
	if(*Cons_droite<-10000) *Cons_droite=-10000;
	if(*Cons_droite>10000) *Cons_droite=10000;
	if(*Cons_gauche<-10000) *Cons_gauche=-10000;
	if(*Cons_gauche>10000) *Cons_gauche=10000;

}
void Mode_Asserv(int mode)
{
	switch(mode)
	{
		case MODE_P:
			Asserv_Reset_Integrateur();
			Asserv_Reset_Derivateur();
		break;
		case MODE_PI:
			Asserv_Reset_Derivateur();
		break;
		case MODE_PD:
			Asserv_Reset_Integrateur();
		break;
	}
	Asserv_mode=mode;
}
void Asserv_Reset_Integrateur(void)
{
	Asserv_Integrale_Distance = 0;
	Asserv_Integrale_angle = 0;
}
void Asserv_Reset_Derivateur(void)
{
	Asserv_Derivee_Distance = 0;
	Asserv_Derivee_angle = 0;
}
