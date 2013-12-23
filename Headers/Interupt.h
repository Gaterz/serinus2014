#ifndef INTERUPT_H_
#define INTERUPT_H_

unsigned enableIRQ(void);
unsigned disableIRQ(void);
unsigned restoreIRQ(unsigned oldCPSR);
#endif /* INTERUPT_H_ */
