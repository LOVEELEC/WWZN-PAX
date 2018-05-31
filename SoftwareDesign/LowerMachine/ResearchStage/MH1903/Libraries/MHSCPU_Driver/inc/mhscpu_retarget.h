#ifndef __MHSCPU_RETARGET_H__
#define __MHSCPU_RETARGET_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "mhscpu_driver.h"
/*===============================FWLIB RETARGET==============================*/
/*--------------------------------VERSION------------------------------------*/		
#define	MH_GetFwlibVersion               MH1903_FWLIB->GetFwlibVersion

/*----------------------------SYSCTRL MODULE---------------------------------*/
//#define SYSCTRL_AHBPeriphClockCmd        MH1903_SYSCTRL.AHBPeriphClockCmd
#define SYSCTRL_AHBPeriphResetCmd        MH1903_SYSCTRL.AHBPeriphResetCmd
#define	SYSCTRL_APBPeriphClockCmd        MH1903_SYSCTRL.APBPeriphClockCmd
#define	SYSCTRL_APBPeriphResetCmd        MH1903_SYSCTRL.APBPeriphResetCmd

#define	SYSCTRL_EnterSleep               MH1903_SYSCTRL.EnterSleep
#define	SYSCTRL_WakeIntDeInit            MH1903_SYSCTRL.WakeIntDeInit
#define	SYSCTRL_WakeUpInt1Config         MH1903_SYSCTRL.WakeUpInt1Config
#define	SYSCTRL_WakeUpInt2Config         MH1903_SYSCTRL.WakeUpInt2Config
#define	SYSCTRL_GetWakeupFlag1Status     MH1903_SYSCTRL.GetWakeupFlag1Status
#define	SYSCTRL_GetWakeupFlag2Status     MH1903_SYSCTRL.GetWakeupFlag2Status
	
#define	SYSCTRL_SYSCLKSourceSelect       MH1903_SYSCTRL.SYSCLKSourceSelect
#define	SYSCTRL_PLLConfig                MH1903_SYSCTRL.PLLConfig
#define	SYSCTRL_PLLDivConfig             MH1903_SYSCTRL.PLLDivConfig
#define	SYSCTRL_HCLKConfig               MH1903_SYSCTRL.HCLKConfig
#define	SYSCTRL_PCLKConfig               MH1903_SYSCTRL.PCLKConfig
//#define	SYSCTRL_GetClocksFreq            MH1903_SYSCTRL.GetClocksFreq

/*------------------------------CRC MODULE----------------------------------*/
#define	CRC_CalcBlockCRC                 MH1903_CRC.CalcBlock
#define	CRC_Calc                         MH1903_CRC.Calc

/*------------------------------ADC MODULE----------------------------------*/	
//#define	ADC_Init                         MH1903_ADC.Init
#define	ADC_StartCmd                     MH1903_ADC.StartCmd
#define	ADC_FIFODeepth                   MH1903_ADC.FIFODeepth
#define	ADC_FIFOReset                    MH1903_ADC.FIFOReset
#define	ADC_ITCmd                        MH1903_ADC.ITCmd
#define ADC_FIFOOverflowITcmd            MH1903_ADC.FIFOOverflowITcmd
#define	ADC_GetFIFOCount                 MH1903_ADC.GetFIFOCount
//#define	ADC_GetResult                    MH1903_ADC.GetResult
#define	ADC_GetFIFOResult                MH1903_ADC.GetFIFOResult
//#define	ADC_CalVoltage                	 MH1903_ADC.CalVoltage
	
/*------------------------------GPIO MODULE---------------------------------*/	
#define	GPIO_DeInit                	 	 MH1903_GPIO.DeInit
#define	GPIO_Init                	 	 MH1903_GPIO.Init
#define	GPIO_StructInit                	 MH1903_GPIO.StructInit

#define	GPIO_ReadInputDataBit            MH1903_GPIO.ReadInputDataBit
#define	GPIO_ReadInputData               MH1903_GPIO.ReadInputData

#define	GPIO_ReadOutputDataBit           MH1903_GPIO.ReadOutputDataBit
#define	GPIO_ReadOutputData              MH1903_GPIO.ReadOutputData

#define	GPIO_SetBits           			 MH1903_GPIO.SetBits
#define	GPIO_ResetBits                   MH1903_GPIO.ResetBits
#define	GPIO_Write                       MH1903_GPIO.Write
#define	GPIO_PullUpCmd                   MH1903_GPIO.PullUpCmd

#define	GPIO_PinRemapConfig              MH1903_GPIO.PinRemapConfig

#define	GPIO_WakeEvenDeInit              MH1903_GPIO.WakeEvenDeInit
#define	GPIO_WakeEvenConfig              MH1903_GPIO.WakeEvenConfig
#define	GPIO_WakeModeConfig              MH1903_GPIO.WakeModeConfig

/*------------------------------EXTI MODULE---------------------------------*/
#define	EXTI_DeInit                      MH1903_EXTI.DeInit
#define	EXTI_LineConfig                  MH1903_EXTI.LineConfig
#define	EXTI_GetITStatus                 MH1903_EXTI.GetITStatus
#define	EXTI_GetITLineStatus             MH1903_EXTI.GetITLineStatus
#define	EXTI_ClearITPendingBit           MH1903_EXTI.ClearITPendingBit

/*-------------------------------TIM MODULE---------------------------------*/
#define	TIM_DeInit                       MH1903_TIM.DeInit
#define	TIM_Init                         MH1903_TIM.Init

#define	TIM_PWMInit                      MH1903_TIM.PWMInit
#define	TIM_Cmd                          MH1903_TIM.Cmd
#define	TIM_ModeConfig                   MH1903_TIM.ModeConfig
#define	TIM_SetPeriod                    MH1903_TIM.SetPeriod
#define	TIM_SetPWMPeriod                 MH1903_TIM.SetPWMPeriod
#define	TIM_ITConfig                     MH1903_TIM.ITConfig
#define	TIM_ClearITPendingBit            MH1903_TIM.ClearITPendingBit
#define	TIM_PWMSinglePulseConfig         MH1903_TIM.PWMSinglePulseConfig

