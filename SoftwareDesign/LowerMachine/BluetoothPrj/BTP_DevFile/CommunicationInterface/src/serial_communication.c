/*
 * serial_communication.c
 *
 *  Created on: 2018Äê5ÔÂ24ÈÕ
 *      Author: LOVE_ELEC
 */

/*********************************************************************
 * INCLUDES
 */
#include <string.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Queue.h>

/* Driver Header files */
#include <ti/drivers/UART.h>

#include "board.h"
#include "serial_communication.h"
#include "simple_gatt_profile.h"

#include "crc16.h"
/*********************************************************************
 * CONSTANTS
 */
// Task configuration
#define COM_TASK_PRIORITY                     1
#define COM_TASK_STACK_SIZE                   644

#define HID_IN_PACKET                   21
#define HID_OUT_PACKET                  21
/*********************************************************************
 * LOCAL VARIABLES
 */
// Task configuration
Task_Struct comTask;
Char comTaskStack[COM_TASK_STACK_SIZE];
//static UART_Handle uart;
/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void SerialCommunication_init(void);
static void SerialCommunication_taskFxn(UArg a0, UArg a1);

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      SerialCommunication_createTask
 *
 * @brief   Task creation function for the serial communication.
 *
 * @param   None.
 *
 * @return  None.
 */
void SerialCommunication_createTask(void)
{
    Task_Params taskParams;

    // Configure task
    Task_Params_init(&taskParams);
    taskParams.stack = comTaskStack;
    taskParams.stackSize = COM_TASK_STACK_SIZE;
    taskParams.priority = COM_TASK_PRIORITY;

    Task_construct(&comTask, SerialCommunication_taskFxn, &taskParams, NULL);
}

/*********************************************************************
 * @fn      SerialCommunication_init
 *
 * @brief
 *
 * @param   None.
 *
 * @return  None.
 */
static void SerialCommunication_init(void)
{
//    UART_Params uartParams;
//
//    /* Call driver init functions */
//    UART_init();
//
//    /* Create a UART with data processing off. */
//    UART_Params_init(&uartParams);
//    uartParams.writeDataMode = UART_DATA_BINARY;
//    uartParams.readDataMode = UART_DATA_BINARY;
//    uartParams.readReturnMode = UART_RETURN_FULL;
//    uartParams.readEcho = UART_ECHO_OFF;
//    uartParams.baudRate = 115200;
//
//    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }
}
void SerialCommunication_SendBleDisconnect(void)
{
    uint8_t DisConMesg[HID_IN_PACKET];
    memset(DisConMesg, 0x00, HID_IN_PACKET);
    DisConMesg[0] = 0x02;
    DisConMesg[1] = 0x58;

    *(width_t *)(&DisConMesg[DisConMesg[2]+4]) = crcCompute(DisConMesg, (DisConMesg[2] + 4));
    UART_write(uart, DisConMesg, HID_IN_PACKET);
}

void SerialCommunication_SendBleConnect(void)
{
    uint8_t ConMesg[HID_IN_PACKET];
    memset(ConMesg, 0x00, HID_IN_PACKET);
    ConMesg[0] = 0x02;
    ConMesg[1] = 0x57;

    *(width_t *)(&ConMesg[ConMesg[2]+4]) = crcCompute(ConMesg, (ConMesg[2]+4));
    UART_write(uart, ConMesg, HID_IN_PACKET);
}


void SerialCommunication_SendBleTransferCMP(void)
{
    uint8_t ConMesg[HID_IN_PACKET];
    memset(ConMesg, 0x00, HID_IN_PACKET);
    ConMesg[0] = 0x02;
    ConMesg[1] = 0x59;

    *(width_t *)(&ConMesg[ConMesg[2]+4]) = crcCompute(ConMesg, (ConMesg[2]+4));
    UART_write(uart, ConMesg, HID_IN_PACKET);
}

void SerialCommunication_Send(uint8_t * pbuf, uint16_t size)
{
    UART_write(uart, pbuf, size);
}
/*********************************************************************
 * @fn      SimpleBLEPeripheral_taskFxn
 *
 * @brief   Application task entry point for the Simple Peripheral.
 *
 * @param   a0, a1 - not used.
 *
 * @return  None.
 */
//static uint8 readDataLen = 0;
static void SerialCommunication_taskFxn(UArg a0, UArg a1)
{
    char ret = 0;
    uint8_t readData = 0;
    // Initialize application
    SerialCommunication_init();

    // Application main loop
    for (;;)
    {
        /* Read data from UART */
        ret = UART_read(uart, &readData, 1);
        if (ret > 0){
            if (piLoopQueue->EnQueue(&BTP_DataMsg.NotifyServiceBuffer, &readData, 1) < 1){
                /* Buffer is Full */
            }
        }
    }
}
/*********************************************************************
*********************************************************************/
