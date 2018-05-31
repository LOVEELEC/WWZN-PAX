/**
  ******************************************************************************
  * @file    OV7251_MIPI_Driver.c
  * @author  LOVE_ELEC
  * @version V1.0.0
  * @date    18-Januery-2018
  * @brief   This file is used to define the OV7251 operation interface.
  ******************************************************************************
  */
  
/* Include -------------------------------------------------------------------*/
#include "OV7251_MIPI_Driver.h"
#include "CameraSensor_Config.h"
#include "Sensor_SCCB.h"
#include "DCMI_Interface.h"
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
	uint32_t PWM_HZ;
	uint32_t DutyCycleHighPluse;
	uint32_t DutyCycleLowPluse;
	SYSCTRL_ClocksTypeDef clocks;
	TIM_PWMInitTypeDef TIM_PWMSetStruct;
}timer_pwm_set;
/* Private define ------------------------------------------------------------*/	
#define OV7251_RST_SCL_PIN          GPIO_Pin_10
#define OV7251_RST_SCL_GPIO_PORT    GPIOH
#define OV7251_RST_SCL_GPIO_CLK     SYSCTRL_APBPeriph_GPIO
#define OV7251_RST_SCL_REMAP        GPIO_Remap_1

#define OV7251_EnResetSensor()      {GPIO_ResetBits(OV7251_RST_SCL_GPIO_PORT, OV7251_RST_SCL_PIN);}
#define OV7251_DisResetSensor()     {GPIO_SetBits(OV7251_RST_SCL_GPIO_PORT, OV7251_RST_SCL_PIN);}
/* Private macro -------------------------------------------------------------*/	
/* Private variables ---------------------------------------------------------*/	
/* Ptivate function prototypes -----------------------------------------------*/
static void OV7251_GPIOConfig(void);
static bool OV7251_RegConfig(void);
static void OV7251_XCKConfig(void);
static void TimerPWMSetStructInit(void);
static void TIMER_Configuration(void);
/*******************************************************************************
* Function Name	: OV7251_Init
* Description	: 用于初始化OV7251相关的内容
* Input			: NONE
* Output		: NONE
* Return		: Status
*******************************************************************************/
bool OV7251_Init(void)
{
    /* SCCB Configuration */
    piSCCB->Init();
    /* Clock Enable：24MHz */
    OV7251_XCKConfig();
    /* DCMI&MIPI Configure */
    Image_Init();
    /* Sensor GPIO Config */
    OV7251_GPIOConfig();
    /* Sensor register Configuration */
    OV7251_RegConfig();
}

/*******************************************************************************
* Function Name	: OV7251_GPIOConfig
* Description	: 用于初始化OV7251摄像头用到的GPIO
* Input			: NONE  
* Output		: NONE
* Return		: NONE
*******************************************************************************/
static void OV7251_GPIOConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SYSCTRL_APBPeriphClockCmd(OV7251_RST_SCL_GPIO_CLK,  ENABLE);
    GPIO_InitStruct.GPIO_Pin = OV7251_RST_SCL_PIN;
	GPIO_InitStruct.GPIO_Remap = GPIO_Remap_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(OV7251_RST_SCL_GPIO_PORT,&GPIO_InitStruct);
}

