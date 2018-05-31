/**
  ******************************************************************************
  * @file    Sensor_SCCB.c
  * @author  LOVE_ELEC
  * @version V1.0.0
  * @date    18-Januery-2018
  * @brief   Camera Sensor SCCB interface definition.
  ******************************************************************************
  */
  

/* Includes ------------------------------------------------------------------*/
#include "Sensor_SCCB.h"
#ifdef USE_SIMULATON_I2C
#include "simulation_i2c.h"
#endif
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/	


#ifdef USE_STM32_I2C
#define I2C_SLAVE_ADDRESS7                      0x30
 /* Configure I2C1 pins: PB10->SIOC and PB11->SIOD */ 
#define Open207V_SCCB                        	I2C2
#define Open207V_SCCB_CLK                    	RCC_APB1Periph_I2C2

#define Open207V_SCCB_SDA_PIN                 	GPIO_Pin_12
#define Open207V_SCCB_SDA_GPIO_PORT           	GPIOC
#define Open207V_SCCB_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOC
#define Open207V_SCCB_SDA_SOURCE              	GPIO_PinSource12
#define Open207V_SCCB_SDA_AF                  	GPIO_AF_I2C2

#define Open207V_SCCB_SCL_PIN                 	GPIO_Pin_10
#define Open207V_SCCB_SCL_GPIO_PORT           	GPIOB
#define Open207V_SCCB_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOB
#define Open207V_SCCB_SCL_SOURCE              	GPIO_PinSource10
#define Open207V_SCCB_SCL_AF                  	GPIO_AF_I2C2
#endif

#ifdef USE_MH1903_I2C
#define I2C_SLAVE_ADDRESS7                      0x55
#define MH1903_SCCB                             I2C0
#define MH1903_SCCB_CLK                         SYSCTRL_APBPeriph_I2C0

#define MH1903_SCCB_SDA_PIN                 	GPIO_Pin_1
#define MH1903_SCCB_SDA_GPIO_PORT           	GPIOB
#define MH1903_SCCB_SDA_GPIO_CLK            	SYSCTRL_APBPeriph_GPIO
#define MH1903_SCCB_SDA_REMAP              	    GPIO_Remap_0

#define MH1903_SCCB_SCL_PIN                 	GPIO_Pin_0
#define MH1903_SCCB_SCL_GPIO_PORT           	GPIOB
#define MH1903_SCCB_SCL_GPIO_CLK            	SYSCTRL_APBPeriph_GPIO
#define MH1903_SCCB_SCL_REMAP              	    GPIO_Remap_0
#endif
/* Private macro -------------------------------------------------------------*/	
/* Private variables ---------------------------------------------------------*/	
/* Ptivate function prototypes -----------------------------------------------*/
static bool SCCB_Init(void);
static void SCCB_GPIO_Config(void);
static void SCCB_Peripherals_Config(void);
static uint8_t SCCB_AddrByteWriteByte(uint8_t RegAdr, uint8_t Data);
static uint8_t SCCB_AddrByteReadByte(uint8_t RegAdr, uint8_t *pData);
static uint8_t SCCB_AddrByteWriteHalfWord(uint8_t RegAdr, uint16_t Data);
static uint8_t SCCB_AddrByteReadHalfWord(uint8_t RegAdr, uint16_t *pData);
static uint8_t SCCB_AddrHalfWordWriteByte(uint16_t RegAdr, uint8_t Data);
static uint8_t SCCB_AddrHalfWordReadByte(uint16_t RegAdr, uint8_t *pData);
static uint8_t SCCB_AddrHalfWordWriteHalfWord(uint16_t RegAdr, uint16_t Data);
static uint8_t SCCB_AddrHalfWordReadHalfWord(uint16_t RegAdr, uint16_t *pData);


static iSCCB_Struct iSCCB = {
    SCCB_Init,
    SCCB_AddrByteWriteByte,
    SCCB_AddrByteReadByte,
    SCCB_AddrByteWriteHalfWord,
    SCCB_AddrByteReadHalfWord,
    SCCB_AddrHalfWordWriteByte,
    SCCB_AddrHalfWordReadByte,
    SCCB_AddrHalfWordWriteHalfWord,
    SCCB_AddrHalfWordReadHalfWord
};


piSCCB_Struct piSCCB = &iSCCB;

