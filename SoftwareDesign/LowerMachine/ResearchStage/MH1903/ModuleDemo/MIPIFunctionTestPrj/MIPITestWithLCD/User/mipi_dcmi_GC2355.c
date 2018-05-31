/**
  ******************************************************************************
  * @file    mipi_dcmi_GC310.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   This file includes the driver for GC310 Camera module mounted on 
  *          
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
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "mhscpu.h"
#include "mipi_dcmi_GC2355.h"
#include "dwc_mipi_csi.h"
#define I2C_GC_OR_START 10
#define I2C_SPECIAL   11

uint8_t DCMI_SingleRandomWrite(uint8_t Reg, uint8_t Data)
{
	uint32_t regTmp=0;
	regTmp = I2C0->IC_TAR;
	regTmp &= (~0x3FF);
	regTmp |= (GC2235MIPI_WRITE_ADDRESS>>1)|(1<<10)|(1<<11)|(1<<8); 
	I2C0->IC_TAR = regTmp;
	
	I2C0->IC_DATA_CMD = Reg;
	udelay(1000);
	I2C0->IC_DATA_CMD = Data|0x200;
	//I2C_SendData(I2C0, GC2235MIPI_WRITE_ADDRESS, I2C_DataEndCondition_Stop);
	//while (RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXE)));  //等到发送fifo空时开始一次传输	
	//I2C_SendData(I2C0, GC2235MIPI_WRITE_ADDRESS, I2C_DataEndCondition_None);
	//while (RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXNF)));
	//I2C_SendData(I2C0, Reg, I2C_DataEndCondition_None);
	//while (RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXNF)));
	//I2C_SendData(I2C0, Data, I2C_DataEndCondition_Stop);
	printf("I2C write reg! \r\n");
	//mdelay(1000);
}

uint8_t DCMI_SingleRandomRead(uint8_t Reg, uint8_t *Data)
{
	uint8_t tmpValue;
	printf("DCMI_SingleRandomRead1! \r\n");
	while(RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXE)));  //等到发送fifo空
	//I2C_SendData(I2C0, GC2235MIPI_READ_ADDRESS, I2C_DataEndCondition_None);
	//while(RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXNF)));
	printf("DCMI_SingleRandomRead2!\r\n");
	I2C_SendData(I2C0, Reg, I2C_DataEndCondition_None);
	while (RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXNF)));
	printf("DCMI_SingleRandomRead3!\r\n");
	I2C_SendData(I2C0, GC2235MIPI_READ_ADDRESS, I2C_DataEndCondition_None);
	while(RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXNF)));
	printf("DCMI_SingleRandomRead4!\r\n");
    /* 如果主接受多个数据则每个数据接受后发送ack，最后一个发nack */
	//while(RESET != I2C_GetFlagStatus(I2C0, I2C_FLAG_RXNE))
	{
		//I2C0->IC_DATA_CMD;	
	}
	printf("DCMI_SingleRandomRead5!\r\n");
	//while(RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXNF)));
	//printf("DCMI_SingleRandomRead6!\r\n");
	///tmpValue = I2C_ReceiveData(I2C0, I2C_DataEndCondition_Stop);
#if 1	
	if (I2C_Mode_Master == I2C_GetI2CMode(I2C0))
	{
		printf("DCMI_SingleRandomRead7!\r\n");
		while(RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_TXNF)));
		printf("DCMI_SingleRandomRead8!\r\n");
		I2C_MasterGenerateReceiveSCL(I2C0, I2C_DataEndCondition_Stop); // I2C_DataEndCondition_Stop
		printf("DCMI_SingleRandomRead9!\r\n");
		while(RESET == (I2C_GetFlagStatus(I2C0, I2C_FLAG_RXNE)));
		//while (RESET == I2C_GetFlagStatus(I2C0, I2C_FLAG_RXNE))
		{
			//I2C0->IC_DATA_CMD;	
		}
		printf("DCMI_SingleRandomRead10!\r\n");
		tmpValue = (uint8_t)I2C_ReadDataFromDR(I2C0);
		printf("DCMI_SingleRandomRead11!\r\n");
	}
#endif	
	printf("DCMI_SingleRandomRead12!\r\n");
	return tmpValue;	
}

void GC2355MIPI_write_cmos_sensor(uint8_t addr, uint8_t para)
{
  	DCMI_SingleRandomWrite(addr,para);
}

uint8_t GC2355MIPI_read_cmos_sensor(uint8_t addr)
{
	uint8_t get_byte=0;
	DCMI_SingleRandomRead(addr,&get_byte);
	return get_byte;
}

void GC2355_pwdn_and_reset_pin_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*
	S_PWDN 	PA5
	S_RESET	PA4
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Remap = GPIO_Remap_1;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);	
}