#define	TIM_GetITStatus                  MH1903_TIM.GetITStatus
#define	TIM_GetAllITStatus               MH1903_TIM.GetAllITStatus
#define	TIM_GetRawITStatus               MH1903_TIM.GetRawITStatus
#define	TIM_GetAllRawITStatus            MH1903_TIM.GetAllRawITStatus

/*------------------------------UART MODULE---------------------------------*/
#define	UART_DeInit                      MH1903_UART.DeInit
#define	UART_Init                        MH1903_UART.Init
#define	UART_StructInit                  MH1903_UART.StructInit
#define	UART_ITConfig                    MH1903_UART.ITConfig

#define	UART_SendData                    MH1903_UART.SendData
#define	UART_ReceiveData                 MH1903_UART.ReceiveData

#define	UART_FIFOInit                    MH1903_UART.FIFOInit
#define	UART_FIFOStructInit              MH1903_UART.FIFOStructInit
#define	UART_FIFOReset                   MH1903_UART.FIFOReset
#define	UART_FIFOCmd                     MH1903_UART.FIFOCmd
#define	UART_SetRTS                      MH1903_UART.SetRTS
#define	UART_ResetRTS                    MH1903_UART.ResetRTS
#define	UART_SetDTR                      MH1903_UART.SetDTR
#define	UART_ResetDTR                    MH1903_UART.ResetDTR
#define	UART_SendBreak                   MH1903_UART.SendBreak
#define	UART_AutoFlowCtrlCmd             MH1903_UART.AutoFlowCtrlCmd
#define	UART_IrDACmd                     MH1903_UART.IrDACmd

#define	UART_GetLineStatus               MH1903_UART.GetLineStatus
#define	UART_GetModemStatus              MH1903_UART.GetModemStatus
#define	UART_GetITIdentity               MH1903_UART.GetITIdentity

#define	UART_IsTXEmpty                   MH1903_UART.IsTXEmpty
#define	UART_IsTXHoldingRegisterEmpty    MH1903_UART.IsTXHoldingRegisterEmpty

#define	UART_IsRXFIFOFull                MH1903_UART.IsRXFIFOFull
#define	UART_IsRXFIFONotEmpty            MH1903_UART.IsRXFIFONotEmpty
#define	UART_IsTXFIFOEmpty               MH1903_UART.IsTXFIFOEmpty
#define	UART_IsTXFIFONotFull             MH1903_UART.IsTXFIFONotFull
#define	UART_IsBusy                      MH1903_UART.IsBusy

#define	UART_DMAGenerateSoftAck          MH1903_UART.DMAGenerateSoftAck

#define	UART_TXHaltCmd                   MH1903_UART.TXHaltCmd
#define	UART_FIFOAccessModeCmd           MH1903_UART.FIFOAccessModeCmd

/*-------------------------------SPI MODULE---------------------------------*/
#define	SPI_DeInit                       MH1903_SPI.DeInit
#define	SPI_Init                         MH1903_SPI.Init
#define	SPI_StructInit                   MH1903_SPI.StructInit
#define	SPI_Cmd                          MH1903_SPI.Cmd

#define	SPI_DMAInit                      MH1903_SPI.DMAInit
#define	SPI_DMAStructInit                MH1903_SPI.DMAStructInit
#define	SPI_DMACmd                       MH1903_SPI.DMACmd

#define	SPI_ITConfig                     MH1903_SPI.ITConfig
#define	SPI_SendData                     MH1903_SPI.SendData
#define	SPI_ReceiveData                  MH1903_SPI.ReceiveData
#define	SPI_DataSizeConfig               MH1903_SPI.DataSizeConfig
#define	SPI_BiDirectionalLineConfig      MH1903_SPI.BiDirectionalLineConfig

#define	SPI_GetITStatus                  MH1903_SPI.GetITStatus
#define	SPI_ClearITPendingBit            MH1903_SPI.ClearITPendingBit

#define	SPI_GetFlagStatus                MH1903_SPI.GetFlagStatus
#define	SPI_GetFlagStatusReg             MH1903_SPI.GetFlagStatusReg

#define	SPI_IsBusy                       MH1903_SPI.IsBusy
#define	SPI_IsTXErr                      MH1903_SPI.IsTXErr
#define	SPI_IsDataCollisionErr           MH1903_SPI.IsDataCollisionErr
#define	SSP_Init                         MH1903_SPI.SSP_Init
#define	SSP_StructInit                   MH1903_SPI.SSP_StructInit

#define	NSM_Init                         MH1903_SPI.NSM_Init
#define	NSM_StructInit                   MH1903_SPI.NSM_StructInit

/*-------------------------------I2C MODULE---------------------------------*/
#define	I2C_DeInit                       MH1903_I2C.DeInit
#define	I2C_Init                         MH1903_I2C.Init
#define	I2C_StructInit                   MH1903_I2C.StructInit

#define	I2C_Cmd                          MH1903_I2C.Cmd
#define	I2C_SetTargetAddress             MH1903_I2C.SetTargetAddress
#define	I2C_DMAInit                      MH1903_I2C.DMAInit
#define	I2C_DMAStructInit                MH1903_I2C.DMAStructInit
#define	I2C_DMACmd                       MH1903_I2C.DMACmd
#define	I2C_SetSDASetupTime              MH1903_I2C.SetSDASetupTime
#define	I2C_SetSDAHoldTime               MH1903_I2C.SetSDAHoldTime

