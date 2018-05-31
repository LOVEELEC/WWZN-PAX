/**
  ******************************************************************************
  * @file    DCMI/MT9V034_Camera/dcmi_MT9V034.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   This file includes the driver for MT9V034 Camera module mounted on 
  *          STM322xG-EVAL board RevA and RevB.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "dcmi_MT9V034.h"
//#include "DCMI_MT9V034_INITTABLE.h"
#include "config.h"

/** @addtogroup DCMI_MT9V034_Camera
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Bits definitions ----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Delay(uint32_t nTime); 
static void Delay_ms(uint32_t nTime);

//unsigned char  B_pixel_matrix[ORIG_WIN_LEN][ORIG_WIN_LEN] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
unsigned char  B_pixel_matrix[MT9V024_HEIGHT][MT9V024_WEIGHT] = {0};

unsigned char MT9V_vsync =0;

/**
  * @brief  Configures the DCMI to interface with the MT9V034 camera module.
  * @param  None
  * @retval None
  */
void DCMI_Config(void)
{
    DCMI_InitTypeDef DCMI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;	
	  DCMI_CROPInitTypeDef DCMI_CROPInitStructure;

    /* Enable DCMI GPIOs clocks */
//    SYSCTRL_APBPeriphClockCmd(SYSCTRL_APBPeriph_GPIO, ENABLE);
//	SYSCTRL_APBPeriphResetCmd(SYSCTRL_APBPeriph_GPIO, ENABLE); 

    /* Enable DCMI clock */
//    SYSCTRL_APBPeriphClockCmd(SYSCTRL_AHBPeriph_DCMI, ENABLE);
//	SYSCTRL_AHBPeriphResetCmd(SYSCTRL_AHBPeriph_DCMI, ENABLE);
	

    /* DCMI GPIO configuration **************************************************/
    /*
        D0 -- PG13
        D1 -- PG14
        D2 -- PG15
        D3 -- PH0
        D4 -- PH1
        D5 -- PH2
        D6 -- PH3
        D7 -- PH4
        PCK - PH13
        HS -- PH12
        VS -- PH11
    */
    GPIO_PinRemapConfig(GPIOH, GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3  | GPIO_Pin_4  |\
                               GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13, GPIO_Remap_0);
    GPIO_PinRemapConfig(GPIOG, GPIO_Pin_13 |\
												GPIO_Pin_14  | GPIO_Pin_15, GPIO_Remap_0);                           

    /* DCMI configuration *******************************************************/ 
#ifndef DCMI_SNAPSHOT
    DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
#else
    DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
#endif
    DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;

    DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;  //MT9V 输出时钟下降沿对齐,0x72寄存器设置

    DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;

    DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;       //低电平数据无效，MT9V's HREF 高电平数据有效

//    DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling; 
//    DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_Low;
//    DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;

    DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
//    DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_1of4_Frame;
    DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

    DCMI_Init(&DCMI_InitStructure);

    /* DCMI CROP configuration *******************************************************/ 
#ifdef DCMI_CROP
    DCMI_CROPInitStructure.DCMI_VerticalStartLine = 0;
    DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 0;
//    DCMI_CROPInitStructure.DCMI_VerticalLineCount = ORIG_WIN_LEN;
//    DCMI_CROPInitStructure.DCMI_CaptureCount = ORIG_WIN_LEN;
    DCMI_CROPInitStructure.DCMI_VerticalLineCount = MT9V024_HEIGHT - 1;
    DCMI_CROPInitStructure.DCMI_CaptureCount = MT9V024_WEIGHT - 1;
    DCMI_CROPConfig(&DCMI_CROPInitStructure);
    DCMI_CROPCmd(ENABLE);
#endif
    /* DCMI Interrupts config ***************************************************/
#ifdef DCMI_IT_SET  
    NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure); 
		
    DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
    DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
    DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
    DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
    DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
#endif
}

