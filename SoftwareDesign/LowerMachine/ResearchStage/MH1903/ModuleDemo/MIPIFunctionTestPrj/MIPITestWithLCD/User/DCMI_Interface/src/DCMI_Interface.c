/**
  ******************************************************************************
  * @file    DCMI_Interface.c
  * @author  LOVE_ELEC
  * @version V1.0.0
  * @date    18-Januery-2018
  * @brief   This file is used to define the DCMI operation interface.
  ******************************************************************************
  */
  
/* Include -------------------------------------------------------------------*/
#include "DCMI_Interface.h"
#include "mipi_dcmi_GC2355.h"
#include "dwc_mipi_csi.h"
#include "config.h"
#include "systick.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/	
/* Private variables ---------------------------------------------------------*/	
LLI lli[45] = {0};
unsigned char  B_pixel_matrix[ORIG_WIN_LEN][ORIG_WIN_LEN];
uint8_t Image_vsync = 0x00;
/* Ptivate function prototypes -----------------------------------------------*/
static void NVIC_Configuration(void);
static void DcmiPixClkSet(uint32_t clkDivid);
static void MH1903_MIPIandDCMIConfig(void);
static void DCMI_Config(void);
static void DCMI_DMA_Configuration(LLI *lli);
static void DCMI_DMA_LLI_Init(void);
/*******************************************************************************
* Function Name	: 
* Description	: 
* Input			: 
* Output		: 
* Return		: 
*******************************************************************************/
bool Image_Init(void)
{
    bool ret = false;
    /* MIPI&DCMI Initialization */
    NVIC_Configuration();
    MH1903_MIPIandDCMIConfig(); 
    return ret;
}

bool Image_ReStart(void)
{
    DMA_InitTypeDef  DMA_InitStructure;
    DMA_ChannelCmd(DMA_Channel_0,DISABLE);
    DCMI_DMA_Configuration(&lli[0]);
    /* DMA Stream Configuration */  
    DMA_InitStructure.DMA_DIR = DMA_DIR_Peripheral_To_Memory;
    DMA_InitStructure.DMA_Peripheral = (uint32_t)DCMI;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(DCMI->DR);	
    DMA_InitStructure.DMA_PeripheralInc = DMA_Inc_Nochange;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_DataSize_Word;
    DMA_InitStructure.DMA_PeripheralBurstSize = DMA_BurstSize_1;  
    
    DMA_InitStructure.DMA_MemoryBaseAddr = (unsigned int)&B_pixel_matrix[0][0];
    DMA_InitStructure.DMA_MemoryInc = DMA_Inc_Increment;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_DataSize_Byte;
    DMA_InitStructure.DMA_MemoryBurstSize = DMA_BurstSize_1;
    DMA_InitStructure.DMA_BlockSize = (ORIG_WIN_LEN * ORIG_WIN_LEN) / 4; 
//    DMA_InitStructure.DMA_PeripheralHandShake = DMA_PeripheralHandShake_Hardware;
    
	DMA_Init(DMA_Channel_0, &DMA_InitStructure);
//    DMA_MultiBlockInit(DMA_Channel_0, &DMA_InitStructure , lli,Multi_Block_MODE10);  
    
    
    
    DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_DMATransferComplete);
    DMA_ITConfig(DMA_Channel_0, DMA_IT_DMATransferComplete, ENABLE);
    
//    DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_BlockTransferComplete);
//    DMA_ITConfig(DMA_Channel_0, DMA_IT_BlockTransferComplete, ENABLE);
    
    DMA_ChannelCmd(DMA_Channel_0,ENABLE);
//    DCMI_CaptureCmd(ENABLE); 
}
/**
  * @brief  NVIC Configuration Functions
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
    
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_1);
	
    NVIC_InitStructure.NVIC_IRQChannel = CSI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure); 
    
//    NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}

/*
用于DCMI及MIPI的pix_clk生成,clk_dcmis来自Hclk
0: (clk_dcmis)/2 （不建议使用）
1: (clk_dcmis)/4
2: (clk_dcmis)/6
以此类推
*/
static void DcmiPixClkSet(uint32_t clkDivid)
{
	uint32_t tmpValue;
	tmpValue = SYSCTRL->FREQ_SEL;
	SYSCTRL->FREQ_SEL = (0x1FFFFFFF&tmpValue) | (clkDivid << 29);
}

static void MH1903_MIPIandDCMIConfig(void)
{
    /*  dmci_sel 1:DCMI外部输入 O:内部与csi2相连 */
	SYSCTRL->DBG_CR &= ~(1 << 13);   
	/* 置1后，MIPI的dataen作为DCMI的HSYNC输入 */
	SYSCTRL->DBG_CR |= 1<<14;
	/* csi2_dcmi_sel 置1后，pc~pf的部分IO复用为CSI2-DCMI接口 */
	SYSCTRL->DBG_CR &= ~(1<<12);
		/* srst_csi2 软复位信号 */
	SYSCTRL->SOFT_RST1 |= 1<<22;
	DcmiPixClkSet(1);  //48Mhz
    
    dwc_csi_host_init();
    /*  check status mipi  */
//	dwc_csi_check_status();
    
    DCMI_DeInit();
	DCMI_Config();
	DCMI_DMA_Configuration(&lli[0]);
//	DCMI_DMA_LLI_Init();
	DMA_ChannelCmd(DMA_Channel_0,ENABLE);
	mdelay(1);
	/* 配置dcmi启动时的fifo数据大小 */
	DCMI_SetDMARequsetFIFOSize(DCMI_DMARequestFIFOSize_4Word);
	/* Enable DCMI interface  */
	DCMI_Cmd(ENABLE);  	
	/* Start Image capture */ 
	DCMI_CaptureCmd(ENABLE);
}