void  GC2355_pwdn_enable(void)
{
	/*
	S_PWDN 	PA5
	S_RESET	PA4
	*/
	//GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	//GPIO_SetBits(GPIOA, GPIO_Pin_5);
	mdelay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	mdelay(1000);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	mdelay(1000);
}

void  GC2355_pwdn_disable(void)
{
	/*data sheet 17p  power on*/
	/*
	S_PWDN 	PA5
	S_RESET	PA4
	*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	mdelay(30);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	mdelay(20);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}
#define GC2355MIPI_2Lane (1)
#define LOG_INF	printf

static void preview_setting(void)
{
	LOG_INF("E!\n");

  	//MIPI//
  	GC2355MIPI_write_cmos_sensor(0xfe,0x03);
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x10, 0x91);
#else
	GC2355MIPI_write_cmos_sensor(0x10, 0x90);
#endif
    GC2355MIPI_write_cmos_sensor(0xfe,0x00);	
	
}
static void capture_setting(uint16_t currefps)
{
	LOG_INF("E! currefps:%d\n",currefps);
	//MIPI//
	GC2355MIPI_write_cmos_sensor(0xfe,0x03);
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x10, 0x91);
#else
	GC2355MIPI_write_cmos_sensor(0x10, 0x90);
#endif
	GC2355MIPI_write_cmos_sensor(0xfe,0x00);
}

static void normal_video_setting(uint16_t currefps)
{
	LOG_INF("E! currefps:%d\n",currefps);
	 GC2355MIPI_write_cmos_sensor(0xfe,0x03);
 #if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x10, 0x91);
#else
	GC2355MIPI_write_cmos_sensor(0x10, 0x90);
#endif
	 GC2355MIPI_write_cmos_sensor(0xfe,0x00);
		
}
static void hs_video_setting(void)
{
    LOG_INF("E\n");
	
	GC2355MIPI_write_cmos_sensor(0xfe,0x03);
 #if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x10, 0x91);
#else
	GC2355MIPI_write_cmos_sensor(0x10, 0x90);
#endif
	GC2355MIPI_write_cmos_sensor(0xfe,0x00);

}
static void slim_video_setting(void)
{
    LOG_INF("E\n");
	
	GC2355MIPI_write_cmos_sensor(0xfe,0x03);
 #if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x10, 0x91);
#else
	GC2355MIPI_write_cmos_sensor(0x10, 0x90);
#endif
	GC2355MIPI_write_cmos_sensor(0xfe,0x00);
}
#if 0
void GC2355MIPI_Sensor_Init(void)

{
	//LOG_INF("E");
	/* SYS */
/////////////////////////////////////////////////////
	//////////////////////	 SYS   //////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xfe,0x80);
	GC2355MIPI_write_cmos_sensor(0xfe,0x80);
	GC2355MIPI_write_cmos_sensor(0xfe,0x80);
	GC2355MIPI_write_cmos_sensor(0xf2,0x00); 
	GC2355MIPI_write_cmos_sensor(0xf6,0x00); 
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0xf7,0x31); 
#else
	GC2355MIPI_write_cmos_sensor(0xf7,0x19); 
