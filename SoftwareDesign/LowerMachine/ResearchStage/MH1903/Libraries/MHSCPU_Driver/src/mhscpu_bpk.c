/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_bpk.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file provides all the BPK firmware functions
 *****************************************************************************/

/* Includes -----------------------------------------------------------------*/
#include "mhscpu_retarget.h"

/* Exported functions -------------------------------------------------------*/
/**
  * @brief  Enable or disable the specified BPK lock
  * @param  BPK_LOCK: specify the bpk lock
  *         This parameter can be one of the following values: 
  *      @arg BPK_LR_LOCK_RESET
  *      @arg BPK_LR_LOCK_KEYWRITE
  *      @arg BPK_LR_LOCK_KEYREAD
  *      @arg BPK_LR_LOCK_KEYCLEAR
  *      @arg BPK_LR_LOCK_SETSCRAMBER
  * @param  NewState: new state of the specified BPK lock
  *			This parameter can be ENABLE or DISABLE
  * @retval None
  */
void BPK_Lock(uint32_t BPK_LOCK, FunctionalState NewState)
{
	assert_param((BPK_LOCK != BPK_LR_LOCK_SELF) && IS_BPK_LOCK(BPK_LOCK));
	
	if (DISABLE != NewState)
	{
		BPK->BPK_LR |= BPK_LOCK;
	}
	else
	{
		BPK->BPK_LR &= ~BPK_LOCK;
	}
}

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
