/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_sysctrl.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file provides all the SYSCTRL firmware functions
 *****************************************************************************/  

/* Includes -----------------------------------------------------------------*/
#include "mhscpu_retarget.h"

/* Exported functions -------------------------------------------------------*/	

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @param  SYSCTRL_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *   For @b this parameter can be any combination
  *   of the following values:        
  *     @arg SYSCTRL_AHBPeriph_DMA
  *     @arg SYSCTRL_AHBPeriph_USB
  *     @arg SYSCTRL_AHBPeriph_QR
  *     @arg SYSCTLR_AHBPeriph_MSRFC
  *     @arg SYSCTRL_AHBPeriph_OTP
  *     @arg SYSCTRL_AHBPeriph_CLCD
  *     @arg SYSCTRL_AHBPeriph_LCD
  *     @arg SYSCTRL_AHBPeriph_CRYPT
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_AHBPeriphClockCmd(uint32_t SYSCTRL_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_AHB_PERIPH(SYSCTRL_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        SYSCTRL->CG_CTRL2 |= SYSCTRL_AHBPeriph_ALL;
    }
    else
    {
        SYSCTRL->CG_CTRL2 &= ~SYSCTRL_AHBPeriph;
    }
}

/**
  * @brief Get the frequencies of different on chip clocks
  * @param SYSCTRL_Clocks: pointer to a SYSCTRL_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval 
  */
void SYSCTRL_GetClocksFreq(SYSCTRL_ClocksTypeDef *SYSCTRL_Clocks)
{
    /* 获取系统时钟 */
    if (SYSCTRL_FREQ_SEL_XTAL_204Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 204000000;
    }
    else if (SYSCTRL_FREQ_SEL_XTAL_192Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 192000000;
    } 
    else if (SYSCTRL_FREQ_SEL_XTAL_180Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 180000000;
    }
    else if (SYSCTRL_FREQ_SEL_XTAL_168Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 168000000;
    } 
    else if (SYSCTRL_FREQ_SEL_XTAL_156Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 156000000;
    }
    else if (SYSCTRL_FREQ_SEL_XTAL_144Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 144000000;
    } 
    else if (SYSCTRL_FREQ_SEL_XTAL_132Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 132000000;
    }
    else if (SYSCTRL_FREQ_SEL_XTAL_120Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 120000000;
    } 
    else if (SYSCTRL_FREQ_SEL_XTAL_108Mhz == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask))
    {
        SYSCTRL_Clocks->PLL_Frequency = 108000000;
    }
    
    /* CPUCLK */
    if (SYSCTRL_FREQ_SEL_PLL_DIV_1_0 == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_PLL_DIV_Mask))
    {
        SYSCTRL_Clocks->CPU_Frequency = SYSCTRL_Clocks->PLL_Frequency;
    }
    else if (SYSCTRL_FREQ_SEL_PLL_DIV_1_2 == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_PLL_DIV_Mask))
    {
        SYSCTRL_Clocks->CPU_Frequency = SYSCTRL_Clocks->PLL_Frequency / 2;
    }
    else if (SYSCTRL_FREQ_SEL_PLL_DIV_1_4 == (SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_PLL_DIV_Mask))
    {
        SYSCTRL_Clocks->CPU_Frequency = SYSCTRL_Clocks->PLL_Frequency / 4;
    }
    
    /* HCLK */
    SYSCTRL_Clocks->HCLK_Frequency = SYSCTRL->HCLK_1MS_VAL * 1000;
    
    /* PCLK */
    SYSCTRL_Clocks->PCLK_Frequency = SYSCTRL->PCLK_1MS_VAL * 1000;
}


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