#endif
	GC2355MIPI_write_cmos_sensor(0xf8,0x06); 
	GC2355MIPI_write_cmos_sensor(0xf9,0x0e); 
	GC2355MIPI_write_cmos_sensor(0xfa,0x00); 
	GC2355MIPI_write_cmos_sensor(0xfc,0x06); 
	GC2355MIPI_write_cmos_sensor(0xfe,0x00);
	
	/////////////////////////////////////////////////////
	///////////////    ANALOG & CISCTL    ///////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x03,0x07); 
	GC2355MIPI_write_cmos_sensor(0x04,0xd0); 
	GC2355MIPI_write_cmos_sensor(0x05,0x03);
	GC2355MIPI_write_cmos_sensor(0x06,0x4c);
	GC2355MIPI_write_cmos_sensor(0x07,0x00);
	GC2355MIPI_write_cmos_sensor(0x08,0x12);
	GC2355MIPI_write_cmos_sensor(0x0a,0x00);
	GC2355MIPI_write_cmos_sensor(0x0c,0x04);
	GC2355MIPI_write_cmos_sensor(0x0d,0x04);
	GC2355MIPI_write_cmos_sensor(0x0e,0xc0);
	GC2355MIPI_write_cmos_sensor(0x0f,0x06);
	GC2355MIPI_write_cmos_sensor(0x10,0x50);
	GC2355MIPI_write_cmos_sensor(0x17,0x17);
	GC2355MIPI_write_cmos_sensor(0x19,0x0b);
	GC2355MIPI_write_cmos_sensor(0x1b,0x48);
	GC2355MIPI_write_cmos_sensor(0x1c,0x12);
	GC2355MIPI_write_cmos_sensor(0x1d,0x10);
	GC2355MIPI_write_cmos_sensor(0x1e,0xbc);
	GC2355MIPI_write_cmos_sensor(0x1f,0xc9);
	GC2355MIPI_write_cmos_sensor(0x20,0x71);
	GC2355MIPI_write_cmos_sensor(0x21,0x20);
	GC2355MIPI_write_cmos_sensor(0x22,0xa0);
	GC2355MIPI_write_cmos_sensor(0x23,0x51);
	GC2355MIPI_write_cmos_sensor(0x24,0x19);
	GC2355MIPI_write_cmos_sensor(0x27,0x20);
	GC2355MIPI_write_cmos_sensor(0x28,0x00);
	GC2355MIPI_write_cmos_sensor(0x2b,0x80);// 0x81 20140926
	GC2355MIPI_write_cmos_sensor(0x2c,0x38);
	GC2355MIPI_write_cmos_sensor(0x2e,0x16);
	GC2355MIPI_write_cmos_sensor(0x2f,0x14);
	GC2355MIPI_write_cmos_sensor(0x30,0x00);
	GC2355MIPI_write_cmos_sensor(0x31,0x01);
	GC2355MIPI_write_cmos_sensor(0x32,0x02);
	GC2355MIPI_write_cmos_sensor(0x33,0x03);
	GC2355MIPI_write_cmos_sensor(0x34,0x07);
	GC2355MIPI_write_cmos_sensor(0x35,0x0b);
	GC2355MIPI_write_cmos_sensor(0x36,0x0f);
	
    /////////////////////////////////////////////////////
	//////////////////////   MIPI   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xfe, 0x03);
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x01, 0x87);
	GC2355MIPI_write_cmos_sensor(0x22, 0x03);  
	GC2355MIPI_write_cmos_sensor(0x23, 0x20);
	GC2355MIPI_write_cmos_sensor(0x25, 0x10);
	GC2355MIPI_write_cmos_sensor(0x29, 0x02);
#else
	GC2355MIPI_write_cmos_sensor(0x01, 0x83);
	GC2355MIPI_write_cmos_sensor(0x22, 0x05);  
	GC2355MIPI_write_cmos_sensor(0x23, 0x30);
	GC2355MIPI_write_cmos_sensor(0x25, 0x15);
	GC2355MIPI_write_cmos_sensor(0x29, 0x06);
