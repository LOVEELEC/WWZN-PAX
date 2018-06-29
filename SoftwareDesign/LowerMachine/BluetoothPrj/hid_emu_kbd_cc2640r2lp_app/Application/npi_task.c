//******************************************************************************
//! \file           npi_task.c
//! \brief          NPI is a TI RTOS Application Thread that provides a
//! \brief          common Network Processor Interface framework.
//
//   Revised        $Date: 2015-02-15 11:57:15 -0800 (Sun, 15 Feb 2015) $
//   Revision:      $Revision: 42612 $
//
//  Copyright 2015 Texas Instruments Incorporated. All rights reserved.
//
// IMPORTANT: Your use of this Software is limited to those specific rights
// granted under the terms of a software license agreement between the user
// who downloaded the software, his/her employer (which must be your employer)
// and Texas Instruments Incorporated (the "License").  You may not use this
// Software unless you agree to abide by the terms of the License. The License
// limits your use, and you acknowledge, that the Software may not be modified,
// copied or distributed unless used solely and exclusively in conjunction with
// a Texas Instruments radio frequency device, which is integrated into
// your product.  Other than for the foregoing purpose, you may not use,
// reproduce, copy, prepare derivative works of, modify, distribute, perform,
// display or sell this Software and/or its documentation for any purpose.
//
//  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
//  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,l
//  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
//  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
//  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
//  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
//  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
//  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
//  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
//  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
//  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
//
//  Should you have any questions regarding your right to use this Software,
//  contact Texas Instruments Incorporated at www.TI.com.
//******************************************************************************

// ****************************************************************************
// includes
// ****************************************************************************

#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#include <string.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>

#include "npi_task.h"
#include "inc/npi_data.h"
#include "inc/npi_rxbuf.h"
#include "inc/npi_tl.h"
#include "hidemukbd.h"
#include "crc16.h"
// ****************************************************************************
// defines
// ****************************************************************************

//! \brief Transport layer RX Event (ie. bytes received, RX ISR etc.)
#define NPITASK_TRANSPORT_RX_EVENT 0x0002

//! \brief Transmit Complete Event (likely associated with TX ISR etc.)
#define NPITASK_TRANSPORT_TX_DONE_EVENT 0x0004

//! \brief ASYNC Message Recieved Event (no framing bytes)
#define NPITASK_FRAME_RX_EVENT 0x0008

//! \brief A framed message buffer is ready to be sent to the transport layer.
#define NPITASK_TX_READY_EVENT 0x0010

//! \brief MRDY Received Event
#define NPITASK_MRDY_EVENT 0x0080

//! \brief Size of stack created for NPI RTOS task
#define NPITASK_STACK_SIZE 512

//! \brief Task priority for NPI RTOS task
#define NPITASK_PRIORITY 1


#if defined (NPI_USE_UART) || defined (NPI_USE_SPI)
//events that TL will use to control the driver
#define MRDY_EVENT                            0x0010
#define TRANSPORT_RX_EVENT                    0x0020
#define TRANSPORT_TX_DONE_EVENT               0x0040

#define APP_TL_BUFF_SIZE                      150
//used to store data read from transport layer
static uint8_t appRxBuf[APP_TL_BUFF_SIZE];
#endif //TL


// ****************************************************************************
// typedefs
// ****************************************************************************

//! \brief Queue record structure
//!
typedef struct NPI_QueueRec_t 
{
    Queue_Elem _elem;
    NPIMSG_msg_t *npiMsg;
} NPI_QueueRec;


//*****************************************************************************
// globals
//*****************************************************************************

uint8 buf[NPI_TL_BUF_SIZE] ={0x00,};
uint16 length;
                
//! \brief ICall ID for stack which will be sending NPI messages
//!
//static uint32_t stackServiceID = 0x0000;

//! \brief RTOS task structure for NPI task
//!
static Task_Struct npiTaskStruct;

//! \brief Allocated memory block for NPI task's stack
//!
Char npiTaskStack[NPITASK_STACK_SIZE];

//! \brief Handle for the ASYNC TX Queue
//!
static Queue_Handle npiTxQueue;

//! \brief Handle for the ASYNC RX Queue
//!
static Queue_Handle npiRxQueue;


//! \brief Pointer to last tx message.  This is free'd once confirmation is
//!        is received that the buffer has been transmitted
//!        (ie. NPITASK_TRANSPORT_TX_DONE_EVENT)
//!
static uint8_t *lastQueuedTxMsg;

