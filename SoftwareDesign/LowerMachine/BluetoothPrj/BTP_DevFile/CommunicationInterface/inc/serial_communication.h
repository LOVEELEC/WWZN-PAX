/*
 * serial_communication.h
 *
 *  Created on: 2018Äê5ÔÂ25ÈÕ
 *      Author: LOVE_ELEC
 */

#ifndef STARTUP_SERIAL_COMMUNICATION_H_
#define STARTUP_SERIAL_COMMUNICATION_H_

void SerialCommunication_SendBleDisconnect(void);
void SerialCommunication_SendBleConnect(void);
void SerialCommunication_SendBleTransferCMP(void);
void SerialCommunication_Send(uint8_t * pbuf, uint16_t size);
void SerialCommunication_createTask(void);


#endif /* STARTUP_SERIAL_COMMUNICATION_H_ */