#endif
	GC2355MIPI_write_cmos_sensor(0x02, 0x11); // 00 20150522
	GC2355MIPI_write_cmos_sensor(0x03, 0x91); // 90 tarvis 20150611
	GC2355MIPI_write_cmos_sensor(0x04, 0x01);
	GC2355MIPI_write_cmos_sensor(0x05, 0x00);
	GC2355MIPI_write_cmos_sensor(0x06, 0xa2);
	GC2355MIPI_write_cmos_sensor(0x11, 0x2b);
	GC2355MIPI_write_cmos_sensor(0x12, 0xd0); 
	GC2355MIPI_write_cmos_sensor(0x13, 0x07); 
	GC2355MIPI_write_cmos_sensor(0x15, 0x60);

	GC2355MIPI_write_cmos_sensor(0x21, 0x10);
	GC2355MIPI_write_cmos_sensor(0x24, 0x02);
	GC2355MIPI_write_cmos_sensor(0x26, 0x08);
	GC2355MIPI_write_cmos_sensor(0x27, 0x06);
	GC2355MIPI_write_cmos_sensor(0x2a, 0x0a); 
	GC2355MIPI_write_cmos_sensor(0x2b, 0x08);
	
	GC2355MIPI_write_cmos_sensor(0x40, 0x00);
	GC2355MIPI_write_cmos_sensor(0x41, 0x00);    
	GC2355MIPI_write_cmos_sensor(0x42, 0x40);
	GC2355MIPI_write_cmos_sensor(0x43, 0x06);  
	GC2355MIPI_write_cmos_sensor(0xfe, 0x00);

	/////////////////////////////////////////////////////
	//////////////////////	 gain   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xb0,0x50);
	GC2355MIPI_write_cmos_sensor(0xb1,0x01);
	GC2355MIPI_write_cmos_sensor(0xb2,0x00);
	GC2355MIPI_write_cmos_sensor(0xb3,0x40);
	GC2355MIPI_write_cmos_sensor(0xb4,0x40);
	GC2355MIPI_write_cmos_sensor(0xb5,0x40);
	GC2355MIPI_write_cmos_sensor(0xb6,0x00);

	/////////////////////////////////////////////////////
	//////////////////////   crop   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x92,0x02);
	GC2355MIPI_write_cmos_sensor(0x94,0x00);
	GC2355MIPI_write_cmos_sensor(0x95,0x04);
	GC2355MIPI_write_cmos_sensor(0x96,0xb0);
	GC2355MIPI_write_cmos_sensor(0x97,0x06);
	GC2355MIPI_write_cmos_sensor(0x98,0x40); 

	/////////////////////////////////////////////////////
	//////////////////////    BLK   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x18,0x02);
	GC2355MIPI_write_cmos_sensor(0x1a,0x01);
	GC2355MIPI_write_cmos_sensor(0x40,0x42);
	GC2355MIPI_write_cmos_sensor(0x41,0x00); 
	GC2355MIPI_write_cmos_sensor(0x44,0x00); 
	GC2355MIPI_write_cmos_sensor(0x45,0x00);
	GC2355MIPI_write_cmos_sensor(0x46,0x00);	
	GC2355MIPI_write_cmos_sensor(0x47,0x00); 
	GC2355MIPI_write_cmos_sensor(0x48,0x00); 
	GC2355MIPI_write_cmos_sensor(0x49,0x00);
	GC2355MIPI_write_cmos_sensor(0x4a,0x00);	
	GC2355MIPI_write_cmos_sensor(0x4b,0x00);	
	GC2355MIPI_write_cmos_sensor(0x4e,0x3c); 
	GC2355MIPI_write_cmos_sensor(0x4f,0x00); 
	GC2355MIPI_write_cmos_sensor(0x5e,0x00);
	GC2355MIPI_write_cmos_sensor(0x66,0x20);
	GC2355MIPI_write_cmos_sensor(0x6a,0x02);
	GC2355MIPI_write_cmos_sensor(0x6b,0x02);
	GC2355MIPI_write_cmos_sensor(0x6c,0x02);
	GC2355MIPI_write_cmos_sensor(0x6d,0x02);
	GC2355MIPI_write_cmos_sensor(0x6e,0x02);
	GC2355MIPI_write_cmos_sensor(0x6f,0x02);
	GC2355MIPI_write_cmos_sensor(0x70,0x02);
	GC2355MIPI_write_cmos_sensor(0x71,0x02);

	/////////////////////////////////////////////////////
	////////////////////  dark sun  /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x87,0x03); 
	GC2355MIPI_write_cmos_sensor(0xe0,0xe7); 
	GC2355MIPI_write_cmos_sensor(0xe3,0xc0); 

	/////////////////////////////////////////////////////
	//////////////////////   MIPI   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xfe, 0x03);
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x10, 0x81);
#else
	GC2355MIPI_write_cmos_sensor(0x10, 0x80);
#endif
	GC2355MIPI_write_cmos_sensor(0xfe, 0x00);

	//preview_setting();
	//normal_video_setting(300);

	//hs_video_setting();
	//slim_video_setting();
	capture_setting(300);

}
#else

void GC2355MIPI_Sensor_Init(void)
{
#if 1
	//LOG_INF("E");
	/* SYS */
	/////////////////////////////////////////////////////
	//////////////////////	 SYS   //////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xfe,0x80);
	GC2355MIPI_write_cmos_sensor(0xfe,0x80);
	GC2355MIPI_write_cmos_sensor(0xfe,0x80);
	GC2355MIPI_write_cmos_sensor(0xf2,0x00); 
	GC2355MIPI_write_cmos_sensor(0xf6,0x00); 
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0xf7,0x31); 
#else
	GC2355MIPI_write_cmos_sensor(0xf7,0x19); 
#endif
	GC2355MIPI_write_cmos_sensor(0xf8,0x03); 
	GC2355MIPI_write_cmos_sensor(0xf9,0x0e); 
	GC2355MIPI_write_cmos_sensor(0xfa,0x00); 
#if 0	
	//GC2355MIPI_write_cmos_sensor(0xfa,0x11); //
	//GC2355MIPI_write_cmos_sensor(0xfd,0x22); //
#endif
	GC2355MIPI_write_cmos_sensor(0xfc,0x06); 
	GC2355MIPI_write_cmos_sensor(0xfe,0x00);
	
	/////////////////////////////////////////////////////
	///////////////    ANALOG & CISCTL    ///////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x03,0x07); 
	GC2355MIPI_write_cmos_sensor(0x04,0xd0); 
	GC2355MIPI_write_cmos_sensor(0x05,0x03);
	GC2355MIPI_write_cmos_sensor(0x06,0x4c);
	GC2355MIPI_write_cmos_sensor(0x07,0x00);
	GC2355MIPI_write_cmos_sensor(0x08,0x12);
	GC2355MIPI_write_cmos_sensor(0x0a,0x00);
	GC2355MIPI_write_cmos_sensor(0x0c,0x04);
