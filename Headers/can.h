/** low level CAN driver functions.
 * code base notamment sur la note d'application AN10438
 */

//config registre C4MOD
#define CAN_RESET_MODE     0x01
#define CAN_OPERATING_MODE 0x00

//acces materiel.
#define    OUTB(x,y)    (*((volatile unsigned char *)(x)) = (y))
#define    INB(x)       (*((volatile unsigned char *)(x)))

#define    OUTW(x,y)    (*((volatile unsigned long *)(x)) = (y))
#define    INW(x)       (*((volatile unsigned long *)(x)))

/** le type defini permet de regrouper les informations relatives
 *  a un message CAN:
 *  - stdIdentifier: identifiant sur 11 bits (standard)
 *  - dlc: taille des donnees (de 0 a 8 octets inclus)
 *  - les donnees mises sous la forme de 2 mots de 32 bits. (8 octets par trame au max)
 */ 
typedef  struct {
  unsigned int  stdIdf;
  unsigned char dlc;  
  unsigned int  dataL; //octets 1 a 4
  unsigned int  dataH; //octets 5 a 8
} canMsgType;

///init CAN hardware (canal 4, 250Kbits/s).
void CANinit_HW();

/**
 *  Transmission du message en parametre.
 *  Cette fonction doit être appelée dans une tache periodique.
 *  renvoi: 
 *  * 0  si tout se passe bien
 *  * -1 si le DLC est invalide (>8)
*/
int CANTransmitMessage(canMsgType *msg);

/**
 * Reception d'un message 
 * si un nouveau message est arrive, alors 
 *  - la structure msg est mise a jour
 *  - la fonction renvoie 1
 * sinon 
 *  - la fonction renvoie 0
 *  - la structure msg n'est pas modifiee
 */
int CANReceiveMessage(canMsgType *msg);

