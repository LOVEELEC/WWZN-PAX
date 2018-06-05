/**
  ******************************************************************************
  * @file    LL_loopQueue.h
  * @author  Megahuntmicro
  * @version V1.0.0
  * @date    15-March-2016
  * @brief   Header file for uartInterface.c.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LL_LOOPQUEUE_H
#define __LL_LOOPQUEUE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdlib.h"  	 
#include "stdint.h"
#include "stdbool.h"

/* Exported types ------------------------------------------------------------*/
typedef uint8_t   LoopDataWidth;      
/* Exported constants --------------------------------------------------------*/     
/* Exported macro ------------------------------------------------------------*/
#define LOOPDATABUFMAXSIZE              (1024)     
//#define USE_MALLOC_DEFINE_BUF_SIZE
/* Exported functions --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
typedef struct _loopQueueStructDef
{
    #ifndef USE_MALLOC_DEFINE_BUF_SIZE
    LoopDataWidth dataBuf[LOOPDATABUFMAXSIZE];
    #endif
    LoopDataWidth *pdataBuf;
    uint32_t dataPtrIn;
    uint32_t dataPtrOut;
    uint32_t DataBufMaxSize;                        // 用于记录数据空间的大小
} loopQueue,*ploopQueue;     

typedef struct _iLoopQueueStructDef{
    #ifndef USE_MALLOC_DEFINE_BUF_SIZE
    bool (*InitQueue)(ploopQueue pploopQueue, uint32_t dataLen);
    bool (*DestroyQueue)(ploopQueue ploopQueue);                        // 若队列存在，则销毁它
    #else
    uint32_t (*InitQueue)(ploopQueue *pploopQueue, uint32_t dataLen);   // 初始化操作，建立一个空队列
    bool (*DestroyQueue)(ploopQueue *ploopQueue);                        // 若队列存在，则销毁它
    #endif
    bool (*ClearQueue)(ploopQueue ploopQueue);                          // 将队列清空
    bool (*QueueEmpty)(ploopQueue ploopQueue);                          // 若队列为空，则返回true，否则返回false
    /* 若队列存在则在队列中插入len长度的数据，若队列空间不足则返回实际写入队列的数据长度 */
    uint32_t (*EnQueue)(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len);
    /* 读取队列中len长度的数据到pbuf中，并返回实际读取的数据长度 */
    uint32_t (*DeQueue)(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len);
    uint32_t (*QueueLength)(ploopQueue ploopQueue);                     // 返回队列的元素个数
} iLoopQueueStruct,*piLoopQueueStruct;

extern piLoopQueueStruct piLoopQueue;

#ifdef __cplusplus
}
#endif

#endif /*__LL_LOOPQUEUE_H */

/************************ (C) COPYRIGHT 2016 Megahuntmicro ****END OF FILE****/
