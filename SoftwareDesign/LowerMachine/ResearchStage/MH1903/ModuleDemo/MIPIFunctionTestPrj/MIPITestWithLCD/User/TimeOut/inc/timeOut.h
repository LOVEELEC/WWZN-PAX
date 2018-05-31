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
	tick Systick_current_time;										// 用于记录系统当前时间
	tick Systick_start_time[MAX_TIMEOUT_CNT];						// 用于记录设置超时的起始时间
	tick Systick_time_out_interval[MAX_TIMEOUT_CNT];				// 用于记录设置的超时时长
	uint8_t timeOuttype;											// 用于记录超时类型(每个bit代表一种超时类型)
} TimeOutParameterDef;	
	 
typedef struct _iTimeOut_Struct_Def{
	void 	(*Init)(void);											// 初始化
	void 	(*TickTimer)(void);										// 用于记录Tick时钟(即Systick中断中要调用的函数)
	void 	(*StopTimeOutTick)(TIMETYPE timeOutType);				// 停止指定类型的超时检测
	void 	(*SetTimeOutTick)(tick time, TIMETYPE timeOutType);		// 设置指定类型超时的超时时长
	uint8_t (*IsTimeOut)(void);										// 检测是否有超时出现,并返回出现超时的超时类型
	bool 	(*GetTypeTimeOutSign)(TIMETYPE timeOutType);			// 获取指定类型的超时是否出现超时
	bool 	(*IsTypeActive)(TIMETYPE timeOutType);					// 检测某一类型的超时是否已经开启
} iTimeOut_Struct, *piTimeOut_Struct;

extern piTimeOut_Struct piTimeOut;
#ifdef __cplusplus
}
#endif	 

#endif	/* __TIME_OUT_H__ */
/************************ (C) COPYRIGHT 2014 Megahuntmicro ****END OF FILE****/
