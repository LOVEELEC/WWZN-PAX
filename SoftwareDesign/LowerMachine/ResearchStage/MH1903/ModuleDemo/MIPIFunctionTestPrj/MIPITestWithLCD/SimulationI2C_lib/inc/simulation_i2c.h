/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : simulation_i2c.h
 * Author               : Megahuntmicro
 * Version              : V1.0.0
 * Date                 : 12/07/2015
 * Description          : Simulation I2C API interface file.
 *****************************************************************************/
 
 
#ifndef __SIMULATION_I2C_H__
#define __SIMULATION_I2C_H__
 
 
#ifdef __cplusplus
extern "C" {
#endif
	
/* Include ------------------------------------------------------------------*/
#include "mhscpu.h"
#include "stdbool.h"
#define RETRY_TIME_MAX          (10)  

typedef enum _SIMULATION_I2C_SPEED_Def
{
    USE_I2C_100KHZ,
    USE_I2C_400KHZ
} SIMULATION_I2C_SPEED;

typedef enum _SIMULATION_I2C_FuncExecStatus_Def
{
    SI2C_SUCCESS,
    SI2C_FAIL
}SI2C_FuncExecStatus;

typedef enum _SIMULATION_I2C_ACK_Status_Def
{
    ACK_SUCCESS,
    ACK_FAIL,
}SI2C_ACK_Status;    
    
typedef enum _SIMULATION_I2C_ACKMODE_Def
{
    SEND_ACK,
    NO_ACK,
} SI2C_ACK_Mode_Def;

/* Exported types -----------------------------------------------------------*/
typedef struct _iSimuI2C_Struct_Def{
    SI2C_FuncExecStatus (*Init)(SIMULATION_I2C_SPEED speed);
    SI2C_FuncExecStatus (*Start)(void);
    SI2C_FuncExecStatus (*Stop)(void);
    SI2C_ACK_Status     (*Wait_Ack)(void);
    SI2C_ACK_Status     (*Send_Ack)(void);
    SI2C_FuncExecStatus (*Send_NAck)(void);
    SI2C_ACK_Status     (*send_byte)(uint8_t send_data);
    uint8_t             (*receive_byte)(SI2C_ACK_Mode_Def ack_mode);
    bool                (*IsBusy)(void);
} iSimuI2C_Struct, *piSimuI2C_Struct;
/* Exported constants -------------------------------------------------------*/	
/* Exported macro -----------------------------------------------------------*/	
/* Exported functions -------------------------------------------------------*/	

/* Exported variables -------------------------------------------------------*/	

extern piSimuI2C_Struct	piSimuI2C;
	 
#ifdef __cplusplus
}
#endif	 

#endif	/* __SIMULATION_I2C_H__ */
/************************ (C) COPYRIGHT 2015 Megahuntmicro ****END OF FILE****/
