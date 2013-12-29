#ifndef TIMER_H_
#define TIMER_H_
void TIMER1InterruptServiceRoutine (void) __attribute__ ((interrupt("IRQ")));
void InitTimer1(void);

#endif /* TIMER_H_ */
