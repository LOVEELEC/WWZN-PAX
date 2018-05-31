/**
  ******************************************************************************
  * @file    DCMI/OV7670_Camera/dcmi_OV7670.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Header for mipi_dcmi_GC310.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MIPI_DCMI_GC2235_H
#define __MIPI_DCMI_GC2235_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f2xx.h"
//#include "SCCB.h"
#include "mhscpu.h"
#include "config.h"
#include "systick.h"
#define GC2355MIPI_SENSOR_ID 			(0x2355)

#define GC2235MIPI_WRITE_ADDRESS		0x78
#define GC2235MIPI_READ_ADDRESS			0x79

void GC2355_pwdn_and_reset_pin_config(void);
void  GC2355_pwdn_enable(void);
void  GC2355_pwdn_disable(void);
void GC2355MIPI_Sensor_Init(void);
uint32_t GC2355MIPIOpen(void);

#endif /* __MIPI_DCMI_GC310_H */