void DCMI_DMA_Configuration(LLI *lli)
{
    DMA_InitTypeDef  DMA_InitStructure;

//	SYSCTRL_AHBPeriphClockCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);
//	SYSCTRL_AHBPeriphResetCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);
    /* DMA Stream Configuration */  
    DMA_InitStructure.DMA_DIR = DMA_DIR_Peripheral_To_Memory;
    DMA_InitStructure.DMA_Peripheral = (uint32_t)DCMI;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(DCMI->DR);	
    DMA_InitStructure.DMA_PeripheralInc = DMA_Inc_Nochange;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_DataSize_Word;
    DMA_InitStructure.DMA_PeripheralBurstSize = DMA_BurstSize_1;  
    
    DMA_InitStructure.DMA_MemoryBaseAddr = (unsigned int)&B_pixel_matrix[0][0];
    DMA_InitStructure.DMA_MemoryInc = DMA_Inc_Increment;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_DataSize_Word;
    DMA_InitStructure.DMA_MemoryBurstSize = DMA_BurstSize_1;
//    DMA_InitStructure.DMA_BlockSize = (ORIG_WIN_LEN * ORIG_WIN_LEN) / 4; 
    DMA_InitStructure.DMA_BlockSize = BDMASIZE;  
    DMA_InitStructure.DMA_PeripheralHandShake = DMA_PeripheralHandShake_Hardware;
    
//	DMA_Init(DMA_Channel_0, &DMA_InitStructure );
    DMA_MultiBlockInit(DMA_Channel_0, &DMA_InitStructure , lli,Multi_Block_MODE10);  
    
    DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_BlockTransferComplete);
    DMA_ITConfig(DMA_Channel_0, DMA_IT_BlockTransferComplete, ENABLE);
		
	DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_Error);
    DMA_ITConfig(DMA_Channel_0, DMA_IT_Error, ENABLE);
//		
}


void UART0_DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStruct;
//    SYSCTRL_AHBPeriphClockCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);
//	SYSCTRL_AHBPeriphResetCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);
    DMA_InitStruct.DMA_Peripheral = (uint32_t)UART0;
//		DMA_InitStruct.DMA_DIR = DMA_DIR_Peripheral_To_Memory	;
    DMA_InitStruct.DMA_DIR = DMA_DIR_Memory_To_Peripheral;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(UART0->OFFSET_0.THR);
	DMA_InitStruct.DMA_PeripheralInc = DMA_Inc_Nochange;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_DataSize_Byte;
	DMA_InitStruct.DMA_PeripheralBurstSize = DMA_BurstSize_1;
    DMA_InitStruct.DMA_MemoryBaseAddr = (unsigned int)&B_pixel_matrix[0][0];
	DMA_InitStruct.DMA_MemoryInc = DMA_Inc_Increment;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_DataSize_Byte;
	DMA_InitStruct.DMA_MemoryBurstSize = DMA_BurstSize_1;
	DMA_InitStruct.DMA_BlockSize = 4095;
	DMA_InitStruct.DMA_PeripheralHandShake = DMA_PeripheralHandShake_Hardware;
     
	DMA_Init(DMA_Channel_2,&DMA_InitStruct);
    
    DMA_ITConfig(DMA_Channel_2, DMA_IT_BlockTransferComplete, ENABLE);
    DMA_ClearITPendingBit(DMA_Channel_2,DMA_IT_BlockTransferComplete);
}
/**
  * @brief  Set PA8 Output SYSCLK/2.
  * @param  None
  * @retval None
  */
void MCO1_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_ClockSecuritySystemCmd(ENABLE);

//	/* Enable GPIOs clocks */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
//		
//	/* Configure MCO (PA8) */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	//RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_3);  //3分频得40M
//	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_5);		 //5分频得24M
//	//RCC_MCO1Config(RCC_MCO1Source_HSI, RCC_MCO1Div_2);   //16M
}

void DCMI_0V7670_RST_PWDN_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;

//	/* Enable GPIOs clocks */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	/*PWDN*/
//	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
//	/*Reset*/
//	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
//	Delay_ms(10);
//	GPIO_SetBits(GPIOB, GPIO_Pin_1);	
}

/**
  * @brief  Set the size.
  * @param  None
  * @retval None
  */
