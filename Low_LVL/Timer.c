/**************************Timer.c*********************************************
Auteur : Julien MAURAT
Date : 22 d�c. 2013
Description : Fonction d'initialisation du timer1 et gestion de son int�ruption
Constantes : N/A
Fonctions : void InitTimer1(void) : initialise le Timer1 a une p�riode pr�d�finie
TIMER1InterruptServiceRoutine (void) : Fonction g�rant l'int�ruption du timer1
**************************************************************************************/
#include "../all_head.h"
int testtimeval=0;
unsigned int Frequence_IT=100;
void __attribute__ ((interrupt("IRQ"))) TIMER1InterruptServiceRoutine (void)
{
	routine_1ms();
    TIMER1_IR = 1 ; // Clears MR0 interrupt
    VICVectAddr = 0;
}
void InitTimer1(void)
{

    //------------------- Init TIMER 1 (see UM10114, chapter 15)
    //--- 1. Reset Counter 0 (Timer Control Register)
    // Bit 0 : 0 (Disables counting)
    // Bit 1 : 1 (Reset)
    TIMER1_TCR = 2 ;
    //--- 2. Set Prescaler
    //    If PCLK = 4 * 14.7456 MHz
    //    We want T = 0.1 ms (counter is incremented every 100 �s), so F = 10 kHz
    //    So: PRESCALER = PCLK / F - 1 = 5897
    TIMER1_PR = ((58982400) / (Frequence_IT*10)) - 1 ;//((58982400) / 10000)
    //--- 3. Set Match Register 0
    //    We want an interrupt every milli-second (1ms = 10 * 100 �s)
    TIMER1_MR0 = 10 - 1 ;
    //--- 4. Set Count control Register
    //    Bits 1-0: 00 (timer mode)
    //    Bits 3-2: XX (any value, because timer mode)
    TIMER1_CCR = 0 ;
    //--- 5. Match Control Register
    //    Bit 0: 1 (interrupt on MR0 match)
    //    Bit 1: 1 (reset on MR0 match)
    //    Bit 2: 0 (do not stop on MR0 match)
    //    Bit 5-3: 000 (MR1 not used)
    //    Bit 8-6: 000 (MR2 not used)
    //    Bit 11-9: 000 (MR3 not used)
    TIMER1_MCR = 3 ;
    //--- 6. Use vector 12 for TIMER1 interrupt
    VICVectAddr12 = (unsigned long) TIMER1InterruptServiceRoutine ;
    VICVectCntl12 = 0x20 | 5 ;

  /*-------------------------------------
   * BE CAREFUL :
   * 0x20 above is to enable the interrupt
   * and 5 is the 0x20 for the Timer1
   * interrrupt as you can see it again as
   * below
   * -------------------------------------*/

    //--- 7. Use IRQ for receiving characters
    //  TIMER1 gets interruption #5 (mask: 0x20)
    VICIntEnClr   = 0x20 ; // TimER1 interrupt generates IRQ
    VICIntEnable |= 0x20 ; // Enable TimER1 interrupt
    //--- 7. Start Counter 0 (Timer Control Register)
    // Bit 0 : 1 (Enables counting)
    // Bit 1 : 0 (no Reset)
    TIMER1_TCR = 1 ;

}
void set_frequence_IT(unsigned int frequence)
{
	TIMER1_TCR = 2 ;
	TIMER1_PR = ((58982400) / (Frequence_IT*10)) - 1 ;
	TIMER1_TCR = 1 ;
}
unsigned int get_grequence_IT()
{
	return Frequence_IT;
}
