#include "all_head.h"
void init_UART0(void)
{
	PINSEL0 |= 0x00000005;
	//UART0_LCR|=0x80;//Enable latch
	UART0_FCR=0b00000111;
	UART0_LCR=0b10000011;//Enable latch
	UART0_DLL=96;
	UART0_DLM=0;
	//Enable FIFO
	UART0_LCR=0b00000011;//8-bit no control 1 stop
	//UART0_LCR&=0b01111111;//clear latch
	UART0_THR='E';
}
