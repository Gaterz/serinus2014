#ifndef ASSERVISSEMENT_HL_H_
#define ASSERVISSEMENT_HL_H_
#define MODE_STOP 0
#define MODE_P 1
#define MODE_PI 2
#define MODE_PD 3
#define MODE_PID 4
void Mode_Asserv(int mode);
int get_Mode_Asserv();
extern signed long Asserv_Cons_distance;
extern double Asserv_Cons_angle;
extern double Asserv_zero;
extern signed long Asserv_dst_act;
void Gestion_Asserv_HL(long Tick_droit,long Tick_gauche,long* ordre_distance,long* ordre_angle);
void Asserv_Reset_Integrateur(void);
void Asserv_Reset_Derivateur(void);
void set_Asserv_angle_abs(double angle_abs);
#endif /* ASSERVISSEMENT_HL_H_ */