#define	I2C_ITConfig                     MH1903_I2C.ITConfig
#define	I2C_GetITStatus                  MH1903_I2C.GetITStatus
#define	I2C_GetRawITStatus               MH1903_I2C.GetRawITStatus
#define	I2C_ClearITPendingBit            MH1903_I2C.ClearITPendingBit
#define	I2C_GetFlagStatus                MH1903_I2C.GetFlagStatus
#define	I2C_GetFlagStatusReg             MH1903_I2C.GetFlagStatusReg
#define	I2C_GetTXAbortSource             MH1903_I2C.GetTXAbortSource
#define	I2C_GetTXAbortSourceReg          MH1903_I2C.GetTXAbortSourceReg
#define	I2C_GetI2CMode                   MH1903_I2C.GetI2CMode

#define	I2C_MasterGenerateReceiveSCL     MH1903_I2C.MasterGenerateReceiveSCL
#define	I2C_ExtendData                   MH1903_I2C.ExtendData
#define	I2C_WriteDataToDR                MH1903_I2C.WriteDataToDR
#define	I2C_ReadDataFromDR               MH1903_I2C.ReadDataFromDR
#define	I2C_SendData                     MH1903_I2C.SendData
#define	I2C_ReceiveData                  MH1903_I2C.ReceiveData
#define	I2C_SendBytes                    MH1903_I2C.SendBytes
#define	I2C_ReceiveBytes                 MH1903_I2C.ReceiveBytes

#define	I2C_SlaveGeneralNACKOnlyCmd      MH1903_I2C.SlaveGeneralNACKOnlyCmd

#define	I2C_IsEnable                     MH1903_I2C.IsEnable

/*-------------------------------KCU MODULE---------------------------------*/
#define	KCU_DeInit                       MH1903_KCU.DeInit
#define	KCU_Init                         MH1903_KCU.Init
#define	KCU_StructInit                   MH1903_KCU.StructInit

#define	KCU_Cmd                          MH1903_KCU.Cmd
#define	KCU_SetRand                      MH1903_KCU.SetRand
	
#define	KCU_ITConfig                     MH1903_KCU.ITConfig
#define	KCU_GetITStatus                  MH1903_KCU.GetITStatus
#define	KCU_ClearITPending               MH1903_KCU.ClearITPending
#define	KCU_GetEvenReg                   MH1903_KCU.GetEvenReg

/*-------------------------------BPK MODULE---------------------------------*/
#define	BPK_IsReady                      MH1903_BPK.IsReady

#define	BPK_WriteKey                     MH1903_BPK.WriteKey
#define	BPK_ReadKey                      MH1903_BPK.ReadKey

#define	BPK_KeyWriteLock                 MH1903_BPK.KeyWriteLock
#define	BPK_KeyReadLock                  MH1903_BPK.KeyReadLock
#define	BPK_KeyClear                     MH1903_BPK.KeyClear

#define	BPK_SetScramber                  MH1903_BPK.SetScramber
#define	BPK_Reset                        MH1903_BPK.Reset

//#define	BPK_Lock                         MH1903_BPK.Lock
#define	BPK_LockSelf                     MH1903_BPK.LockSelf
#define	BPK_GetLockStatus                MH1903_BPK.GetLockStatus

/*-----------------------------SENSOR MODULE-------------------------------*/
#define	SENSOR_SetRand                   MH1903_SENSOR.SetRand
//#define	SENSOR_EXTInit                   MH1903_SENSOR.EXTInit
//#define	SENSOR_EXTPortCmd                MH1903_SENSOR.EXTPortCmd
#define	SENSOR_EXTCmd                    MH1903_SENSOR.EXTCmd
#define	SENSOR_EXTIsRuning               MH1903_SENSOR.EXTIsRuning
//#define	SENSOR_ANACmd                    MH1903_SENSOR.ANACmd
#define	SENSOR_Lock                      MH1903_SENSOR.Lock
#define	SENSOR_AttackRespMode            MH1903_SENSOR.AttackRespMode

#define	SENSOR_GetITStatus               MH1903_SENSOR.GetITStatus
#define	SENSOR_GetITStatusReg            MH1903_SENSOR.GetITStatusReg
#define	SENSOR_ClearITPendingBit         MH1903_SENSOR.ClearITPendingBit

#define	SENSOR_GetEXTTrigPull            MH1903_SENSOR.GetEXTTrigPull
#define	SENSOR_SetEXTTrigPull            MH1903_SENSOR.SetEXTTrigPull

#define	SENSOR_GetEXTFilter              MH1903_SENSOR.GetEXTFilter
//#define	SENSOR_SetEXTFilter              MH1903_SENSOR.SetEXTFilter

#define	SENSOR_GetEXTPulsePeriod         MH1903_SENSOR.GetEXTPulsePeriod
#define	SENSOR_SetEXTPulsePeriod         MH1903_SENSOR.SetEXTPulsePeriod

#define	SENSOR_GetEXTPulseHold           MH1903_SENSOR.GetEXTPulseHold
#define	SENSOR_SetEXTPulseHold           MH1903_SENSOR.SetEXTPulseHold

#define	SENSOR_GetEXTPulsePull           MH1903_SENSOR.GetEXTPulsePull
#define	SENSOR_SetEXTPulsePull           MH1903_SENSOR.SetEXTPulsePull

#define	SENSOR_GetEXTStaticSample        MH1903_SENSOR.GetEXTStaticSample
#define	SENSOR_SetEXTStaticSample        MH1903_SENSOR.SetEXTStaticSample
#define	SENSOR_GetEXTDynamicSample       MH1903_SENSOR.GetEXTDynamicSample
#define	SENSOR_SetEXTDynamicSample       MH1903_SENSOR.SetEXTDynamicSample

#define	SENSOR_GetEXTDynamicFreq         MH1903_SENSOR.GetEXTDynamicFreq
#define	SENSOR_SetEXTDynamicFreq         MH1903_SENSOR.SetEXTDynamicFreq

/*-------------------------------SSC MODULE---------------------------------*/
#define	SSC_Init                         MH1903_SSC.Init

#define	SSC_GetITStatus                  MH1903_SSC.GetITStatus
#define	SSC_ClearITPendingBit            MH1903_SSC.ClearITPendingBit

