/**************************Interupt.c*********************************************
Auteur : Julien MAURAT
Date : 22 d�c. 2013
Description : Fonction pour activier et d�sactiver les interruption dans le stack acuel
Constantes : N/A
Fonctions : unsigned [enable/disable]IRQ(void) : active ou d�sactive les int�ruptions
**************************************************************************************/
#include "../all_head.h"
#define IRQ_MASK 0x00000080

static inline unsigned asm_get_cpsr(void)
{
  unsigned long retval;
  asm volatile (" mrs  %0, cpsr" : "=r" (retval) : /* no inputs */  );
  return retval;
}

static inline void asm_set_cpsr(unsigned val)
{
  asm volatile (" msr  cpsr, %0" : /* no outputs */ : "r" (val)  );
}

unsigned enableIRQ(void)
{
  unsigned _cpsr;

  _cpsr = asm_get_cpsr();
  asm_set_cpsr(_cpsr & ~IRQ_MASK);
  return _cpsr;
}

unsigned disableIRQ(void)
{
  unsigned _cpsr;

  _cpsr = asm_get_cpsr();
  asm_set_cpsr(_cpsr | IRQ_MASK);
  return _cpsr;
}

unsigned restoreIRQ(unsigned oldCPSR)
{
  unsigned _cpsr;

  _cpsr = asm_get_cpsr();
  asm_set_cpsr((_cpsr & ~IRQ_MASK) | (oldCPSR & IRQ_MASK));
  return _cpsr;
}
