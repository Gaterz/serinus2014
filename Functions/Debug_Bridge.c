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
	addToSend(addDebug(&Asserv_Cons_distance, TYPE_LONG));
	addToSend(addDebug(&Asserv_dst_act, TYPE_LONG));
	addToSend(addDebug(&Odo_angle, TYPE_DOUBLE));
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
unsigned char RX_buffer[10];
void addToRXBuffer(unsigned char c)
{
	int i;
	for(i=10;i>0;i--)
	{
		RX_buffer[i]=RX_buffer[i-1];
	}
	RX_buffer[0]=c;
	if(RX_buffer[0]==0x5A && RX_buffer[1]==0x6B)
	{
		RX_routine();
	}

}
void RX_routine()
{
unsigned char type= RX_buffer[2];
unsigned char id=RX_buffer[3];
switch(type)
{
case TYPE_INT :
	*(int*)debugList[id]=RX_buffer[4]<<8;
	*(int*)debugList[id]+=RX_buffer[5];
			break;
case TYPE_UINT :
	*(unsigned int*)debugList[id]=RX_buffer[4]<<8;
	*(unsigned int*)debugList[id]+=RX_buffer[5];
			break;
case TYPE_LONG :
	*(long*)debugList[id]=RX_buffer[4]<<24;
	*(long*)debugList[id]+=RX_buffer[5]<<16;
	*(long*)debugList[id]+=RX_buffer[6]<<8;
	*(long*)debugList[id]+=RX_buffer[7];
			break;
case TYPE_ULONG :
	*(unsigned long*)debugList[id]=RX_buffer[4]<<24;
	*(unsigned long*)debugList[id]+=RX_buffer[5]<<16;
	*(unsigned long*)debugList[id]+=RX_buffer[6]<<8;
	*(unsigned long*)debugList[id]+=RX_buffer[7];
			break;
case TYPE_DOUBLE :
	tmp.data[0]=RX_buffer[4];
	tmp.data[1]=RX_buffer[5];
	tmp.data[2]=RX_buffer[6];
	tmp.data[3]=RX_buffer[7];
	*(double*)debugList[id]=tmp.f;
		break;
}
}