#define	SSC_SetDataRAMScrambler          MH1903_SSC.SetDataRAMScrambler
#define	SSC_BPKAccessCtrlConfig          MH1903_SSC.BPKAccessCtrlConfig

#define	SSC_SENSORCmd                    MH1903_SSC.SensorCmd
#define	SSC_SENSORLock                   MH1903_SSC.SensorLock
#define	SSC_SENSORAttackRespMode         MH1903_SSC.SensorAttackRespMode

/*------------------------------TRNG MODULE---------------------------------*/
#define	TRNG_Start                       MH1903_TRNG.Start
#define	TRNG_Stop                        MH1903_TRNG.Stop
#define	TRNG_Get                         MH1903_TRNG.Get
#define	TRNG_SetPseudoRandom             MH1903_TRNG.SetPseudoRandom
//#define	TRNG_DirectOutANA                MH1903_TRNG.DirectOutANA

#define	TRNG_ITConfig                    MH1903_TRNG.ITConfig
#define	TRNG_GetITStatus                 MH1903_TRNG.GetITStatus
#define	TRNG_ClearITPendingBit           MH1903_TRNG.ClearITPendingBit
#define	TRNG_SelectPDSource              MH1903_TRNG.SelectPDSource

/*------------------------------RTC MODULE--------------------------------*/
#define	RTC_IsReady                      MH1903_RTC.IsReady

#define	RTC_ResetCounter                 MH1903_RTC.ResetCounter
#define	RTC_GetCounter                   MH1903_RTC.GetCounter

#define	RTC_SetRefRegister               MH1903_RTC.SetRefRegister
#define	RTC_GetRefRegister               MH1903_RTC.GetRefRegister

#define	RTC_SetAlarm                     MH1903_RTC.SetAlarm

#define	RTC_GetAttrackTime               MH1903_RTC.RTC_GetAttrackTime

#define	RTC_ITConfig                     MH1903_RTC.ITConfig
#define	RTC_ClearITPendingBit            MH1903_RTC.ClearITPendingBit
#define	RTC_GetITStatus                  MH1903_RTC.GetITStatus

/*------------------------------WDT MODULE--------------------------------*/
#define	WDT_SetReload                    MH1903_WDT.SetReload
#define	WDT_ReloadCounter                MH1903_WDT.ReloadCounter
#define	WDT_Enable                       MH1903_WDT.Enable
#define	WDT_ModeConfig                   MH1903_WDT.ModeConfig

#define	WDT_GetITStatus                  MH1903_WDT.GetITStatus
#define	WDT_ClearITPendingBit            MH1903_WDT.ClearITPendingBit

/*------------------------------DMA MODULE--------------------------------*/
#define	DMA_Init                         MH1903_DMA.Init
#define	DMA_ChannelCmd                   MH1903_DMA.ChannelCmd
#define	DMA_Cmd                          MH1903_DMA.Cmd

#define	DMA_SetSRCAddress                MH1903_DMA.SetSRCAddress
#define	DMA_SetDSRAddress                MH1903_DMA.SetDSRAddress
#define	DMA_SetChannelHardShakePeriph    MH1903_DMA.SetChannelHardShakePeriph
 
#define	DMA_ITConfig                     MH1903_DMA.ITConfig

#define	DMA_IsChannelEnabled             MH1903_DMA.IsChannelEnabled
 
#define	DMA_GetITStatus                  MH1903_DMA.GetITStatus
#define	DMA_GetRawStatus                 MH1903_DMA.GetRawStatus
#define	DMA_ClearITPendingBit            MH1903_DMA.ClearITPendingBit

//#define	DMA_MultiBlockInit               MH1903_DMA.MultiBlockInit
#define	DMA_InitLLI                      MH1903_DMA.InitLLI

/*------------------------------LCD MODULE--------------------------------*/
#define	LCD_BusRead                      MH1903_LCD.BusRead
#define	LCD_BusWrite                     MH1903_LCD.BusWrite

#define	LCD_Read                         MH1903_LCD.Read
#define	LCD_Write                        MH1903_LCD.Write

#define	LCD_ReadBuff                     MH1903_LCD.ReadBuff
#define	LCD_WriteBuff                    MH1903_LCD.WriteBuff
#define	LCD_Init                         MH1903_LCD.Init
#define	LCD_FIFODMAconfig                MH1903_LCD.FIFODMAconfig

/*------------------------------CLCD MODULE-------------------------------*/
#define	CLCD_Init                        MH1903_CLCD.Init
#define	CLCD_InterruptEventsEnable       MH1903_CLCD.InterruptEventsEnable
#define	CLCD_InterruptEventsDisable      MH1903_CLCD.InterruptEventsDisable
#define	CLCD_PowerUp                     MH1903_CLCD.PowerUp
#define	CLCD_PowerDown                   MH1903_CLCD.PowerDown
#define	CLCD_VCompEventsEnable           MH1903_CLCD.VCompEventsEnable
#define	CLCD_BppSet                      MH1903_CLCD.BppSet
#define	CLCD_DrawCLS                     MH1903_CLCD.DrawCLS
#define	CLCD_PaletteInitialise           MH1903_CLCD.PaletteInitialise
#define	CLCD_ColorOrderSet               MH1903_CLCD.ColorOrderSet
#define	CLCD_DMAFrameBufferSet           MH1903_CLCD.DMAFrameBufferSet
#define	CLCD_BytesPer_Panel              MH1903_CLCD.BytesPer_Panel

/*------------------------------DCMI MODULE-------------------------------*/
#define	DCMI_DeInit                      MH1903_DCMI.DeInit

#define	DCMI_Init                        MH1903_DCMI.Init
#define	DCMI_StructInit                  MH1903_DCMI.StructInit
#define	DCMI_CROPConfig                  MH1903_DCMI.CROPConfig
#define	DCMI_CROPCmd                     MH1903_DCMI.CROPCmd
#define	DCMI_SetEmbeddedSynchroCodes     MH1903_DCMI.SetEmbeddedSynchroCodes
#define	DCMI_JPEGCmd                     MH1903_DCMI.JPEGCmd
#define	DCMI_SetDMARequsetFIFOSize       MH1903_DCMI.SetDMARequsetFIFOSize

