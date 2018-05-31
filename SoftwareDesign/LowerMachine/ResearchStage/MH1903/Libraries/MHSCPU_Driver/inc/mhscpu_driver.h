/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_driver.h
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-May-2017
 * @brief               : This file contains all the module functions prototypes for the firmware library
 *****************************************************************************/

#ifndef __MHSCPU_DRIVER_H
#define __MHSCPU_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "mhscpu_sysctrl.h"
#include "mhscpu_spi.h"
#include "mhscpu_wdt.h"
#include "mhscpu_crc.h"
#include "mhscpu_timer.h"
#include "mhscpu_gpio.h"
#include "mhscpu_exti.h"
#include "mhscpu_rtc.h"
#include "mhscpu_sensor.h"
#include "mhscpu_ssc.h"
#include "mhscpu_bpk.h"
#include "mhscpu_trng.h"
#include "mhscpu_i2c.h"
#include "mhscpu_kcu.h"
#include "mhscpu_adc.h"
#include "mhscpu_dma.h"
#include "mhscpu_lcdi.h"
#include "mhscpu_clcd.h"
#include "mhscpu_dcmi.h"
#include "mhscpu_sdio.h"
#include "mhscpu_cache.h"
#include "mhscpu_qspi.h"
#include "mhscpu_otp.h"
#include "mhscpu_version.h"
#include "mhscpu_uart.h"

#ifdef USE_CRYPT_MODULE
#include "mh_sha.h"
#include "mh_aes.h"
#include "mh_des.h"
#include "mh_rsa.h"
#include "mh_ecc.h"
#include "mh_sm2.h"
#include "mh_sm3.h"	
#include "mh_sm4.h"
#include "mh_bignum.h"
#include "mh_misc.h"
#include "mh_crypt.h"	 
#include "mh_crypt_version.h"
#endif

#ifdef USE_USB_MODULE
#include "usb_core.h"
#include "usbd_core.h"
#endif

#ifdef USE_SCI_MODULE
#include "mhscpu_sci.h"
#include "emv_core.h"
#include "iso7816_3.h"

#define SCI_FUNC_PATCH     (0)
#endif

/* Exported types ------------------------------------------------------------*/
/* SYSCTRL Module */
typedef struct
{
	void (*AHBPeriphClockCmd)(uint32_t SYSCTRL_AHBPeriph, FunctionalState NewState);
	void (*AHBPeriphResetCmd)(uint32_t SYSCTRL_AHBPeriph, FunctionalState NewState);
	void (*APBPeriphClockCmd)(uint32_t SYSCTRL_APBPeriph, FunctionalState NewState);
	void (*APBPeriphResetCmd)(uint32_t SYSCTRL_APBPeriph, FunctionalState NewState);

	void (*EnterSleep)(SleepMode_TypeDef SleepMode);
	void (*WakeIntDeInit)(void);
	void (*WakeUpInt1Config)(uint32_t SYSCTRL_WakeInt, FunctionalState NewState);
	void (*WakeUpInt2Config)(uint32_t SYSCTRL_WakeInt, FunctionalState NewState);
	uint32_t (*GetWakeupFlag1Status)(void);
	uint32_t (*GetWakeupFlag2Status)(void);

	void (*SYSCLKSourceSelect)(SYSCLK_SOURCE_TypeDef source_select);
	void (*PLLConfig)(SYSCTRL_PLL_TypeDef PLL_Freq);
	void (*PLLDivConfig)(uint32_t PLL_Div);
	void (*HCLKConfig)(uint32_t HCLK_Div);
	void (*PCLKConfig)(uint32_t PCLK_Div);

	void (*GetClocksFreq)(SYSCTRL_ClocksTypeDef *SYSCTRL_Clocks);
}SYSCTRL_FuncTypeDef;

/* CRC Module */
typedef struct
{
	uint32_t (*CalcBlock)(uint32_t CRC_type, uint8_t *pData, uint32_t len);
	uint32_t (*Calc)(CRC_ConfigTypeDef *CRC_Config, uint8_t *pData, uint32_t len);
}CRC_FuncTypeDef;

/* ADC Module */
typedef struct
{
	void (*Init)(ADC_InitTypeDef *ADC_InitStruct);
	void (*StartCmd)(FunctionalState NewState);
	void (*FIFODeepth)(uint32_t FIFO_Deepth);
	void (*FIFOReset)(void);
	void (*ITCmd)(FunctionalState NewState);
	void (*FIFOOverflowITcmd)(FunctionalState NewState);
	int32_t (*GetFIFOCount)(void);
	int32_t (*GetResult)(void);
	int32_t (*GetFIFOResult)(uint16_t *ADCdata, uint32_t len);
	uint32_t (*CalVoltage)(uint32_t u32ADC_Value, uint32_t u32ADC_Ref_Value);
}ADC_FuncTypeDef;

/* GPIO Module */
typedef struct
{
	void (*DeInit)(void);
	void (*Init)(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
	void (*StructInit)(GPIO_InitTypeDef *GPIO_InitStruct);

	uint8_t (*ReadInputDataBit)(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
	uint16_t (*ReadInputData)(GPIO_TypeDef *GPIOx);

	uint8_t (*ReadOutputDataBit)(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
	uint16_t (*ReadOutputData)(GPIO_TypeDef *GPIOx);

	void (*SetBits)(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
	void (*ResetBits)(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
	void (*Write)(GPIO_TypeDef *GPIOx, uint16_t PortVal);
	void (*PullUpCmd)(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, FunctionalState NewState);

	void (*PinRemapConfig)(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_RemapTypeDef GPIO_Remap);

	void (*WakeEvenDeInit)(void);
	void (*WakeEvenConfig)(uint32_t GPIO_PortSource, uint32_t GPIO_PinSource, FunctionalState NewState);
	void (*WakeModeConfig)(GPIO_WakeModeTypeDef GPIO_WakeMode);	
}GPIO_FuncTypeDef;

/* EXTI Module */
typedef struct
{
	void (*DeInit)(void);
	void (*LineConfig)(uint32_t EXTI_Line, uint32_t EXTI_PinSource,  EXTI_TriggerTypeDef EXTI_Trigger);
	uint32_t (*GetITStatus)(void);
	uint32_t (*GetITLineStatus)(uint32_t EXTI_Line);
	void (*ClearITPendingBit)(uint32_t EXTI_Line);
}EXTI_FuncTypeDef;

/* TIMER Module */
typedef struct
{
	void (*DeInit)(TIM_Module_TypeDef *TIMMx);
	void (*Init)(TIM_Module_TypeDef *TIMMx, TIM_InitTypeDef *TIM_InitStruct);

	void (*PWMInit)(TIM_Module_TypeDef *TIMMx, TIM_PWMInitTypeDef *TIM_PWMInitStruct);
	void (*Cmd)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx, FunctionalState NewState);
	void (*ModeConfig)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx, TIM_ModeTypeDef TIM_Mode);
	void (*SetPeriod)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx, uint32_t Period);
	void (*SetPWMPeriod)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx, uint32_t PWM_LowLevelPeriod, uint32_t PWM_HighLevelPeriod);
	void (*ITConfig)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx, FunctionalState NewState);
	void (*ClearITPendingBit)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx);
	void (*PWMSinglePulseConfig)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx, FunctionalState NewState);

	ITStatus (*GetITStatus)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx);
	uint32_t (*GetAllITStatus)(TIM_Module_TypeDef *TIMMx);
	ITStatus (*GetRawITStatus)(TIM_Module_TypeDef *TIMMx, TIM_NumTypeDef TIMx);
	uint32_t (*GetAllRawITStatus)(TIM_Module_TypeDef *TIMMx);
}TIM_FuncTypeDef;

