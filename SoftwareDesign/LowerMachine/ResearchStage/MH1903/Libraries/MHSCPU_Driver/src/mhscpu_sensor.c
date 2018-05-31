/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_sensor.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file provides all the SENSOR firmware functions
 *****************************************************************************/

/* Include ------------------------------------------------------------------*/
#include "mhscpu_retarget.h"

/******************************************************************************/
/*                                                                            */
/*                      SENSOR Control Unit Block                             */
/*                                                                            */
/******************************************************************************/

/****************  Bit definition for SEN_EXT_CFG register  *******************/
#define SEN_EXT_CFG_EXTS_LEVEL                      (0x0FFFUL)
#define SEN_EXT_CFG_FREQ_POS                        (12)
#define SEN_EXT_CFG_FREQ                            (BIT(13)|BIT(12))
#define SEN_EXT_CFG_FREQ_0                          BIT(12)
#define SEN_EXT_CFG_FREQ_1                          BIT(13)
#define SEN_EXT_CFG_EXTS_PROC                       BIT(15)

#define SEN_EXT_CFG_S_GF_POS                        (16)
#define SEN_EXT_CFG_S_GF                            (BIT(17)|BIT(16))
#define SEN_EXT_CFG_S_GF_0                          BIT(16)
#define SEN_EXT_CFG_S_GF_1                          BIT(17)

#define SEN_EXT_CFG_GF_EN                           BIT(18)
#define SEN_EXT_CFG_PUPU_EN                         BIT(19)
#define SEN_EXT_CFG_PUPU_HOLD_TIME                  (BIT(21)|BIT(20))
#define SEN_EXT_CFG_PUPU_HOLD_TIME_POS              (20)
#define SEN_EXT_CFG_PUPU_HOLD_TIME_0                BIT(20)
#define SEN_EXT_CFG_PUPU_HOLD_TIME_1                BIT(21)
#define SEN_EXT_CFG_D_GF_POS                        (22)
#define SEN_EXT_CFG_D_GF                            (BIT(23)|BIT(22))
#define SEN_EXT_CFG_D_GF_0                          BIT(22)
#define SEN_EXT_CFG_D_GF_1                          BIT(23)
#define SEN_EXT_CFG_PUPU_FREQ                       BIT(24)
#define SEN_EXT_CFG_TRIG_PULL                       BIT(26)


/****************  Bit definition for SEN_BRIDGE register  ********************/
#define SEN_BRIDGE_READ_START                       BIT(0)
#define SEN_BRIDGE_READ_READY                       BIT(1)
/*****************  Bit definition for SEN_SOFT_EN register  *******************/
#define SEN_SOFT_EN_SOFT_ATTACK_EN                  BIT(0)
/****************  Bit definition for SEN_SOFT_ATTACK register  ********************/
#define SEN_SOFT_ATTACK_SOFT_ATTACK                 BIT(0)
/****************  Bit definition for SEN_SOFT_LOCK register  ********************/
#define SEN_SOFT_LOCK_SOFT_ATTACK_LOCK              BIT(31)


#define SEN_ENABLE                                  ((uint32_t)0xAA)
#define SEN_DISABLE                                 ((uint32_t)0x55)

typedef enum
{
    SENSOR_EN_EXT0 = 0,
    SENSOR_EN_EXT1,
    SENSOR_EN_EXT2,
    SENSOR_EN_EXT3,
    SENSOR_EN_EXT4,
    SENSOR_EN_EXT5,
    SENSOR_EN_EXT6,
    SENSOR_EN_EXT7,
    //SENSOR_EN_EXT8,
    //SENSOR_EN_EXT9,
    //SENSOR_EN_EXT10,
    //SENSOR_EN_EXT11,
    SENSOR_EN_VH = 12,
    SENSOR_EN_VL,
    SENSOR_EN_TH,
    SENSOR_EN_TL,
    SENSOR_EN_XTAL32,
    SENSOR_EN_MESH,
    SENSOR_EN_VOLGLITCH,
}SENSOR_EN_Def;

/**
  * @brief  
  * @param  
  * @retval None
  */
