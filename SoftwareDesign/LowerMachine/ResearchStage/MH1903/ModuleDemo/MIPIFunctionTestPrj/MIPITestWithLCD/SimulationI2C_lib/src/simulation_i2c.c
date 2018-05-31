/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : simulation_i2c.c
 * Author               : Megahuntmicro
 * Version              : V1.0.0
 * Date                 : 12/07/2015
 * Description          : Simulation I2C function file.
 *****************************************************************************/
 
/* Include ------------------------------------------------------------------*/
#include "simulation_i2c.h"
#include "si2c_delay.h"
/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/	
#define SMIULATION_I2C_SPEED_100KHZ             (6)         // 10us()
#define SMIULATION_I2C_SPEED_400KHZ             (2)         // 2.5us

//#define USE_I2C_TEST

#define SI2C_PORT_RTC               SYSCTRL_APBPeriph_GPIO
#define SI2C_PORT                   GPIOB
#define SI2C_SCL_PIN                GPIO_Pin_0
#define SI2C_SDA_PIN                GPIO_Pin_1

#define GPIOx						((GPIO_TypeDef *) SI2C_PORT)
#define GPIO_PINx_DIR_In(x)\
{\
		GPIOx->OEN &= ~x;\
		GPIOx->OEN |= x;\
}\


#define GPIO_PINx_DIR_Out(x)\
{\
		GPIOx->OEN &= ~x;\
}\

/* SDA GPIO DIR Func def */
#define SI2C_SDA_IN()           GPIO_PINx_DIR_In(SI2C_SDA_PIN)
#define SI2C_SDA_OUT()          GPIO_PINx_DIR_Out(SI2C_SDA_PIN)

/* GPIO Manipulation Function */
#define SI2C_SCL_HIGH()		    GPIOx->IODR |= SI2C_SCL_PIN  //SCL
#define SI2C_SCL_LOW()		    GPIOx->IODR &= ~SI2C_SCL_PIN  //SCL
#define SI2C_SDA_HIGH()		    GPIOx->IODR |= SI2C_SDA_PIN  //SDA
#define SI2C_SDA_LOW()		    GPIOx->IODR &= ~SI2C_SDA_PIN  //SDA
#define READ_SDA				(GPIOx->IODR & ((uint32_t)SI2C_SDA_PIN << 16))  //输入SDA 

/* Private macro ------------------------------------------------------------*/	
/* Private variables --------------------------------------------------------*/	
static uint8_t SmiuI2c_Speed = SMIULATION_I2C_SPEED_100KHZ;
/* Ptivate function prototypes ----------------------------------------------*/	
static SI2C_FuncExecStatus simulation_i2c_init(SIMULATION_I2C_SPEED speed);
static SI2C_FuncExecStatus simulation_i2c_start(void);
static SI2C_FuncExecStatus simulation_i2c_stop(void);
static SI2C_ACK_Status simulation_i2c_wait_ack(void);
static SI2C_ACK_Status simulation_i2c_ack(void);
static SI2C_FuncExecStatus simulation_i2c_nack(void);
static SI2C_ACK_Status simulation_i2c_send_byte(uint8_t send_data);
static uint8_t simulation_i2c_receive_byte(SI2C_ACK_Mode_Def ack_mode);
static bool simulation_i2c_isBusy(void);

static iSimuI2C_Struct iSimuI2C = {
    simulation_i2c_init,
    simulation_i2c_start,
    simulation_i2c_stop,
    simulation_i2c_wait_ack,
    simulation_i2c_ack,
    simulation_i2c_nack,
    simulation_i2c_send_byte,
    simulation_i2c_receive_byte,
    simulation_i2c_isBusy
};
    
piSimuI2C_Struct	piSimuI2C = &iSimuI2C;
/******************************************************************************
* Function Name  : simulation_i2c_init
* Description    : simulaition i2c initialization function
* Input          : NONE
* Output         : NONE
* Return         : Results of the simulation I2C initialization function
******************************************************************************/
static SI2C_FuncExecStatus simulation_i2c_init(SIMULATION_I2C_SPEED speed)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
	GPIO_InitStructure.GPIO_Pin = SI2C_SDA_PIN | SI2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
    GPIO_InitStructure.GPIO_Remap = GPIO_Remap_1;
	GPIO_Init(SI2C_PORT, &GPIO_InitStructure);
    if (speed == USE_I2C_100KHZ){
        SmiuI2c_Speed = SMIULATION_I2C_SPEED_100KHZ;
    }else if(speed == USE_I2C_400KHZ){
        SmiuI2c_Speed = SMIULATION_I2C_SPEED_400KHZ;
    }
    SI2C_SDA_OUT();     //sda线输出
	SI2C_SDA_HIGH();	  	  
	SI2C_SCL_HIGH();
    return SI2C_SUCCESS;
}

