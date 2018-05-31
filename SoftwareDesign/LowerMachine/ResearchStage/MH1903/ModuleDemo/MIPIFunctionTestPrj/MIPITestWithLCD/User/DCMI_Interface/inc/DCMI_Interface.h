/**
  ******************************************************************************
  * @file    DCMI_Interface.h
  * @author  LOVE_ELEC
  * @version V1.0.0
  * @date    18-Januery-2018
  * @brief   This file is used to link the DCMI operator interface.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DCMI_INTERFACE_H
#define __DCMI_INTERFACE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mhscpu.h"	
#include "stdbool.h"
/* Exported types ------------------------------------------------------------*/      
/* Exported constants --------------------------------------------------------*/     
/* Exported macro ------------------------------------------------------------*/  
/* Exported functions --------------------------------------------------------*/
bool Image_Init(void);
bool Image_ReStart(void);
/* Exported variables --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /*__DCMI_INTERFACE_H */

/************************* (C) COPYRIGHT 2018 LOVE_ELEC ******END OF FILE******/