uint32_t SENSOR_EXTInit(SENSOR_EXTInitTypeDef *SENSOR_EXTInitStruct)
{
    uint32_t i;	
    uint32_t tmpSensorExtType = 0, tmpSensorExtCfg = 0;
    uint32_t tmpSensorExtPort = 0, tmpSensorExtPortEn = 0;

    if (SET == SENSOR_EXTIsRuning())
	{
        return 3;	
	}

    /* simple rule check,each pin can be used only one mode */
    if (SENSOR_EXTInitStruct->SENSOR_Port_Static & SENSOR_EXTInitStruct->SENSOR_Port_Dynamic)
    {
        return 1;
    }
    
    /* Set SEN_EXT_TYPE register */
    for (i = 0; i < EXT_SENSOR_NUM/2; i++)
    {
        if (0 != (SENSOR_EXTInitStruct->SENSOR_Port_Dynamic & (0x03 << (i * 2))))
        {
            tmpSensorExtType |= (0x01 << (i * 2));
        }
    }	
	
    tmpSensorExtType |= (SENSOR_EXTInitStruct->SENSOR_Port_Pull & 0xFF) << 12;
    SENSOR->SEN_EXT_TYPE = tmpSensorExtType;

    /* set Dynamci Sensor ExtPort Frequency */
    SENSOR->SEN_EXT_CFG = (SENSOR->SEN_EXT_CFG & ~SEN_EXT_CFG_FREQ) | 
                          (SENSOR_EXTInitStruct->SENSOR_DynamicFrequency << SEN_EXT_CFG_FREQ_POS);


    /* set ExtPort Glitch Frequency */
    SENSOR->SEN_EXT_CFG = (SENSOR->SEN_EXT_CFG & ~SEN_EXT_CFG_D_GF) | 
                          (SENSOR_EXTInitStruct->SENSOR_Dynamic_Sample << SEN_EXT_CFG_D_GF_POS);

    SENSOR->SEN_EXT_CFG = (SENSOR->SEN_EXT_CFG & ~SEN_EXT_CFG_S_GF) | 
                          (SENSOR_EXTInitStruct->SENSOR_Static_Sample << SEN_EXT_CFG_S_GF_POS);

    /* enable/disable Dyanmci Sensor Glitch */
    if (DISABLE != SENSOR_EXTInitStruct->SENSOR_GlitchEnable)
    {
        SENSOR->SEN_EXT_CFG |= SEN_EXT_CFG_GF_EN;
    }

    tmpSensorExtCfg = SENSOR->SEN_EXT_CFG;
    /* disable ExtPort PUPU resistance */
    tmpSensorExtCfg &= ~SEN_EXT_CFG_PUPU_EN;
    tmpSensorExtCfg = (tmpSensorExtCfg & ~SEN_EXT_CFG_PUPU_FREQ) |
					  (SENSOR_EXTInitStruct->SENSOR_PUPU_Frequency << 24);
	
    tmpSensorExtCfg = (tmpSensorExtCfg & ~SEN_EXT_CFG_PUPU_HOLD_TIME) |
					  (SENSOR_EXTInitStruct->SENSOR_PUPU_HoldTime << SEN_EXT_CFG_PUPU_HOLD_TIME_POS);
	
    /* enable/disable ExtPort PUPU resistance */
    if (DISABLE != SENSOR_EXTInitStruct->SENSOR_PUPU_Enable)
    {
        tmpSensorExtCfg |= SEN_EXT_CFG_PUPU_EN;
    }
	
    tmpSensorExtCfg &= ~SEN_EXT_CFG_TRIG_PULL;
    if (DISABLE != SENSOR_EXTInitStruct->SENSOR_Trig_Hold_Enable)
    {
        tmpSensorExtCfg |= SEN_EXT_CFG_TRIG_PULL;
    }
    SENSOR->SEN_EXT_CFG = tmpSensorExtCfg;

    /* Enable or Disable Ext Sensors */
    if (DISABLE != SENSOR_EXTInitStruct->SENSOR_Port_Enable)
	{
        tmpSensorExtPortEn = SEN_ENABLE;	
	}
    else
	{
        tmpSensorExtPortEn = SEN_DISABLE;	
	}

	/* setting SEN_EN[x] register to effect the Sensor Port */
    tmpSensorExtPort = SENSOR_EXTInitStruct->SENSOR_Port_Static | SENSOR_EXTInitStruct->SENSOR_Port_Dynamic;
	for (i = 0; i < EXT_SENSOR_NUM; i++)
	{
		if (tmpSensorExtPort & (SENSOR_Port_S0 << i))
		{
			SENSOR->SEN_EN[SENSOR_EN_EXT0+i] = tmpSensorExtPortEn;
		}
		else
		{
			SENSOR->SEN_EN[SENSOR_EN_EXT0+i] = SEN_DISABLE;
		}
	}
 
    return 0;
}

uint32_t SENSOR_EXTPortCmd(uint32_t SENSOR_Port, FunctionalState NewState)
{
	uint32_t i;	
    volatile uint32_t tmpSensorExtPortEn = 0;
	
    if (SET == SENSOR_EXTIsRuning())
	{
		return 3;
	}
    
    if (DISABLE != NewState)
	{
        tmpSensorExtPortEn = SEN_ENABLE;	
	}
    else
	{
       tmpSensorExtPortEn = SEN_DISABLE;	
	}
    
	for (i = 0; i < EXT_SENSOR_NUM; i++)
	{
		if (SENSOR_Port & (SENSOR_Port_S0 << i))
		{
			SENSOR->SEN_EN[SENSOR_EN_EXT0+i] = tmpSensorExtPortEn;
		}
	}
    
    return 0;
}

/**
  * @brief  
  * @param  
  * @retval None
  */
uint32_t SENSOR_ANACmd(uint32_t SENSOR_ANA, FunctionalState NewState)
{
	uint32_t i;	
    volatile uint32_t tmpSensorExtPortEn = 0;
    assert_param(IS_SENSOR_ANA(SENSOR_ANA));

    if (DISABLE != NewState)
	{
        tmpSensorExtPortEn = SEN_ENABLE;	
	}
    else
	{
        tmpSensorExtPortEn = SEN_DISABLE;	
	}

	for (i = 0; i < INNER_SENSOR_NUM; i++)
	{
		if (SENSOR_ANA & (SENSOR_ANA_VOL_HIGH << i))
		{
			SENSOR->SEN_EN[SENSOR_EN_VH+i] = tmpSensorExtPortEn;
		}
	}
	
	if ((SENSOR_ANA & SENSOR_ANA_MESH) && (DISABLE == NewState))
	{
		SENSOR->SEN_EN[SENSOR_EN_MESH] |= BIT(31);
	}
	  
    return 0;
}

FunctionalState SENSOR_SetEXTFilter(FunctionalState NewState)
{
    if (DISABLE == NewState)
    {
        SENSOR->SEN_EXT_CFG &= ~SEN_EXT_CFG_GF_EN;
    }
    else
    {
        SENSOR->SEN_EXT_CFG |= SEN_EXT_CFG_GF_EN;
    }
	
    return NewState;
}

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