/*******************************************************************************
* Function Name	: OV7251_RegConfig
* Description	: 用于配置OV7251的寄存器
* Input			: NONE  
* Output		: NONE
* Return		: Status: false：初始化失败；true:初始化成功；
*******************************************************************************/
static bool OV7251_RegConfig(void)
{
    uint8_t CHIP_ID_H;
	uint8_t CHIP_ID_L;
    uint8_t REG0C;
//    OV7251_EnResetSensor();
//    mdelay(1);
    OV7251_DisResetSensor();
    mdelay(100);            // 等待OV7251状态稳定
    if(piSCCB->AddrHalfWordReadByte(0x300A,&CHIP_ID_H) != 0)
     {
        #ifdef USE_SELFTEST_MODE
        set_cled_state(CLED_BLUE);       /* sensor Error */
        while (1);
        #endif
        printf("> Error at step 1");
        return false;
	 }
	 if(piSCCB->AddrHalfWordReadByte(0x300B,&CHIP_ID_L) != 0)
     {
        #ifdef USE_SELFTEST_MODE
        set_cled_state(CLED_BLUE);       /* sensor Error */
        while (1);
        #endif
        printf("> Error at step 2");
		return false;
	 }
     printf("> OV7251 ID is 0x%04x.\n",((CHIP_ID_H << 8)|CHIP_ID_L));
	 if(piSCCB->AddrHalfWordReadByte(0x300C,&REG0C) != 0)
     {
        #ifdef USE_SELFTEST_MODE
        set_cled_state(CLED_BLUE);       /* sensor Error */
        while (1);
        #endif
		return false;
	 }
     printf("> OV7251 Revision ID is 0x%02x.\n",REG0C);
////	 if(DCMI_SingleRandomRead_OV(0x3001,&temp0) != 0)
////		 return 0xff;
////	 
////	 if(DCMI_SingleRandomRead_OV(0x3d83,&temp1) != 0)
////		 return 0xff;
	if ((CHIP_ID_H == 0x77) && (CHIP_ID_L == 0x50) && (REG0C == 0xf0))
	{
        uint16_t i = 0;
		for(i = 0; i < OV7251_REG_NUM; i++)
		{
			if(piSCCB->AddrHalfWordWriteByte(OV7251_Sensor_Config[i].Address,OV7251_Sensor_Config[i].Value) != 0)
			{
//                #ifdef USE_SELFTEST_MODE
//                set_cled_state(CLED_BLUE);       /* sensor Error */
//                while (1);
//                #endif
                printf("> Write Error\n");
				return false;    
			}
//            if(piSCCB->AddrHalfWordReadByte(OV7251_Sensor_Config[i].Address,&REG0C) == 0){
//                if (REG0C != OV7251_Sensor_Config[i].Value){
//                    printf("> OV7251 Reg 0x%04x value is 0x%02x.\n",OV7251_Sensor_Config[i].Address,REG0C);
////                    return false;
//                }
//            }
		}
			
	}else{
        printf("> Sensor ID Check Error!\n");
    }  
    return true; 
}

/*******************************************************************************
* Function Name	: OV7251_RegConfig
* Description	: 用于配置OV7251的寄存器
* Input			: NONE  
* Output		: NONE
* Return		: Status: false：初始化失败；true:初始化成功；
*******************************************************************************/
timer_pwm_set timerPWMSet;
static void OV7251_XCKConfig(void)
{
    SYSCTRL_APBPeriphClockCmd(SYSCTRL_APBPeriph_TIMM0,ENABLE);
	SYSCTRL_APBPeriphResetCmd(SYSCTRL_APBPeriph_TIMM0,ENABLE);
    GPIO_PinRemapConfig(GPIOB, GPIO_Pin_12, GPIO_Remap_2);    						//PB12 pwm for sensor clk
	TimerPWMSetStructInit();
	TIMER_Configuration();
	TIM_Cmd(TIMM0, TIM_3, ENABLE);
}

static void TimerPWMSetStructInit(void)
{

	timerPWMSet.PWM_HZ = 24000000;//12000000;
	timerPWMSet.DutyCycleHighPluse = 1;
	timerPWMSet.DutyCycleLowPluse = 1;

	SYSCTRL_GetClocksFreq(&timerPWMSet.clocks);
    
    if(timerPWMSet.clocks.PCLK_Frequency < (timerPWMSet.PWM_HZ * 2))
    {
        printf("You set PWM frequency is %dHz.\n",timerPWMSet.PWM_HZ);
        printf("The highest frequency of PWM is PCLK_Frequency/2,is %dHz.\n",timerPWMSet.clocks.PCLK_Frequency / 2);
        while(1);
    }
}

static void TIMER_Configuration(void)
{
	uint32_t Period = 0;
	uint32_t DutyCyclePeriod = 0;
	
	Period = timerPWMSet.clocks.PCLK_Frequency / timerPWMSet.PWM_HZ;

	timerPWMSet.TIM_PWMSetStruct.TIM_LowLevelPeriod = (Period/2 - 1);
	timerPWMSet.TIM_PWMSetStruct.TIM_HighLevelPeriod = (Period - timerPWMSet.TIM_PWMSetStruct.TIM_LowLevelPeriod - 2);
    timerPWMSet.TIM_PWMSetStruct.TIMx = TIM_3;
    TIM_PWMInit(TIMM0, &timerPWMSet.TIM_PWMSetStruct);
}
/************************* (C) COPYRIGHT 2018 LOVE_ELEC ******END OF FILE******/