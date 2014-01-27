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
void get_linear_coord(signed long x_dest,signed long y_dest,signed long x_source,signed long y_source,signed long* distance,long double* angle)
{
	signed long delta_x=x_dest-x_source;
	signed long delta_y=y_dest-y_source;
	*distance=sqrt(delta_x*delta_x+delta_y*delta_y);
	*angle=atan2(delta_x,delta_y);
}
/*
signed long Asserv_Cons_distance = 0;
signed long Asserv_Cons_angle = 0;

///////////static_vars/////////////////////////////////////////////////////
static int Asserv_mode=0;
*/
static signed int phase_deplacement=DEPLACEMENT_ARRET;
void move_to(signed long x_dest,signed long y_dest)
{
	signed long distance;
	long double angle;
	get_linear_coord(x_dest,y_dest,Odo_pos_x,Odo_pos_x,&distance,&angle);
	Mode_Asserv(MODE_PD);
	getDeplacement_state(distance,angle);
}

signed int getDeplacement_state(signed long distance,long double angle)
{
	signed int state=DEPLACEMENT_ARRET;
	if(angle < THRESHOLD_ANGLE)
	{
		if(distance < THRESHOLD_DISTANCE)
		{
			state=DEPLACEMENT_ARRET;
		}
		else
		{
			state=DEPLACEMENT_AVANCE;
		}
	}
	else
	{
		state=DEPLACEMENT_ROTATION;
	}
}