#if 1	
	GC2355MIPI_write_cmos_sensor(0x0d,0x04);
	GC2355MIPI_write_cmos_sensor(0x0e,0xc0);
	GC2355MIPI_write_cmos_sensor(0x0f,0x06);
	GC2355MIPI_write_cmos_sensor(0x10,0x50);
#else
	GC2355MIPI_write_cmos_sensor(0x0d,0x01);
	GC2355MIPI_write_cmos_sensor(0x0e,0xe0);
	GC2355MIPI_write_cmos_sensor(0x0f,0x02);
	GC2355MIPI_write_cmos_sensor(0x10,0xf0);
#endif
	GC2355MIPI_write_cmos_sensor(0x17,0x17);
	GC2355MIPI_write_cmos_sensor(0x19,0x0b);
	GC2355MIPI_write_cmos_sensor(0x1b,0x48);
	GC2355MIPI_write_cmos_sensor(0x1c,0x12);
	GC2355MIPI_write_cmos_sensor(0x1d,0x10);
	GC2355MIPI_write_cmos_sensor(0x1e,0xbc);
	GC2355MIPI_write_cmos_sensor(0x1f,0xc9);
	GC2355MIPI_write_cmos_sensor(0x20,0x71);
	GC2355MIPI_write_cmos_sensor(0x21,0x20);
	GC2355MIPI_write_cmos_sensor(0x22,0xa0);
	GC2355MIPI_write_cmos_sensor(0x23,0x51);
	GC2355MIPI_write_cmos_sensor(0x24,0x19);
	GC2355MIPI_write_cmos_sensor(0x27,0x20);
	GC2355MIPI_write_cmos_sensor(0x28,0x00);
	GC2355MIPI_write_cmos_sensor(0x2b,0x80);// 0x81 20140926
	GC2355MIPI_write_cmos_sensor(0x2c,0x38);
	GC2355MIPI_write_cmos_sensor(0x2e,0x16);
	GC2355MIPI_write_cmos_sensor(0x2f,0x14);
	GC2355MIPI_write_cmos_sensor(0x30,0x00);
	GC2355MIPI_write_cmos_sensor(0x31,0x01);
	GC2355MIPI_write_cmos_sensor(0x32,0x02);
	GC2355MIPI_write_cmos_sensor(0x33,0x03);
	GC2355MIPI_write_cmos_sensor(0x34,0x07);
	GC2355MIPI_write_cmos_sensor(0x35,0x0b);
	GC2355MIPI_write_cmos_sensor(0x36,0x0f);
	
    /////////////////////////////////////////////////////
	//////////////////////   MIPI   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xfe, 0x03);
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x01, 0x87);
	GC2355MIPI_write_cmos_sensor(0x22, 0x03);  
	GC2355MIPI_write_cmos_sensor(0x23, 0x20);
	GC2355MIPI_write_cmos_sensor(0x25, 0x10);
	GC2355MIPI_write_cmos_sensor(0x29, 0x02);
#else
	GC2355MIPI_write_cmos_sensor(0x01, 0x83);
	GC2355MIPI_write_cmos_sensor(0x22, 0x05);  
	GC2355MIPI_write_cmos_sensor(0x23, 0x30);
	GC2355MIPI_write_cmos_sensor(0x25, 0x15);
	GC2355MIPI_write_cmos_sensor(0x29, 0x06);
