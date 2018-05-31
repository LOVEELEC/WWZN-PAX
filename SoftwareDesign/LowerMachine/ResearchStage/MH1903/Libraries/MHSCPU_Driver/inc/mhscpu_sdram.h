/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_sdram.h
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file contains all the functions prototypes for the SDRAM firmware library
 *****************************************************************************/
#ifndef __MHSCPU_SDRAM_H
#define __MHSCPU_SDRAM_H

#include "mhscpu.h"


typedef struct
{
	uint32_t MPMC_Endian;				// Little-Endian = 0, Big-Endian = 1
	uint32_t MPMC_Buffer;				// AHB-Buffer Enable = 1, Disable = 0
	uint32_t MPMC_LowPower;             // Low-Powber Enable = 1, Disable = 0
	uint32_t MPMC_CAS;               	// CAS
} MPMC_InitTypeDef;


void SDRAM_Init(MPMC_InitTypeDef *MPMC_InitStruct);


#endif


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
