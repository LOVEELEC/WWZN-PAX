/**
  ******************************************************************************
  * @file    Sensor_SCCB.h
  * @author  LOVE_ELEC
  * @version V1.0.0
  * @date    18-Januery-2018
  * @brief   Camera Sensor SCCB interface definition.
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SENSOR_SCCB_H
#define __SENSOR_SCCB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mhscpu.h"
#include "stdint.h"
#include "stdbool.h"
/* Private define ------------------------------------------------------------*/
//#define USE_STM32_I2C
//#define USE_MH1903_I2C     
#define USE_SIMULATON_I2C
     
#define I2C_PAGESIZE	4
/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define SCCB_Open207V_FLAG_TIMEOUT          10000
#define OV7670_DEVICE_WRITE_ADDRESS         0x90
#define OV7670_DEVICE_READ_ADDRESS          0x91
#define MIPI_DEVICE_WRITE_ADDRESS           0x1c
#define MIPI_DEVICE_READ_ADDRESS            0x1d


#define OV6710_DEVICE_WRITE_ADDRESS         0xc0
#define OV6710_DEVICE_READ_ADDRESS          0xc1

#define OV7251_DEVICE_WRITE_ADDRESS         0xc0
#define OV7251_DEVICE_READ_ADDRESS          0xc1

#define SCCB_SPEED                          I2C_ClockSpeed_400KHz
#define SCCB_SLAVE_ADDRESS7                 0xFE

#ifdef USE_MH1903_I2C
#define DEVICE_WRITE_ADDRESS                (OV7251_DEVICE_WRITE_ADDRESS >> 1)
#define DEVICE_READ_ADDRESS                 (OV7251_DEVICE_READ_ADDRESS >> 1)
#else
#define DEVICE_WRITE_ADDRESS                (OV7251_DEVICE_WRITE_ADDRESS)
#define DEVICE_READ_ADDRESS                 (OV7251_DEVICE_READ_ADDRESS)
#endif
/* Exported types ------------------------------------------------------------*/  
typedef struct _iSCCB_Struct_Def{
    bool    (*Init)(void);
    uint8_t (*AddrByteWriteByte)(uint8_t RegAdr, uint8_t Data);
    uint8_t (*AddrByteReadByte)(uint8_t RegAdr, uint8_t *pData);
    uint8_t (*AddrByteWriteHalfWord)(uint8_t RegAdr, uint16_t Data);
    uint8_t (*AddrByteReadHalfWord)(uint8_t RegAdr, uint16_t *pData);
    uint8_t (*AddrHalfWordWriteByte)(uint16_t RegAdr, uint8_t Data);
    uint8_t (*AddrHalfWordReadByte)(uint16_t RegAdr, uint8_t *pData);
    uint8_t (*AddrHalfWordWriteHalfWord)(uint16_t RegAdr, uint16_t Data);
    uint8_t (*AddrHalfWordReadHalfWord)(uint16_t RegAdr, uint16_t *pData);
} iSCCB_Struct, *piSCCB_Struct;
/* Exported constants --------------------------------------------------------*/     
/* Exported macro ------------------------------------------------------------*/  
/* Exported functions --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern piSCCB_Struct piSCCB;
#ifdef __cplusplus
}
#endif

#endif /*__OV7251_MIPI_DRIVER_H */

/************************* (C) COPYRIGHT 2018 LOVE_ELEC ******END OF FILE******/
