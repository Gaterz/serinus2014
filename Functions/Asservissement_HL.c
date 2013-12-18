/**************************Asservissement_HL.c*********************************************
Auteur : Julien MAURAT
Date : 14 d�c. 2013
Description : Fonctions abstraites de gestion de l'asservissement
L'asservissement sur le robot est g�rer de la manierre suivante :
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
Consigne angle----->+  +--->PID+-------+-------+                      +------->Diff�rence+---+
                   | - |   +-+-+                                           (-)+----------+   |
                   +-^-+                                                                     |
                     |                                                                       |
                     +-----------------------------------------------------------------------+
Constantes : P,I et D du PID de distance et de celui d'angle
Fonctions : void Gestion_Asserv_HL(...) : Renvoi en sortie les consignes en fonction des
valeurs de codeuses envoy�es
**************************************************************************************/
#include "../all_head.h"
///////////coefficients////////////////////////////////////////////////////
#define P_PID_DISTANCE 1.0
#define I_PID_DISTANCE 0.0
#define D_PID_DISTANCE 0.0
#define P_PID_ANGLE 1.0
#define I_PID_ANGLE 0.0
#define D_PID_ANGLE 0.0
#define MODE_P 0
#define MODE_PI 1
#define MODE_PD 2
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
	//Vars////////////////////////////////////////////////////////////
	signed long delta_distance=0;
	signed long delta_angle=0;
	//Moyennage////////////////////////////////////////////////////////////
	signed long Moyenne = (Tick_droit+Tick_gauche)/2;

	//Diff�rence///////////////////////////////////////////////////////////
	signed long Difference = Tick_droit-Tick_gauche;

	//Calcul d'erreur//////////////////////////////////////////////////////
	signed long Erreur_distance 	=Asserv_Cons_distance	-	Moyenne;
	signed long Erreur_angle 		=Asserv_Cons_angle		-	Difference;

	//Int�gration//////////////////////////////////////////////////////////
	if(Asserv_mode==MODE_PI)
	{
		Asserv_Integrale_Distance	+=Erreur_distance;
		Asserv_Integrale_angle		+=Erreur_angle;
	}

	//D�rivation///////////////////////////////////////////////////////////
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
	*Cons_droite=ordre_distance+ordre_angle;
	*Cons_gauche=ordre_distance-ordre_angle;
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