/*******************************************************************************
* Function Name	: SCCB_Init
* Description	: 用于SCCB Interface的初始化
* Input			: NONE
* Output		: NONE
* Return		: STATUE：false:初始化失败；true:初始化成功；
*******************************************************************************/
static bool SCCB_Init(void)
{
    bool ret = true;
    /* 时钟使能GPIO 配置 */
    SCCB_GPIO_Config();
    /* I2C 模块配置 */
    SCCB_Peripherals_Config();
    return ret;
}


#ifdef USE_STM32_I2C
/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 用于配置SCCB所用接口对应的GPIO
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void SCCB_GPIO_Config(void)
{
    uint16_t temp;
	I2C_InitTypeDef  SCCB_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 
	
	RCC_AHB1PeriphClockCmd(Open207V_SCCB_SDA_GPIO_CLK | Open207V_SCCB_SCL_GPIO_CLK,ENABLE);
	
	RCC_APB1PeriphClockCmd(Open207V_SCCB_CLK,ENABLE);

    GPIO_PinAFConfig(Open207V_SCCB_SDA_GPIO_PORT, Open207V_SCCB_SDA_SOURCE, Open207V_SCCB_SDA_AF);
	GPIO_PinAFConfig(Open207V_SCCB_SCL_GPIO_PORT, Open207V_SCCB_SCL_SOURCE, Open207V_SCCB_SCL_AF);
    
    GPIO_InitStructure.GPIO_Pin =  Open207V_SCCB_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Open207V_SCCB_SDA_GPIO_PORT, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin =  Open207V_SCCB_SCL_PIN;
	GPIO_Init(Open207V_SCCB_SCL_GPIO_PORT, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : SCCB_Peripherals_Config
* Description    : 用于配置SCCB所用外设
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void SCCB_Peripherals_Config(void)
{
    I2C_DeInit(Open207V_SCCB);
	SCCB_InitStructure.I2C_Mode = I2C_Mode_I2C;
	SCCB_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	SCCB_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS7;
	SCCB_InitStructure.I2C_Ack = I2C_Ack_Enable;
	SCCB_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	SCCB_InitStructure.I2C_ClockSpeed = SCCB_SPEED;
	
	I2C_Cmd(Open207V_SCCB, ENABLE);
	I2C_Init(Open207V_SCCB, &SCCB_InitStructure);
	
	I2C_AcknowledgeConfig(Open207V_SCCB, ENABLE);	
    
    ORIG_MCO1_Init();
}



/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Device: OV7670 write address.
  * @param  Addr: OV7670 register address. 
  * @param  Data: data to be written to the specific register 
  * @retval 0x00 if write operation is OK. 
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
static uint8_t DCMI_SingleRandomWrite(uint8_t Reg, uint8_t Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, DEVICE_WRITE_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
  I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send Data */
  I2C_SendData(Open207V_SCCB, Data);    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 STOP Condition */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);
  
  /* If operation is OK, return 0 */
  return 0;
}

/**
  * @brief  Writes a WORD at a specific Camera register
  * @param  Device: MT9V034 write address.
  * @param  Addr: MT9V034 register address. 
  * @param  Data: data to be written to the specific register 
  * @retval 0x00 if write operation is OK. 
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
static uint8_t SCCB_WriteWord(uint8_t Reg, uint16_t Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, DEVICE_WRITE_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
  I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send Data WORD */
  I2C_SendData(Open207V_SCCB, ((Data >> 8) & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
	I2C_SendData(Open207V_SCCB, (Data & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 STOP Condition */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);
  
  /* If operation is OK, return 0 */
  return 0;
}


/**
  * @brief  Reads a byte from a specific Camera register 
  * @param  Device: OV7670 write address.
  * @param  Addr: OV7670 register address. 
  * @retval data read from the specific register or 0xFF if timeout condition 
  *         occured. 
  */
static uint8_t DCMI_SingleRandomRead(uint8_t Reg, uint8_t *Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;

    /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
  I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);

  /*-----------------------------------------------------------------------------------*/
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);
  
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, DEVICE_READ_ADDRESS, I2C_Direction_Receiver);
   
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
      
  /*-----------------------------------------------------------------------------------*/
  /* Prepare an NACK for the next data received */
  I2C_AcknowledgeConfig(Open207V_SCCB, DISABLE);

  /* Test on Open207V_SCCB EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE); 

  /*-----------------------------------------------------------------------------------*/
  /* Receive the Data */
  *Data = I2C_ReceiveData(Open207V_SCCB);
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* return the read data */
  return 0;
}

