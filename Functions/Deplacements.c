/**************************Deplacements.c*********************************************
Auteur : Julien MAURAT
Date : 18 déc. 2013
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
#include <math.h>
//static int
void get_linear_coord(signed long x_dest,signed long y_dest,signed long x_source,signed long y_source,signed long* distance,double* angle)
{
	signed long delta_x=x_dest-x_source;
	signed long delta_y=y_dest-y_source;
	*distance=sqrt(delta_x*delta_x+delta_y*delta_y);
	*angle=atan2(delta_y,delta_x);
}
/*
signed long Asserv_Cons_distance = 0;
signed long Asserv_Cons_angle = 0;

///////////static_vars/////////////////////////////////////////////////////
static int Asserv_mode=0;
*/
static signed int phase_deplacement=DEPLACEMENT_DEBUT;
static unsigned int Tempo_move_to=0;
signed int move_to(signed long x_dest,signed long y_dest)
{
	signed long distance;
	double angle;
	get_linear_coord(x_dest,y_dest,Odo_pos_x,Odo_pos_y,&distance,&angle);
	switch(phase_deplacement)
	{

	case DEPLACEMENT_DEBUT :
		phase_deplacement=DEPLACEMENT_ROTATION;
		break;
	case DEPLACEMENT_ARRET :
		FLAG_RESET_CODEURS=1;
		break;
	case DEPLACEMENT_ROTATION :
		Asserv_Cons_angle=angle;
		if(Tempo_move_to<THRESHOLD_ANGLE_TEMPO)
		{
			if(Odo_angle<angle+THRESHOLD_ANGLE && Odo_angle>angle-THRESHOLD_ANGLE)
			{
				Tempo_move_to++;
			}
			else
			{
				Tempo_move_to=0;
			}
		}
		else
		{
			Tempo_move_to=0;
			phase_deplacement=DEPLACEMENT_ARRET;
		}

		break;
	case DEPLACEMENT_AVANCE :

		break;
	case DEPLACEMENT_RALENTI :

		break;
	case DEPLACEMENT_FIN :

		break;

	}
	return phase_deplacement;
}