/* UART Module */
typedef struct
{
	void (*DeInit)(UART_TypeDef *UARTx);
	void (*Init)(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);
	void (*StructInit)(UART_InitTypeDef *UART_InitStruct);
	void (*ITConfig)(UART_TypeDef *UARTx, uint32_t UART_IT, FunctionalState NewState);

	void (*SendData)(UART_TypeDef *UARTx, uint8_t Data);
	uint8_t (*ReceiveData)(UART_TypeDef *UARTx);

	void (*FIFOInit)(UART_TypeDef *UARTx, UART_FIFOInitTypeDef *UART_FIFOInitStruct);
	void (*FIFOStructInit)(UART_FIFOInitTypeDef *UART_FIFOInitStruct);
	void (*FIFOReset)(UART_TypeDef *UARTx, uint32_t UART_FIFO);
	void (*FIFOCmd)(UART_TypeDef *UARTx, FunctionalState NewState);
	void (*SetRTS)(UART_TypeDef *UARTx);
	void (*ResetRTS)(UART_TypeDef *UARTx);
	void (*SetDTR)(UART_TypeDef *UARTx);
	void (*ResetDTR)(UART_TypeDef *UARTx);
	void (*SendBreak)(UART_TypeDef *UARTx);
	void (*AutoFlowCtrlCmd)(UART_TypeDef *UARTx, FunctionalState NewState);
	void (*IrDACmd)(UART_TypeDef *UARTx, FunctionalState NewState);

	uint32_t (*GetLineStatus)(UART_TypeDef *UARTx);
	uint32_t (*GetModemStatus)(UART_TypeDef *UARTx);
	uint32_t (*GetITIdentity)(UART_TypeDef *UARTx);

	Boolean (*IsTXEmpty)(UART_TypeDef *UARTx);
	Boolean (*IsTXHoldingRegisterEmpty)(UART_TypeDef *UARTx);

	Boolean (*IsRXFIFOFull)(UART_TypeDef *UARTx);
	Boolean (*IsRXFIFONotEmpty)(UART_TypeDef *UARTx);
	Boolean (*IsTXFIFOEmpty)(UART_TypeDef *UARTx);
	Boolean (*IsTXFIFONotFull)(UART_TypeDef *UARTx);
	Boolean (*IsBusy)(UART_TypeDef *UARTx);

	void (*DMAGenerateSoftAck)(UART_TypeDef *UARTx);

	void (*TXHaltCmd)(UART_TypeDef *UARTx, FunctionalState NewStatus);
	void (*FIFOAccessModeCmd)(UART_TypeDef *UARTx, FunctionalState NewStatus);
	uint8_t (*FIFOTxRead)(UART_TypeDef *UARTx);	
}UART_FuncTypeDef;