/******************************************************************************
* Function Name  : simulation_i2c_isBusy
* Description    : simulaition i2c Bus Status Detect
* Input          : NONE
* Output         : NONE
* Return         : Results of the simulation I2C BUS Status
******************************************************************************/
static bool simulation_i2c_isBusy(void)
{
    SI2C_SDA_IN(); 
    if(READ_SDA){
        return false;
    }
    return true;
}

/******************************************************************************
* Function Name  : simulation_i2c_start
* Description    : simulaition i2c start function
* Input          : NONE
* Output         : NONE
* Return         : Results of the simulation I2C start function
******************************************************************************/
static SI2C_FuncExecStatus simulation_i2c_start(void)
{
    #ifndef USE_I2C_TEST
    SI2C_SDA_OUT();     //sda线输出
	SI2C_SDA_HIGH();	  	  
	SI2C_SCL_HIGH();
	si2c_delay_us(SmiuI2c_Speed*2);
 	SI2C_SDA_LOW();//START:when CLK is high,DATA change form high to low 
	si2c_delay_us(SmiuI2c_Speed*2);
	SI2C_SCL_LOW();//钳住I2C总线，准备发送或接收数据 
    #else
    SI2C_SDA_OUT();     //sda线输出
	SI2C_SDA_HIGH();	  	  
	SI2C_SCL_HIGH();
	si2c_delay_us(4);
 	SI2C_SDA_LOW();//START:when CLK is high,DATA change form high to low 
	si2c_delay_us(4);
	SI2C_SCL_LOW();//钳住I2C总线，准备发送或接收数据 
    #endif
    return SI2C_SUCCESS;
}

/******************************************************************************
* Function Name  : simulation_i2c_stop
* Description    : simulaition i2c stop function
* Input          : NONE
* Output         : NONE
* Return         : Results of the simulation I2C stop function
******************************************************************************/
static SI2C_FuncExecStatus simulation_i2c_stop(void)
{
    #ifndef USE_I2C_TEST
    SI2C_SDA_OUT();     //sda线输出
    /* 防止线上状态不对，造成不能Stop */
    SI2C_SCL_HIGH();
	SI2C_SDA_LOW();	  	//STOP:when CLK is high DATA change form low to high  
	si2c_delay_us(SmiuI2c_Speed);
    /* 停止 */
	SI2C_SDA_HIGH();    //发送I2C总线结束信号
    si2c_delay_us(SmiuI2c_Speed);
    #else
    SI2C_SDA_OUT();     //sda线输出
    SI2C_SCL_LOW();
	SI2C_SDA_LOW();	  	//STOP:when CLK is high DATA change form low to high  
	si2c_delay_us(4);
 	SI2C_SCL_HIGH();
	si2c_delay_us(4);
	SI2C_SDA_HIGH();    //发送I2C总线结束信号
    si2c_delay_us(4);
    #endif
    return SI2C_SUCCESS;
}

/******************************************************************************
* Function Name  : simulation_i2c_wait_ack
* Description    : simulatipn i2c wait ack function
* Input          : NONE
* Output         : NONE
* Return         : ACK response results
******************************************************************************/
static SI2C_ACK_Status simulation_i2c_wait_ack(void)
{
    #ifndef USE_I2C_TEST
    uint8_t ucErrTime=0;
    SI2C_SCL_LOW();          //时钟输出0 
    si2c_delay_us(1);	
	SI2C_SDA_OUT();
	SI2C_SDA_HIGH();
    SI2C_SDA_IN();      //SDA设置为输入  
    si2c_delay_us(SmiuI2c_Speed - 1);	   
	SI2C_SCL_HIGH();
    si2c_delay_us(SmiuI2c_Speed);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			simulation_i2c_stop();
			return ACK_FAIL;
		}
	}
	SI2C_SCL_LOW();          //时钟输出0 
    #else
    uint8_t ucErrTime=0;
	SI2C_SDA_IN();      //SDA设置为输入  
	SI2C_SDA_HIGH();
    si2c_delay_us(2);	   
	SI2C_SCL_HIGH();
    si2c_delay_us(2);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			simulation_i2c_stop();
			return ACK_FAIL;
		}
	}
	si2c_delay_us(1);
	SI2C_SCL_LOW();          //时钟输出0 
    si2c_delay_us(2);	  
    #endif
    return ACK_SUCCESS;
}

