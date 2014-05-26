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
	signed long delta_x=(x_dest-x_source)/100;
	signed long delta_y=(y_dest-y_source)/100;
	if(delta_x==0 && delta_y ==0)
	{
		*distance=0;
		*angle=0;
	}
	else
	{
		*distance=sqrt(delta_x*delta_x+delta_y*delta_y)*100;
		if(delta_y==0||delta_x==0)
		{
			if(delta_y==0)
			{
				if(delta_x>0)
				{
					*angle=0;
				}
				else
				{
					*angle=ODO_PI;
				}
			}
			else
			{
				if(delta_y>0)
				{
					*angle=ODO_PI/2;
				}
				else
				{
					*angle=-(ODO_PI/2);
				}
			}
		}
		else
		{
			*angle=atan((float)((float)delta_y/(float)delta_x));
			if(delta_x<0)
			{
				if(delta_y<0)
				{
					*angle-=ODO_PI;
				}
				else
				{
					*angle+=ODO_PI;
				}
			}
		}
	}


}
/*
signed long Asserv_Cons_distance = 0;
signed long Asserv_Cons_angle = 0;

///////////static_vars/////////////////////////////////////////////////////
static int Asserv_mode=0;
*/
signed int phase_deplacement=DEPLACEMENT_DEBUT;
static unsigned int Tempo_move_to=0;
unsigned char flag_stop=0;
signed int move_to(signed long x_dest,signed long y_dest, unsigned char backward)
{
	signed long distance;
	double angle;
	get_linear_coord(x_dest,y_dest,Odo_pos_x,Odo_pos_y,&distance,&angle);
	if(backward==1)
	{
		distance=-distance;
		if(angle >0)
		{
			angle-=ODO_PI;
		}
		else
		{
			angle+=ODO_PI;
		}
	}
	if(flag_stop==1)
	{
		if(Check_Dist_Sonard()==0)
		{
			flag_stop=0;
			Mode_Asserv(MODE_PID);
		}
	}
	else if(0)//Check_Dist_Sonard()==1)
	{
		Mode_Asserv(MODE_STOP);
		flag_stop=1;
	}
	else
	{

	switch(phase_deplacement)
	{

	case DEPLACEMENT_DEBUT :
		FLAG_RESET_CODEURS=1;

		while(FLAG_RESET_CODEURS==1);
		phase_deplacement=DEPLACEMENT_ROTATION;
		break;
	case DEPLACEMENT_ARRET :
		Mode_Asserv(MODE_STOP);
		break;
	case DEPLACEMENT_ROTATION :
		set_Asserv_angle_abs(angle);
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
					phase_deplacement=DEPLACEMENT_AVANCE;
					Asserv_Cons_distance=distance;
					FLAG_IT_1MS=1;
					while(FLAG_IT_1MS==1);
				}


		break;
	case DEPLACEMENT_AVANCE :
		if(Tempo_move_to<THRESHOLD_ANGLE_TEMPO)
				{
					if(Asserv_dst_act<THRESHOLD_DISTANCE_AV && Asserv_dst_act>-THRESHOLD_DISTANCE_AV)
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
	case DEPLACEMENT_RALENTI :

		break;
	case DEPLACEMENT_FIN :

		break;

	}
	}
	return phase_deplacement;
}

unsigned char Check_Dist_Sonard()
{
	if(Dist_Sonard0<350||Dist_Sonard1<350)
	{
		return 1;
	}
	return 0;
}
void self_pos_jaune()
{
	int i;
	FLAG_IT_1MS=1;
	while(FLAG_IT_1MS==1)
	{
	}
	Mode_Asserv(MODE_STOP);
	FLAG_MANUAL=1;
	controlMotor1_invert(-3000);
	controlMotor2_invert(-3000);
	for(i=0;i<300;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	Odo_pos_y=2000;
	Odo_angle=ODO_PI/2.0;

	controlMotor1_invert(3000);
	controlMotor2_invert(3000);

	for(i=0;i<70;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	controlMotor1_invert(0);
	controlMotor2_invert(0);
	FLAG_RESET_CODEURS=1;
		while(FLAG_RESET_CODEURS==1);
	Mode_Asserv(MODE_PID);
	FLAG_MANUAL=0;
	set_Asserv_angle_abs(0.0);
	for(i=0;i<200;i++)
		{
			FLAG_IT_1MS=1;
			while(FLAG_IT_1MS==1)
			{
			}
		}



	FLAG_IT_1MS=1;
	while(FLAG_IT_1MS==1)
	{
	}
	Mode_Asserv(MODE_STOP);
	FLAG_MANUAL=1;
	controlMotor1_invert(-3000);
	controlMotor2_invert(-3000);
	for(i=0;i<300;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	Odo_pos_x=2000;
	controlMotor1_invert(3000);
	controlMotor2_invert(3000);

	for(i=0;i<70;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	controlMotor1_invert(0);
	controlMotor2_invert(0);
	FLAG_RESET_CODEURS=1;
	while(FLAG_RESET_CODEURS==1);
	Mode_Asserv(MODE_PID);
	set_Asserv_angle_abs(0.0);

	FLAG_MANUAL=0;


}

void self_pos_rouge()
{
	int i;
	FLAG_IT_1MS=1;
	while(FLAG_IT_1MS==1)
	{
	}
	Mode_Asserv(MODE_STOP);
	FLAG_MANUAL=1;
	controlMotor1_invert(-3000);
	controlMotor2_invert(-3000);
	for(i=0;i<300;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	Odo_pos_y=10400;
	Odo_angle=ODO_PI/2.0;

	controlMotor1_invert(3000);
	controlMotor2_invert(3000);

	for(i=0;i<30;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	controlMotor1_invert(0);
	controlMotor2_invert(0);
	for(i=0;i<200;i++)
		{
			FLAG_IT_1MS=1;
			while(FLAG_IT_1MS==1)
			{
			}
		}
	FLAG_RESET_CODEURS=1;
		while(FLAG_RESET_CODEURS==1);
	Mode_Asserv(MODE_PID);
	FLAG_MANUAL=0;
	set_Asserv_angle_abs(0.0);
	for(i=0;i<200;i++)
		{
			FLAG_IT_1MS=1;
			while(FLAG_IT_1MS==1)
			{
			}
		}



	FLAG_IT_1MS=1;
	while(FLAG_IT_1MS==1)
	{
	}
	Mode_Asserv(MODE_STOP);
	FLAG_MANUAL=1;
	controlMotor1_invert(-3500);
	controlMotor2_invert(-3000);
	for(i=0;i<300;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	Odo_pos_x=10400;
	controlMotor1_invert(3500);
	controlMotor2_invert(3000);

	for(i=0;i<70;i++)
	{
		FLAG_IT_1MS=1;
		while(FLAG_IT_1MS==1)
		{
		}
	}
	controlMotor1_invert(0);
	controlMotor2_invert(0);
	for(i=0;i<200;i++)
		{
			FLAG_IT_1MS=1;
			while(FLAG_IT_1MS==1)
			{
			}
		}
	FLAG_RESET_CODEURS=1;
	while(FLAG_RESET_CODEURS==1);
	Mode_Asserv(MODE_PID);
	set_Asserv_angle_abs(0.0);
	FLAG_MANUAL=0;
}
