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
    uint32_t DataBufMaxSize;                        // ���ڼ�¼���ݿռ�Ĵ�С
} loopQueue,*ploopQueue;     

typedef struct _iLoopQueueStructDef{
    #ifndef USE_MALLOC_DEFINE_BUF_SIZE
    bool (*InitQueue)(ploopQueue pploopQueue, uint32_t dataLen);
    bool (*DestroyQueue)(ploopQueue ploopQueue);                        // �����д��ڣ���������
    #else
    uint32_t (*InitQueue)(ploopQueue *pploopQueue, uint32_t dataLen);   // ��ʼ������������һ���ն���
    bool (*DestroyQueue)(ploopQueue *ploopQueue);                        // �����д��ڣ���������
    #endif
    bool (*ClearQueue)(ploopQueue ploopQueue);                          // ���������
    bool (*QueueEmpty)(ploopQueue ploopQueue);                          // ������Ϊ�գ��򷵻�true�����򷵻�false
    /* �����д������ڶ����в���len���ȵ����ݣ������пռ䲻���򷵻�ʵ��д����е����ݳ��� */
    uint32_t (*EnQueue)(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len);
    /* ��ȡ������len���ȵ����ݵ�pbuf�У�������ʵ�ʶ�ȡ�����ݳ��� */
    uint32_t (*DeQueue)(ploopQueue ploopQueue, LoopDataWidth *pbuf, uint32_t len);
    uint32_t (*QueueLength)(ploopQueue ploopQueue);                     // ���ض��е�Ԫ�ظ���
} iLoopQueueStruct,*piLoopQueueStruct;

extern piLoopQueueStruct piLoopQueue;

#ifdef __cplusplus
}
#endif

#endif /*__LL_LOOPQUEUE_H */

/************************ (C) COPYRIGHT 2016 Megahuntmicro ****END OF FILE****/
