/*
 * serial_communication.h
 *
 *  Created on: 2018Äê5ÔÂ25ÈÕ
 *      Author: LOVE_ELEC
 */

#ifndef STARTUP_SERIAL_COMMUNICATION_H_
#define STARTUP_SERIAL_COMMUNICATION_H_

/* Driver Header files */
#include <ti/drivers/UART.h>

#include "LL_loopQueue.h"


#define HID_IN_PACKET                   21
#define HID_OUT_PACKET                  21

typedef struct _BTP_DataMsg_Struct_Def{
    loopQueue WriteServiceBuffer;
    loopQueue NotifyServiceBuffer;
} BTP_DataMsg_Struct, *pBTP_DataMsg_Struct;


extern UART_Handle uart;
extern pBTP_DataMsg_Struct pBTP_DataMsg;

void SerialCommunication_createTask(void);


#endif /* STARTUP_SERIAL_COMMUNICATION_H_ */