/**
  * @brief  Reads a WORD from a specific Camera register 
  * @param  Device: MT9V034 write address.
  * @param  Addr: MT9V034 register address. 
  * @retval data read from the specific register or 0xFF if timeout condition 
  *         occured. 
  */
static uint8_t SCCB_ReadWord(uint8_t Reg, uint16_t *Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;

    /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
  I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);

  /*-----------------------------------------------------------------------------------*/
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);
  
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, DEVICE_READ_ADDRESS, I2C_Direction_Receiver);
   
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
      
  /*-----------------------------------------------------------------------------------*/
	 /* Prepare an ACK for the next data received */
  I2C_AcknowledgeConfig(Open207V_SCCB, ENABLE);

  /* Test on Open207V_SCCB EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
	/* Receive the Data */
  *Data = I2C_ReceiveData(Open207V_SCCB) << 8;
	/*-----------------------------------------------------------------------------------*/
	 /* Prepare an NACK for the next data received */
  I2C_AcknowledgeConfig(Open207V_SCCB, DISABLE);

  /* Test on Open207V_SCCB EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE); 

  /*-----------------------------------------------------------------------------------*/
  /* Receive the Data */
  *Data |= I2C_ReceiveData(Open207V_SCCB);
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* return the read data */
  return 0;
}

static uint8_t DCMI_SingleRandomRead_MIPI(uint16_t Reg, uint16_t *Data)
{
 uint32_t timeout = DCMI_TIMEOUT_MAX;

    /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, MIPI_DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
//  I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));
	/*-----------------------------------------------------------------------------------*/
	 /* Send Data WORD */
  I2C_SendData(Open207V_SCCB, ((Reg >> 8) & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
	I2C_SendData(Open207V_SCCB, (Reg & 0x00FF));  
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/	
  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);

  /*-----------------------------------------------------------------------------------*/
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);
  
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, MIPI_DEVICE_READ_ADDRESS, I2C_Direction_Receiver);
   
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
      
  /*-----------------------------------------------------------------------------------*/
	 /* Prepare an ACK for the next data received */
  I2C_AcknowledgeConfig(Open207V_SCCB, ENABLE);

  /* Test on Open207V_SCCB EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
	/* Receive the Data */
  *Data = I2C_ReceiveData(Open207V_SCCB) << 8;
	/*-----------------------------------------------------------------------------------*/
	 /* Prepare an NACK for the next data received */
  I2C_AcknowledgeConfig(Open207V_SCCB, DISABLE);

  /* Test on Open207V_SCCB EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE); 

  /*-----------------------------------------------------------------------------------*/
  /* Receive the Data */
  *Data |= I2C_ReceiveData(Open207V_SCCB);
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* return the read data */
  return 0;
}

