#ifndef MAIN_H_
#define MAIN_H_
void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));
void strrn (void);
#include "LPC22xx.h"
#include "all_head.h"
#endif /* MAIN_H_ */