/* SPI Module */
typedef struct
{
	void (*DeInit)(SPI_TypeDef *SPIx);
	void (*Init)(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
	void (*StructInit)(SPI_InitTypeDef *SPI_InitStruct);
	void (*Cmd)(SPI_TypeDef *SPIx, FunctionalState NewState);

	void (*DMAInit)(SPI_TypeDef *SPIx, SPI_DMAInitTypeDef *SPI_DMAInitStruct);
	void (*DMAStructInit)(SPI_DMAInitTypeDef *SPI_DMAInitStruct);
	void (*DMACmd)(SPI_TypeDef *SPIx, uint32_t SPI_DMAReq, FunctionalState NewState);

	void (*ITConfig)(SPI_TypeDef *SPIx, uint32_t SPI_IT, FunctionalState NewState);
	void (*SendData)(SPI_TypeDef *SPIx, uint16_t Data);
	uint16_t (*ReceiveData)(SPI_TypeDef *SPIx);
	void (*DataSizeConfig)(SPI_TypeDef *SPIx, uint32_t SPI_DataSize);
	void (*BiDirectionalLineConfig)(SPI_TypeDef *SPIx, uint32_t SPI_Direction);

	ITStatus (*GetITStatus)(SPI_TypeDef *SPIx, uint32_t SPI_IT);
	void (*ClearITPendingBit)(SPI_TypeDef *SPIx, uint32_t SPI_IT);

	FlagStatus (*GetFlagStatus)(SPI_TypeDef *SPIx, uint32_t SPI_FLAG);
	uint32_t (*GetFlagStatusReg)(SPI_TypeDef *SPIx);

	FlagStatus (*IsBusy)(SPI_TypeDef *SPIx);
	FlagStatus (*IsTXErr)(SPI_TypeDef *SPIx);
	FlagStatus (*IsDataCollisionErr)(SPI_TypeDef *SPIx);

	void (*SSP_Init)(SPI_TypeDef *SPIx, SSP_InitTypeDef *SSP_InitStruct);
	void (*SSP_StructInit)(SSP_InitTypeDef *SSP_InitStruct);

	void (*NSM_Init)(SPI_TypeDef *SPIx, NSM_InitTypeDef *NSM_InitStruct);
	void (*NSM_StructInit)(NSM_InitTypeDef *NSM_InitStruct);	
}SPI_FuncTypeDef;

/* I2C Module */
typedef struct
{
	void (*DeInit)(I2C_TypeDef *I2Cx);
	void (*Init)(I2C_TypeDef *I2Cx,I2C_InitTypeDef *I2C_InitStruct);
	void (*StructInit)(I2C_InitTypeDef *I2C_InitStruct);

	void (*Cmd)(I2C_TypeDef *I2Cx, FunctionalState NewState);
	void (*SetTargetAddress)(I2C_TypeDef *I2Cx, uint32_t TargetAddress, uint32_t TargetAddressMode);
	void (*DMAInit)(I2C_TypeDef *I2Cx, I2C_DMAInitTypeDef *I2C_DMAInitStruct);
	void (*DMAStructInit)(I2C_DMAInitTypeDef *I2C_DMAInitStruct);
	void (*DMACmd)(I2C_TypeDef *I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState);
	void (*SetSDASetupTime)(I2C_TypeDef *I2Cx,uint32_t PCLKCycles);
	void (*SetSDAHoldTime)(I2C_TypeDef *I2Cx,uint32_t PCLKCycles);

	void (*ITConfig)(I2C_TypeDef *I2Cx,uint32_t I2C_IT, FunctionalState NewState);
	ITStatus (*GetITStatus)(I2C_TypeDef *I2Cx,uint32_t I2C_IT);
	ITStatus (*GetRawITStatus)(I2C_TypeDef *I2Cx,uint32_t I2C_IT);
	void (*ClearITPendingBit)(I2C_TypeDef *I2Cx,uint32_t I2C_IT);
	FlagStatus (*GetFlagStatus)(I2C_TypeDef *I2Cx,uint32_t I2C_FLAG);
	uint32_t (*GetFlagStatusReg)(I2C_TypeDef *I2Cx);
	FlagStatus (*GetTXAbortSource)(I2C_TypeDef *I2Cx,uint32_t I2C_TX_ABRT);
	uint32_t (*GetTXAbortSourceReg)(I2C_TypeDef *I2Cx);
	I2CMode_TypeDef (*GetI2CMode)(I2C_TypeDef *I2Cx);

	void (*MasterGenerateReceiveSCL)(I2C_TypeDef *I2Cx, I2CDataEndCondition_TypeDef DataCondition);
	uint16_t (*ExtendData)(uint8_t Data, I2CDataCMD_TypeDef DataCMD, I2CDataEndCondition_TypeDef DataCondition);
	void (*WriteDataToDR)(I2C_TypeDef *I2Cx, uint16_t ExtendData);
	uint8_t (*ReadDataFromDR)(I2C_TypeDef *I2Cx);
	void (*SendData)(I2C_TypeDef *I2Cx, uint8_t Data, I2CDataEndCondition_TypeDef DataCondition);
	uint8_t (*ReceiveData)(I2C_TypeDef *I2Cx, I2CDataEndCondition_TypeDef DataCondition);
	void (*SendBytes)(I2C_TypeDef *I2Cx, uint8_t *Data, uint32_t DataLen, I2CDataEndCondition_TypeDef DataCondition);
	void (*ReceiveBytes)(I2C_TypeDef *I2Cx, uint8_t *Data, uint32_t DataLen, I2CDataEndCondition_TypeDef DataCondition);

	void (*SlaveGeneralNACKOnlyCmd)(I2C_TypeDef *I2Cx, FunctionalState NewState);

	FlagStatus (*IsEnable)(I2C_TypeDef *I2Cx);		
}I2C_FuncTypeDef;

/* KCU Module */
typedef struct
{
	void (*DeInit)(void);
	void (*Init)(KCU_InitTypeDef *KCU_InitStruct);
	void (*StructInit)(KCU_InitTypeDef *KCU_InitStruct);

	void (*Cmd)(FunctionalState NewState);	 
	uint32_t (*SetRand)(uint32_t rand);

	void (*ITConfig)(uint32_t KCU_IT, FunctionalState NewState);
	FlagStatus (*GetITStatus)(uint32_t KCU_IT);
	void (*ClearITPending)(void);
	uint32_t (*GetEvenReg)(void);	
}KCU_FuncTypeDef;

/* BPK Module */
typedef struct
{
	FlagStatus (*IsReady)(void);

	ErrorStatus (*WriteKey)(uint32_t *Key,uint32_t Key_Len, uint32_t Key_Offset);
	ErrorStatus (*ReadKey)(uint32_t *Key,uint32_t Key_Len, uint32_t Key_Offset);

	void (*KeyWriteLock)(uint16_t BPK_KEY_Region, FunctionalState NewState);
	void (*KeyReadLock)(uint16_t BPK_KEY_Region, FunctionalState NewState);
	void (*KeyClear)(uint16_t BPK_KEY_Region);

	void (*SetScramber)(uint32_t Scram);
	void (*Reset)(void);

	void (*Lock)(uint32_t BPK_LOCK, FunctionalState NewState);
	void (*LockSelf)(void);
	FlagStatus (*GetLockStatus)(uint32_t BPK_LOCK);
}BPK_FuncTypeDef;

/* SENSOR Module */
typedef struct
{
	uint32_t (*SetRand)(uint32_t Rand);
	uint32_t (*EXTInit)(SENSOR_EXTInitTypeDef *SENSOR_EXTInitStruct);
	uint32_t (*EXTPortCmd)(uint32_t SENSOR_Port, FunctionalState NewState);
	uint32_t (*EXTCmd)(FunctionalState NewState);
	FlagStatus (*EXTIsRuning)(void);
	uint32_t (*ANACmd)(uint32_t SENSOR_ANA, FunctionalState NewState);
	void (*Lock)(uint32_t SENSOR_LOCK);
	void (*AttackRespMode)(SENSOR_RespModeTypeDef SENSOR_RespMode);

	int32_t (*GetITStatus)(uint32_t ITState);
	int32_t (*GetITStatusReg)(void);
	void (*ClearITPendingBit)(void);

	FunctionalState (*GetEXTTrigPull)(void);
	FunctionalState (*SetEXTTrigPull)(FunctionalState NewState);

	FunctionalState (*GetEXTFilter)(void);
	FunctionalState (*SetEXTFilter)(FunctionalState NewState);

	uint32_t (*GetEXTPulsePeriod)(void);
	uint32_t (*SetEXTPulsePeriod)(uint32_t Period);

	uint32_t (*GetEXTPulseHold)(void);
	uint32_t (*SetEXTPulseHold)(uint32_t tphHold);

	FunctionalState (*GetEXTPulsePull)(void);
	FunctionalState (*SetEXTPulsePull)(FunctionalState NewState);	

	uint32_t (*GetEXTStaticSample)(void);
	uint32_t (*SetEXTStaticSample)(uint32_t tscTimes);
	uint32_t (*GetEXTDynamicSample)(void);
	uint32_t (*SetEXTDynamicSample)(uint32_t tscTimes);

	uint32_t (*GetEXTDynamicFreq)(void);
	uint32_t (*SetEXTDynamicFreq)(uint32_t tdfFreq);		
}SENSOR_FuncTypeDef;

/* SSC Module */
typedef struct
{
	void (*Init)(SSC_InitTypeDef *SSC_InitStruct);
	
	ITStatus (*GetITStatus)(uint32_t SSC_IT);
	void (*ClearITPendingBit)(uint32_t SSC_IT);

	void (*SetDataRAMScrambler)(uint32_t Scrambler);
	void (*BPKAccessCtrlConfig)(uint32_t SSC_BPKAccessCtrBlock, SSC_BPKAccessCtrlTypeDef SSC_BPKAccessCtr);
	
	uint32_t (*SensorCmd)(uint32_t SSC_SENSOR, FunctionalState NewState);
	void (*SensorLock)(uint32_t SSC_SENSOR);
	void (*SensorAttackRespMode)(SSC_SENSOR_RespModeTypeDef SSC_SENSOR_RespMode);
}SSC_FuncTypeDef;

/* TRNG Module */
typedef struct
{
	void (*Start)(TRNG_ChannelTypeDef TRNGx);
	void (*Stop)(TRNG_ChannelTypeDef TRNGx);
	uint32_t (*Get)(uint32_t rand[4], TRNG_ChannelTypeDef TRNGx);
	void (*SetPseudoRandom)(uint32_t PseudoRandom);
	void (*DirectOutANA)(TRNG_ChannelTypeDef TRNGx, FunctionalState NewState);

	void (*ITConfig)(FunctionalState NewState);
	ITStatus (*GetITStatus)(uint32_t TRNG_IT);
	void (*ClearITPendingBit)(uint32_t TRNG_IT);	

	void (*SelectPDSource)(TRNG_PDSourceTypeDef SOURCEx);	
}TRNG_FuncTypeDef;

/* RTC Module */
typedef struct
{
	FlagStatus (*IsReady)(void);

	void (*ResetCounter)(void);
	uint32_t (*GetCounter)(void);

	void (*SetRefRegister)(uint32_t RefValue);
	uint32_t (*GetRefRegister)(void);

	void  (*SetAlarm)(uint32_t AlarmValue);

	uint32_t (*GetAttrackTime)(void);

	void (*ITConfig)(FunctionalState NewState);
	void (*ClearITPendingBit)(void);
	ITStatus (*GetITStatus)(void);	
}RTC_FuncTypeDef;

/* WDT Module */
typedef struct
{
	void (*SetReload)(uint32_t Reload);
	void (*ReloadCounter)(void);
	void (*Enable)(void);
	void (*ModeConfig)(WDT_ModeTypeDef WDT_Mode);
		 
	ITStatus (*GetITStatus)(void);
	void (*ClearITPendingBit)(void);	
}WDT_FuncTypeDef;

/* DMA Module */
typedef struct
{
	void (*Init)(DMA_TypeDef *DMA_Channelx, DMA_InitTypeDef *DMA_InitStruct);
	void (*ChannelCmd)(DMA_TypeDef *DMA_Channelx, FunctionalState NewState);
	void (*Cmd)(FunctionalState NewState);

	void (*SetSRCAddress)(DMA_TypeDef *DMA_Channelx, uint32_t Address);
	void (*SetDSRAddress)(DMA_TypeDef *DMA_Channelx, uint32_t Address);
	void (*SetChannelHardShakePeriph)(DMA_TypeDef *DMA_Channelx,uint32_t HardwareHandshake_Peripheral);
		 
	void (*ITConfig)(DMA_TypeDef *DMA_Channelx, uint32_t DMA_IT, FunctionalState NewState);

	FunctionalState (*IsChannelEnabled)(DMA_TypeDef *DMA_Channelx);
		 
	ITStatus (*GetITStatus)(DMA_TypeDef *DMA_Channelx,uint32_t DMA_IT);
	FlagStatus (*GetRawStatus)(DMA_TypeDef *DMA_Channelx,uint32_t DMA_IT);
	void (*ClearITPendingBit)(DMA_TypeDef *DMA_Channelx,uint32_t DMA_IT);

	void (*MultiBlockInit)(DMA_TypeDef *DMA_Channelx, DMA_InitTypeDef *DMA_InitStruct , LLI *first_lli, uint8_t Multi_Block_Mode);
	void (*InitLLI)(DMA_TypeDef *DMA_Channelx, LLI *lli, LLI *next_lli, void *src_addr, void *dest_addr, uint16_t btsize);	
}DMA_FuncTypeDef;

/* LCD Module */
typedef struct
{
	void (*BusRead)(LCD_TypeDef *LCDx, uint8_t u8CD);
	void (*BusWrite)(LCD_TypeDef *LCDx, uint8_t u8CD, uint8_t value);

	void (*Read)(LCD_TypeDef *LCDx, uint8_t u8CD, uint8_t *dat);
	void (*Write)(LCD_TypeDef *LCDx, uint8_t u8CD, uint8_t u8Value);

	int32_t (*ReadBuff)(LCD_TypeDef *LCDx, LCD_InitTypeDef *pLcdInit, uint8_t *pu8Buff, uint32_t u32BuffLen);
	int32_t (*WriteBuff)(LCD_TypeDef *LCDx, LCD_InitTypeDef *pLcdInit, uint8_t *pu8Buff, uint32_t u32BuffLen);

	void (*Init)(LCD_TypeDef *LCDx, LCD_InitTypeDef *pLcdInit);
	void (*FIFODMAconfig)(LCD_TypeDef *LCDx, LCD_InitTypeDef *LCD_InitType);
}LCD_FuncTypeDef;

/* CLCD Module */
typedef struct
{
	uint32_t (*Init)(CLCD_TypeDef *ClCD, CLCD_InitTypeDef *CLCD_InitStruct);
	void (*InterruptEventsEnable)(CLCD_TypeDef *ClCD, uint32_t Interrupts);
	void (*InterruptEventsDisable)(CLCD_TypeDef *ClCD, uint32_t Interrupts);
	void  (*PowerUp)(CLCD_TypeDef *ClCD, CLCD_DisplayParams *pParams);
	void (*PowerDown)(CLCD_TypeDef *ClCD, CLCD_DisplayParams *pParams);
	void (*VCompEventsEnable)(CLCD_TypeDef *ClCD, CLCD_eVComp_ITime eVCompEvent);
	uint32_t (*BppSet)(CLCD_TypeDef *ClCD, CLCD_DisplayParams *pState, uint32_t Bpp);
	void (*DrawCLS)(CLCD_TypeDef *ClCD, CLCD_DisplayParams *pState, uint32_t c);
	void (*PaletteInitialise)(CLCD_TypeDef *ClCD, uint32_t *Palette);
	void (*ColorOrderSet)(CLCD_TypeDef * ClCD,CLCD_DisplayParams *pParams);
	void (*DMAFrameBufferSet)(CLCD_TypeDef *ClCD, CLCD_DisplayParams *pParams);
	uint32_t (*BytesPer_Panel)(CLCD_DisplayParams *pParams);
#if SCI_FUNC_PATCH
	int32_t (*CLCD_RefreshSet)(CLCD_TypeDef *  pBase,CLCD_DisplayParams *  pParams,uint32_t Refresh);
#endif		
}CLCD_FuncTypeDef;

/* DCMI Module */
typedef struct
{
	void (*DeInit)(void);

	void (*Init)(DCMI_InitTypeDef *DCMI_InitStruct);
	void (*StructInit)(DCMI_InitTypeDef *DCMI_InitStruct);
	void (*CROPConfig)(DCMI_CROPInitTypeDef *DCMI_CROPInitStruct);
	void (*CROPCmd)(FunctionalState NewState);
	void (*SetEmbeddedSynchroCodes)(DCMI_CodesInitTypeDef* DCMI_CodesInitStruct);
	void (*JPEGCmd)(FunctionalState NewState);
	void (*SetDMARequsetFIFOSize)(uint32_t NewFIFOSize);

	void (*Cmd)(FunctionalState NewState);
	void (*CaptureCmd)(FunctionalState NewState);
	uint32_t (*ReadData)(void);
	uint32_t (*GetFIFODataWordNum)(void);

	void (*ITConfig)(uint16_t DCMI_IT, FunctionalState NewState);
	FlagStatus (*GetFlagStatus)(uint16_t DCMI_FLAG);
	void (*ClearFlag)(uint16_t DCMI_FLAG);
	ITStatus (*GetITStatus)(uint16_t DCMI_IT);
	void (*ClearITPendingBit)(uint16_t DCMI_IT);		
}DCMI_FuncTypeDef;


/* SDIO Module */
//typedef struct
//{
//	void (*DeInit)(void);
//	void (*Reset)(void);
//	void (*ControllerReset)(void);
//	void (*FIFOReset)(void);
//	void (*DMAReset)(void);
//	void (*GlobalITCmd)(FunctionalState NewState);
//	void (*DMACmd)(FunctionalState NewState);
//	void (*AssertReadWait)(void);
//	void (*ClearReadWait)(void);
//	void (*SendIrqReap)(FunctionalState NewState);
//	void (*AbordReadData)(FunctionalState NewState);
//	void (*CCSDSend)(FunctionalState NewState);
//	void (*CCSDSendAutoStop)(FunctionalState NewState);
//	void (*CEATAITCmd)(FunctionalState NewState);
//	void (*CardVolA)(uint32_t VolValue);
//	void (*CardVolB)(uint32_t VolValue);
//	void (*ODPullup)(FunctionalState NewState);

//	void (*ClockInit)(SDIO_ClockInitTypeDef *SDIO_ClockInitStruct);
//	void (*ClockSourceSel)(SDIO_CardTypeDef SDIO_Cardx, SDIO_ClockSourceTypeDef SDIO_ClockSource);
//	void (*SetPowerState)(SDIO_CardTypeDef SDIO_Cardx, uint32_t SDIO_PowerState);
//	uint32_t (*GetPowerState)(SDIO_CardTypeDef SDIO_Cardx);
//	void (*LowPowerModeCmd)(SDIO_CardTypeDef SDIO_Cardx, FunctionalState NewState);

//	void (*SetBusWide)(SDIO_CardTypeDef SDIO_Cardx, uint32_t SDIO_BusWide);

//	void (*SetTimeOut)(uint32_t DataTimeOut, uint32_t RespTimeOut);
//	void (*SetDataTimeOut)(uint32_t DataTimeOut);
//	void (*SetRespTimeOut)(uint32_t RespTimeOut);

//	void (*SetFIFOThreshold)(uint32_t RxFIFOThreshold, uint32_t TxFIFOThreshold);
//	void (*SetRxFIFOThreshold)(uint32_t FIFOThreshold);
//	void (*SetTxFIFOThreshold)(uint32_t FIFOThreshold);

//	void (*CardHardwareResetCmd)(SDIO_CardTypeDef SDIO_Cardx, FunctionalState NewState);
//	FlagStatus (*CardDetected)(SDIO_CardTypeDef SDIO_Cardx);
//	FlagStatus (*CardWriteProtected)(SDIO_CardTypeDef SDIO_Cardx);

//	void (*SetDataByteCount)(uint32_t Count);
//	uint32_t (*GetDataByteCount)(void);
//	void (*SetDataBlockSize)(uint16_t BlockSize);
//	uint32_t (*GetDataBlockSize)(void);
//	uint32_t (*ReadData)(void);
//	void (*WriteData)(uint32_t Data);
//	uint32_t (*GetFIFOCount)(void);

//	void (*ITConfig)(SDIO_CardTypeDef SDIO_Cardx, uint32_t SDIO_IT, FunctionalState NewState);
//	ITStatus (*GetRawITStatus)(SDIO_CardTypeDef SDIO_Cardx, uint32_t SDIO_IT);
//	uint32_t (*GetRawITReg)(void);
//	ITStatus (*GetITStatus)(SDIO_CardTypeDef SDIO_Cardx, uint32_t SDIO_IT);
//	void (*ClearITPendingBit)(uint32_t SDIO_IT);

//	void (*SendCommand)(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
//	void (*CmdStructInit)(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
//	uint32_t (*GetResponse)(uint32_t SDIO_RESP);
//	uint8_t (*GetCommandResponse)(void);

//	uint32_t (*GetCFSMStatus)(void);
//	FlagStatus (*GetStatus)(uint32_t SDIO_STATUS);	
//}SDIO_FuncTypeDef;

/* CACHE Module */
typedef struct
{
	void (*Init)(CACHE_TypeDef *Cache, CACHE_InitTypeDef *CACHE_InitStruct);
	void (*Clean)(CACHE_TypeDef *Cache, CACHE_InitTypeDef *CACHE_InitStruct);
	void (*CleanAll)(CACHE_TypeDef *Cache);
}CACHE_FuncTypeDef;

/* QSPI Module */
typedef struct
{
	void (*Init)(QSPI_InitTypeDef *mhqspi);

	uint32_t (*ReadID)(QSPI_CommandTypeDef *cmdParam);
	uint8_t (*WriteParam)(QSPI_CommandTypeDef *cmdParam, uint16_t wrData);
	uint8_t (*EraseSector)(QSPI_CommandTypeDef *cmdParam, uint32_t SectorAddress);
	uint8_t (*EraseChip)(QSPI_CommandTypeDef *cmdParam);
	uint8_t (*ProgramPage)(QSPI_CommandTypeDef *cmdParam, DMA_TypeDef *DMA_Channelx, uint32_t adr, uint32_t sz, uint8_t *buf);

	uint8_t (*DeepPowerDown)(QSPI_CommandTypeDef *cmdParam);
	uint8_t (*ReleaseDeepPowerDown)(QSPI_CommandTypeDef *cmdParam);

	uint8_t (*Read)(QSPI_CommandTypeDef *cmdParam, uint8_t* buf, uint32_t addr, uint32_t sz);

	uint16_t (*StatusReg)(QSPI_CommandTypeDef *cmdParam);
}QSPI_FuncTypeDef;

/* OTP Module */
typedef struct
{
	void (*WakeUp)(void);
	void (*Unlock)(void);
	void (*Lock)(void);
	void (*ClearStatus)(void);
	void (*SetLatency)(uint8_t u8_1UsClk, uint8_t u8_10NsCLK);
	void (*TimCmd)(FunctionalState NewState);
	void (*HideBlock)(uint32_t u32Addr);
	void (*SetProtect)(uint32_t u32Addr);
	void (*SetProtectLock)(uint32_t u32Addr);
	void (*UnProtect)(uint32_t u32Addr);
	void (*ClearAllHiddenBlock)(void);
	OTP_HideTypeDef (*IsHide)(uint32_t u32Addr);
	OTP_ReadReadyTypeDef (*IsReadReady)(void);
	OTP_WrieDoneTypeDef (*IsWriteDone)(void);
	OTP_StatusTypeDef (*GetFlag)(void);
	OTP_LockTypeDef (*IsProtect)(uint32_t u32Addr);
	OTP_LockTypeDef (*IsProtectLock)(uint32_t u32Addr);
	OTP_StatusTypeDef (*WriteWord)(uint32_t addr, uint32_t w);
	uint32_t (*GetProtect)(void);
	uint32_t (*GetProtectLock)(void);
	void (*PowerOn)(void);
}OTP_FuncTypeDef;


#ifdef USE_CRYPT_MODULE
/* CRYPT Module */
typedef struct
{
	/************************************************** DES **************************************************/
	uint32_t (*des_enc)(mh_pack_mode_def pack_mode,
				        uint8_t *output, uint32_t obytes,
				        uint8_t *input, uint32_t ibytes,
			            mh_des_key_def key, mh_des_iv_def iv,
				        mh_rng_callback f_rng, void *p_rng);
	
	uint32_t (*des_dec)(mh_pack_mode_def pack_mode,
						uint8_t *output, uint32_t obytes,
						uint8_t *input, uint32_t ibytes,
						mh_des_key_def key,	mh_des_iv_def iv,
						mh_rng_callback f_rng, void *p_rng);

	uint32_t (*tdes_enc)(mh_pack_mode_def pack_mode,
					     uint8_t *output, uint32_t obytes,
 					     uint8_t *input, uint32_t ibytes,
					     mh_tdes_key_def *key, mh_des_iv_def iv,
					     mh_rng_callback f_rng, void *p_rng);
	
	uint32_t (*tdes_dec)(mh_pack_mode_def pack_mode,
						 uint8_t *output, uint32_t obytes,
						 uint8_t *input, uint32_t ibytes,
						 mh_tdes_key_def *key, mh_des_iv_def iv,
						 mh_rng_callback f_rng, void *p_rng);	

	/************************************************** RSA **************************************************/
	uint32_t (*rsa_private_crt)(uint8_t *output, uint8_t *input, mh_rsa_private_key *key, mh_rng_callback f_rng, void *p_rng);					
	uint32_t (*rsa_public)(uint8_t *output, uint8_t *input, mh_rsa_public_key *key, mh_rng_callback f_rng, void *p_rng);	
	uint32_t (*rsa_efc_gen_key)(mh_rsa_private_key *key, uint32_t exponent, uint32_t nbits, mh_rng_callback f_rng, void *p_rng);

	uint32_t (*rsa_complete_key)(mh_rsa_private_key *key, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*rsa_complete_key_e)(mh_rsa_private_key *key, mh_rng_callback f_rng, void *p_rng);
    
    uint32_t (*rsa_gen_efc_para)(mh_rsa_efc_para_def *efc, uint32_t *qmin, uint32_t *qmax, uint32_t qlen);
    uint32_t (*rsa_gen_key)(mh_rsa_private_key *key, uint32_t exponent, uint32_t nbits, mh_rng_callback f_rng, void *p_rng);
    
	uint32_t (*rsa_get_private_key_C_Q)(mh_rsa_private_key *key, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*rsa_get_public_key_C_Q)(mh_rsa_public_key *key, mh_rng_callback f_rng, void *p_rng);

	uint32_t (*rsa_is_prime)( uint32_t *X, uint32_t size, mh_rng_callback f_rng, void *p_rng);

	uint32_t (*rsa_efc_gen_prime)( uint32_t *X, uint32_t nbits, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*rsa_private)(uint8_t *output, uint8_t *input, mh_rsa_private_key *key, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*rsa_private_tmp)(uint8_t *output, uint8_t *input, mh_rsa_private_key *key, mh_rng_callback f_rng, void *p_rng);

	int (*rsa_public_func)(uint8_t *output, uint32_t *outputlen, const uint8_t *input, uint32_t inputlen, const rsa_pub_key_t *publickey);			   					   					   
	int (*rsa_private_func)(uint8_t *output, uint32_t *outputlen, const uint8_t *input, uint32_t inputlen, const rsa_pri_key_t *privatekey);
	
	/************************************************** AES **************************************************/
	uint32_t (*aes_enc)(mh_pack_mode_def pack_mode,
					    uint8_t *output, uint32_t obytes,
					    uint8_t *input, uint32_t ibytes,
					    uint8_t *key, mh_aes_key_size_def kSize, 
					    mh_aes_iv_def iv,
					    mh_rng_callback f_rng, void *p_rng);

	uint32_t (*aes_dec)(mh_pack_mode_def pack_mode,
					    uint8_t *output, uint32_t oBytes,
					    uint8_t *input, uint32_t iBytes,
					    uint8_t *key, mh_aes_key_size_def kSize, 
					    mh_aes_iv_def iv,
					    mh_rng_callback f_rng, void *p_rng);	

	/************************************************** ECC **************************************************/
	void (*ecc_config)(ecc_para *para,uint32_t config);
	uint32_t (*ecc_genkey)(ecc_key *key, ecc_para *para, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*ecc_verifykey)(ecc_key *key,ecc_para *para,uint32_t config, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*ecc_pmul)(ecc_point_a *r,ecc_point_a *a,uint32_t *b,ecc_para *para, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*ecc_pmul_f2m)(ecc_point_a *r,ecc_point_a *a,uint32_t *k,ecc_para *para, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*ecc_verifypoint)(ecc_point_a *a,ecc_para *para);
	uint32_t (*ecc_pmul_calc)(ecc_point_a *r, ecc_point_a *a, uint32_t *k, ecc_para *para);
	uint32_t (*ecc_pmul_calc_blinding)(ecc_point_a *r, ecc_point_a *a, uint32_t *k, ecc_para *para, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*ecc_pmul_f2m_calc)(ecc_point_a *r, ecc_point_a *a, uint32_t *k,uint32_t len,ecc_para *para);
	uint32_t (*ecc_pmul_f2m_calc_blinding)(ecc_point_a *r, ecc_point_a *a, uint32_t *k, ecc_para *para, mh_rng_callback f_rng, void *p_rng);

	void (*ecc_j2a)(ecc_point_a *r,ecc_point_j *a,const ecc_para *para);
	void (*ecc_j2mj)(ecc_point_mj *r,ecc_point_j *a,const ecc_para *para);
	void (*ecc_j2mj_t)(uint32_t *r,uint32_t *z,const ecc_para *para);

	uint32_t (*ecc_padd_a)(ecc_point_a *r,ecc_point_a *a,ecc_point_a *b,const ecc_para *para);
	uint32_t (*ecc_padd_ja)(ecc_point_j *r,ecc_point_j *a,ecc_point_a *b,const ecc_para *para);
	uint32_t (*ecc_pdbl_a)(ecc_point_a *r,ecc_point_a *a,const ecc_para *para);
	uint32_t (*ecc_pdbl_j)(ecc_point_j *r,ecc_point_j *a,const ecc_para *para);
	uint32_t (*ecc_pdbl_mj)(ecc_point_mj *r,ecc_point_mj *a,const ecc_para *para);

	void (*ecc_naf)(int8_t *w, uint32_t *w_len, uint32_t *w_oe, const uint32_t *k, uint32_t k_len);
	void (*ecc_naf_point)(ecc_point_naf (*naf_p)[8],ecc_point_a *a,const ecc_para *para);

	/************************************************** SHA **************************************************/
	uint32_t (*sha)(mh_sha_mode_def mode, uint8_t *output, uint8_t *input, uint32_t ibytes);
	uint32_t (*sha_sec)(mh_sha_mode_def type, uint8_t *output, uint8_t *input, uint32_t ibytes,
							mh_rng_callback f_rng, void *p_rng);

	void (*sha1_starts)(sha1_context *ctx);
	void (*sha1_update)(sha1_context *ctx,const uint8_t *input,uint32_t i_len);
	void (*sha1_finish)(sha1_context *ctx,uint8_t digest[20]);

	void (*sha256_starts)(sha2_context *ctx);
	void (*sha256_update)(sha2_context *ctx,const uint8_t *input,uint32_t i_len);
	void (*sha256_finish)(sha2_context *ctx,uint8_t digest[32]);	

	/************************************************** SM2 **************************************************/
	uint32_t (*sm2_genkey)(mh_sm2_private_key *key, const mh_sm2_ellipse_para *para, mh_rng_callback f_rng, void *p_rng);

	uint32_t (*sm2_kdf)(uint8_t *K, uint32_t klen, const uint8_t *Z, uint32_t zlen);	
	uint32_t (*sm2_hash_z)(uint8_t Za[32], uint8_t *IDa, uint16_t IDalen, mh_sm2_ellipse_para *para, mh_sm2_public_key *key);
	uint32_t (*sm2_hash_e)(uint32_t e[8], uint8_t Za[32], uint8_t *m, uint32_t mlen);

	uint32_t (*sm2_enc)(uint8_t *output, uint32_t *olen,
						const uint8_t *input, uint32_t ilen,
						const mh_sm2_public_key *key, const mh_sm2_ellipse_para *para,
						mh_rng_callback f_rng, void *p_rng);
	uint32_t (*sm2_dec)(uint8_t *output, uint32_t *olen,
						const uint8_t *input, uint32_t ilen,
						const mh_sm2_private_key *key, const mh_sm2_ellipse_para *para,
						mh_rng_callback f_rng, void *p_rng);

	uint32_t (*sm2_digital_sign)(mh_sm2_sign *sign, uint8_t Za[32],
								uint8_t *msg, uint32_t mlen,
								mh_sm2_private_key *key, mh_sm2_ellipse_para *para,
								mh_rng_callback f_rng, void *p_rng);
	uint32_t (*sm2_verify_sign)(mh_sm2_sign *sign, uint8_t Za[32],
								uint8_t *msg, uint32_t mlen,
								mh_sm2_public_key *key, mh_sm2_ellipse_para *para,
								mh_rng_callback f_rng, void *p_rng);
	uint32_t (*sm2_digital_sign_with_e)(mh_sm2_sign *sign, uint32_t e[8],
								        uint8_t *msg, uint32_t mlen,
								        mh_sm2_private_key *key, mh_sm2_ellipse_para *para,
								        mh_rng_callback f_rng, void *p_rng);
	uint32_t (*sm2_verify_sign_with_e)(mh_sm2_sign *sign, uint32_t e[8],
								       uint8_t *msg, uint32_t mlen,
								       mh_sm2_public_key *key, mh_sm2_ellipse_para *para,
								       mh_rng_callback f_rng, void *p_rng);
								
	uint32_t (*sm2_key_ex_equation_0)(uint8_t _x[32], uint32_t *_xlen, 
								      const uint8_t x[32], uint32_t w);
	void (*sm2_key_ex_equation_1)(uint8_t *t, const uint8_t *d, 
							      const uint8_t *x, const uint8_t *r, 
							      mh_sm2_ellipse_para *para);
	void (*sm2_key_ex_equation_2)(mh_sm2_point *P, uint8_t *t, 
							      uint8_t *x, mh_sm2_point *R, 
							      mh_sm2_ellipse_para *para, mh_sm2_public_key *key,
							      mh_rng_callback f_rng, void *p_rng);

	uint32_t (*sm2_key_ex_section_0)(mh_sm2_point *R, uint8_t *t, uint8_t *rand,
								 	 mh_sm2_ellipse_para *para, mh_sm2_private_key *key,
									 mh_rng_callback f_rng, void *p_rng);
	uint32_t (*sm2_key_ex_section_1)(uint8_t *K, uint32_t Klen, mh_sm2_point *P, 
								     mh_sm2_point *R, uint8_t *t, 
								     uint8_t *Za, uint8_t *Zb, 
								     mh_sm2_ellipse_para *para, mh_sm2_public_key *key,
								     mh_rng_callback f_rng, void *p_rng);
	uint32_t (*sm2_key_ex_hash)(uint8_t *Hash, uint8_t HashHead,
							    mh_sm2_point *P,uint8_t *Za, uint8_t *Zb,
							    mh_sm2_point *Ra, mh_sm2_point *Rb);

	int (*SM2Sign)(sm2_sign *info, uint8_t *msg, uint32_t mlen,
				   mh_sm2_private_key *key, mh_sm2_ellipse_para *para,
				   mh_rng_callback f_rng, void *p_rng);
					
	int (*SM2Verify)(sm2_sign *info,uint8_t *msg, uint32_t mlen,
					 mh_sm2_public_key *key, mh_sm2_ellipse_para *para,
					 mh_rng_callback f_rng, void *p_rng);	

	/************************************************** SM3 **************************************************/	
	uint32_t (*sm3)(uint8_t output[32], uint8_t *input, uint64_t ibytes);	

	/************************************************** SM4 **************************************************/		
	uint32_t (*sm4_enc)(mh_pack_mode_def pack_mode, 
						uint8_t *output, uint32_t obytes, 
						uint8_t *input, uint32_t ibytes, 
						mh_sm4_key_def key, mh_sm4_iv_def iv,
						mh_rng_callback f_rng, void *p_rng);

	uint32_t (*sm4_dec)(mh_pack_mode_def pack_mode, 
						uint8_t *output, uint32_t obytes, 
						uint8_t *input, uint32_t ibytes, 
						mh_sm4_key_def key, mh_sm4_iv_def iv,
						mh_rng_callback f_rng, void *p_rng);

	/************************************************ BIG NUM ************************************************/		
	void (*bn_set_int)(uint32_t *r,uint32_t a,uint32_t len);
	void (*bn_cpy)(uint32_t *r,uint32_t *a,uint32_t len);
	uint32_t (*bn_cmp)(uint32_t *a,uint32_t *b,uint32_t len);
	uint32_t (*bn_swap)(uint32_t *a, uint32_t *b, uint32_t len);
	uint32_t (*bn_cmp_int)(uint32_t *a,uint32_t b,uint32_t len);

	int32_t (*bn_add)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t len);
	int32_t (*bn_sub)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t len);
	int32_t (*bn_add_int)(uint32_t *r,uint32_t *a,uint32_t b,uint32_t len);
	int32_t (*bn_sub_int)(uint32_t *r,uint32_t *a,uint32_t b,uint32_t len);
	uint32_t (*bn_modadd)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t *p,uint32_t len);
	uint32_t (*bn_modsub)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t *p,uint32_t len);
	uint32_t (*bn_mul)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t len_a,uint32_t len_b);
	uint32_t (*bn_div)(uint32_t *r_q,uint32_t *r_r,uint32_t *a,uint32_t *b,uint32_t len_a,uint32_t len_b);

	void (*bn_set_p)(bn_type_p *type_p, uint32_t *p, uint32_t *p_c, uint32_t p_q);

	uint32_t (*bn_modexp_p)(uint32_t *r, uint32_t *a, uint32_t *b, uint32_t len_b, bn_type_p *p, uint32_t len);
	uint32_t (*bn_get_C)(uint32_t *r,uint32_t *p,uint32_t len);
	uint32_t (*bn_get_Q)(uint32_t *r,uint32_t *p);
	uint32_t (*bn_modmul_p)(uint32_t *r,uint32_t *a,uint32_t *b,bn_type_p *p,uint32_t len);
	uint32_t (*bn_modmul)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t len);
	uint32_t (*bn_modinv_1024)(uint32_t *r,uint32_t *a,uint32_t *p,uint32_t len_a, uint32_t len_b);
	uint32_t (*bn_modinv)(uint32_t *r, uint32_t *a, uint32_t *b, uint32_t len_a, uint32_t len_b);

	uint32_t (*bn_s_cpy)(uint32_t *r,uint32_t *a,uint32_t len, mh_rng_callback f_rng, void *p_rng);

	uint32_t (*bn_s_mul)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t len_a,uint32_t len_b, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*bn_s_div)(uint32_t *r_q,uint32_t *r_r,uint32_t *a,uint32_t *b,uint32_t len_a,uint32_t len_b, mh_rng_callback f_rng, void *p_rng);

	uint32_t (*bn_s_modexp_p)(uint32_t *r, uint32_t *a, uint32_t *b, uint32_t len_b, bn_type_p *p, uint32_t len, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*bn_s_get_C)(uint32_t *r,uint32_t *p,uint32_t len, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*bn_s_get_Q)(uint32_t *r,uint32_t *p, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*bn_s_modmul_p)(uint32_t *r,uint32_t *a,uint32_t *b,bn_type_p *p,uint32_t len, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*bn_s_modinv_1024)(uint32_t *r,uint32_t *a,uint32_t *p,uint32_t len_a, uint32_t len_b, mh_rng_callback f_rng, void *p_rng);

	uint32_t (*bn_get_C_f2m)(uint32_t *r,uint32_t *p,uint32_t len);
	uint32_t (*bn_get_Q_f2m)(uint32_t *r,uint32_t *a);
	uint32_t (*bn_modmul_p_f2m)(uint32_t *r,uint32_t *a,uint32_t *b,bn_type_p *p,uint32_t len);
	uint32_t (*bn_modmul_f2m)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t len);
	uint32_t (*bn_modinv_f2m)(uint32_t *r,uint32_t *a,uint32_t *p,uint32_t len);

	uint32_t (*bn_gcd)(uint32_t *a,uint32_t *b,uint32_t len);
	uint32_t (*bn_gcd_int)(uint32_t a,uint32_t *b,uint32_t len);

	void (*bn_shift_r)(uint32_t *r, uint32_t *a, uint32_t len, uint32_t bits );
	void (*bn_shift_l)(uint32_t *r, uint32_t *a, uint32_t len, uint32_t bits );
	uint32_t (*bn_lsb)( const uint32_t *a, uint32_t len );
	uint32_t (*bn_msb)( const uint32_t *a, uint32_t len );
	uint32_t (*bn_byte)( const uint32_t *a, uint32_t len );
	uint32_t (*bn_len)( const uint32_t *a, uint32_t len );
	void (*bn_xor)(uint32_t *r,uint32_t *a,uint32_t *b,uint32_t len);
	
	/************************************************** MISC *************************************************/	
	uint32_t (*mh_memcmp)(const void *dest, const void *src, uint32_t size);
	uint32_t (*mh_is_equal)(const void *dest,const void *src, uint32_t size, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*mh_memcpy)(void *dest, const void *src, uint16_t size, mh_rng_callback f_rng, void *p_rng);	
	uint32_t (*mh_memswap)(void *dest, uint32_t dsize, const void *src, uint32_t ssize, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*memswap)(void *dest, uint32_t dsize, const void *src, uint32_t ssize);
	uint32_t (*mh_xor_u32)(uint32_t *xor, uint32_t *src, uint16_t nwords, mh_rng_callback f_rng, void *p_rng);
	uint32_t (*mh_sum_u32)(uint32_t *sum, uint32_t *src, uint16_t nwords, mh_rng_callback f_rng, void *p_rng);
	
	/************************************************* Common ************************************************/		
	void (*reset)(void);
	void (*it_clear)(void);	
	uint32_t (*version)(void);
}CRYPT_FuncTypeDef;
#endif

