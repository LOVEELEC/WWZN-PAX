/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : si2c_delay.c
 * Author               : Megahuntmicro
 * Version              : V1.0.0
 * Date                 : 12/07/2015
 * Description          : Simulation I2C delay function file.
 *****************************************************************************/
 
/* Include ------------------------------------------------------------------*/
#include "si2c_delay.h"
#include "systick.h"
/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/	
/* Private macro ------------------------------------------------------------*/	
/* Private variables --------------------------------------------------------*/	
static uint8_t  fac_us = 0;//us延时倍乘数
static uint16_t fac_ms = 0;//ms延时倍乘数
/* Ptivate function prototypes ----------------------------------------------*/	

/******************************************************************************
* Function Name  : si2c_delay_init
* Description    : simulation i2c delay initialization function
* Input          : NONE
* Output         : NONE
* Return         : NONE
******************************************************************************/
void si2c_delay_init(uint8_t SYSCLK)
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
//	fac_us = SYSCLK / 8;		    
//	fac_ms = (uint16_t)fac_us * 1000;
    /* SysTick 时钟改为32K */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    /* 不使用Systick */
    fac_us = 2;
    /* 使用Systick */
    fac_ms = 32;
}

/******************************************************************************
* Function Name  : si2c_delay_ms
* Description    : simulation i2c delay ms function
* Input          : nms:delay time(unit:ms)
* Output         : NONE
* Return         : NONE
******************************************************************************/
void si2c_delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD = (uint32_t)nms * fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;           //清空计数器
	SysTick->CTRL = 0x01 ;          //开始倒数  
	do
	{
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));//等待时间到达   
	SysTick->CTRL = 0x00;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	  	    
}   

/******************************************************************************
* Function Name  : si2c_delay_us
* Description    : simulation i2c delay us function
* Input          : nus:delay time(unit:us)
* Output         : NONE
* Return         : NONE
******************************************************************************/		    								   
void si2c_delay_us(uint32_t nus)
{		
//	uint32_t temp;	    	 
//	SysTick->LOAD = nus * fac_us; //时间加载	  		 
//	SysTick->VAL = 0x00;        //清空计数器
//	SysTick->CTRL = 0x01 ;      //开始倒数 	 
//	do
//	{
//		temp = SysTick->CTRL;
//	}
//	while(temp & 0x01 && !(temp & (1 << 16)));//等待时间到达   
//	SysTick->CTRL = 0x00;       //关闭计数器
//	SysTick->VAL = 0X00;       //清空计数器	 
//    uint32_t temp;
//    for (temp = 0; temp < nus * fac_us; temp++)
//    {
//     __ASM{
//            nop;
//        }
//    }
    udelay(nus);
}

/************************ (C) COPYRIGHT 2015 Megahuntmicro ****END OF FILE****/