#endif
	GC2355MIPI_write_cmos_sensor(0x02, 0x00);
	GC2355MIPI_write_cmos_sensor(0x03, 0x90);
	GC2355MIPI_write_cmos_sensor(0x04, 0x01);
	GC2355MIPI_write_cmos_sensor(0x05, 0x00);
	GC2355MIPI_write_cmos_sensor(0x06, 0xa2);
	GC2355MIPI_write_cmos_sensor(0x11, 0x2b);
	GC2355MIPI_write_cmos_sensor(0x12, 0xd0); 
	GC2355MIPI_write_cmos_sensor(0x13, 0x07); 
	GC2355MIPI_write_cmos_sensor(0x15, 0x60);

	GC2355MIPI_write_cmos_sensor(0x21, 0x10);
	GC2355MIPI_write_cmos_sensor(0x24, 0x02);
	GC2355MIPI_write_cmos_sensor(0x26, 0x08);
	GC2355MIPI_write_cmos_sensor(0x27, 0x06);
	GC2355MIPI_write_cmos_sensor(0x2a, 0x0a); 
	GC2355MIPI_write_cmos_sensor(0x2b, 0x08);
	
	GC2355MIPI_write_cmos_sensor(0x40, 0x00);
	GC2355MIPI_write_cmos_sensor(0x41, 0x00);    
	GC2355MIPI_write_cmos_sensor(0x42, 0x40);
	GC2355MIPI_write_cmos_sensor(0x43, 0x06);  
	GC2355MIPI_write_cmos_sensor(0xfe, 0x00);

	/////////////////////////////////////////////////////
	//////////////////////	 gain   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xb0,0x50);
	GC2355MIPI_write_cmos_sensor(0xb1,0x01);
	GC2355MIPI_write_cmos_sensor(0xb2,0x00);
	GC2355MIPI_write_cmos_sensor(0xb3,0x40);
	GC2355MIPI_write_cmos_sensor(0xb4,0x40);
	GC2355MIPI_write_cmos_sensor(0xb5,0x40);
	GC2355MIPI_write_cmos_sensor(0xb6,0x00);

	/////////////////////////////////////////////////////
	//////////////////////   crop   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x92,0x02);
	GC2355MIPI_write_cmos_sensor(0x94,0x00);
	GC2355MIPI_write_cmos_sensor(0x95,0x04);
	GC2355MIPI_write_cmos_sensor(0x96,0xb0);
	GC2355MIPI_write_cmos_sensor(0x97,0x06);
	GC2355MIPI_write_cmos_sensor(0x98,0x40); 

	/////////////////////////////////////////////////////
	//////////////////////    BLK   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x18,0x02);
	GC2355MIPI_write_cmos_sensor(0x1a,0x01);
	GC2355MIPI_write_cmos_sensor(0x40,0x42);
	GC2355MIPI_write_cmos_sensor(0x41,0x00); 
	GC2355MIPI_write_cmos_sensor(0x44,0x00); 
	GC2355MIPI_write_cmos_sensor(0x45,0x00);
	GC2355MIPI_write_cmos_sensor(0x46,0x00);	
	GC2355MIPI_write_cmos_sensor(0x47,0x00); 
	GC2355MIPI_write_cmos_sensor(0x48,0x00); 
	GC2355MIPI_write_cmos_sensor(0x49,0x00);
	GC2355MIPI_write_cmos_sensor(0x4a,0x00);	
	GC2355MIPI_write_cmos_sensor(0x4b,0x00);	
	GC2355MIPI_write_cmos_sensor(0x4e,0x3c); 
	GC2355MIPI_write_cmos_sensor(0x4f,0x00); 
	GC2355MIPI_write_cmos_sensor(0x5e,0x00);
	GC2355MIPI_write_cmos_sensor(0x66,0x20);
	GC2355MIPI_write_cmos_sensor(0x6a,0x02);
	GC2355MIPI_write_cmos_sensor(0x6b,0x02);
	GC2355MIPI_write_cmos_sensor(0x6c,0x02);
	GC2355MIPI_write_cmos_sensor(0x6d,0x02);
	GC2355MIPI_write_cmos_sensor(0x6e,0x02);
	GC2355MIPI_write_cmos_sensor(0x6f,0x02);
	GC2355MIPI_write_cmos_sensor(0x70,0x02);
	GC2355MIPI_write_cmos_sensor(0x71,0x02);

	/////////////////////////////////////////////////////
	////////////////////  dark sun  /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0x87,0x03); 
	GC2355MIPI_write_cmos_sensor(0xe0,0xe7); 
	GC2355MIPI_write_cmos_sensor(0xe3,0xc0); 

	/////////////////////////////////////////////////////
	//////////////////////   MIPI   /////////////////////
	/////////////////////////////////////////////////////
	GC2355MIPI_write_cmos_sensor(0xfe, 0x03);
#if defined(GC2355MIPI_2Lane)
	GC2355MIPI_write_cmos_sensor(0x10, 0x81);
#else
	GC2355MIPI_write_cmos_sensor(0x10, 0x80);
#endif
	GC2355MIPI_write_cmos_sensor(0xfe, 0x00);

	//preview_setting();
	//normal_video_setting(300);

	//hs_video_setting();
	//slim_video_setting();
	capture_setting(300);