#ifdef USE_SCI_MODULE
 /* EMV Module */
typedef struct
{
	int (*tell_case)(struct emv_apdu_req *apdu_req);
	int (*atr_analyser)(struct emv_core *terminal, struct emv_atr *su_atr, unsigned char *atr);
	int (*atr_parse)(struct emv_core *terminal, struct emv_atr *su_atr);
	int (*t0_exchange)(struct emv_core *terminal, struct emv_apdu_req *apdu_req, struct emv_apdu_rsp *apdu_resp);
	int (*t1_compute_lrc)(struct emv_t1_block *t1_block);
	int (*t1_extract)(struct emv_apdu_req *apdu_req, unsigned char *buf);
	int (*t1_iblock_pack)(struct emv_core *terminal, const unsigned char *buf, int len, struct emv_t1_block  *t1_block );
	int (*t1_block_xmit)(struct emv_core *terminal, struct emv_t1_block *t1_block);
	int (*t1_block_recv)(struct emv_core *terminal, struct emv_t1_block *t1_block);
	int (*t1_exchange)(struct emv_core *terminal, struct emv_apdu_req *apdu_req, struct emv_apdu_rsp *apdu_resp);
	int (*t1_ifsd_request)(struct emv_core *terminal);
	
	int (*fi_const_table)(int index);
	int (*di_const_table)(int index);
	int (*fi_const_index)(int fi);
	int (*di_const_index)(int di);

	int (*adjust_timeout_type)(struct emv_core *terminal);
	int (*iso_atr_parse)(struct emv_core *pdev, struct emv_atr *su_atr);
	int (*iso_condsel_procedure)(struct emv_core *pdev);
	int (*iso_pps_procedure)(struct emv_core *pdev, struct emv_atr *su_atr);

	int (*core_init)(struct emv_core *terminal, struct emv_queue *queue);
	int (*queue_flush)(struct emv_core *terminal);
	int (*queue_empty)(struct emv_core *terminal);
	int (*queue_length)(struct emv_core *terminal);
	int (*queue_fill)(struct emv_core *terminal, unsigned char *pbuf, int length);
	int (*queue_spill)(struct emv_core *terminal, unsigned char *pbuf, int length);
	
	int (*iso7816_device_init)(void);
	int (*iso7816_init)(unsigned int slot, unsigned int option, unsigned char *out_atr);
	int (*iso7816_exchange)(unsigned int slot, int mode, ST_APDU_REQ *apdu_req, ST_APDU_RSP *apdu_rsp);
	void (*iso7816_close)(unsigned int slot);
	int (*iso7816_detect)(unsigned int slot);
	int (*iso7816_getlibversion)(void);
	
	int (*isvalid_channel)(int slot);
	int (*select_slot)(int slot);
	int (*hard_init)(void);
	int (*disturb_interruption)(struct emv_core *pdev, int enable);
	int (*hard_power_pump)(struct emv_core *pdev);
	int (*hard_cold_reset)(struct emv_core *pdev);
	int (*hard_warm_reset)(struct emv_core *pdev);
	int (*hard_power_dump)(struct emv_core *pdev);
	int (*hard_xmit)(struct emv_core *pdev);
	int (*hard_detect)(struct emv_core *pdev);

#if SCI_FUNC_PATCH
	int32_t (*ConfigEMV)(uint8_t SCI_Bitmap, uint32_t SCIx_Clk);
#endif	
}EMV_FuncTypeDef;
#endif

