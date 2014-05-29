#ifndef DEPLACEMENTS_H_
#define DEPLACEMENTS_H_
#define DEPLACEMENT_ARRET 0
#define DEPLACEMENT_ROTATION 1
#define DEPLACEMENT_AVANCE 2
#define DEPLACEMENT_RALENTI 3
#define DEPLACEMENT_DEBUT 4
#define DEPLACEMENT_FIN 5
#define DEPLACEMENT_STOP 6
void get_linear_coord(signed long x_dest,signed long y_dest,signed long x_source,signed long y_source,signed long* distance,double* angle);
signed int move_to(signed long x_dest,signed long y_dest, unsigned char backward);
extern signed int phase_deplacement;
void self_pos_rouge();
void self_pos_jaune();
extern unsigned char Check_Dist_Sonard();
extern unsigned char INHIB_SONAR0;
extern unsigned char INHIB_SONAR1;
extern unsigned char INHIB_SONAR2;
extern unsigned char INHIB_SONAR3;
#endif /* DEPLACEMENTS_H_ */