#define	DCMI_Cmd                         MH1903_DCMI.Cmd
#define	DCMI_CaptureCmd                  MH1903_DCMI.CaptureCmd
#define	DCMI_ReadData                    MH1903_DCMI.ReadData
#define	DCMI_GetFIFODataWordNum          MH1903_DCMI.GetFIFODataWordNum

#define	DCMI_ITConfig                    MH1903_DCMI.ITConfig
#define	DCMI_GetFlagStatus               MH1903_DCMI.GetFlagStatus
#define	DCMI_ClearFlag                   MH1903_DCMI.ClearFlag
#define	DCMI_GetITStatus                 MH1903_DCMI.GetITStatus
#define	DCMI_ClearITPendingBit           MH1903_DCMI.ClearITPendingBit


/*------------------------------SDIO MODULE--------------------------------*/
//#define	SDIO_DeInit                      MH1903_SDIO.DeInit
//#define	SDIO_Reset                       MH1903_SDIO.Reset
//#define	SDIO_ControllerReset             MH1903_SDIO.ControllerReset
//#define	SDIO_FIFOReset                   MH1903_SDIO.FIFOReset
//#define	SDIO_DMAReset                    MH1903_SDIO.DMAReset
//#define	SDIO_GlobalITCmd                 MH1903_SDIO.GlobalITCmd
//#define	SDIO_DMACmd                      MH1903_SDIO.DMACmd
//#define	SDIO_AssertReadWait              MH1903_SDIO.AssertReadWait
//#define	SDIO_ClearReadWait               MH1903_SDIO.ClearReadWait
//#define	SDIO_SendIrqReap                 MH1903_SDIO.SendIrqReap
//#define	SDIO_AbordReadData               MH1903_SDIO.AbordReadData
//#define	SDIO_CCSDSend                    MH1903_SDIO.CCSDSend
//#define	SDIO_CCSDSendAutoStop            MH1903_SDIO.CCSDSendAutoStop
//#define	SDIO_CEATAITCmd                  MH1903_SDIO.CEATAITCmd
//#define	SDIO_CardVolA                    MH1903_SDIO.CardVolA
//#define	SDIO_CardVolB                    MH1903_SDIO.CardVolB
//#define	SDIO_ODPullup                    MH1903_SDIO.ODPullup

//#define	SDIO_ClockInit                   MH1903_SDIO.ClockInit
//#define	SDIO_ClockSourceSel              MH1903_SDIO.ClockSourceSel
//#define	SDIO_SetPowerState               MH1903_SDIO.SetPowerState
//#define	SDIO_GetPowerState               MH1903_SDIO.GetPowerState
//#define	SDIO_LowPowerModeCmd             MH1903_SDIO.LowPowerModeCmd

//#define	SDIO_SetBusWide                  MH1903_SDIO.SetBusWide

//#define	SDIO_SetTimeOut                  MH1903_SDIO.SetTimeOut
//#define	SDIO_SetDataTimeOut              MH1903_SDIO.SetDataTimeOut
//#define	SDIO_SetRespTimeOut              MH1903_SDIO.SetRespTimeOut

//#define	SDIO_SetFIFOThreshold            MH1903_SDIO.SetFIFOThreshold
//#define	SDIO_SetRxFIFOThreshold          MH1903_SDIO.SetRxFIFOThreshold
//#define	SDIO_SetTxFIFOThreshold          MH1903_SDIO.SetTxFIFOThreshold

//#define	SDIO_CardHardwareResetCmd        MH1903_SDIO.CardHardwareResetCmd
//#define	SDIO_CardDetected                MH1903_SDIO.CardDetected
//#define	SDIO_CardWriteProtected          MH1903_SDIO.CardWriteProtected

//#define	SDIO_SetDataByteCount            MH1903_SDIO.SetDataByteCount
//#define	SDIO_GetDataByteCount            MH1903_SDIO.GetDataByteCount
//#define	SDIO_SetDataBlockSize            MH1903_SDIO.SetDataBlockSize
//#define	SDIO_GetDataBlockSize            MH1903_SDIO.GetDataBlockSize
//#define	SDIO_ReadData                    MH1903_SDIO.ReadData
//#define	SDIO_WriteData                   MH1903_SDIO.WriteData
//#define	SDIO_GetFIFOCount                MH1903_SDIO.GetFIFOCount

//#define	SDIO_ITConfig                    MH1903_SDIO.ITConfig
//#define	SDIO_GetRawITStatus              MH1903_SDIO.GetRawITStatus
//#define	SDIO_GetRawITReg                 MH1903_SDIO.GetRawITReg
//#define	SDIO_GetITStatus                 MH1903_SDIO.GetITStatus
//#define	SDIO_ClearITPendingBit           MH1903_SDIO.ClearITPendingBit

//#define	SDIO_SendCommand                 MH1903_SDIO.SendCommand
//#define	SDIO_CmdStructInit               MH1903_SDIO.CmdStructInit
//#define	SDIO_GetResponse                 MH1903_SDIO.GetResponse
//#define	SDIO_GetCommandResponse          MH1903_SDIO.GetCommandResponse

//#define	SDIO_GetCFSMStatus               MH1903_SDIO.GetCFSMStatus
//#define	SDIO_GetStatus                   MH1903_SDIO.GetStatus
		
/*-------------------------------CACHE MODULE--------------------------------*/	
#define	Cache_Flash_Init                 MH1903_CACHE.Init
#define	Cache_Clean                      MH1903_CACHE.Clean
#define	Cache_Clean_all                  MH1903_CACHE.CleanAll