static uint8_t SCCB_WriteWord_MIPI(uint16_t Reg, uint16_t Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, MIPI_DEVICE_WRITE_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
//  I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));
/*-----------------------------------------------------------------------------------*/
	 /* Send Data WORD */
  I2C_SendData(Open207V_SCCB, ((Reg >> 8) & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
	I2C_SendData(Open207V_SCCB, (Reg & 0x00FF));  
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/	
  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send Data WORD */
  I2C_SendData(Open207V_SCCB, ((Data >> 8) & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
	I2C_SendData(Open207V_SCCB, (Data & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 STOP Condition */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);
  
  /* If operation is OK, return 0 */
  return 0;
}

static uint8_t DCMI_SingleRandomRead_OV(uint16_t Reg, uint8_t *Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;

    /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, OV6710_DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
   /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
 // I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));
/*-----------------------------------------------------------------------------------*/
	 /* Send Data WORD */
  I2C_SendData(Open207V_SCCB, ((Reg >> 8) & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
	I2C_SendData(Open207V_SCCB, (Reg & 0x00FF));  
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/	
	
  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);

  /*-----------------------------------------------------------------------------------*/
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);
  
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, OV6710_DEVICE_READ_ADDRESS, I2C_Direction_Receiver);
   
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
      
  /*-----------------------------------------------------------------------------------*/
  /* Prepare an NACK for the next data received */
  I2C_AcknowledgeConfig(Open207V_SCCB, DISABLE);

  /* Test on Open207V_SCCB EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE); 

  /*-----------------------------------------------------------------------------------*/
  /* Receive the Data */
  *Data = I2C_ReceiveData(Open207V_SCCB);
  /* Clear AF flag if arised */
  I2C2->SR1 |= (uint16_t)0x0400;

  /* return the read data */
  return 0;
}

static uint8_t SCCB_WriteWord_OV(uint16_t Reg, uint8_t Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  
  /* Generate the Start Condition */
  I2C_GenerateSTART(Open207V_SCCB, ENABLE);

  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(Open207V_SCCB, OV6710_DEVICE_WRITE_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
//  I2C_SendData(Open207V_SCCB, (uint8_t)(Reg));
/*-----------------------------------------------------------------------------------*/
	 /* Send Data WORD */
  I2C_SendData(Open207V_SCCB, ((Reg >> 8) & 0x00FF));    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
	I2C_SendData(Open207V_SCCB, (Reg & 0x00FF));  
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/	
  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   /*-----------------------------------------------------------------------------------*/
  
	I2C_SendData(Open207V_SCCB, Data);    

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(Open207V_SCCB, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
   /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 STOP Condition */
  I2C_GenerateSTOP(Open207V_SCCB, ENABLE);
  
  /* If operation is OK, return 0 */
  return 0;
}

#endif


#ifdef USE_MH1903_I2C
/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 用于配置SCCB所用接口对应的GPIO
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void SCCB_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SYSCTRL_APBPeriphClockCmd(MH1903_SCCB_SDA_GPIO_CLK | MH1903_SCCB_SCL_GPIO_CLK,  ENABLE);
    SYSCTRL_APBPeriphClockCmd(MH1903_SCCB_CLK, ENABLE);
	SYSCTRL_APBPeriphResetCmd(MH1903_SCCB_CLK, ENABLE);
    GPIO_PinRemapConfig(MH1903_SCCB_SDA_GPIO_PORT, MH1903_SCCB_SDA_PIN, MH1903_SCCB_SDA_REMAP);
    GPIO_PinRemapConfig(MH1903_SCCB_SCL_GPIO_PORT, MH1903_SCCB_SCL_PIN, MH1903_SCCB_SCL_REMAP);
    
//    GPIO_InitStruct.GPIO_Pin = MH1903_SCCB_SDA_PIN | MH1903_SCCB_SCL_PIN;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStruct.GPIO_Remap = MH1903_SCCB_SCL_REMAP;
//    GPIO_Init(MH1903_SCCB_SDA_GPIO_PORT,&GPIO_InitStruct);
}

/*******************************************************************************
* Function Name  : SCCB_Peripherals_Config
* Description    : 用于配置SCCB所用外设
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void SCCB_Peripherals_Config(void)
{
    I2C_InitTypeDef I2C_InitStruct;
	SYSCTRL_ClocksTypeDef clocks;
	uint32_t tempReg=0;
	
	memset(&I2C_InitStruct,0x0,sizeof(I2C_InitTypeDef));
//	I2C_StructInit(&I2C_InitStruct);
	SYSCTRL_GetClocksFreq(&clocks);
	I2C_InitStruct.I2C_ClockSpeed = SCCB_SPEED;                             //I2C_ClockSpeed_400KHz;
	I2C_InitStruct.I2C_Mode = I2C_Mode_Master;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_1;
	I2C_InitStruct.I2C_TargetAddress = DEVICE_WRITE_ADDRESS;
	I2C_InitStruct.I2C_TargetAddressMode = I2C_TargetAddressMode_7bit;
//	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	
//	I2C_InitStruct.I2C_RXFIFOFullThreshold = I2C_RXFIFOFullThreshold_1;
//	I2C_InitStruct.I2C_TXFIFOEmptyThreshold = I2C_TXFIFOEmptyThreshold_0;
//	I2C_InitStruct.I2C_SDASetupTime = 1 + (300*clocks.PCLK_Frequency)/1000000000;   //300ns
//	I2C_InitStruct.I2C_SDAHoldTime =  (600*clocks.PCLK_Frequency)/100000000; //600ns
//	I2C_InitStruct.I2C_OwnAddress = 0x55;
//    I2C_InitStruct.I2C_GenerateRestartEnable = ENABLE;
	I2C_Init(MH1903_SCCB, &I2C_InitStruct);
	I2C_Cmd(MH1903_SCCB, ENABLE);
}
/*
 *****************************************************************************
 * Function Name  : SCCB_AddrByteWriteByte
 * Description    : 用于配置寄存器地址是1个Byte，并且对应的数据也是1个Byte的情况
 * Input          : RegAdr：register address；
 *                  Data: data to be written to the specific register 
 * Output         : None
 * Return         : status:
 *                       0x00 if write operation is OK. 
 *                       0xFF if timeout condition occured (device not connected or bus error).
 * Attention		 : None
 *******************************************************************************
*/
static uint8_t SCCB_AddrByteWriteByte(uint8_t RegAdr, uint8_t Data)
{
    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXE)));  //等到发送fifo空
    I2C_SendData(MH1903_SCCB, DEVICE_WRITE_ADDRESS, I2C_DataEndCondition_Stop);
    while (RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, RegAdr, I2C_DataEndCondition_None);
	while (RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, Data, I2C_DataEndCondition_Stop);
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrByteReadByte
* Description    : Reads a Byte data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrByteReadByte(uint8_t RegAdr, uint8_t *pData)
{
    uint8_t tmpValue;
	while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXE)));  //等到发送fifo空
	I2C_SendData(MH1903_SCCB, DEVICE_READ_ADDRESS, I2C_DataEndCondition_None);
	while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, RegAdr, I2C_DataEndCondition_None);
	while (RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	if (I2C_Mode_Master == I2C_GetI2CMode(MH1903_SCCB))
	{
		while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
		I2C_MasterGenerateReceiveSCL(MH1903_SCCB, I2C_DataEndCondition_Stop); // I2C_DataEndCondition_Stop
		while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_RXNE)));
		tmpValue = (uint8_t)I2C_ReadDataFromDR(MH1903_SCCB);
	}
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrByteWriteHalfWord
* Description    : 用于配置寄存器地址是1个Byte，并且对应的数据是2个Byte的情况
* Input          : RegAdr：register address；
*                  Data: data to be written to the specific register 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrByteWriteHalfWord(uint8_t RegAdr, uint16_t Data)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrByteReadHalfWord
* Description    : Reads a HalfWord data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrByteReadHalfWord(uint8_t RegAdr, uint16_t *pData)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordWriteByte
* Description    : 用于配置寄存器地址是2个Byte，并且对应的数据是1个Byte的情况
* Input          : RegAdr：register address；
*                  Data: data to be written to the specific register 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordWriteByte(uint16_t RegAdr, uint8_t Data)
{
    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXE)));  //等到发送fifo空
    I2C_SendData(MH1903_SCCB, DEVICE_WRITE_ADDRESS, I2C_DataEndCondition_Restart);
    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, (uint8_t)((RegAdr >> 8) & 0xFF), I2C_DataEndCondition_None);
    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, (uint8_t)(RegAdr & 0xFF), I2C_DataEndCondition_None);
    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, Data, I2C_DataEndCondition_Stop);
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordReadByte
* Description    : Reads a Byte data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordReadByte(uint16_t RegAdr, uint8_t *pData)
{
    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXE)));  //等到发送fifo空
    I2C_SendData(MH1903_SCCB, DEVICE_WRITE_ADDRESS, I2C_DataEndCondition_Restart);
