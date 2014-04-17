/*
 * Debug_Bridge.h
 *
 *  Created on: 16 avr. 2014
 *      Author: Julien
 */

#ifndef DEBUG_BRIDGE_H_
#define DEBUG_BRIDGE_H_
#define TYPE_INT 0
#define TYPE_UINT 1
#define TYPE_LONG 2
#define TYPE_ULONG 3
#define TYPE_DOUBLE 4
void routine_DebugBridge();
void addDebug(void* varAdr, unsigned char varType);
#endif /* DEBUG_BRIDGE_H_ */