#ifdef USE_USB_MODULE
/* USB DEVICE(MSC & VCP) Module */
typedef struct
{
	/************************************************ USB DCD ***********************************************/	
	uint32_t (*DCD_EP_Open)(USB_OTG_CORE_HANDLE *pdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);

	uint32_t (*DCD_EP_Close)(USB_OTG_CORE_HANDLE *pdev, uint8_t  ep_addr);

	uint32_t (*DCD_EP_PrepareRx)( USB_OTG_CORE_HANDLE *pdev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len);
	  
	uint32_t (*DCD_EP_Tx)(USB_OTG_CORE_HANDLE *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len);
	uint32_t (*DCD_EP_Stall)(USB_OTG_CORE_HANDLE *pdev, uint8_t epnum);
	uint32_t (*DCD_EP_ClrStall)(USB_OTG_CORE_HANDLE *pdev, uint8_t epnum);
	uint32_t (*DCD_EP_Flush)(USB_OTG_CORE_HANDLE *pdev, uint8_t epnum);

	/*********************************************** USB DCD INT ********************************************/	
	uint32_t (*OTG_ISR_Handler)(USB_OTG_CORE_HANDLE *pdev);

	/*********************************************** USBD CORE **********************************************/	
	void (*USBD_Init)(USB_OTG_CORE_HANDLE *pdev, USB_OTG_CORE_ID_TypeDef coreID,  USBD_DEVICE *pDevice,  USBD_Class_cb_TypeDef *class_cb,  USBD_Usr_cb_TypeDef *usr_cb);

	/*********************************************** USBD IOREQ *********************************************/	
	USBD_Status (*USBD_CtlSendData)(USB_OTG_CORE_HANDLE  *pdev, uint8_t *buf, uint16_t len);
	USBD_Status (*USBD_CtlContinueSendData)(USB_OTG_CORE_HANDLE *pdev, uint8_t *pbuf, uint16_t len);
	USBD_Status (*USBD_CtlPrepareRx)(USB_OTG_CORE_HANDLE *pdev, uint8_t *pbuf, uint16_t len);
	USBD_Status (*USBD_CtlContinueRx)(USB_OTG_CORE_HANDLE *pdev, uint8_t *pbuf, uint16_t len);
	uint16_t (*USBD_GetRxCount)(USB_OTG_CORE_HANDLE  *pdev, uint8_t epnum);
	
	/************************************************ USBD REQ **********************************************/
	void (*USBD_CtlError)(USB_OTG_CORE_HANDLE *pdev, USB_SETUP_REQ *req);
	void (*USBD_GetString)(uint8_t *desc, uint8_t *unicode, uint16_t *len);	
}USB_FuncTypeDef;
#endif