static void DCMI_Config(void)
{
    DCMI_InitTypeDef DCMI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;	
	DCMI_CROPInitTypeDef DCMI_CROPInitStructure;
//    SYSCTRL_APBPeriphClockCmd(SYSCTRL_APBPeriph_GPIO | SYSCTRL_APBPeriph_DCMIS, ENABLE);
//	SYSCTRL_APBPeriphResetCmd(SYSCTRL_APBPeriph_DCMIS, ENABLE);
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
    GPIO_PinRemapConfig(GPIOG, GPIO_Pin_13 | GPIO_Pin_14  | GPIO_Pin_15, GPIO_Remap_0);                           

    /* DCMI configuration *******************************************************/ 
#ifndef DCMI_SNAPSHOT
    DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
#else
    DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
#endif
    DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;

//    DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;   	//输出时钟下降沿对齐，0x72寄存器设置
    DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling; 
    
//    DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
    DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_Low;
    
	/*  低电平数据无效，高电平数据有效，对于mipi直接过来的hsync是低有效,如果使用dataen则为高电平有效  */
//    DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;       	
    DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;    

    DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
//    DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_1of4_Frame;
    DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

    DCMI_Init(&DCMI_InitStructure);

    /* DCMI CROP configuration *******************************************************/ 
    DCMI_CROPInitStructure.DCMI_VerticalStartLine = 0;
    DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 0;
    DCMI_CROPInitStructure.DCMI_VerticalLineCount = ORIG_WIN_LEN;
    DCMI_CROPInitStructure.DCMI_CaptureCount = ORIG_WIN_LEN;
    DCMI_CROPConfig(&DCMI_CROPInitStructure);
    DCMI_CROPCmd(ENABLE);
    /* DCMI Interrupts config ***************************************************/
    NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure); 
    NVIC_InitStructure.NVIC_IRQChannel = DMA_IRQn;
	NVIC_Init(&NVIC_InitStructure);
		
//    DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
//    DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
//    DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
    DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
//    DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
}

static void DCMI_DMA_Configuration(LLI *lli)
{
    DMA_InitTypeDef  DMA_InitStructure;
//    SYSCTRL_AHBPeriphClockCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);
//    SYSCTRL_AHBPeriphResetCmd(SYSCTRL_AHBPeriph_DMA, ENABLE);    
    /* DMA Stream Configuration */  
    DMA_InitStructure.DMA_DIR = DMA_DIR_Peripheral_To_Memory;
    DMA_InitStructure.DMA_Peripheral = (uint32_t)DCMI;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(DCMI->DR);	
    DMA_InitStructure.DMA_PeripheralInc = DMA_Inc_Nochange;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_DataSize_Word;
    DMA_InitStructure.DMA_PeripheralBurstSize = DMA_BurstSize_1;  
    
    DMA_InitStructure.DMA_MemoryBaseAddr = (unsigned int)&B_pixel_matrix[0][0];
    DMA_InitStructure.DMA_MemoryInc = DMA_Inc_Increment;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_DataSize_Byte;
    DMA_InitStructure.DMA_MemoryBurstSize = DMA_BurstSize_1;
    DMA_InitStructure.DMA_BlockSize = (ORIG_WIN_LEN * ORIG_WIN_LEN) / 4; 
//    DMA_InitStructure.DMA_PeripheralHandShake = DMA_PeripheralHandShake_Hardware;
    
	DMA_Init(DMA_Channel_0, &DMA_InitStructure);
//    DMA_MultiBlockInit(DMA_Channel_0, &DMA_InitStructure , lli,Multi_Block_MODE10);  
    
    DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_DMATransferComplete);
    DMA_ITConfig(DMA_Channel_0, DMA_IT_DMATransferComplete, ENABLE);
    
//    DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_BlockTransferComplete);
//    DMA_ITConfig(DMA_Channel_0, DMA_IT_BlockTransferComplete, ENABLE);
	
	DMA_ClearITPendingBit(DMA_Channel_0,DMA_IT_Error);
    DMA_ITConfig(DMA_Channel_0, DMA_IT_Error, ENABLE);
}


static void DCMI_DMA_LLI_Init(void)
{
	int i = 0;
	for( i = 0 ; i < 45 ; i++)
		DMA_InitLLI(DMA_Channel_0,&lli[i],&lli[i+1], (void*)&DCMI->DR,(void*)((uint32_t)B_pixel_matrix + BDMASIZE * 4 * i ),BDMASIZE);
//        DMA_InitLLI(DMA_Channel_0,&lli[i],&lli[i+1], (void*)&DCMI->DR,(void*)((uint32_t)B_pixel_matrix),(ORIG_WIN_LEN * ORIG_WIN_LEN) / 4);
	if( i == 45)
		DMA_InitLLI(DMA_Channel_0,&lli[i],&lli[0], (void*)&DCMI->DR,(void*)((uint32_t)B_pixel_matrix + BDMASIZE * 4 * i),BDMASIZE);
//        DMA_InitLLI(DMA_Channel_0,&lli[i],&lli[0], (void*)&DCMI->DR,(void*)((uint32_t)B_pixel_matrix),(ORIG_WIN_LEN * ORIG_WIN_LEN) / 4);
}
/************************* (C) COPYRIGHT 2018 LOVE_ELEC ******END OF FILE******/