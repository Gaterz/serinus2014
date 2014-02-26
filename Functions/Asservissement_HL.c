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
long double Asserv_Cons_angle = 0;
long double Asserv_zero = 0;
long double Asserv_dst_act =0;
///////////static_vars/////////////////////////////////////////////////////
static int Asserv_mode=0;
static signed long Asserv_Integrale_Distance = 0;
static signed long Asserv_Integrale_angle = 0;
static signed long Asserv_Derivee_Distance = 0;
static signed long Asserv_Derivee_angle = 0;
///////////////////////////////////////////////////////////////////////////
void Gestion_Asserv_HL(signed long Tick_droit,signed long Tick_gauche,signed long* ordre_distance,signed long* ordre_angle)
{
	//Vars/////////////////////////////////////////////////////////////////
	signed long delta_distance=0;
	signed long delta_angle=0;
	//signed long ordre_distance=0;
	//signed long ordre_angle=0;
	//Si pas en STOP///////////////////////////////////////////////////////
	if(get_Mode_Asserv() !=MODE_STOP)
	{
	//Moyennage////////////////////////////////////////////////////////////
	signed long Moyenne = (Tick_droit+Tick_gauche)/2;
	temp_dst=Moyenne;
	tableau_identif[temp_i]=Moyenne;
	temp_i++;


	//Différence///////////////////////////////////////////////////////////
	signed long Difference = Tick_gauche-Tick_droit;

	//Calcul d'erreur//////////////////////////////////////////////////////
	signed long Erreur_distance 	=Asserv_Cons_distance	-	Moyenne;
	Asserv_dst_act=Erreur_distance;
	signed long Erreur_angle 		=Asserv_Cons_angle*ENTRAXE_TICK_DIA		-	Difference;

	//Intégration//////////////////////////////////////////////////////////
	if(Asserv_mode==MODE_PI)
	{
		Asserv_Integrale_Distance	+=Erreur_distance;
		Asserv_Integrale_angle		+=Erreur_angle;
		if(Asserv_Integrale_Distance> ASSERV_MAX_INTEGRALE_DST)	Asserv_Integrale_Distance=	ASSERV_MAX_INTEGRALE_DST;
		if(Asserv_Integrale_Distance<-ASSERV_MAX_INTEGRALE_DST)	Asserv_Integrale_Distance= -ASSERV_MAX_INTEGRALE_DST;
		if(Asserv_Integrale_angle>	ASSERV_MAX_INTEGRALE_ANG)	Asserv_Integrale_angle=	ASSERV_MAX_INTEGRALE_ANG;
		if(Asserv_Integrale_angle< -ASSERV_MAX_INTEGRALE_ANG)	Asserv_Integrale_angle=-ASSERV_MAX_INTEGRALE_ANG;
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
	*ordre_distance	=		Erreur_distance	* P_PID_DISTANCE	+
							Asserv_Integrale_Distance * I_PID_DISTANCE 	-
							delta_distance * D_PID_DISTANCE;

	*ordre_angle		=	Erreur_angle * P_PID_ANGLE			+
							Asserv_Integrale_angle * I_PID_ANGLE 		-
							delta_angle * D_PID_ANGLE;

	//Calcul des consignes/////////////////////////////////////////////////
	//*Cons_droite=ordre_distance-ordre_angle;
	//*Cons_gauche=ordre_distance+ordre_angle;
	}
}
void Mode_Asserv(int mode)
{
	switch(mode)
	{
		case MODE_STOP:
			Asserv_Reset_Integrateur();
			Asserv_Reset_Derivateur();
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
int get_Mode_Asserv()
{
	return Asserv_mode;
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
void set_Asserv_angle_abs(long double angle_abs)
{
	long double tmp = angle_abs-Asserv_zero;
	//Asserv_Cons_angle = angle_abs-Asserv_zero;
	if(tmp>ODO_ANGLE_MAX)
	{
	tmp-=2*ODO_PI;
	}
	if(tmp<ODO_ANGLE_MIN)
	{
		tmp+=2*ODO_PI;
	}
	Asserv_Cons_angle=tmp;
}