/* MH1903 FWLIB */
typedef struct
{
	char driver_tag[16];
	uint32_t (*GetFwlibVersion)(void);
	
	/* General Peripheral Module */
	SYSCTRL_FuncTypeDef    m_SYSCTRL;
	CRC_FuncTypeDef        m_CRC;
	ADC_FuncTypeDef        m_ADC;
	GPIO_FuncTypeDef       m_GPIO;
	EXTI_FuncTypeDef       m_EXTI;
	TIM_FuncTypeDef        m_TIM;
	UART_FuncTypeDef       m_UART;
	SPI_FuncTypeDef        m_SPI;
	I2C_FuncTypeDef        m_I2C;
	KCU_FuncTypeDef        m_KCU;
	BPK_FuncTypeDef        m_BPK;
	SENSOR_FuncTypeDef     m_SENSOR;
	SSC_FuncTypeDef        m_SSC;
	TRNG_FuncTypeDef       m_TRNG;
	RTC_FuncTypeDef        m_RTC;
	WDT_FuncTypeDef        m_WDT;
	DMA_FuncTypeDef        m_DMA;
	LCD_FuncTypeDef        m_LCD;
	CLCD_FuncTypeDef       m_CLCD;
	DCMI_FuncTypeDef       m_DCMI;
//	SDIO_FuncTypeDef       m_SDIO;
	CACHE_FuncTypeDef      m_CACHE;
	QSPI_FuncTypeDef       m_QSPI;
	OTP_FuncTypeDef        m_OTP;

#ifdef USE_CRYPT_MODULE
	/* CRYPT Module */
	CRYPT_FuncTypeDef      m_CRYPT;
#endif

#ifdef USE_SCI_MODULE
	/* EMV Module */
	EMV_FuncTypeDef        m_EMV;
#endif

#ifdef USE_USB_MODULE	
	/* USB Module */
	USB_FuncTypeDef        m_USB;
#endif	
}MH1903_FuncTypeDef;