#else
GC2355MIPI_write_cmos_sensor(0xfe,0x80);
GC2355MIPI_write_cmos_sensor(0xfe,0x80);
GC2355MIPI_write_cmos_sensor(0xfe,0x80);
GC2355MIPI_write_cmos_sensor(0xf2,0x00);
GC2355MIPI_write_cmos_sensor(0xf6,0x00);      
GC2355MIPI_write_cmos_sensor(0xf7,0x33);         
GC2355MIPI_write_cmos_sensor(0xf8,0x04);
GC2355MIPI_write_cmos_sensor(0xf9,0x0e);
GC2355MIPI_write_cmos_sensor(0xfa,0x00);
GC2355MIPI_write_cmos_sensor(0xfc,0x06);
GC2355MIPI_write_cmos_sensor(0xfe,0x00);        
GC2355MIPI_write_cmos_sensor(0x03,0x07);
GC2355MIPI_write_cmos_sensor(0x04,0xd0);
GC2355MIPI_write_cmos_sensor(0x05,0x03);
GC2355MIPI_write_cmos_sensor(0x06,0x4c);
GC2355MIPI_write_cmos_sensor(0x07,0x00);
GC2355MIPI_write_cmos_sensor(0x08,0x12);
GC2355MIPI_write_cmos_sensor(0x0a,0x00);
GC2355MIPI_write_cmos_sensor(0x0c,0x04);
GC2355MIPI_write_cmos_sensor(0x0d,0x04);
GC2355MIPI_write_cmos_sensor(0x0e,0xc0);
GC2355MIPI_write_cmos_sensor(0x0f,0x06);
GC2355MIPI_write_cmos_sensor(0x10,0x50);
GC2355MIPI_write_cmos_sensor(0x17,0x17);
GC2355MIPI_write_cmos_sensor(0x19,0x0b);
GC2355MIPI_write_cmos_sensor(0x1b,0x48);
GC2355MIPI_write_cmos_sensor(0x1c,0x12);
GC2355MIPI_write_cmos_sensor(0x1d,0x10);
GC2355MIPI_write_cmos_sensor(0x1e,0xbc);
GC2355MIPI_write_cmos_sensor(0x1f,0xc9);
GC2355MIPI_write_cmos_sensor(0x20,0x71);
GC2355MIPI_write_cmos_sensor(0x21,0x20);
GC2355MIPI_write_cmos_sensor(0x22,0xa0);
GC2355MIPI_write_cmos_sensor(0x23,0x51);
GC2355MIPI_write_cmos_sensor(0x24,0x19);
GC2355MIPI_write_cmos_sensor(0x27,0x20);
GC2355MIPI_write_cmos_sensor(0x28,0x00);
GC2355MIPI_write_cmos_sensor(0x2b,0x80);
GC2355MIPI_write_cmos_sensor(0x2c,0x38);
GC2355MIPI_write_cmos_sensor(0x2e,0x16);
GC2355MIPI_write_cmos_sensor(0x2f,0x14);
GC2355MIPI_write_cmos_sensor(0x30,0x00);
GC2355MIPI_write_cmos_sensor(0x31,0x01);
GC2355MIPI_write_cmos_sensor(0x32,0x02);
GC2355MIPI_write_cmos_sensor(0x33,0x03);
GC2355MIPI_write_cmos_sensor(0x34,0x07);
GC2355MIPI_write_cmos_sensor(0x35,0x0b);
GC2355MIPI_write_cmos_sensor(0x36,0x0f);
GC2355MIPI_write_cmos_sensor(0xfe,0x03);
GC2355MIPI_write_cmos_sensor(0x01,0x87);
GC2355MIPI_write_cmos_sensor(0x02,0x00);
GC2355MIPI_write_cmos_sensor(0x03,0x90);
GC2355MIPI_write_cmos_sensor(0x04,0x01);
GC2355MIPI_write_cmos_sensor(0x05,0x00);
GC2355MIPI_write_cmos_sensor(0x06,0xa2);
GC2355MIPI_write_cmos_sensor(0x10,0x81);
GC2355MIPI_write_cmos_sensor(0x11,0x2b);
GC2355MIPI_write_cmos_sensor(0x12,0xd0);
GC2355MIPI_write_cmos_sensor(0x13,0x07);
GC2355MIPI_write_cmos_sensor(0x15,0x60);      
GC2355MIPI_write_cmos_sensor(0x21,0x10);
GC2355MIPI_write_cmos_sensor(0x22,0x03);
GC2355MIPI_write_cmos_sensor(0x23,0x20);
GC2355MIPI_write_cmos_sensor(0x24,0x02);
GC2355MIPI_write_cmos_sensor(0x25,0x10);
GC2355MIPI_write_cmos_sensor(0x26,0x08);
GC2355MIPI_write_cmos_sensor(0x27,0x06);
GC2355MIPI_write_cmos_sensor(0x29,0x02);
GC2355MIPI_write_cmos_sensor(0x2a,0x0a);
GC2355MIPI_write_cmos_sensor(0x2b,0x08);     
GC2355MIPI_write_cmos_sensor(0x40,0x00);
GC2355MIPI_write_cmos_sensor(0x41,0x00);
GC2355MIPI_write_cmos_sensor(0x42,0x40);
GC2355MIPI_write_cmos_sensor(0x43,0x06);
GC2355MIPI_write_cmos_sensor(0xfe,0x00);
GC2355MIPI_write_cmos_sensor(0xb0,0x50);
GC2355MIPI_write_cmos_sensor(0xb1,0x01);
GC2355MIPI_write_cmos_sensor(0xb2,0x00);
GC2355MIPI_write_cmos_sensor(0xb3,0x40);
GC2355MIPI_write_cmos_sensor(0xb4,0x40);
GC2355MIPI_write_cmos_sensor(0xb5,0x40);
GC2355MIPI_write_cmos_sensor(0xb6,0x00);
GC2355MIPI_write_cmos_sensor(0x92,0x02);
GC2355MIPI_write_cmos_sensor(0x94,0x00);
GC2355MIPI_write_cmos_sensor(0x95,0x04);
GC2355MIPI_write_cmos_sensor(0x96,0xb0);
GC2355MIPI_write_cmos_sensor(0x97,0x06);
GC2355MIPI_write_cmos_sensor(0x98,0x40);
GC2355MIPI_write_cmos_sensor(0x18,0x02);
GC2355MIPI_write_cmos_sensor(0x1a,0x01);
GC2355MIPI_write_cmos_sensor(0x40,0x42);
GC2355MIPI_write_cmos_sensor(0x41,0x00);
GC2355MIPI_write_cmos_sensor(0x44,0x00);
GC2355MIPI_write_cmos_sensor(0x45,0x00);
GC2355MIPI_write_cmos_sensor(0x46,0x00);
GC2355MIPI_write_cmos_sensor(0x47,0x00);
GC2355MIPI_write_cmos_sensor(0x48,0x00);
GC2355MIPI_write_cmos_sensor(0x49,0x00);
GC2355MIPI_write_cmos_sensor(0x4a,0x00);
GC2355MIPI_write_cmos_sensor(0x4b,0x00);
GC2355MIPI_write_cmos_sensor(0x4e,0x3c);
GC2355MIPI_write_cmos_sensor(0x4f,0x00);
GC2355MIPI_write_cmos_sensor(0x5e,0x00);
GC2355MIPI_write_cmos_sensor(0x66,0x20);
GC2355MIPI_write_cmos_sensor(0x6a,0x02);
GC2355MIPI_write_cmos_sensor(0x6b,0x02);
GC2355MIPI_write_cmos_sensor(0x6c,0x02);
GC2355MIPI_write_cmos_sensor(0x6d,0x02);
GC2355MIPI_write_cmos_sensor(0x6e,0x02);
GC2355MIPI_write_cmos_sensor(0x6f,0x02);
GC2355MIPI_write_cmos_sensor(0x70,0x02);
GC2355MIPI_write_cmos_sensor(0x71,0x02);
GC2355MIPI_write_cmos_sensor(0x87,0x03);
GC2355MIPI_write_cmos_sensor(0xe0,0xe7);
GC2355MIPI_write_cmos_sensor(0xe3,0xc0);
GC2355MIPI_write_cmos_sensor(0xfe,0x03);
GC2355MIPI_write_cmos_sensor(0x10,0x91);
GC2355MIPI_write_cmos_sensor(0xfe,0x00);
#endif

}
#endif
void GC2355MIPI_Sensor_DeInit(void)
{
	/*data sheet 17p  power on*/
	/*
	S_PWDN 	PA5
	S_RESET	PA4
	*/
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
}
uint32_t GC2355MIPIOpenCheck(void)
{
	uint32_t i;
	uint16_t sensor_id=0;
	uint8_t data;

	//  Read sensor ID to adjust I2C is OK?
	for(i=0;i<3;i++)
	{
		sensor_id = ((GC2355MIPI_read_cmos_sensor(0xf0) << 8) | GC2355MIPI_read_cmos_sensor(0xf1));
		if(sensor_id != GC2355MIPI_SENSOR_ID)  
		{
			printf("GC2355MIPI Read Sensor ID Fail[open] = 0x%x\r\n", sensor_id); 
			return -1;
		}
	}
	printf("GC2355MIPI Read Sensor ID = 0x%x\r\n", sensor_id); 
	data =GC2355MIPI_read_cmos_sensor(0xfa);
	printf("GC2355MIPI 0xfa = 0x%x\r\n", data); 
	data =GC2355MIPI_read_cmos_sensor(0xfd);
	printf("GC2355MIPI 0xfd = 0x%x\r\n", data); 
	data =GC2355MIPI_read_cmos_sensor(0x13);
	printf("GC2355MIPI 0x13 = 0x%x\r\n", data); 
	data =GC2355MIPI_read_cmos_sensor(0x14);
	printf("GC2355MIPI 0x14 = 0x%x\r\n", data); 

	data =GC2355MIPI_read_cmos_sensor(0x11);
	printf("GC2355MIPI 0x11 = 0x%x\r\n", data); 
	data =GC2355MIPI_read_cmos_sensor(0x12);
	printf("GC2355MIPI 0x12 = 0x%x\r\n", data); 
	return 0;
}