uint8_t DCMI_MT9V_Init(LLI *lli)
{
//	uint8_t i;
//	unsigned short MTChipVersion;
//	
//	MTChipVersion = 0;
//	SCCB_GPIO_Config();
	DCMI_DeInit();
	DCMI_Config();
	MCO1_Init();
	
/* Configures the DMA2 to transfer Data from DCMI to the LCD ****************/
  /* Enable DMA2 clock */
//    SYSCTRL_AHBPeriphClockCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);
//	SYSCTRL_AHBPeriphResetCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);
    DCMI_DMA_Configuration(lli);
	
//  	Delay_ms(0xfff);
//	if(SCCB_WriteWord(0x0C, 0x0001)!=0)   // SENSER RESET
//		return 0xff;
//	Delay_ms(0xfff);
//  
//	if (SCCB_ReadWord(0x00, &MTChipVersion) != 0)
//		return 0xff;
//	if (MTChipVersion == MT9V034_ID)
//	{
//		for(i = 0; i < MT9V_REG_NUM; i++)
//		{
//			if(SCCB_WriteWord(Sensor_Config[i].Address,Sensor_Config[i].Value)!=0)
//			{
//				return 0xff;
//			}
//		}
//	}
//	//MT9V034_config_window(272,16,320,240);// set 240*320
// 	Delay_ms(0xfff);
	return 0;//Init ok
}

/**
  * @brief  Read the OV7670 Manufacturer identifier.
  * @param  OV7670ID: pointer to the OV7670 Manufacturer identifier. 
  * @retval None
  */
uint8_t DCMI_OV7670_ReadID(OV7670_IDTypeDef* OV7670ID)
{
	uint8_t temp;
	if(DCMI_SingleRandomRead(OV7670_MIDH,&temp)!=0)
		return 0xff;
	OV7670ID->Manufacturer_ID1 = temp;
	if(DCMI_SingleRandomRead(OV7670_MIDL,&temp)!=0)
		return 0xff;
	OV7670ID->Manufacturer_ID2 = temp;
	if(DCMI_SingleRandomRead(OV7670_VER,&temp)!=0)
		return 0xff;
	OV7670ID->Version = temp;
	if(DCMI_SingleRandomRead(OV7670_PID,&temp)!=0)
		return 0xff;
	OV7670ID->PID = temp;

	return 0;
}
/**
  * @brief  config_OV7660_window 
  * @param  //(140,16,640,480) is good for VGA
  *			//(272,16,320,240) is good for QVGA
  * @retval None
  */
void OV7670_config_window(uint16_t startx, uint16_t starty, uint16_t width, uint16_t height)
{
	uint16_t endx=(startx+width);
	uint16_t endy=(starty+height*2);// must be "height*2"
	uint8_t temp_reg1, temp_reg2;
	uint8_t state,temp;
	
	state = state;	   //Prevent report warning

	state = DCMI_SingleRandomRead(0x03, &temp_reg1 );
	temp_reg1 &= 0xC0;
	state = DCMI_SingleRandomRead(0x32, &temp_reg2 );
	temp_reg2 &= 0xC0;
	
	// Horizontal
	temp = temp_reg2|((endx&0x7)<<3)|(startx&0x7);
	state = DCMI_SingleRandomWrite(0x32, temp );
	temp = (startx&0x7F8)>>3;
	state = DCMI_SingleRandomWrite(0x17, temp );
	temp = (endx&0x7F8)>>3;
	state = DCMI_SingleRandomWrite(0x18, temp );
	
	// Vertical
	temp = temp_reg1|((endy&0x7)<<3)|(starty&0x7);
	state = DCMI_SingleRandomWrite(0x03, temp );
	temp = (starty&0x7F8)>>3;
	state = DCMI_SingleRandomWrite(0x19, temp );
	temp = (endy&0x7F8)>>3;
    state = DCMI_SingleRandomWrite(0x1A, temp );
}
 			 			  
/**
  * @}
  */
static void Delay(uint32_t nTime)
{
    while(nTime--);
} 

static void Delay_ms(uint32_t nTime)
{
    while(nTime--)
  	{Delay(1000);}
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