//! \brief NPI thread ICall Semaphore.
//!
//ICall_Semaphore appSem = NULL; //ZH
Semaphore_Handle appSem = NULL;

Semaphore_Params  semParams ; 
Semaphore_Struct structSem; /* Memory allocated at build time */


//! \brief NPI ICall Application Entity ID.
//!
ICall_EntityID npiAppEntityID = 0;

//! \brief Task pending events
//!
static uint16_t NPITask_events = 0;

//! \brief Event flags for capturing Task-related events from ISR context
//!
static uint16_t TX_DONE_ISR_EVENT_FLAG = 0;
static uint16_t MRDY_ISR_EVENT_FLAG = 0;
static uint16_t TRANSPORT_RX_ISR_EVENT_FLAG = 0;

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief      NPI main event processing loop.
//!
static void NPITask_process(void);

//! \brief Callback function registered with Transport Layer
//!
static void NPITask_transportRXCallBack(int size);

//! \brief Callback function registered with Transport Layer
//!
static void NPITask_transportTxDoneCallBack(int size);

//! \brief Callback function registered with Transport Layer
//!
static void NPITask_MRDYEventCB(int size);

//! \brief ASYNC TX Q Processing function.
//!
static void NPITask_ProcessTXQ(void);

//! \brief ASYNC RX Q Processing function.
//!
static void NPITask_processRXQ(void);


#define HID_IN_PACKET                   21
#define HID_OUT_PACKET                  21
static void SerialCommunication_SendBleDisconnect(void);
static void SerialCommunication_SendBleConnect(void);
static void SerialCommunication_SendBleTransferCMP(void);
static void SerialCommunication_Send(uint8_t * pbuf, uint16_t size);
static iSerialTransferStruct iSerialTransfer = {
    HidEmuKbd_SendMsgtoBLERF,
    SerialCommunication_Send,
    SerialCommunication_SendBleDisconnect,
    SerialCommunication_SendBleConnect,
    SerialCommunication_SendBleTransferCMP,
};


piSerialTransferStruct piSerialTransfer = &iSerialTransfer;

static void SerialCommunication_SendBleDisconnect(void)
{
    uint8_t DisConMesg[HID_IN_PACKET];
    memset(DisConMesg, 0x00, HID_IN_PACKET);
    DisConMesg[0] = 0x02;
    DisConMesg[1] = 0x58;

    *(width_t *)(&DisConMesg[DisConMesg[2]+4]) = crcCompute(DisConMesg, (DisConMesg[2] + 4));
    NPITask_sendToHost(DisConMesg, HID_IN_PACKET);
}

static void SerialCommunication_SendBleConnect(void)
{
    uint8_t ConMesg[HID_IN_PACKET];
    memset(ConMesg, 0x00, HID_IN_PACKET);
    ConMesg[0] = 0x02;
    ConMesg[1] = 0x57;

    *(width_t *)(&ConMesg[ConMesg[2]+4]) = crcCompute(ConMesg, (ConMesg[2]+4));
    NPITask_sendToHost(ConMesg, HID_IN_PACKET);
}


static void SerialCommunication_SendBleTransferCMP(void)
{
    uint8_t CmpMesg[HID_IN_PACKET];
    memset(CmpMesg, 0x00, HID_IN_PACKET);
    CmpMesg[0] = 0x02;
    CmpMesg[1] = 0x59;

    *(width_t *)(&CmpMesg[CmpMesg[2]+4]) = crcCompute(CmpMesg, (CmpMesg[2]+4));
    NPITask_sendToHost(CmpMesg, HID_IN_PACKET);
}

static void SerialCommunication_Send(uint8_t * pbuf, uint16_t size)
{
    NPITask_sendToHost(pbuf, size);
}
// -----------------------------------------------------------------------------
//! \brief      Initialization for the NPI Thread
//!
//! \return     void
// -----------------------------------------------------------------------------
static void NPITask_inititializeTask(void)
{

    NPITask_events = 0;

    lastQueuedTxMsg = NULL;

    // create a Tx Queue instance
    npiTxQueue = Queue_create(NULL, NULL);
    // create an Rx Queue instance
    npiRxQueue = Queue_create(NULL, NULL);

    Semaphore_Params_init(&semParams);
	Semaphore_construct(&structSem, 0, &semParams);
	/* It's optional to store the handle */
	appSem = Semaphore_handle(&structSem);

	// Initialize Network Processor Interface (NPI) and Transport Layer
    NPITL_initTL( &NPITask_transportTxDoneCallBack,
                  &NPITask_transportRXCallBack,
                  &NPITask_MRDYEventCB );

}


