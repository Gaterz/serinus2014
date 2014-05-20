/*
 * Msg_can.h
 *
 *  Created on: 17 mars 2014
 *      Author: Julien
 */

#ifndef MSG_CAN_H_

#define MSG_CAN_H_
extern canMsgType Message_R;
extern canMsgType Message_Pompes;
extern canMsgType Message_Ax_12;
extern canMsgType Message_Activat;

#define ID_MSG_CAN_SONARS 1 	//R
#define ID_MSG_CAN_POMPES 2		//T
#define ID_MSG_CAN_AX12_T 3		//T
#define ID_MSG_CAN_BUTTON 4		//R
#define ID_MSG_CAN_AX12_R 5		//R
#define ID_MSG_CAN_ACTIVATE 6	//T
#endif /* MSG_CAN_H_ */