//    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, (uint8_t)((RegAdr >> 8) & 0xFF), I2C_DataEndCondition_None);
//    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));
	I2C_SendData(MH1903_SCCB, (uint8_t)(RegAdr & 0xFF), I2C_DataEndCondition_None);
//    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_TXNF)));  //等到发送fifo空
    I2C_SendData(MH1903_SCCB, DEVICE_READ_ADDRESS, I2C_DataEndCondition_Restart);
//    while(RESET == (I2C_GetFlagStatus(MH1903_SCCB, I2C_FLAG_RXNE)));
    *pData = I2C_ReceiveData(MH1903_SCCB,I2C_DataEndCondition_Stop);
    printf("> Enter 5\r\n");
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordWriteHalfWord
* Description    : 用于配置寄存器地址是2个Byte，并且对应的数据是2个Byte的情况
* Input          : RegAdr：register address；
*                  Data: data to be written to the specific register 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordWriteHalfWord(uint16_t RegAdr, uint16_t Data)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordReadHalfWord
* Description    : Reads a HalfWord data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordReadHalfWord(uint16_t RegAdr, uint16_t *pData)
{
    /* If operation is OK, return 0 */
    return 0;
}

#endif
#ifdef USE_SIMULATON_I2C
/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 用于配置SCCB所用接口对应的GPIO
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void SCCB_GPIO_Config(void)
{
    piSimuI2C->Init(USE_I2C_100KHZ);
}

