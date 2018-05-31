/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_trng.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file provides all the TRNG firmware functions
 *****************************************************************************/

/* Include ------------------------------------------------------------------*/
#include "mhscpu_retarget.h"


const uint32_t TRNG_RNG_AMA_PD_Mask[1] =			{TRNG_RNG_AMA_PD_TRNG0_Mask};
const uint32_t TRNG_RNG_AMA_ANA_OUT_Mask[1] =		{TRNG_RNG_AMA_ANA_OUT_TRNG0_Mask};
const uint32_t TRNG_RNG_CSR_S128_Mask[1] =			{TRNG_RNG_CSR_S128_TRNG0_Mask};
const uint32_t TRNG_RNG_CSR_ATTACK_Mask[1] =		{TRNG_RNG_CSR_ATTACK_TRNG0_Mask};

/**
  * @method	TRNG_DirectOutANA
  * @brief	
  * @param	TRNGx
  * @param	NewState
  * @retval 
  */
void TRNG_DirectOutANA(TRNG_ChannelTypeDef TRNGx, FunctionalState NewState)
{
	assert_param(IS_TRNG_CHANNEL(TRNGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if(NewState != DISABLE)
	{
		TRNG->RNG_AMA |= TRNG_RNG_AMA_ANA_OUT_Mask[TRNGx];
	}
	else
	{
		TRNG->RNG_AMA &= ~TRNG_RNG_AMA_ANA_OUT_Mask[TRNGx];
	}
}

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/

