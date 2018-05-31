/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_qspi.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file provides all the QSPI firmware functions
 *****************************************************************************/

 /* Includes ----------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include "mhscpu_retarget.h"


typedef enum
{
    MH_OK = 0x00,
    MH_ERROR = 0x01,
    MH_BUSY = 0x02,
    MH_TIMEOUT = 0x03
}MH_StatusTypeDef;

typedef struct
{
    uint8_t Instruction;       
    QSPI_BusModeTypeDef BusMode;
    QSPI_CmdFormatTypeDef CmdFormat;
    uint32_t Address;
	
    uint32_t WrData;
    uint32_t RdData;
	
}MH_CommandTypeDef;


#define MH_QSPI_TIMEOUT_DEFAULT_CNT	        (19000)

#define IS_PARAM_NOTNULL(PARAM)			    ((PARAM) != NULL)
#define IS_QSPI_ADDR(ADDR)					((((int32_t)(ADDR) ) >= (uint32_t)(0x00000000)) &&\
											(((int32_t)(ADDR) ) <= (uint32_t)(0x00FFFFFF)))

#define IS_QSPI_ADDR_ADD_SZ(ADDR, SZ)		((((int32_t)((ADDR) + (SZ))) >= (uint32_t)(0x00000000)) && \
											(((int32_t)((ADDR) + (SZ))) <= (uint32_t)(0x00FFFFFF)))

#define MH_QSPI_ACCESS_REQ_ENABLE           (0x00000001U)

#define MAX_RD_DATA_LEN		0x10
#define MAX_WR_DATA_LEN		0x04


static MH_StatusTypeDef MH_QSPI_Command(MH_CommandTypeDef *cmd, int32_t timeout)
{
	MH_StatusTypeDef status = MH_ERROR;
	
	assert_param(IS_PARAM_NOTNULL(cmd));	

	MHSCPU_MODIFY_REG32(&(QSPI->REG_RDATA), (QUADSPI_REG_RDATA), (0x00000000));
	
	MHSCPU_MODIFY_REG32(&(QSPI->REG_WDATA), (QUADSPI_REG_WDATA), (cmd->WrData));
	MHSCPU_MODIFY_REG32(&(QSPI->ADDRES), (QUADSPI_ADDRESS_ADR), (cmd->Address << 8));
	MHSCPU_MODIFY_REG32(&(QSPI->FCU_CMD), 
						(QUADSPI_FCU_CMD_CODE | QUADSPI_FCU_CMD_BUS_MODE | QUADSPI_FCU_CMD_CMD_FORMAT | QUADSPI_FCU_CMD_ACCESS_REQ),
						(((uint32_t)(cmd->Instruction << 24)) |((uint32_t)( cmd->BusMode<< 8)) |((uint32_t)( cmd->CmdFormat << 4))| (MH_QSPI_ACCESS_REQ_ENABLE)));
	
	//Wait For CMD done
	for (timeout = 0; timeout < MH_QSPI_TIMEOUT_DEFAULT_CNT; timeout += 4)
	{
		if (QSPI->INT_RAWSTATUS & BIT0)
		{
			QSPI->INT_CLEAR = 0x01;
			status = MH_OK;
			break;
		}
	}

	cmd->RdData = QSPI->REG_RDATA;

	return status;
}

uint8_t QSPI_Read(QSPI_CommandTypeDef *cmdParam, uint8_t* buf, uint32_t addr, uint32_t sz)
{
	uint32_t read_times = 0,i = 0, j = 0, k = 0;
	uint8_t end_len = 0;
	MH_CommandTypeDef sCommand;

	addr &= (uint32_t)(0x00FFFFFF);
	assert_param(IS_QSPI_ADDR(addr));
	assert_param(IS_QSPI_ADDR_ADD_SZ(addr, sz));
	
	if (cmdParam == NULL)
	{
		sCommand.Instruction = READ_CMD;
		sCommand.BusMode = QSPI_BUSMODE_111;
		sCommand.CmdFormat = QSPI_CMDFORMAT_CMD8_ADDR24_RDAT;
	}
	else
	{
		sCommand.Instruction = cmdParam->Instruction;       
		sCommand.BusMode = cmdParam->BusMode;
		sCommand.CmdFormat = cmdParam->CmdFormat;
	}
	
	//由于芯片读取速率问题，每次最多读6*32bits的数据
	read_times = sz / MAX_RD_DATA_LEN;
	end_len = sz % MAX_RD_DATA_LEN;

	for (i = 0; i < read_times; i ++)
	{
		QSPI->FIFO_CNTL |= BIT15;
		QSPI->BYTE_NUM = MAX_RD_DATA_LEN;
		
		sCommand.Address = addr;

		if (MH_QSPI_Command(&sCommand, MH_QSPI_TIMEOUT_DEFAULT_CNT) != MH_OK)
		{
			return QSPI_STATUS_ERROR;
		}

		j = (QSPI->FIFO_CNTL & 0x0000000F);
		for(k = 0; k < j; k++)
		{
			*(uint32_t *)(buf) =  QSPI->RD_FIFO;
			buf += 4;
		}
		
		addr = addr + MAX_RD_DATA_LEN;
	}

	QSPI->FIFO_CNTL |= BIT15;
	sCommand.Address = addr;
	if (end_len > 0)
	{
		QSPI->BYTE_NUM = end_len;
		
		if(MH_QSPI_Command(&sCommand, MH_QSPI_TIMEOUT_DEFAULT_CNT) != MH_OK)
		{
			return QSPI_STATUS_ERROR;
		}
		
		j = (QSPI->FIFO_CNTL & 0x0000000F);
		for(k = 0; k < j; k++)
		{
			*(uint32_t *)(buf) = QSPI->RD_FIFO;
			buf += 4;
		}
	}
	
	return QSPI_STATUS_OK;
}


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