/*-------------------------------QSPI MODULE---------------------------------*/	
#define	QSPI_Init                        MH1903_QSPI.Init
#define	QSPI_ReadID                      MH1903_QSPI.ReadID 
#define	QSPI_WriteParam                  MH1903_QSPI.WriteParam
#define	QSPI_EraseSector                 MH1903_QSPI.EraseSector
#define	QSPI_EraseChip                   MH1903_QSPI.EraseChip
#define	QSPI_ProgramPage                 MH1903_QSPI.ProgramPage
#define	QSPI_DeepPowerDown               MH1903_QSPI.DeepPowerDown
#define	QSPI_ReleaseDeepPowerDown        MH1903_QSPI.ReleaseDeepPowerDown
//#define	QSPI_Read                        MH1903_QSPI.Read
#define	QSPI_StatusReg                   MH1903_QSPI.StatusReg

/*--------------------------------OTP MODULE---------------------------------*/
#define	OTP_WakeUp                       MH1903_OTP.WakeUp
#define	OTP_Unlock                       MH1903_OTP.Unlock
#define	OTP_Lock                         MH1903_OTP.Lock
#define	OTP_ClearStatus                  MH1903_OTP.ClearStatus
#define	OTP_SetLatency                   MH1903_OTP.SetLatency
#define	OTP_TimCmd                       MH1903_OTP.TimCmd
#define	OTP_HideBlock                    MH1903_OTP.HideBlock
#define	OTP_SetProtect                   MH1903_OTP.SetProtect
#define	OTP_SetProtectLock               MH1903_OTP.SetProtectLock
#define	OTP_UnProtect                    MH1903_OTP.UnProtect
#define	OTP_ClearAllHeddenBlock          MH1903_OTP.ClearAllHeddenBlock
#define	OTP_IsHide                       MH1903_OTP.IsHide
#define	OTP_IsReadReady                  MH1903_OTP.IsReadReady
#define	OTP_IsWriteDone                  MH1903_OTP.IsWriteDone
#define	OTP_GetFlag                      MH1903_OTP.GetFlag
#define	OTP_IsProtect                    MH1903_OTP.IsProtect
#define	OTP_IsProtectLock                MH1903_OTP.IsProtectLock
#define	OTP_WriteWord                    MH1903_OTP.WriteWord
#define	OTP_GetProtect                   MH1903_OTP.GetProtect
#define	OTP_GetProtectLock               MH1903_OTP.GetProtectLock
#define	OTP_PowerOn                      MH1903_OTP.PowerOn
/*=============================FWLIB RETARGET END===========================*/

#ifdef USE_CRYPT_MODULE
/*==============================CRYPT RETARGET==============================*/
#define mh_des_enc                       MH1903_CRYPT.des_enc
#define mh_des_dec                       MH1903_CRYPT.des_dec
#define mh_tdes_enc                      MH1903_CRYPT.tdes_enc
#define mh_tdes_dec                      MH1903_CRYPT.tdes_dec

#define mh_rsa_private_crt               MH1903_CRYPT.rsa_private_crt
#define mh_rsa_public                    MH1903_CRYPT.rsa_public
#define mh_rsa_efc_gen_key               MH1903_CRYPT.rsa_efc_gen_key
#define mh_rsa_complete_key              MH1903_CRYPT.rsa_complete_key
#define mh_rsa_complete_key_e            MH1903_CRYPT.rsa_complete_key_e
#define mh_rsa_gen_efc_para              MH1903_CRYPT.rsa_gen_efc_para
#define mh_rsa_gen_key                   MH1903_CRYPT.rsa_gen_key
#define mh_rsa_get_private_key_C_Q       MH1903_CRYPT.rsa_get_private_key_C_Q
#define mh_rsa_get_public_key_C_Q        MH1903_CRYPT.rsa_get_public_key_C_Q
#define mh_rsa_is_prime                  MH1903_CRYPT.rsa_is_prime
#define mh_rsa_efc_gen_prime             MH1903_CRYPT.rsa_efc_gen_prime
#define mh_rsa_private                   MH1903_CRYPT.rsa_private
#define mh_rsa_private_tmp               MH1903_CRYPT.rsa_private_tmp
#define rsa_public_func                  MH1903_CRYPT.rsa_public_func
#define rsa_private_func                 MH1903_CRYPT.rsa_private_func

#define mh_aes_enc                       MH1903_CRYPT.aes_enc
#define mh_aes_dec                       MH1903_CRYPT.aes_dec

#define ecc_config                       MH1903_CRYPT.ecc_config
#define ecc_genkey                       MH1903_CRYPT.ecc_genkey
#define ecc_verifykey                    MH1903_CRYPT.ecc_verifykey
#define ecc_pmul                         MH1903_CRYPT.ecc_pmul
#define ecc_pmul_f2m                     MH1903_CRYPT.ecc_pmul_f2m
#define ecc_verifypoint                  MH1903_CRYPT.ecc_verifypoint
#define ecc_pmul_calc                    MH1903_CRYPT.ecc_pmul_calc
#define ecc_pmul_calc_blinding           MH1903_CRYPT.ecc_pmul_calc_blinding
#define ecc_pmul_f2m_calc                MH1903_CRYPT.ecc_pmul_f2m_calc
#define ecc_pmul_f2m_calc_blinding       MH1903_CRYPT.ecc_pmul_f2m_calc_blinding
#define ecc_j2a                          MH1903_CRYPT.ecc_j2a
#define ecc_j2mj                         MH1903_CRYPT.ecc_j2mj
#define ecc_j2mj_t                       MH1903_CRYPT.ecc_j2mj_t
#define ecc_padd_a                       MH1903_CRYPT.ecc_padd_a
#define ecc_padd_ja                      MH1903_CRYPT.ecc_padd_ja
#define ecc_pdbl_a                       MH1903_CRYPT.ecc_pdbl_a
#define ecc_pdbl_j                       MH1903_CRYPT.ecc_pdbl_j
#define ecc_pdbl_mj                      MH1903_CRYPT.ecc_pdbl_mj
#define ecc_naf                          MH1903_CRYPT.ecc_naf
#define ecc_naf_point                    MH1903_CRYPT.ecc_naf_point

