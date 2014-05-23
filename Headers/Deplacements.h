#ifndef DEPLACEMENTS_H_
#define DEPLACEMENTS_H_
#define DEPLACEMENT_ARRET 0
#define DEPLACEMENT_ROTATION 1
#define DEPLACEMENT_AVANCE 2
#define DEPLACEMENT_RALENTI 3
#define DEPLACEMENT_DEBUT 4
#define DEPLACEMENT_FIN 5
void get_linear_coord(signed long x_dest,signed long y_dest,signed long x_source,signed long y_source,signed long* distance,double* angle);
signed int move_to(signed long x_dest,signed long y_dest);
extern signed int phase_deplacement;
extern void self_pos();
unsigned char Check_Dist_Sonard();
#endif /* DEPLACEMENTS_H_ */
