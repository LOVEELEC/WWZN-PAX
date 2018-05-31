/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_sdram.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file provides all the SDRAM firmware functions
 *****************************************************************************/  

/* Include ------------------------------------------------------------------*/
#include "mhscpu_sdram.h"

#define FILLWORD	(0xA55A5AA5UL)
#define PAGEBYTES	8192
#define PAGEWORDS	2048

uint32_t *testbuf;
uint32_t *testread;
uint32_t ModeReister;


void SDRAM_Init(MPMC_InitTypeDef *MPMC_InitStructure)
{
	// DISABLE MPMC
	MPMC->CONTROL = 0;
	// Wait Stable
	Delay_10us(1);
	
	// FeedBack Clock Delay 45бу
	SYSCTRL->MPMC_CTRL = 0x0002001F;
	MPMC->CONFIG = MPMC_InitStructure->MPMC_Endian;					// Little-endian Mode
	MPMC->DYNAMIC_REFRESH = 38;				// Dyn Refresh Time 46
	MPMC->DYNAMIC_READCONFIG = 0x00001111;	// Postive + FeedBack
	MPMC->DYNAMIC_RP = 0x02&0x0F;			// MPMC Dyn t(RP) > 15ns [0:3] (default 0x0F + 1 CLK)
	MPMC->DYNAMIC_RAS = 0x04&0x0F;			// MPMC Dyn t(RAS) > 40ns [0:3] (default 0x0F + 1 CLK)
	MPMC->DYNAMIC_SREX = 0x04&0x7F;			// MPMC Dyn t(SREX) > 72ns [0:6] (default 0x0F + 1 CLK)
	MPMC->DYNAMIC_WR = 0x02&0x0F;			// MPMC Dyn t(WR) > 2CLK [0:3] (default 0x0F + 1 CLK)
	MPMC->DYNAMIC_RC = 0x02&0x1F;			// MPMC Dyn t(RC) > 60ns [0:4] (default 0x1F + 1 CLK)
	MPMC->DYNAMIC_RFC = 0x07&0x1F;			// MPMC Dyn t(RFC) > 60ns [0:4] (default 0x1F + 1 CLK)
	MPMC->DYNAMIC_XSR = 0x04&0xFF;			// MPMC Dyn t(XSR) > 72ns [0:7] (default 0x0F + 1 CLK)
	MPMC->DYNAMIC_RRD = 0x02&0x0F;			// MPMC Dyn t(RRD) > 2CLK [0:3] (default 0x0F + 1 CLK)
	MPMC->DYNAMIC_MRD = 0x02&0x0F;			// MPMC Dyn t(MRD/RSC) > 2CLK [0:3] (default 0x0F + 1 CLK)
	// tCCD, read/write to read/write period
	MPMC->DYNAMIC_CDLR = 0x01&0x0F;			// MPMC Dyn t(CDLR) > 1CLK [0:3] (default 0x0F + 1 CLK)
	MPMC->DYNAMIC_CONFIG1 = 0x480;			// MPMC Dyn Choice 128M(8Mx16),4 banks,row 12,col 9
	MPMC->DYNAMIC_RASCAS1 = 0x03|(MPMC_InitStructure->MPMC_CAS << 8);			// MPMC CAS Choice three cycles
										// MPMC RAS 3 cycles (default)
	MPMC->AHB_CONTROL0 = MPMC_InitStructure->MPMC_Buffer;
	MPMC->AHB_CONTROL1 = MPMC_InitStructure->MPMC_Buffer;
	MPMC->AHB_CONTROL2 = MPMC_InitStructure->MPMC_Buffer;
	MPMC->AHB_CONTROL3 = MPMC_InitStructure->MPMC_Buffer;
	MPMC->AHB_CONTROL4 = MPMC_InitStructure->MPMC_Buffer;
	MPMC->DYNAMIC_CONTROL = 0x18a;			// SDRAM NOP
	MPMC->DYNAMIC_CONTROL = 0x10a;			// SDRAM PreCharge
	MPMC->CONTROL = 1;

	Delay_10us(1);
	// Wait Stable
	while (MPMC->STATUS)
	{
		Delay_10us(2);
	}

	MPMC->DYNAMIC_CONTROL = 0x08a;			// SDRAM Mode Register Setting
	Delay_10us(1);
	ModeReister = *((uint32_t *)(0x60001000|(MPMC_InitStructure->MPMC_CAS << 16)));
	Delay_10us(1);
	MPMC->DYNAMIC_CONTROL = 0xa;		   // SDRAM Normal
}
