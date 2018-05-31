/**
  ******************************************************************************
  * @file    OV7251_MIPI_Driver.h
  * @author  LOVE_ELEC
  * @version V1.0.0
  * @date    18-Januery-2018
  * @brief   This file is used to link the OV7251 operator interface.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OV7251_MIPI_DRIVER_H
#define __OV7251_MIPI_DRIVER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Sensor_SCCB.h"
/* Exported types ------------------------------------------------------------*/      
/* Exported constants --------------------------------------------------------*/     
/* Exported macro ------------------------------------------------------------*/  
/* Exported functions --------------------------------------------------------*/
bool OV7251_Init(void);
/* Exported variables --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /*__OV7251_MIPI_DRIVER_H */

/************************* (C) COPYRIGHT 2018 LOVE_ELEC ******END OF FILE******/
