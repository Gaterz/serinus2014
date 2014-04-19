/**************************Debug_Bridge.c*********************************************
Auteur : Julien MAURAT
Date : 16 avr. 2014
Description : 
Constantes :
Fonctions :
**************************************************************************************/
#include "../all_head.h"
union ufloat {
  float f;
  char data[sizeof(float)];
}tmp;
void* debugList[100];
unsigned char debugType[100];
unsigned char ToSend[100];
unsigned char Ndebug=0;
unsigned char NtoSend=0;
void init_DebugBridge()
{
	int i;
	for(i=0;i<100;i++)
	{
		ToSend[i]=0;
	}
	addToSend(addDebug(&Odo_pos_x, TYPE_LONG));
	addToSend(addDebug(&Odo_pos_y, TYPE_LONG));
}
void routine_DebugBridge()
{
	int i;
	UART0_Sendchar_u(0x5A);
	UART0_Sendchar_u(0xB6);
	UART0_Sendchar_u(0x7C);
	UART0_Sendchar_u(0xD8);
	UART0_Sendchar_u(NtoSend);
	for(i=0;i<Ndebug;i++)
	{
		if(ToSend[i]==1)
		{
			UART0_Sendchar_u(i);
			UART0_Sendchar_u(debugType[i]);
			switch(debugType[i])
			{
			case TYPE_INT :
				UART0_Sendchar_u(*(int*)debugList[i]>>8);
				UART0_Sendchar_u(*(int*)debugList[i]&0xFF);
						break;
			case TYPE_UINT :
				UART0_Sendchar_u(*(unsigned int*)debugList[i]>>8);
				UART0_Sendchar_u(*(unsigned int*)debugList[i]&0xFF);
						break;
			case TYPE_LONG :
				UART0_Sendchar_u((*(long*)debugList[i]>>24)&0xFF);
				UART0_Sendchar_u((*(long*)debugList[i]>>16)&0xFF);
				UART0_Sendchar_u((*(long*)debugList[i]>>8)&0xFF);
				UART0_Sendchar_u(*(long*)debugList[i]&0xFF);
						break;
			case TYPE_ULONG :
				UART0_Sendchar_u((*(unsigned long*)debugList[i]>>24)&0xFF);
				UART0_Sendchar_u((*(unsigned long*)debugList[i]>>16)&0xFF);
				UART0_Sendchar_u((*(unsigned long*)debugList[i]>>8)&0xFF);
				UART0_Sendchar_u(*(unsigned long*)debugList[i]&0xFF);
						break;
			case TYPE_DOUBLE :
				tmp.f=(float)(*(double*)debugList[i]);
				UART0_Sendchar_u(tmp.data[0]);
				UART0_Sendchar_u(tmp.data[1]);
				UART0_Sendchar_u(tmp.data[2]);
				UART0_Sendchar_u(tmp.data[3]);
						break;
			}
		}

	}
}
void removeToSend(unsigned char id)
{
	ToSend[id]=0;
	NtoSend--;
}
void addToSend(unsigned char id)
{
	ToSend[id]=1;
	NtoSend++;
}
unsigned char addDebug(void* varAdr, unsigned char varType)
{
	debugList[Ndebug]=varAdr;
	debugType[Ndebug]=varType;
	//ToSend[Ndebug]=1;
	Ndebug++;
	return Ndebug-1;

}
