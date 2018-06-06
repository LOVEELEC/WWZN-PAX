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
#include <icall.h>

#include "board.h"
#include "serial_communication.h"
#include "util.h"

#include "hiddev.h"
#include "hidkbdservice.h"
/*********************************************************************
 * CONSTANTS
 */
// Task configuration
#define COM_TASK_PRIORITY                     2
#define COM_TASK_STACK_SIZE                   644

// App event passed from profiles.
typedef struct
{
  appEvtHdr_t hdr; // Event header
} hidBtpEvt_t;


/*********************************************************************
 * LOCAL VARIABLES
 */
// Task configuration
Task_Struct comTask;
Char comTaskStack[COM_TASK_STACK_SIZE];

UART_Handle uart;
BTP_DataMsg_Struct BTP_DataMsg;
pBTP_DataMsg_Struct pBTP_DataMsg = &BTP_DataMsg;

extern Queue_Handle appMsgQueue;
extern ICall_SyncHandle syncEvent;
/*********************************************************************
 * LOCAL FUNCTIONS
 */
//static void SerialCommunication_init(void);
static void SerialCommunication_taskFxn(UArg a0, UArg a1);

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

static void SimpleBLEPeripheral_ServiceBufferInit(void)
{
    piLoopQueue->InitQueue(&BTP_DataMsg.WriteServiceBuffer,sizeof(BTP_DataMsg.WriteServiceBuffer.dataBuf));
    piLoopQueue->InitQueue(&BTP_DataMsg.NotifyServiceBuffer,sizeof(BTP_DataMsg.WriteServiceBuffer.dataBuf));
}

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
void SerialCommunication_init(void)
{
    UART_Params uartParams;

    SimpleBLEPeripheral_ServiceBufferInit();

    /* Call driver init functions */
    UART_init();

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 1000000;

    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }
}

void SerialCommunication_Send(uint8_t * pbuf, uint16_t size)
{
//    uint16_t realLen = BTP_DataMsg.WriteServiceBuffer.DataBufMaxSize - piLoopQueue->QueueLength(&BTP_DataMsg.WriteServiceBuffer);
//    if (realLen >= size){
//        if (piLoopQueue->EnQueue(&BTP_DataMsg.WriteServiceBuffer, readData, size) ==  size){
//            /* Enqueue the message */
////            UART_write(uart, readData, HID_IN_PACKET);
//        }
//    }else{
//        /* Buffer is Full */
//
//    }
    UART_write(uart, pbuf, size);
}
/*********************************************************************
 * @fn      HidEmuKbd_enqueueMsg
 *
 * @brief   Creates a message and puts the message in RTOS queue.
 *
 * @param   event  - message event.
 * @param   state  - message state.
 *#define HIDEMUKBD_KEY_CHANGE_EVT              0x0001
 * @return  TRUE or FALSE
 */
static uint8_t HidBTP_enqueueMsg(void)
{
    hidBtpEvt_t *pMsg;

  // Create dynamic pointer to message.
  if (pMsg = ICall_malloc(sizeof(hidBtpEvt_t)))
  {
    pMsg->hdr.event = 0x0001;
    pMsg->hdr.state = 0x50;

    // Enqueue the message.
    return Util_enqueueMsg(appMsgQueue, syncEvent, (uint8_t *)pMsg);
  }

  return FALSE;
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
    uint16_t realLen = 0x00;
    uint8_t readData[HID_IN_PACKET] = {0};
    // Initialize application
    SerialCommunication_init();
//    if (uart == NULL) {
//        /* UART_open() failed */
//        while (1);
//    }

    // Application main loop
    for (;;)
    {
        /* Read data from UART */
        ret = UART_read(uart, readData, HID_IN_PACKET);
        if (ret == HID_IN_PACKET){
            realLen = BTP_DataMsg.NotifyServiceBuffer.DataBufMaxSize - piLoopQueue->QueueLength(&BTP_DataMsg.NotifyServiceBuffer);
            if (realLen >= HID_IN_PACKET){
                if (piLoopQueue->EnQueue(&BTP_DataMsg.NotifyServiceBuffer, readData, HID_IN_PACKET) ==  HID_IN_PACKET){
                    /* Enqueue the message */
//                    UART_write(uart, readData, HID_IN_PACKET);
                    HidBTP_enqueueMsg();
                }
            }else{
                /* Buffer is Full */

            }
        }
    }
}
/*********************************************************************
*********************************************************************/