#define MH1903_FWLIB          ((MH1903_FuncTypeDef *)0x00008000)

#define MH1903_SYSCTRL        MH1903_FWLIB->m_SYSCTRL
#define MH1903_CRC        	  MH1903_FWLIB->m_CRC
#define MH1903_ADC            MH1903_FWLIB->m_ADC
#define MH1903_GPIO           MH1903_FWLIB->m_GPIO
#define MH1903_EXTI           MH1903_FWLIB->m_EXTI
#define MH1903_TIM            MH1903_FWLIB->m_TIM
#define MH1903_UART           MH1903_FWLIB->m_UART
#define MH1903_SPI            MH1903_FWLIB->m_SPI
#define MH1903_I2C            MH1903_FWLIB->m_I2C
#define MH1903_KCU            MH1903_FWLIB->m_KCU
#define MH1903_BPK            MH1903_FWLIB->m_BPK
#define MH1903_SENSOR         MH1903_FWLIB->m_SENSOR
#define MH1903_SSC            MH1903_FWLIB->m_SSC
#define MH1903_TRNG           MH1903_FWLIB->m_TRNG
#define MH1903_RTC            MH1903_FWLIB->m_RTC
#define MH1903_WDT            MH1903_FWLIB->m_WDT
#define MH1903_DMA            MH1903_FWLIB->m_DMA
#define MH1903_LCD            MH1903_FWLIB->m_LCD
#define MH1903_CLCD           MH1903_FWLIB->m_CLCD
#define MH1903_DCMI           MH1903_FWLIB->m_DCMI
#define MH1903_QR             MH1903_FWLIB->m_QR
#define MH1903_SDIO           MH1903_FWLIB->m_SDIO
#define MH1903_CACHE          MH1903_FWLIB->m_CACHE
#define MH1903_QSPI           MH1903_FWLIB->m_QSPI
#define MH1903_OTP            MH1903_FWLIB->m_OTP

#ifdef USE_CRYPT_MODULE
#define MH1903_CRYPT          MH1903_FWLIB->m_CRYPT
#endif

#ifdef USE_SCI_MODULE
#define MH1903_EMVCORE        MH1903_FWLIB->m_EMV
#endif

#ifdef USE_USB_MODULE
#define MH1903_USBCORE        MH1903_FWLIB->m_USB
#endif


#ifdef __cplusplus
}
#endif

#endif   ///< __MHSCPU_DRIVER_H


/************************ (C) COPYRIGHT 2014 Megahuntmicro ****END OF FILE****/
