/**************************Deplacements.c*********************************************
Auteur : Julien MAURAT
Date : 18 déc. 2013
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
void get_linear_coord(signed long x_dest,signed long y_dest,signed long x_source,signed long y_source,signed long* distance,long double* angle)
{
	signed long delta_x=x_dest-x_source;
	signed long delta_y=y_dest-y_source;
	*distance=sqrt(delta_x*delta_x+delta_y*delta_y);

}