/*******************************************************************************
* Function Name  : SCCB_Peripherals_Config
* Description    : 用于配置SCCB所用外设
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void SCCB_Peripherals_Config(void)
{
    /* Disable */
}
/*
 *****************************************************************************
 * Function Name  : SCCB_AddrByteWriteByte
 * Description    : 用于配置寄存器地址是1个Byte，并且对应的数据也是1个Byte的情况
 * Input          : RegAdr：register address；
 *                  Data: data to be written to the specific register 
 * Output         : None
 * Return         : status:
 *                       0x00 if write operation is OK. 
 *                       0xFF if timeout condition occured (device not connected or bus error).
 * Attention		 : None
 *******************************************************************************
*/
static uint8_t SCCB_AddrByteWriteByte(uint8_t RegAdr, uint8_t Data)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrByteReadByte
* Description    : Reads a Byte data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrByteReadByte(uint8_t RegAdr, uint8_t *pData)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrByteWriteHalfWord
* Description    : 用于配置寄存器地址是1个Byte，并且对应的数据是2个Byte的情况
* Input          : RegAdr：register address；
*                  Data: data to be written to the specific register 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrByteWriteHalfWord(uint8_t RegAdr, uint16_t Data)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrByteReadHalfWord
* Description    : Reads a HalfWord data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrByteReadHalfWord(uint8_t RegAdr, uint16_t *pData)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordWriteByte
* Description    : 用于配置寄存器地址是2个Byte，并且对应的数据是1个Byte的情况
* Input          : RegAdr：register address；
*                  Data: data to be written to the specific register 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordWriteByte(uint16_t RegAdr, uint8_t Data)
{
    uint32_t timeout = RETRY_TIME_MAX;
    while(SI2C_SUCCESS != piSimuI2C->Start()){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte(DEVICE_WRITE_ADDRESS)){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte((uint8_t)((RegAdr >> 8) & 0x00FF))){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte((uint8_t)(RegAdr & 0x00FF))){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte(Data)){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    piSimuI2C->Stop();
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordReadByte
* Description    : Reads a Byte data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordReadByte(uint16_t RegAdr, uint8_t *pData)
{
    uint32_t timeout = RETRY_TIME_MAX;
    while (true == piSimuI2C->IsBusy());
    while(SI2C_SUCCESS != piSimuI2C->Start()){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0){
            printf("> Start\n");
            return 0xFF;
        }
    }
    
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte(DEVICE_WRITE_ADDRESS)){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0){
           printf("> Send Write Addr\n"); 
            return 0xFF;
        }
    }
    
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte((uint8_t)((RegAdr >> 8) & 0x00FF))){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0){ 
            printf("> Reg H\n");
            return 0xFF;
        }
    }
    
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte((uint8_t)(RegAdr & 0x00FF))){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0){
            printf("> Reg L\n");
            return 0xFF;
        }
    }
    
    timeout = RETRY_TIME_MAX;
    while(SI2C_SUCCESS != piSimuI2C->Start()){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0){
            printf("> ReStart \n");
            return 0xFF;
        }
    }
   
    timeout = RETRY_TIME_MAX;
    while(ACK_SUCCESS != piSimuI2C->send_byte(DEVICE_READ_ADDRESS)){
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0){
            printf("> Write Read Addr\n");
            return 0xFF;
        }
    }
    
    *pData = piSimuI2C->receive_byte(NO_ACK);
    piSimuI2C->Stop();
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordWriteHalfWord
* Description    : 用于配置寄存器地址是2个Byte，并且对应的数据是2个Byte的情况
* Input          : RegAdr：register address；
*                  Data: data to be written to the specific register 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordWriteHalfWord(uint16_t RegAdr, uint16_t Data)
{
    /* If operation is OK, return 0 */
    return 0;
}

/*******************************************************************************
* Function Name  : SCCB_AddrHalfWordReadHalfWord
* Description    : Reads a HalfWord data from a specific register 
* Input          : RegAdr：register address；
*                  pData: data read from the specific register or 0xFF if timeout condition 
*                         occured. 
* Output         : None
* Return         : status:
*                       0x00 if write operation is OK. 
*                       0xFF if timeout condition occured (device not connected or bus error).
* Attention		 : None
*******************************************************************************/
static uint8_t SCCB_AddrHalfWordReadHalfWord(uint16_t RegAdr, uint16_t *pData)
{
    /* If operation is OK, return 0 */
    return 0;
}

#endif
/************************* (C) COPYRIGHT 2018 LOVE_ELEC ******END OF FILE******/
