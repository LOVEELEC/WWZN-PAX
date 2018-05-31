/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_driver.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-May-2017
 * @brief               : This file contains all the module functions for the firmware library
 *****************************************************************************/

/* Includes -----------------------------------------------------------------*/
#include "mhscpu_driver.h"

#ifdef USE_USB_MODULE
#include "usb_dcd_int.h"
#include "usbd_req.h"
#include "usbd_ioreq.h"
#endif

#include "emv_fidi_table.h"
#include "emv_patch.h"
#include "emv_queue.h"
#include "emv_hard.h"

const MH1903_FuncTypeDef MH1903_FirmwareLib __attribute__ ((at(0x00008000), used)) =
{
	"MH1903_LIB",
	MH_GetFwlibVersion,
	
    /********************SYSCTRL MODULE********************/
	{
		SYSCTRL_AHBPeriphClockCmd,
		SYSCTRL_AHBPeriphResetCmd,
		SYSCTRL_APBPeriphClockCmd,
		SYSCTRL_APBPeriphResetCmd,

		SYSCTRL_EnterSleep,
		SYSCTRL_WakeIntDeInit,
		SYSCTRL_WakeUpInt1Config,
		SYSCTRL_WakeUpInt2Config,
		SYSCTRL_GetWakeupFlag1Status,
		SYSCTRL_GetWakeupFlag2Status,

		SYSCTRL_SYSCLKSourceSelect,
		SYSCTRL_PLLConfig,
		SYSCTRL_PLLDivConfig,
		SYSCTRL_HCLKConfig,
		SYSCTRL_PCLKConfig,

		SYSCTRL_GetClocksFreq
	},
	
    /**********************CRC MODULE**********************/	
	{
		CRC_CalcBlockCRC,
		CRC_Calc
	},
	
	/**********************ADC MODULE**********************/
	{
		ADC_Init,
		ADC_StartCmd,
		ADC_FIFODeepth,
		ADC_FIFOReset,
		ADC_ITCmd,
		ADC_FIFOOverflowITcmd,
		ADC_GetFIFOCount,
		ADC_GetResult,
		ADC_GetFIFOResult,
		ADC_CalVoltage	
	},

	/**********************GPIO MODULE*********************/
	{
		GPIO_DeInit,
		GPIO_Init,
		GPIO_StructInit,

		GPIO_ReadInputDataBit,
		GPIO_ReadInputData,

		GPIO_ReadOutputDataBit,
		GPIO_ReadOutputData,

		GPIO_SetBits,
		GPIO_ResetBits,
		GPIO_Write,
		GPIO_PullUpCmd,

		GPIO_PinRemapConfig,

		GPIO_WakeEvenDeInit,
		GPIO_WakeEvenConfig,
		GPIO_WakeModeConfig	
	},

	/**********************EXTI MODULE*********************/
	{
		EXTI_DeInit,
		EXTI_LineConfig,
		EXTI_GetITStatus,
		EXTI_GetITLineStatus,
		EXTI_ClearITPendingBit
	},

	/**********************TIM MODULE**********************/		
	{
		TIM_DeInit,
		TIM_Init,

		TIM_PWMInit,
		TIM_Cmd,
		TIM_ModeConfig,
		TIM_SetPeriod,
		TIM_SetPWMPeriod,
		TIM_ITConfig,
		TIM_ClearITPendingBit,
		TIM_PWMSinglePulseConfig,

		TIM_GetITStatus,
		TIM_GetAllITStatus,
		TIM_GetRawITStatus,
		TIM_GetAllRawITStatus
	},

	/**********************UART MODULE*********************/
	{
		UART_DeInit,
		UART_Init,
		UART_StructInit,
		UART_ITConfig,

		UART_SendData,
		UART_ReceiveData,

		UART_FIFOInit,
		UART_FIFOStructInit,
		UART_FIFOReset,
		UART_FIFOCmd,
		UART_SetRTS,
		UART_ResetRTS,
		UART_SetDTR,
		UART_ResetDTR,
		UART_SendBreak,
		UART_AutoFlowCtrlCmd,
		UART_IrDACmd,

		UART_GetLineStatus,
		UART_GetModemStatus,
		UART_GetITIdentity,

		UART_IsTXEmpty,
		UART_IsTXHoldingRegisterEmpty,

		UART_IsRXFIFOFull,
		UART_IsRXFIFONotEmpty,
		UART_IsTXFIFOEmpty,
		UART_IsTXFIFONotFull,
		UART_IsBusy,

		UART_DMAGenerateSoftAck,

		UART_TXHaltCmd,
		UART_FIFOAccessModeCmd	
	},

	/**********************SPI MODULE**********************/	      
	{
		SPI_DeInit,
		SPI_Init,
		SPI_StructInit,
		SPI_Cmd,

		SPI_DMAInit,
		SPI_DMAStructInit,
		SPI_DMACmd,

		SPI_ITConfig,
		SPI_SendData,
		SPI_ReceiveData,
		SPI_DataSizeConfig,
		SPI_BiDirectionalLineConfig,

		SPI_GetITStatus,
		SPI_ClearITPendingBit,

		SPI_GetFlagStatus,
		SPI_GetFlagStatusReg,

		SPI_IsBusy,
		SPI_IsTXErr,
		SPI_IsDataCollisionErr,
		SSP_Init,
		SSP_StructInit,

		NSM_Init,
		NSM_StructInit	
	},

	/**********************I2C MODULE**********************/
	{
		I2C_DeInit,
		I2C_Init,
		I2C_StructInit,
		
		I2C_Cmd,
		I2C_SetTargetAddress,
		I2C_DMAInit,
		I2C_DMAStructInit,
		I2C_DMACmd,
		I2C_SetSDASetupTime,
		I2C_SetSDAHoldTime,

		I2C_ITConfig,
		I2C_GetITStatus,
		I2C_GetRawITStatus,
		I2C_ClearITPendingBit,
		I2C_GetFlagStatus,
		I2C_GetFlagStatusReg,
		I2C_GetTXAbortSource,
		I2C_GetTXAbortSourceReg,
		I2C_GetI2CMode,

		I2C_MasterGenerateReceiveSCL,
		I2C_ExtendData,
		I2C_WriteDataToDR,
		I2C_ReadDataFromDR,
		I2C_SendData,
		I2C_ReceiveData,
		I2C_SendBytes,
		I2C_ReceiveBytes,

		I2C_SlaveGeneralNACKOnlyCmd,

		I2C_IsEnable		
	},

	/**********************KCU MODULE**********************/	
	{
		KCU_DeInit,
		KCU_Init,
		KCU_StructInit,
		
		KCU_Cmd,
		KCU_SetRand,
		
		KCU_ITConfig,
		KCU_GetITStatus,
		KCU_ClearITPending,
		KCU_GetEvenReg
	},

	/**********************BPK MODULE**********************/	
	{
		BPK_IsReady,
		
		BPK_WriteKey,
		BPK_ReadKey,
		
		BPK_KeyWriteLock,
		BPK_KeyReadLock,
		BPK_KeyClear,
		
		BPK_SetScramber,
		BPK_Reset,
		
		BPK_Lock,
		BPK_LockSelf,
		BPK_GetLockStatus		
	},

	/*********************SENSOR MODULE********************/	
	{
		SENSOR_SetRand,
		SENSOR_EXTInit,
		SENSOR_EXTPortCmd,
		SENSOR_EXTCmd,
		SENSOR_EXTIsRuning,
		SENSOR_ANACmd,
		SENSOR_Lock,
		SENSOR_AttackRespMode,

		SENSOR_GetITStatus,
		SENSOR_GetITStatusReg,
		SENSOR_ClearITPendingBit,

		SENSOR_GetEXTTrigPull,
		SENSOR_SetEXTTrigPull,

		SENSOR_GetEXTFilter,
		SENSOR_SetEXTFilter,

		SENSOR_GetEXTPulsePeriod,
		SENSOR_SetEXTPulsePeriod,

		SENSOR_GetEXTPulseHold,
		SENSOR_SetEXTPulseHold,

		SENSOR_GetEXTPulsePull,
		SENSOR_SetEXTPulsePull,

		SENSOR_GetEXTStaticSample,
		SENSOR_SetEXTStaticSample,
		SENSOR_GetEXTDynamicSample,
		SENSOR_SetEXTDynamicSample,

		SENSOR_GetEXTDynamicFreq,
		SENSOR_SetEXTDynamicFreq		
	},

	/**********************SSC MODULE**********************/		
	{
		SSC_Init,
		
		SSC_GetITStatus,
		SSC_ClearITPendingBit,

		SSC_SetDataRAMScrambler,
		SSC_BPKAccessCtrlConfig,
		
		SSC_SENSORCmd,
		SSC_SENSORLock,
		SSC_SENSORAttackRespMode
	},

	/*********************TRNG MODULE**********************/	
	{
		TRNG_Start,
		TRNG_Stop,
		TRNG_Get,
		TRNG_SetPseudoRandom,
		TRNG_DirectOutANA,

		TRNG_ITConfig,
		TRNG_GetITStatus,
		TRNG_ClearITPendingBit,
		TRNG_SelectPDSource
	},

	/**********************RTC MODULE**********************/			
	{
		RTC_IsReady,

		RTC_ResetCounter,
		RTC_GetCounter,

		RTC_SetRefRegister,
		RTC_GetRefRegister,

		RTC_SetAlarm,

		RTC_GetAttrackTime,

		RTC_ITConfig,
		RTC_ClearITPendingBit,
		RTC_GetITStatus		
	},

	/**********************WDT MODULE**********************/	
	{
		WDT_SetReload,
		WDT_ReloadCounter,
		WDT_Enable,
		WDT_ModeConfig,
			 
		WDT_GetITStatus,
		WDT_ClearITPendingBit
	},

	/**********************DMA MODULE**********************/	
	{
		DMA_Init,
		DMA_ChannelCmd,
		DMA_Cmd,

		DMA_SetSRCAddress,
		DMA_SetDSRAddress,
		DMA_SetChannelHardShakePeriph,
			 
		DMA_ITConfig,

		DMA_IsChannelEnabled,
			 
		DMA_GetITStatus,
		DMA_GetRawStatus,
		DMA_ClearITPendingBit,

		DMA_MultiBlockInit,
		DMA_InitLLI	
	},

	/**********************LCD MODULE**********************/	
	{
		LCD_BusRead,
		LCD_BusWrite,

		LCD_Read,
		LCD_Write,

		LCD_ReadBuff,
		LCD_WriteBuff,
		LCD_Init,
		LCD_FIFODMAconfig
	},

	/*********************CLCD MODULE**********************/	
	{
		CLCD_Init,
		CLCD_InterruptEventsEnable,
		CLCD_InterruptEventsDisable,
		CLCD_PowerUp,
		CLCD_PowerDown,
		CLCD_VCompEventsEnable,
		CLCD_BppSet,
		CLCD_DrawCLS,
		CLCD_PaletteInitialise,
		CLCD_ColorOrderSet,
		CLCD_DMAFrameBufferSet,
		CLCD_BytesPer_Panel
	},

	/*********************DCMI MODULE**********************/
	{
		DCMI_DeInit,

		DCMI_Init,
		DCMI_StructInit,
		DCMI_CROPConfig,
		DCMI_CROPCmd,
		DCMI_SetEmbeddedSynchroCodes,
		DCMI_JPEGCmd,
		DCMI_SetDMARequsetFIFOSize,

		DCMI_Cmd,
		DCMI_CaptureCmd,
		DCMI_ReadData,
		DCMI_GetFIFODataWordNum,

		DCMI_ITConfig,
		DCMI_GetFlagStatus,
		DCMI_ClearFlag,
		DCMI_GetITStatus,
		DCMI_ClearITPendingBit		
	},

	/**********************QR MODULE***********************/
	{
		QR_DeInit,

		QR_SMUAD,
		QR_SMUSDX,
		QR_MatrixMultiple,
		QR_Projection,
		QR_GetMatrixResult,
		QR_GetProjectionResult,

		QR_ITConfig,
		QR_GetITStatus,
		QR_ClearITPendingBit,
		QR_GetFlagStatus,
		QR_ClearFlag	
	},

	/*********************SDIO MODULE**********************/
	{
		SDIO_DeInit,
		SDIO_Reset,
		SDIO_ControllerReset,
		SDIO_FIFOReset,
		SDIO_DMAReset,
		SDIO_GlobalITCmd,
		SDIO_DMACmd,
		SDIO_AssertReadWait,
		SDIO_ClearReadWait,
		SDIO_SendIrqReap,
		SDIO_AbordReadData,
		SDIO_CCSDSend,
		SDIO_CCSDSendAutoStop,
		SDIO_CEATAITCmd,
		SDIO_CardVolA,
		SDIO_CardVolB,
		SDIO_ODPullup,

		SDIO_ClockInit,
		SDIO_ClockSourceSel,
		SDIO_SetPowerState,
		SDIO_GetPowerState,
		SDIO_LowPowerModeCmd,

		SDIO_SetBusWide,

		SDIO_SetTimeOut,
		SDIO_SetDataTimeOut,
		SDIO_SetRespTimeOut,

		SDIO_SetFIFOThreshold,
		SDIO_SetRxFIFOThreshold,
		SDIO_SetTxFIFOThreshold,

		SDIO_CardHardwareResetCmd,
		SDIO_CardDetected,
		SDIO_CardWriteProtected,

		SDIO_SetDataByteCount,
		SDIO_GetDataByteCount,
		SDIO_SetDataBlockSize,
		SDIO_GetDataBlockSize,
		SDIO_ReadData,
		SDIO_WriteData,
		SDIO_GetFIFOCount,

		SDIO_ITConfig,
		SDIO_GetRawITStatus,
		SDIO_GetRawITReg,
		SDIO_GetITStatus,
		SDIO_ClearITPendingBit,

		SDIO_SendCommand,
		SDIO_CmdStructInit,
		SDIO_GetResponse,
		SDIO_GetCommandResponse,

		SDIO_GetCFSMStatus,
		SDIO_GetStatus		
	},
	
	/*********************CACHE MODULE*********************/
	{
		Cache_Flash_Init,
		Cache_Clean,
		Cache_Clean_all
	},

	/*********************QSPI MODULE**********************/	
	{
		QSPI_Init,
		
		QSPI_ReadID,
		QSPI_WriteParam,
		QSPI_EraseSector,
		QSPI_EraseChip,
		QSPI_ProgramPage,
		
		QSPI_DeepPowerDown,
		QSPI_ReleaseDeepPowerDown,
		
		QSPI_Read,
		QSPI_StatusReg
	},

	/**********************OTP MODULE**********************/	
	{
		OTP_WakeUp,
		OTP_Unlock,
		OTP_Lock,
		OTP_ClearStatus,
	    OTP_SetLatency,
		OTP_TimCmd,
		OTP_HideBlock,
		OTP_SetProtect,
	    OTP_SetProtectLock,
		OTP_UnProtect,
		OTP_ClearAllHiddenBlock,
		OTP_IsHide,
		OTP_IsReadReady,
		OTP_IsWriteDone,
		OTP_GetFlag,
		OTP_IsProtect,
		OTP_IsProtectLock,
		OTP_WriteWord,
		OTP_GetProtect,
		OTP_GetProtectLock,
		OTP_PowerOn	
	},
	
	/*********************CRYPT MODULE*********************/		
	{
		/*********************DES**********************/
		mh_des_enc,
		mh_des_dec,
		mh_tdes_enc,
		mh_tdes_dec,

		/*********************RSA**********************/	
		mh_rsa_private_crt,
		mh_rsa_public,
		mh_rsa_efc_gen_key,
		
		mh_rsa_complete_key,
		mh_rsa_complete_key_e,
		
		mh_rsa_gen_efc_para,
		mh_rsa_gen_key,
		
		mh_rsa_get_private_key_C_Q,
		mh_rsa_get_public_key_C_Q,

		mh_rsa_is_prime,
		
		mh_rsa_efc_gen_prime,
		mh_rsa_private,
		mh_rsa_private_tmp,

		rsa_public_func,
		rsa_private_func,

		/*********************AES**********************/
		mh_aes_enc,
		mh_aes_dec,

		/*********************ECC**********************/
		ecc_config,
		ecc_genkey,
		ecc_verifykey,
		ecc_pmul,
		ecc_pmul_f2m,
		ecc_verifypoint,
		ecc_pmul_calc,
		ecc_pmul_calc_blinding,
		ecc_pmul_f2m_calc,
		ecc_pmul_f2m_calc_blinding,
		
		ecc_j2a,
		ecc_j2mj,
		ecc_j2mj_t,

		ecc_padd_a,
		ecc_padd_ja,
		ecc_pdbl_a,
		ecc_pdbl_j,
		ecc_pdbl_mj,

		ecc_naf,
		ecc_naf_point,
		
		/*********************SHA**********************/
		mh_sha,
		mh_sha_sec,

		sha1_starts,
		sha1_update,
		sha1_finish,

		sha256_starts,
		sha256_update,
		sha256_finish,

		/*********************SM2**********************/	
		sm2_genkey,
		mh_sm2_kdf,
		mh_sm2_hash_z,
		mh_sm2_hash_e,

		mh_sm2_enc,
		mh_sm2_dec,
		
		mh_sm2_digital_sign,
		mh_sm2_verify_sign,
		mh_sm2_digital_sign_with_e,
		mh_sm2_verify_sign_with_e,

		mh_sm2_key_ex_equation_0,
		mh_sm2_key_ex_equation_1,
		mh_sm2_key_ex_equation_2,

		mh_sm2_key_ex_section_0,
		mh_sm2_key_ex_section_1,
		mh_sm2_key_ex_hash,

		MH_SM2Sign,
		MH_SM2Verify,

		/*********************SM3**********************/		
		mh_sm3,

		/*********************SM4**********************/	
		mh_sm4_enc,
		mh_sm4_dec,
		
		/*******************BIG NUM********************/		
		bn_set_int,
	    bn_cpy,
		bn_cmp,
		bn_swap,
		bn_cmp_int,

		bn_add,
		bn_sub,
		bn_add_int,
	    bn_sub_int,
		bn_modadd,
		bn_modsub,
		bn_mul,
		bn_div,

		bn_set_p,

		bn_modexp_p,
		bn_get_C,
		bn_get_Q,
		bn_modmul_p,
		bn_modmul,
		bn_modinv_1024,
		bn_modinv,

		bn_s_cpy,

		bn_s_mul,
		bn_s_div,

		bn_s_modexp_p,
		bn_s_get_C,
		bn_s_get_Q,
		bn_s_modmul_p,
		bn_s_modinv_1024,

		bn_get_C_f2m,
		bn_get_Q_f2m,
		bn_modmul_p_f2m,
	    bn_modmul_f2m,
		bn_modinv_f2m,

		bn_gcd,
		bn_gcd_int,

		bn_shift_r,
		bn_shift_l,
		bn_lsb,
	    bn_msb,
	    bn_byte,
		bn_len,
		bn_xor,

		/*********************MISC*********************/
		mh_memcmp,
		mh_is_equal,
		mh_memcpy,
		mh_memswap,
		memswap,
		mh_xor_u32,
		mh_sum_u32,

		/********************Common********************/		
		mh_crypt_reset,
		mh_crypt_it_clear,
		mh_crypt_version
	},
	
	/**********************EMV MODULE**********************/	
	{
		emv_tell_case,
		emv_atr_analyser,
		emv_atr_parse,
		emv_t0_exchange,
		emv_t1_compute_lrc,
		emv_t1_extract,
		emv_t1_iblock_pack,
		emv_t1_block_xmit,
		emv_t1_block_recv,
		emv_t1_exchange,
		emv_t1_ifsd_request,
		
		fi_const_table,
		di_const_table,
		fi_const_index,
		di_const_index,
		
		adjust_timeout_type,
		iso_atr_parse,
		iso_condsel_procedure,
		iso_pps_procedure,
		
		emv_core_init,
		emv_queue_flush,
		emv_queue_empty,
		emv_queue_length,
		emv_queue_fill,
		emv_queue_spill,
			
		iso7816_device_init,
		iso7816_init,
		iso7816_exchange,
		iso7816_close,
		iso7816_detect,
		iso7816_getlibversion,
		
		isvalid_channel,
		select_slot,
		emv_hard_init,
		emv_disturb_interruption,
		emv_hard_power_pump,
		emv_hard_cold_reset,
		emv_hard_warm_reset,
		emv_hard_power_dump,
		emv_hard_xmit,
		emv_hard_detect,
#if SCI_FUNC_PATCH		
		SCI_ConfigEMV,
#endif		
	},	

#ifdef USE_USB_MODULE
	{
		/*********************USB Dcd**********************/
		DCD_EP_Open,
		DCD_EP_Close,

		DCD_EP_PrepareRx,
		  
		DCD_EP_Tx,
		DCD_EP_Stall,
		DCD_EP_ClrStall,
		DCD_EP_Flush,
		
		/*******************USB Dcd Int********************/
		USBD_OTG_ISR_Handler,
		
		/********************USBD Core*********************/
		USBD_Init,
		
		/********************USBD Ioreq********************/	
		USBD_CtlSendData,
		USBD_CtlContinueSendData,
		USBD_CtlPrepareRx,
		USBD_CtlContinueRx,
		USBD_GetRxCount,
		
		/*********************USBD Req*********************/
		USBD_CtlError,
		USBD_GetString,
	}
#endif	
};


/************************ (C) COPYRIGHT 2014 Megahuntmicro ****END OF FILE****/