/******************************************************************************
* Function Name  : simulation_i2c_ack
* Description    : simulation i2c ack function 
* Input          : NONE
* Output         : NONE 
* Return         : ACK response to the execution result
******************************************************************************/
static SI2C_ACK_Status simulation_i2c_ack(void)
{
    #ifndef USE_I2C_TEST
    SI2C_SCL_LOW();
    si2c_delay_us(1);
	SI2C_SDA_OUT();
	SI2C_SDA_LOW();
	si2c_delay_us(SmiuI2c_Speed - 1);
	SI2C_SCL_HIGH();
	si2c_delay_us(SmiuI2c_Speed);
	SI2C_SCL_LOW();
//	si2c_delay_us(SmiuI2c_Speed);
	SI2C_SDA_HIGH();
    #else
    SI2C_SCL_LOW();
	SI2C_SDA_OUT();
	SI2C_SDA_LOW();
	si2c_delay_us(2);
	SI2C_SCL_HIGH();
	si2c_delay_us(2);
	SI2C_SCL_LOW();
	si2c_delay_us(2);
	SI2C_SDA_HIGH();
    #endif
    return ACK_SUCCESS;
}

/******************************************************************************
* Function Name  : simulation_i2c_nack
* Description    : simulation i2c nack function 
* Input          : NONE
* Output         : NONE 
* Return         : NACK response to the execution result
******************************************************************************/
static SI2C_FuncExecStatus simulation_i2c_nack(void)
{
    #ifndef USE_I2C_TEST
    SI2C_SCL_LOW();
	si2c_delay_us(1);
    SI2C_SDA_OUT();
	SI2C_SDA_HIGH();
	si2c_delay_us(SmiuI2c_Speed - 1);
	SI2C_SCL_HIGH();
	si2c_delay_us(SmiuI2c_Speed);
	SI2C_SCL_LOW();
    #else
    SI2C_SCL_LOW();
	SI2C_SDA_OUT();
	si2c_delay_us(1);
	SI2C_SDA_HIGH();
	si2c_delay_us(2);
	SI2C_SCL_HIGH();
	si2c_delay_us(2);
	SI2C_SCL_LOW();
    #endif
    return SI2C_SUCCESS;
}

/******************************************************************************
* Function Name  : simulation_i2c_send_byte
* Description    : simulation i2c send byte function
* Input          : send_data:Data to be transmitted
* Output         : NONE
* Return         : Results of the simulation I2C send byte function
******************************************************************************/
static SI2C_ACK_Status simulation_i2c_send_byte(uint8_t send_data)
{
    uint8_t t;   
	SI2C_SDA_OUT();
    #ifndef USE_I2C_TEST	    
    for(t = 0; t < 8; t++)
    {   
        SI2C_SCL_LOW();	  
        si2c_delay_us(1);          
        if ((send_data & 0x80) >> 7)
        {
            SI2C_SDA_HIGH();	
        }else{
            SI2C_SDA_LOW();
        }
        send_data <<= 1; 	  
		si2c_delay_us(SmiuI2c_Speed - 1);   
		SI2C_SCL_HIGH();
		si2c_delay_us(SmiuI2c_Speed); 
//		SI2C_SCL_LOW();	
//		si2c_delay_us(SmiuI2c_Speed);
    }
    SI2C_SCL_LOW();	
    si2c_delay_us(SmiuI2c_Speed);
    #else	    
    SI2C_SCL_LOW();//拉低时钟开始数据传输
    for(t = 0; t < 8; t++)
    {              
        if ((send_data & 0x80) >> 7)
        {
            SI2C_SDA_HIGH();	
        }else{
            SI2C_SDA_LOW();
        }
        send_data <<= 1; 	  
		si2c_delay_us(2);   
		SI2C_SCL_HIGH();
		si2c_delay_us(2); 
		SI2C_SCL_LOW();	
		si2c_delay_us(2);
    }
    #endif
    return simulation_i2c_wait_ack();
}

/******************************************************************************
* Function Name  : simulation_i2c_send_byte
* Description    : simulation i2c receive byte function
* Input          : NONE
* Output         : NONE
* Return         : received data
******************************************************************************/
static uint8_t simulation_i2c_receive_byte(SI2C_ACK_Mode_Def ack_mode)
{
    uint8_t rx_data = 0, i;
	SI2C_SDA_IN();//SDA设置为输入
    for(i = 0; i < 8; i++ ){
    #ifndef USE_I2C_TEST
    
        SI2C_SCL_LOW(); 
        si2c_delay_us(SmiuI2c_Speed);
		SI2C_SCL_HIGH();
        si2c_delay_us(SmiuI2c_Speed);
        rx_data <<= 1;
        if(READ_SDA)
            rx_data++;   
    #else
        SI2C_SCL_LOW(); 
        si2c_delay_us(1);
		SI2C_SCL_HIGH();
        si2c_delay_us(1);
        rx_data <<= 1;
        if(READ_SDA)
            rx_data++;   
		si2c_delay_us(1); 	
    #endif
    }
    if (ack_mode != SEND_ACK){
        simulation_i2c_nack();//发送nACK
    }else{
        simulation_i2c_ack(); //发送ACK 
    }
    return rx_data;
}

/************************ (C) COPYRIGHT 2015 Megahuntmicro ****END OF FILE****/
