/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_cache.h
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file contains all the functions prototypes for the CACHE firmware library
 *****************************************************************************/

#ifndef __MHSCPU_CACHE_H
#define __MHSCPU_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mhscpu.h"

#define AES_I3 (0x00112233)
#define AES_I2 (0x44556677) 
#define AES_I1 (0x8899aabb)     
#define AES_I0 (0xccddeeff) 

#define AES_K3 (0xffeeddcc)
#define AES_K2 (0xbbaa9988) 
#define AES_K1 (0x77665544)     
#define AES_K0 (0x33221100)  

#define AES_BYPASS				(0xA5)
#define KEY_GEN					(0xA5)
#define KI_READ_EN				(1)
#define KI_READ_EN_POS			(8)


typedef struct                        
{      
	uint32_t I[4];
	uint32_t K[4];   
	uint32_t AES_CS;
    	uint32_t BACK_DOOR;

	uint32_t aes_enable;
	uint32_t Address;                 
	uint32_t size;             
}CACHE_InitTypeDef;

void Cache_Flash_Init(CACHE_TypeDef* Cache, CACHE_InitTypeDef* CACHE_InitStruct);
void Cache_Clean(CACHE_TypeDef* Cache, CACHE_InitTypeDef* CACHE_InitStruct);
void Cache_Clean_all(CACHE_TypeDef* Cache);

#ifdef __cplusplus
}
#endif

#endif


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