// -----------------------------------------------------------------------------
//! \brief      NPI main event processing loop.
//!
//! \return     void
// -----------------------------------------------------------------------------
static void NPITask_process(void)
{ 
//    unsigned char hello[] = "Hello World.\n";
//    NPITask_sendToHost(hello, sizeof(hello));
    
    /* Forever loop */
    for (;; )
    {
        /* Wait for response message */
        if (Semaphore_pend(appSem, BIOS_WAIT_FOREVER))
        {
            // Capture the ISR events flags now within a critical section.  
            // We do this to avoid possible race conditions where the ISR is 
            // modifying the event mask while the task is read/writing it.
            UInt hwiKey = Hwi_disable(); UInt taskKey = Task_disable();
            
            NPITask_events = NPITask_events | TX_DONE_ISR_EVENT_FLAG | 
                             MRDY_ISR_EVENT_FLAG | TRANSPORT_RX_ISR_EVENT_FLAG;
            
            TX_DONE_ISR_EVENT_FLAG = 0;
            MRDY_ISR_EVENT_FLAG = 0;
            TRANSPORT_RX_ISR_EVENT_FLAG = 0;
            
            Task_restore(taskKey); Hwi_restore(hwiKey);

            // MRDY event
            if (NPITask_events & NPITASK_MRDY_EVENT)
            {
                NPITask_events &= ~NPITASK_MRDY_EVENT;
#ifdef POWER_SAVING
                NPITL_handleMrdyEvent();
#endif //POWER_SAVING

            }

            // An ASYNC message is ready to send to the Host
            if(NPITask_events & NPITASK_TX_READY_EVENT)
            {

                    if ((!Queue_empty(npiTxQueue)) && !NPITL_checkNpiBusy())
                    {
                        NPITask_ProcessTXQ();
                    }
  
                if (Queue_empty(npiTxQueue))
                {
                    // Q is empty, it's safe to clear the event flag.
 
                    NPITask_events &= ~NPITASK_TX_READY_EVENT;
                }
                else
                {
                    // Q is not empty, there's more to handle so preserve the
                    // flag and repost to the task semaphore.
                    Semaphore_post(appSem);
                }
            }

            // The Transport Layer has received some bytes
            if(NPITask_events & NPITASK_TRANSPORT_RX_EVENT)
            {
                length = NPIRxBuf_GetRxBufCount();
                
                //Do custom app processing
                NPIRxBuf_ReadFromRxBuf(buf, length);

                /* Send Data to HidEmuKbd_enqueueMsg */
                piSerialTransfer->SendMsgtoBLERF(buf,length);
//                //Echo back via UART
//                NPITask_sendToHost(buf, length);

                if (NPIRxBuf_GetRxBufCount() == 0)
                {
                    // No additional bytes to collect, clear the flag.

                    NPITask_events &= ~NPITASK_TRANSPORT_RX_EVENT;
                }
                else
                {
                    // Additional bytes to collect, preserve the flag and repost
                    // to the semaphore
                    Semaphore_post(appSem);
                }
            }

            // The last transmission to the host has completed.
            if(NPITask_events & NPITASK_TRANSPORT_TX_DONE_EVENT)
            {
                // Current TX is done.
                
                NPITask_events &= ~NPITASK_TRANSPORT_TX_DONE_EVENT;

                    if (!Queue_empty(npiTxQueue))
                    {
                        // There are pending ASYNC messages waiting to be sent
                        // to the host. Set the appropriate flag and post to
                        // the semaphore.
                        NPITask_events |= NPITASK_TX_READY_EVENT;
                        Semaphore_post(appSem);
                    }
            }
        }
    }
}

// -----------------------------------------------------------------------------
//! \brief      NPI Task function called from within NPITask_Fxn
//!
//! \return     void
// -----------------------------------------------------------------------------
void NPITask_task(void)
{
    // Initialize application
    NPITask_inititializeTask();

    // No return from TestProfile2 process
    NPITask_process();
}


// -----------------------------------------------------------------------------
// Exported Functions


// -----------------------------------------------------------------------------
//! \brief      NPI task entry point.
//!
//! \return     void
// -----------------------------------------------------------------------------
Void NPITask_Fxn(UArg a0, UArg a1)
{
    NPITask_task();
}

