#ifndef ASSERVISSEMENT_HL_H_
#define ASSERVISSEMENT_HL_H_
#define MODE_P 0
#define MODE_PI 1
#define MODE_PD 2
extern signed long Asserv_Cons_distance;
extern signed long Asserv_Cons_angle;
void Gestion_Asserv_HL(long Tick_droit,long Tick_gauche,long* Cons_droite,long* Cons_gauche);
void Asserv_Reset_Integrateur(void);
void Asserv_Reset_Derivateur(void);
#endif /* ASSERVISSEMENT_HL_H_ */
