/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : mhscpu_adc.c
 * Author               : Megahuntmicro
 * Version              : V1.0.0
 * Date                 : 05/28/2017
 * Description          : ADC module functions set.
 *****************************************************************************/
 
/* Include ------------------------------------------------------------------*/
#include "mhscpu_retarget.h"


/******************************************************************************
* Function Name  : ADC_Init
* Description    : ��ʼ��ADC,��ʼ���ο�ֵ
* Input          : ADC_InitStruct��Ҫ��ʼ�������ݽṹָ��
* Return         : NONE
******************************************************************************/
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct)
{
    assert_param(IS_ADC_CHANNEL(ADC_InitStruct->ADC_Channel));
    assert_param(IS_ADC_SAMP(ADC_InitStruct->ADC_SampSpeed));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_IRQ_EN));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_FIFO_EN));

    /* Select ADC Channel */
    ADC0->ADC_CR1 = (ADC0->ADC_CR1 & ~(0x7)) | ADC_InitStruct->ADC_Channel; 
    /* Select ADC Channel Samping */
    ADC0->ADC_CR1 = (ADC0->ADC_CR1 & ~(0x3 << 3)) | (ADC_InitStruct->ADC_SampSpeed << 3);
    /* Set ADC Interrupt */
    if (ENABLE == ADC_InitStruct->ADC_IRQ_EN )
    {
        NVIC_EnableIRQ(ADC0_IRQn);
        ADC0->ADC_CR1 |= ADC_IRQ_EN_BIT;
    }else
    {
        ADC0->ADC_CR1 &= ~ADC_IRQ_EN_BIT;
    }
    /* Set ADC FIFO */
    if (ENABLE == ADC_InitStruct->ADC_FIFO_EN)
    {
        ADC0->ADC_FIFO |= ADC_FIFO_EN_BIT;
    }else
    {
        ADC0->ADC_FIFO &= ~ADC_FIFO_EN_BIT;
    }
}

/******************************************************************************
* Function Name  : ADC_GetResult
* Description    : ������ȡADC��Ӧͨ����ֵ,�г�ʱ���
* Input          : None
* Return         : 0:��ȡ��ʱ  Other:ADCֵ
******************************************************************************/
int32_t ADC_GetResult(void)
{
    while((!(ADC0->ADC_SR & ADC_DONE_FLAG)));

    return ADC0->ADC_DATA & 0xFFF;
}

/******************************************************************************
* Function Name  : ADC_CalVoltage
* Description    : ����ת����ĵ�ѹֵ
* Input          : u32ADC_Value: ADC�ɼ�ֵ
*                : u32ADC_Ref_Value: ADC�ο���ѹ
* Output         : NONE
* Return         : ����ת����ĵ�ѹֵ
******************************************************************************/
uint32_t ADC_CalVoltage(uint32_t u32ADC_Value, uint32_t u32ADC_Ref_Value)
{
    return (u32ADC_Value * u32ADC_Ref_Value / 4095);
}

/******************************************************************************
* Function Name  : ADC_BuffCmd
* Description    : ADC Buffʹ�ܿ���
* Input          : NewState:ADC BUFFʹ�ܿ���,����ȡENABLE��DISABLE
* Output         : NONE
* Return         : NONE
******************************************************************************/
void ADC_BuffCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if(DISABLE != NewState)
	{
		ADC0->ADC_CR2 &= ~ADC_BUFF_EN_BIT;
	}
	else
	{
		ADC0->ADC_CR2 |= ADC_BUFF_EN_BIT;
	}
}


/************************ (C) COPYRIGHT 2017 Megahuntmicro ****END OF FILE****/
