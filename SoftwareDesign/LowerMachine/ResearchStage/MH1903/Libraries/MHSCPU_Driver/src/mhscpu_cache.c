/**************************************************************************//**
 * @file     mhscpu_qspi.c
 * @brief    This file provides all the GPIO firmware function.
 * @version  V1.00
 * @date     11. April 2015
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/
#include "mhscpu_cache.h"
#define CACHE_REFRESH_POS		(31)
#define KEY_GEN_START_POS		(31)	
#define KEY_GEN_START			(1UL)

#define ALL_TAG					(1)
#define ALL_TAG_POS					(30)

#define CACHE_BUSY				(1)
#define CACHE_BUSY_POS				(29)

void Cache_Flash_Init(CACHE_TypeDef* Cache, CACHE_InitTypeDef* CACHE_InitStruct)
{
	int i;
	
	if(CACHE_InitStruct->aes_enable==ENABLE)
	{
		for (i = 0; i < 5000; i++)
		{
			if (Cache->CACHE_AES_CS & BIT29)	//cache正在从Flash中取指
			{
				continue;
			}
			break;
		}
		Cache->CACHE_AES_CS = (Cache->CACHE_AES_CS & ~0xFF) | 0xA5;	//AES密钥生成模式
		Cache->CACHE_BACK_DOOR = CACHE_InitStruct->BACK_DOOR;

		Cache->CACHE_AES_I3 = CACHE_InitStruct->I[3];
		Cache->CACHE_AES_I2 = CACHE_InitStruct->I[2];   
		Cache->CACHE_AES_I1 = CACHE_InitStruct->I[1];       
		Cache->CACHE_AES_I0 = CACHE_InitStruct->I[0];   

		Cache->CACHE_AES_K3 = CACHE_InitStruct->K[3];
		Cache->CACHE_AES_K2 = CACHE_InitStruct->K[2];   
		Cache->CACHE_AES_K1 = CACHE_InitStruct->K[1];       
		Cache->CACHE_AES_K0 = CACHE_InitStruct->K[0];           

		Cache->CACHE_AES_CS |= (KEY_GEN_START << KEY_GEN_START_POS); 
		for (i = 0; i < 5000; i++)
		{
			if((Cache->CACHE_AES_CS >> KEY_GEN_START_POS) == 0)
			{
			    Cache->CACHE_AES_CS = 0x0;
			    break;
			}   
		} 
		Cache->CACHE_AES_CS = 0;
	}
	else
	{
		Cache->CACHE_BACK_DOOR = AES_BYPASS;
	}
	
}

/*clean cache flash data/instructions*/
void Cache_Clean(CACHE_TypeDef* Cache, CACHE_InitTypeDef* CACHE_InitStruct)
{
	uint32_t i,address;
	address = CACHE_InitStruct->Address &0x1F;
	for(i=0;i < CACHE_InitStruct->size;i+=32)
	{
		//flush cache line 
		Cache->CACHE_REF = (address+i);
		Cache->CACHE_REF |= (1UL << CACHE_REFRESH_POS);
		while((Cache->CACHE_REF & (1UL << CACHE_REFRESH_POS)));	
	}
}

void Cache_Clean_all(CACHE_TypeDef* Cache)
{
	//flush cache all 
	while((Cache->CACHE_AES_CS &(1UL << CACHE_BUSY_POS)));
	Cache->CACHE_REF = (1UL << ALL_TAG_POS);
	Cache->CACHE_REF |= (1UL << CACHE_REFRESH_POS);
	while((Cache->CACHE_REF & (1UL << CACHE_REFRESH_POS)));	
}
