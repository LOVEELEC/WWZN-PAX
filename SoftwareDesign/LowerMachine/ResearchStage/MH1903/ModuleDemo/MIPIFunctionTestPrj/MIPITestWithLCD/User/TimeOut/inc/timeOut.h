/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : timeOut.h
 * Author               : Megahuntmicro
 * Version              : V1.0.0
 * Date                 : 07/29/2014
 * Description          : Header file for timeOut.c file.
 *****************************************************************************/
 
 
#ifndef __TIME_OUT_H__
#define __TIME_OUT_H__
 
 
#ifdef __cplusplus
extern "C" {
#endif
	
/* Include ------------------------------------------------------------------*/
#include "mhscpu.h"	
#include "stdbool.h"
/* Exported types -----------------------------------------------------------*/
/* Exported constants -------------------------------------------------------*/	
/* Exported macro -----------------------------------------------------------*/	
/* Exported functions -------------------------------------------------------*/	
/* Exported variables -------------------------------------------------------*/	
#define MAX_TIMEOUT_CNT			(5)

typedef enum _TIMETYPE_DEF{
	WAIT_TOKEN,
	WAIT_USB_SENDCMP,
	WAIT_IMAGE_COLLECTION_CMP,
	WAIT_CLOGGED_RECOVERY,
	WAIT_SENDPOWERONMES_INV
} TIMETYPE;
	
typedef unsigned int  			tick;
typedef struct _TimeOutParameterDef
{
	tick Systick_current_time;										// ���ڼ�¼ϵͳ��ǰʱ��
	tick Systick_start_time[MAX_TIMEOUT_CNT];						// ���ڼ�¼���ó�ʱ����ʼʱ��
	tick Systick_time_out_interval[MAX_TIMEOUT_CNT];				// ���ڼ�¼���õĳ�ʱʱ��
	uint8_t timeOuttype;											// ���ڼ�¼��ʱ����(ÿ��bit����һ�ֳ�ʱ����)
} TimeOutParameterDef;	
	 
typedef struct _iTimeOut_Struct_Def{
	void 	(*Init)(void);											// ��ʼ��
	void 	(*TickTimer)(void);										// ���ڼ�¼Tickʱ��(��Systick�ж���Ҫ���õĺ���)
	void 	(*StopTimeOutTick)(TIMETYPE timeOutType);				// ָֹͣ�����͵ĳ�ʱ���
	void 	(*SetTimeOutTick)(tick time, TIMETYPE timeOutType);		// ����ָ�����ͳ�ʱ�ĳ�ʱʱ��
	uint8_t (*IsTimeOut)(void);										// ����Ƿ��г�ʱ����,�����س��ֳ�ʱ�ĳ�ʱ����
	bool 	(*GetTypeTimeOutSign)(TIMETYPE timeOutType);			// ��ȡָ�����͵ĳ�ʱ�Ƿ���ֳ�ʱ
	bool 	(*IsTypeActive)(TIMETYPE timeOutType);					// ���ĳһ���͵ĳ�ʱ�Ƿ��Ѿ�����
} iTimeOut_Struct, *piTimeOut_Struct;

extern piTimeOut_Struct piTimeOut;
#ifdef __cplusplus
}
#endif	 

#endif	/* __TIME_OUT_H__ */
/************************ (C) COPYRIGHT 2014 Megahuntmicro ****END OF FILE****/
