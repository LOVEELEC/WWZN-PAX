


#include "mhscpu.h"
#include "mhscpu_it.h"
#include <string.h>
#include <stdio.h>
#include "DCMI_Interface.h"
extern uint8_t tmpRece;
extern uint32_t flagRece;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles DMA interrupt request.
  * @param  None
  * @retval None
  */
unsigned int g_test_cnt = 0x00;
void DMA0_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA_Channel_0,DMA_IT_BlockTransferComplete))
    {
        DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_BlockTransferComplete);
        g_test_cnt++;
//        printf("> Enter DMA0 Intrrupt!\n");
//        Image_ReStart();
    }
    
    if (DMA_GetITStatus(DMA_Channel_0,DMA_IT_DMATransferComplete))
    {
        DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_DMATransferComplete);
        g_test_cnt++;
//        printf("> Enter DMA0 Intrrupt!\n");
//        Image_ReStart();
    }
    
    if (DMA_GetITStatus(DMA_Channel_0,DMA_IT_Error))
    {
        DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_Error);
//        printf("DMA_IT_Error\r\n");
	}
}

/**
  * @brief  This function handles DCMI interrupt request.
  * @param  None
  * @retval None
  */
extern unsigned char Image_vsync;
void DCMI_IRQHandler(void)
{  	   
	if (DCMI_GetITStatus(DCMI_IT_VSYNC) != RESET) 
	{	 		   
		if (Image_vsync == 0)
        {
            Image_vsync = 1;
            /* Start Image capture */ 
            DCMI_CaptureCmd(ENABLE);
        }else{
            Image_vsync = 2;
        }         
		DCMI_ClearITPendingBit(DCMI_IT_VSYNC);	  
	}
	
	if (DCMI_GetITStatus(DCMI_IT_LINE) != RESET) 
	{
		DCMI_ClearITPendingBit(DCMI_IT_LINE); 			  
	}
	
    if (DCMI_GetITStatus(DCMI_IT_OVF) != RESET)
    {
        DCMI_ClearITPendingBit(DCMI_IT_OVF); 
    }
    
	if (DCMI_GetITStatus(DCMI_IT_FRAME) != RESET) 
	{
		if (Image_vsync == 0)
        {
            Image_vsync = 2;
        }
        DCMI_ClearITPendingBit(DCMI_IT_FRAME);
//        printf(">Enter Frame Intrrupt 0x%04x!\n",g_test_cnt);
//        Image_ReStart();
//        DCMI_CaptureCmd(ENABLE); 
	}
    
	if (DCMI_GetITStatus(DCMI_IT_ERR) != RESET) 
	{
		DCMI_ClearITPendingBit(DCMI_IT_ERR);
	}
}


extern void dw_csi_irq(void);
void CSI2_IRQHandler(void)
{
//	printf("mipi module err, please check! \n");
	dw_csi_irq();
}
///**
//  * @brief  This function handles SysTick Handler.
//  * @param  None
//  * @retval None
//  */
//void SysTick_Handler(void)
//{
//	
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */

void PPP_IRQHandler(void)
{
}



/**/