#define mh_sha                           MH1903_CRYPT.sha
#define mh_sha_sec                       MH1903_CRYPT.sha_sec
#define sha1_starts                      MH1903_CRYPT.sha1_starts
#define sha1_update                      MH1903_CRYPT.sha1_update
#define sha1_finish                      MH1903_CRYPT.sha1_finish
#define sha256_starts                    MH1903_CRYPT.sha256_starts
#define sha256_update                    MH1903_CRYPT.sha256_update
#define sha256_finish                    MH1903_CRYPT.sha256_finish

#define sm2_genkey                       MH1903_CRYPT.sm2_genkey
#define mh_sm2_kdf                       MH1903_CRYPT.sm2_kdf
#define mh_sm2_hash_z                    MH1903_CRYPT.sm2_hash_z
#define mh_sm2_hash_e                    MH1903_CRYPT.sm2_hash_e
#define mh_sm2_enc                       MH1903_CRYPT.sm2_enc
#define mh_sm2_dec                       MH1903_CRYPT.sm2_dec
#define mh_sm2_digital_sign              MH1903_CRYPT.sm2_digital_sign
#define mh_sm2_verify_sign               MH1903_CRYPT.sm2_verify_sign
#define mh_sm2_digital_sign_with_e       MH1903_CRYPT.sm2_digital_sign_with_e
#define mh_sm2_verify_sign_with_e        MH1903_CRYPT.sm2_verify_sign_with_e
#define mh_sm2_key_ex_equation_0         MH1903_CRYPT.sm2_key_ex_equation_0
#define mh_sm2_key_ex_equation_1         MH1903_CRYPT.sm2_key_ex_equation_1
#define mh_sm2_key_ex_equation_2         MH1903_CRYPT.sm2_key_ex_equation_2	
#define mh_sm2_key_ex_section_0          MH1903_CRYPT.sm2_key_ex_section_0
#define mh_sm2_key_ex_section_1          MH1903_CRYPT.sm2_key_ex_section_1
#define mh_sm2_key_ex_hash               MH1903_CRYPT.sm2_key_ex_hash
#define MH_SM2Sign                       MH1903_CRYPT.MH_SM2Sign
#define MH_SM2Verify                     MH1903_CRYPT.MH_SM2Verify

#define mh_sm3                           MH1903_CRYPT.sm3

#define mh_sm4_enc                       MH1903_CRYPT.sm4_enc
#define mh_sm4_dec                       MH1903_CRYPT.sm4_dec

#define bn_set_int                       MH1903_CRYPT.bn_set_int
#define bn_cpy                           MH1903_CRYPT.bn_cpy
#define bn_cmp                           MH1903_CRYPT.bn_cmp
#define bn_swap                          MH1903_CRYPT.bn_swap
#define bn_cmp_int                       MH1903_CRYPT.bn_cmp_int
#define bn_add                           MH1903_CRYPT.bn_add
#define bn_sub                           MH1903_CRYPT.bn_sub
#define bn_add_int                       MH1903_CRYPT.bn_add_int
#define bn_sub_int                       MH1903_CRYPT.bn_sub_int
#define bn_modadd                        MH1903_CRYPT.bn_modadd
#define bn_modsub                        MH1903_CRYPT.bn_modsub
#define bn_mul                           MH1903_CRYPT.bn_mul
#define bn_div                           MH1903_CRYPT.bn_div
#define bn_set_p                         MH1903_CRYPT.bn_set_p
#define bn_modexp_p                      MH1903_CRYPT.bn_modexp_p
#define bn_get_C                         MH1903_CRYPT.bn_get_C
#define bn_get_Q                         MH1903_CRYPT.bn_get_Q
#define bn_modmul_p                      MH1903_CRYPT.bn_modmul_p
#define bn_modmul                        MH1903_CRYPT.bn_modmul
#define bn_modinv_1024                   MH1903_CRYPT.bn_modinv_1024
#define bn_modinv                        MH1903_CRYPT.bn_modinv
#define bn_s_cpy                         MH1903_CRYPT.bn_s_cpy
#define bn_s_mul                         MH1903_CRYPT.bn_s_mul
#define bn_s_div                         MH1903_CRYPT.bn_s_div
#define bn_s_modexp_p                    MH1903_CRYPT.bn_s_modexp_p
#define bn_s_get_C                       MH1903_CRYPT.bn_s_get_C
#define bn_s_get_Q                       MH1903_CRYPT.bn_s_get_Q
#define bn_s_modmul_p                    MH1903_CRYPT.bn_s_modmul_p
#define bn_s_modinv_1024                 MH1903_CRYPT.bn_s_modinv_1024
#define bn_get_C_f2m                     MH1903_CRYPT.bn_get_C_f2m
#define bn_get_Q_f2m                     MH1903_CRYPT.bn_get_Q_f2m
#define bn_modmul_p_f2m                  MH1903_CRYPT.bn_modmul_p_f2m
#define bn_modmul_f2m                    MH1903_CRYPT.bn_modmul_f2m
#define bn_modinv_f2m                    MH1903_CRYPT.bn_modinv_f2m
#define bn_gcd                           MH1903_CRYPT.bn_gcd
#define bn_gcd_int                       MH1903_CRYPT.bn_gcd_int
#define bn_shift_r                       MH1903_CRYPT.bn_shift_r
#define bn_shift_l                       MH1903_CRYPT.bn_shift_l
#define bn_lsb                           MH1903_CRYPT.bn_lsb
#define bn_msb                           MH1903_CRYPT.bn_msb
#define bn_byte                          MH1903_CRYPT.bn_byte
#define bn_len                           MH1903_CRYPT.bn_len
#define bn_xor                           MH1903_CRYPT.bn_xor

#define mh_memcmp                        MH1903_CRYPT.mh_memcmp
#define mh_is_equal                      MH1903_CRYPT.mh_is_equal
#define mh_memcpy                        MH1903_CRYPT.mh_memcpy
#define mh_memswap                       MH1903_CRYPT.mh_memswap
#define memswap                          MH1903_CRYPT.memswap
#define mh_xor_u32                       MH1903_CRYPT.mh_xor_u32
#define mh_sum_u32                       MH1903_CRYPT.mh_sum_u32

