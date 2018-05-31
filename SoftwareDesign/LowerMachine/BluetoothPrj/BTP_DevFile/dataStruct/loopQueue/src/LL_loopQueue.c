/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : LL_loopQueue.c
 * Author               : Megahuntmicro
 * Version              : V1.0.0
 * Date                 : 15-March-2016
 * Description          : This file is used to define the loop queue data structure 
 *                        and the processing interface.
 *****************************************************************************/
 
/* Include ------------------------------------------------------------------*/
#include "LL_loopQueue.h"
#include "string.h"
/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/	
/* Private macro ------------------------------------------------------------*/	
/* Private variables --------------------------------------------------------*/	
/* Ptivate function prototypes ----------------------------------------------*/	
#ifndef USE_MALLOC_DEFINE_BUF_SIZE
static bool InitQueue(ploopQueue pploopQueue, uint32_t dataLen);
static bool DestroyQueue(ploopQueue ploopQueue);   
#else
static uint32_t InitQueue(loopQueue **pploopQueue, uint32_t dataLen);
static bool DestroyQueue(ploopQueue *ploopQueue);   
#endif 
static bool ClearQueue(ploopQueue ploopQueue);       
static bool QueueEmpty(ploopQueue ploopQueue);     
static uint32_t EnQueue(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len);
static uint32_t DeQueue(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len);
static uint32_t QueueLength(ploopQueue ploopQueue); 

static iLoopQueueStruct iLoopQueue = {
    InitQueue,
    DestroyQueue,
    ClearQueue,
    QueueEmpty,
    EnQueue,
    DeQueue,
    QueueLength
};
piLoopQueueStruct piLoopQueue = &iLoopQueue;
/*******************************************************************************
* Function Name	: 
* Description	: 
* Input			: 
* Output		: 
* Return		: 
*******************************************************************************/
#ifndef USE_MALLOC_DEFINE_BUF_SIZE
static bool InitQueue(ploopQueue pploopQueue, uint32_t dataLen)
{
    memset(pploopQueue,0x00,sizeof(loopQueue));
    pploopQueue->DataBufMaxSize = sizeof(pploopQueue->dataBuf);
    pploopQueue->pdataBuf = pploopQueue->dataBuf;
    return (true);
}  

static bool DestroyQueue(ploopQueue ploopQueue)
{
    return (true);
}
#else
static uint32_t InitQueue(loopQueue **pploopQueue, uint32_t dataLen)
{
    *pploopQueue = (loopQueue *)malloc(sizeof(loopQueue));
    if (pploopQueue == NULL)
    {
        return (0);
    }
    memset(*pploopQueue,0x00,sizeof(loopQueue));
    (*pploopQueue)->pdataBuf = (LoopDataWidth *)malloc(dataLen * sizeof(LoopDataWidth));
    if ((*pploopQueue)->pdataBuf == NULL)
    {   
        return (0);
    }
    (*pploopQueue)->DataBufMaxSize = dataLen;
    return (dataLen);
}

static bool DestroyQueue(ploopQueue *ploopQueue)
{
    free(ploopQueue);
    if (*ploopQueue == NULL)
    {
        return (true);
    }
    return (false);
}  
#endif
    
static bool ClearQueue(ploopQueue ploopQueue)
{
    ploopQueue->dataPtrIn = 0x00;
    ploopQueue->dataPtrOut = 0x00;
    memset(ploopQueue->pdataBuf,0x00,ploopQueue->DataBufMaxSize);
    return (true);
}    

static bool QueueEmpty(ploopQueue ploopQueue)
{
    if ((ploopQueue->dataPtrIn + 1) % ploopQueue->DataBufMaxSize \
                 == ploopQueue->dataPtrOut)
    {
        return (false);
    }
    return (true);
}   

static uint32_t EnQueue(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len)
{
    uint32_t ret = 0x00;
    LoopDataWidth *pdataBuf = pbuf;
    if (ploopQueue != NULL)
    {
        uint32_t datalen = len;
        while (datalen--)
        {
            if ((ploopQueue->dataPtrIn + 1) % ploopQueue->DataBufMaxSize \
                 == ploopQueue->dataPtrOut)
            {
                return (ret);
            }
            ploopQueue->pdataBuf[ploopQueue->dataPtrIn] = *pdataBuf++;
            ploopQueue->dataPtrIn = (ploopQueue->dataPtrIn + 1) % ploopQueue->DataBufMaxSize;
            ret++;
        }
    }
    return (ret);
}

static uint32_t DeQueue(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len)
{
    uint32_t ret = 0x00;
    LoopDataWidth *pdataBuf = pbuf;
    if (ploopQueue != NULL)
    {
        uint32_t datalen = len;
        while (datalen--)
        {
            if (ploopQueue->dataPtrOut == ploopQueue->dataPtrIn)
            {
                return (ret);
            }
            *pdataBuf++ = ploopQueue->pdataBuf[ploopQueue->dataPtrOut];
            ploopQueue->dataPtrOut = (ploopQueue->dataPtrOut + 1) % ploopQueue->DataBufMaxSize;
            ret++;
        }
    }
    return (ret);
}    

static uint32_t QueueLength(ploopQueue ploopQueue)
{
    return ((ploopQueue->dataPtrIn + ploopQueue->DataBufMaxSize - \
             ploopQueue->dataPtrOut) % ploopQueue->DataBufMaxSize);
}

/************************ (C) COPYRIGHT 2016 Megahuntmicro ****END OF FILE****/