// -----------------------------------------------------------------------------
//! \brief      Task creation function for NPI
//!
//! \return     void
// -----------------------------------------------------------------------------
void NPITask_createTask(uint32_t stackID)
{
    memset(&npiTaskStack, 0xDD, sizeof(npiTaskStack));

    // Configure and create the NPI task.
    Task_Params npiTaskParams;
    Task_Params_init(&npiTaskParams);
    npiTaskParams.stack = npiTaskStack;
    npiTaskParams.stackSize = NPITASK_STACK_SIZE;
    npiTaskParams.priority = NPITASK_PRIORITY;

    Task_construct(&npiTaskStruct, NPITask_Fxn, &npiTaskParams, NULL);
}

// -----------------------------------------------------------------------------
//! \brief      API for application task to send a message to the Host.
//!             NOTE: It's assumed all message traffic to the stack will use
//!             other (ICALL) APIs/Interfaces.
//!
//! \param[in]  pMsg    Pointer to "unframed" message buffer.
//!
//! \return     void
// -----------------------------------------------------------------------------
void NPITask_sendToHost(uint8_t *pMsg, uint16 length)
{
    NPI_QueueRec *recPtr;

    NPIMSG_msg_t *pNPIMsg =(NPIMSG_msg_t *)ICall_malloc( sizeof(NPIMSG_msg_t));
    
    if(pNPIMsg)
    {
      pNPIMsg->msgType = NPIMSG_Type_ASYNC;
      pNPIMsg->pBuf = (uint8 *)ICall_allocMsg(length);
      pNPIMsg->pBufSize = length;
        
      if(pNPIMsg->pBuf)
      {
          // Payload
          memcpy(pNPIMsg->pBuf, pMsg, length);
      }
      
      recPtr = ICall_malloc(sizeof(NPI_QueueRec));

      recPtr->npiMsg = pNPIMsg;
    }
    
    switch (pNPIMsg->msgType)
    {
        case NPIMSG_Type_ASYNC:
        {
            Queue_enqueue(npiTxQueue, &recPtr->_elem);
            NPITask_events |= NPITASK_TX_READY_EVENT;
            Semaphore_post(appSem);
            break;
        }
        default:
        {
            //error
            break;
        }
    }
}


// -----------------------------------------------------------------------------
//! \brief      Dequeue next message in the ASYNC TX Queue and send to serial
//!             interface.
//!
//! \return     void
// -----------------------------------------------------------------------------
static void NPITask_ProcessTXQ(void)
{

    NPI_QueueRec *recPtr = NULL;

    recPtr = Queue_dequeue(npiTxQueue);

    if (recPtr != NULL)
    {
		lastQueuedTxMsg = recPtr->npiMsg->pBuf;

		NPITL_writeTL(recPtr->npiMsg->pBuf, recPtr->npiMsg->pBufSize);

		//free the Queue record
		ICall_free(recPtr->npiMsg);
		ICall_free(recPtr);
	}

}

// -----------------------------------------------------------------------------
// Call Back Functions

// -----------------------------------------------------------------------------
//! \brief      Call back function for TX Done event from transport layer.
//!
//! \param[in]  size    Number of bytes transmitted.
//!
//! \return     void
// -----------------------------------------------------------------------------
static void NPITask_transportTxDoneCallBack(int size)
{
    
    if(lastQueuedTxMsg)
    {
        //Deallocate most recent message being transmitted.
        ICall_freeMsg(lastQueuedTxMsg);

        lastQueuedTxMsg = NULL;
    }

    // Post the event to the NPI task thread.
    TX_DONE_ISR_EVENT_FLAG = NPITASK_TRANSPORT_TX_DONE_EVENT;
    Semaphore_post(appSem);
}

// -----------------------------------------------------------------------------
//! \brief      RX Callback provided to Transport Layer for RX Event (ie.Bytes
//!             received).
//!
//! \param[in]  size    Number of bytes received.
//!
//! \return     void
// -----------------------------------------------------------------------------
static void NPITask_transportRXCallBack(int size)
{
    NPIRxBuf_Read(size);
    TRANSPORT_RX_ISR_EVENT_FLAG = NPITASK_TRANSPORT_RX_EVENT;
    Semaphore_post(appSem);
}

// -----------------------------------------------------------------------------
//! \brief      RX Callback provided to Transport Layer for MRDY Event
//!
//! \param[in]  size    N/A
//!
//! \return     void
// -----------------------------------------------------------------------------
static void NPITask_MRDYEventCB(int size)
{
    MRDY_ISR_EVENT_FLAG = NPITASK_MRDY_EVENT;
    Semaphore_post(appSem);
}