#define mh_crypt_reset                   MH1903_CRYPT.reset
#define mh_crypt_it_clear                MH1903_CRYPT.it_clear
#define mh_crypt_version                 MH1903_CRYPT.version
/*=============================CRYPT RETARGET END===========================*/
#endif

#ifdef USE_USB_MODULE
/*===============================USB RETARGET===============================*/
#define DCD_EP_Open                      MH1903_USBCORE.DCD_EP_Open
#define DCD_EP_Close                     MH1903_USBCORE.DCD_EP_Close
#define DCD_EP_PrepareRx                 MH1903_USBCORE.DCD_EP_PrepareRx
#define DCD_EP_Tx                        MH1903_USBCORE.DCD_EP_Tx
#define DCD_EP_Stall                     MH1903_USBCORE.DCD_EP_Stall
#define DCD_EP_ClrStall                  MH1903_USBCORE.DCD_EP_ClrStall
#define DCD_EP_Flush                     MH1903_USBCORE.DCD_EP_Flush

#define USBD_OTG_ISR_Handler             MH1903_USBCORE.OTG_ISR_Handler

#define USBD_Init                        MH1903_USBCORE.USBD_Init

#define USBD_CtlSendData                 MH1903_USBCORE.USBD_CtlSendData
#define USBD_CtlContinueSendData         MH1903_USBCORE.USBD_CtlContinueSendData
#define USBD_CtlPrepareRx                MH1903_USBCORE.USBD_CtlPrepareRx
#define USBD_CtlContinueRx               MH1903_USBCORE.USBD_CtlContinueRx
#define USBD_GetRxCount                  MH1903_USBCORE.USBD_GetRxCount

#define USBD_CtlError                    MH1903_USBCORE.USBD_CtlError
#define USBD_GetString                   MH1903_USBCORE.USBD_GetString
/*=============================USB RETARGET END=============================*/
#endif

#ifdef USE_SCI_MODULE
/*===============================EMV RETARGET===============================*/
#define emv_tell_case                    MH1903_EMVCORE.tell_case
#define emv_atr_analyser                 MH1903_EMVCORE.atr_analyser
#define emv_atr_parse                    MH1903_EMVCORE.atr_parse
#define emv_t0_exchange                  MH1903_EMVCORE.t0_exchange
#define emv_t1_compute_lrc               MH1903_EMVCORE.t1_compute_lrc
#define emv_t1_extract                   MH1903_EMVCORE.t1_extract
#define emv_t1_iblock_pack               MH1903_EMVCORE.t1_iblock_pack
#define emv_t1_block_xmit                MH1903_EMVCORE.t1_block_xmit
#define emv_t1_block_recv                MH1903_EMVCORE.t1_block_recv
#define emv_t1_exchange                  MH1903_EMVCORE.t1_exchange
#define emv_t1_ifsd_request              MH1903_EMVCORE.t1_ifsd_request

#define fi_const_table                   MH1903_EMVCORE.fi_const_table
#define di_const_table                   MH1903_EMVCORE.di_const_table
#define fi_const_index                   MH1903_EMVCORE.fi_const_index
#define di_const_index                   MH1903_EMVCORE.di_const_index

#define adjust_timeout_type              MH1903_EMVCORE.adjust_timeout_type
#define iso_atr_parse                    MH1903_EMVCORE.iso_atr_parse
#define iso_condsel_procedure            MH1903_EMVCORE.iso_condsel_procedure
#define iso_pps_procedure                MH1903_EMVCORE.iso_pps_procedure

#define emv_core_init                    MH1903_EMVCORE.core_init
#define emv_queue_flush                  MH1903_EMVCORE.queue_flush
#define emv_queue_empty                  MH1903_EMVCORE.queue_empty
#define emv_queue_length                 MH1903_EMVCORE.queue_length
#define emv_queue_fill                   MH1903_EMVCORE.queue_fill
#define emv_queue_spill                  MH1903_EMVCORE.queue_spill

#define iso7816_device_init              MH1903_EMVCORE.iso7816_device_init
#define iso7816_init                     MH1903_EMVCORE.iso7816_init
#define iso7816_exchange                 MH1903_EMVCORE.iso7816_exchange
#define iso7816_close                    MH1903_EMVCORE.iso7816_close
#define iso7816_detect                   MH1903_EMVCORE.iso7816_detect
#define iso7816_getlibversion            MH1903_EMVCORE.iso7816_getlibversion

#define isvalid_channel                  MH1903_EMVCORE.isvalid_channel
#define select_slot                      MH1903_EMVCORE.select_slot
#define emv_hard_init                    MH1903_EMVCORE.hard_init
#define emv_disturb_interruption         MH1903_EMVCORE.disturb_interruption
#define emv_hard_power_pump              MH1903_EMVCORE.hard_power_pump
#define emv_hard_cold_reset              MH1903_EMVCORE.hard_cold_reset
#define emv_hard_warm_reset              MH1903_EMVCORE.hard_warm_reset
#define emv_hard_power_dump              MH1903_EMVCORE.hard_power_dump
#define emv_hard_xmit                    MH1903_EMVCORE.hard_xmit
#define emv_hard_detect                  MH1903_EMVCORE.hard_detect

#if SCI_FUNC_PATCH
#define SCI_ConfigEMV                    MH1903_EMVCORE.ConfigEMV
#else
#define SCI_ConfigEMV                    (*(int32_t (*)(uint8_t SCI_Bitmap, uint32_t SCIx_Clk))0x0001070f)
#endif
/*=============================EMV RETARGET END=============================*/
#endif


#ifdef __cplusplus
}
#endif

#endif //__MHSCPU_RETARGET_H__


/************************ (C) COPYRIGHT 2014 Megahuntmicro ****END OF FILE****/

