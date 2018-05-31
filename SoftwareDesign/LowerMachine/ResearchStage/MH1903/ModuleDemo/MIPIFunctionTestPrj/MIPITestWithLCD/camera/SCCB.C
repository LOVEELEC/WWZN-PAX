/*********************************************************************************************************
*
* File                : 24C02.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "SCCB.h"
#include "simulation_i2c.h"
#include "si2c_delay.h"
__IO uint32_t  DCMI_TIMEOUT_MAX = SCCB_Open207V_FLAG_TIMEOUT;

/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void SCCB_GPIO_Config(void)
{
    si2c_delay_init(32);
    while (simulation_i2c_init() != SI2C_SUCCESS);
}

/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Device: OV7670 write address.
  * @param  Addr: OV7670 register address. 
  * @param  Data: data to be written to the specific register 
  * @retval 0x00 if write operation is OK. 
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
uint8_t DCMI_SingleRandomWrite(uint8_t Reg, uint8_t Data)
{
    uint32_t timeout = DCMI_TIMEOUT_MAX;
    
    /* Generate the Start Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_start() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    /*-----------------------------------------------------------------------------------*/
    /* Send DCMI selcted device slave Address for write */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(OV7670_DEVICE_WRITE_ADDRESS) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    /*-----------------------------------------------------------------------------------*/
    /* Send I2C2 location address LSB */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte((uint8_t)(Reg)) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Send Data */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(Data) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Send I2C2 STOP Condition */
    /* Generate the Start Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_stop() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
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
uint8_t SCCB_WriteWord(uint8_t Reg, uint16_t Data)
{
    uint32_t timeout = DCMI_TIMEOUT_MAX;
    
    /* Generate the Start Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_start() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    /*-----------------------------------------------------------------------------------*/
    /* Send DCMI selcted device slave Address for write */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(OV7670_DEVICE_WRITE_ADDRESS) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Send I2C2 location address LSB */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte((uint8_t)(Reg)) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Send Data WORD */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte((Data >> 8) & 0x00FF) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(Data & 0x00FF) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Send I2C2 STOP Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_stop() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

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
uint8_t DCMI_SingleRandomRead(uint8_t Reg, uint8_t *Data)
{
    uint32_t timeout = DCMI_TIMEOUT_MAX;

    /* Generate the Start Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_start() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    /*-----------------------------------------------------------------------------------*/
    /* Send DCMI selcted device slave Address for write */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(OV7670_DEVICE_WRITE_ADDRESS) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Send I2C2 location address LSB */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte((uint8_t)(Reg)) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    /*-----------------------------------------------------------------------------------*/    
    /* Prepare Stop after receiving data */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_stop() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Generate the Start Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_start() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    
    /*-----------------------------------------------------------------------------------*/
    /* Send DCMI selcted device slave Address for Read */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(OV7670_DEVICE_READ_ADDRESS) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
         
    /*-----------------------------------------------------------------------------------*/
    /* Prepare an NACK for the next data received */
//  I2C_AcknowledgeConfig(Open207V_SCCB, DISABLE); 
    /*-----------------------------------------------------------------------------------*/
    /* Receive the Data */
    *Data = simulation_i2c_receive_byte(NO_ACK);
    /*-----------------------------------------------------------------------------------*/    
    /* Prepare Stop after receiving data */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_stop() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    
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
uint8_t SCCB_ReadWord(uint8_t Reg, uint16_t *Data)
{
    uint32_t timeout = DCMI_TIMEOUT_MAX;

    /* Generate the Start Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_start() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    
    /*-----------------------------------------------------------------------------------*/
    /* Send DCMI selcted device slave Address for write */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(OV7670_DEVICE_WRITE_ADDRESS) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    /*-----------------------------------------------------------------------------------*/
    /* Send I2C2 location address LSB */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte((uint8_t)(Reg)) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/    
    /* Prepare Stop after receiving data */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_stop() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /*-----------------------------------------------------------------------------------*/
    /* Generate the Start Condition */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_start() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }
    
    /*-----------------------------------------------------------------------------------*/
    /* Send DCMI selcted device slave Address for write */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_send_byte(OV7670_DEVICE_READ_ADDRESS) != ACK_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }  
//  /*-----------------------------------------------------------------------------------*/
//	 /* Prepare an ACK for the next data received */
//  I2C_AcknowledgeConfig(Open207V_SCCB, ENABLE);

    /*-----------------------------------------------------------------------------------*/
    /* Receive the Data */
    *Data = simulation_i2c_receive_byte(SEND_ACK) << 8;//	/* Receive the Data */
//	/*-----------------------------------------------------------------------------------*/
//	 /* Prepare an NACK for the next data received */
//  I2C_AcknowledgeConfig(Open207V_SCCB, DISABLE);

    /*-----------------------------------------------------------------------------------*/
    /* Receive the Data */
    *Data |= simulation_i2c_receive_byte(NO_ACK);
    /*-----------------------------------------------------------------------------------*/    
    /* Prepare Stop after receiving data */
    timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
    while (simulation_i2c_stop() != SI2C_SUCCESS)
    {
        /* If the timeout delay is exeeded, exit with error code */
        if ((timeout--) == 0) return 0xFF;
    }

    /* return the read data */
    return 0;
}
