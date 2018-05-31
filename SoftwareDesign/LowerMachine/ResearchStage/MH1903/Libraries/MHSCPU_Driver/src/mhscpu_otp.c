/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_otp.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file provides all the OTP firmware functions
 *****************************************************************************/

/* Include ------------------------------------------------------------------*/
#include "mhscpu_otp.h"
#define DBG_MODULE (1)
#if DBG_MODULE == 1
#include <stdio.h>
#endif

#define OTP_DONE_FLAG               BIT(0)
#define OTP_START                   BIT(0)
#define OTP_WAKEUPEN                BIT(1)

#define OTP_TIM_EN                  (0xA5)

/*OTP unlock key*/
#define OTP_KEY1 				(0xABCD00A5)
#define OTP_KEY2 				(0x1234005A)

#ifdef USE_ROM_SECTION
#define __OTP_DATA_SECTION   __attribute__((section("otp_data")))
#else
#define __OTP_DATA_SECTION
#endif

static uint32_t gu32OTP_Key1 __OTP_DATA_SECTION = 0;
static uint32_t gu32OTP_Key2 __OTP_DATA_SECTION = 0;


/******************************************************************************
* Function Name  : OTP_Operate
* Description    : ������OTP�Ĳ���
* Input          : NONE
* Return         : NONE
******************************************************************************/
static void OTP_Operate(void)
{
    OTP->CS |= OTP_START;
}

/******************************************************************************
 * Function Name  : OTP_WakeUp
 * Description    : ���OTP��������״̬������OTP��
                    �ӳ��͹��Ļ���ʱ��Ҫ����OTP��
 * Input          : NONE
 * Return         : NONE
******************************************************************************/
void OTP_WakeUp(void)
{
	OTP->CFG |= OTP_WAKEUPEN;
}

/******************************************************************************
 * Function Name  : OTP_SetLatency
 * Description    : ����OTPʱ��Ĵ������ֱ�����1Us��10ns��ʱ�Ӹ�����
                    �������0�����յ�ǰʱ��Ƶ�ʼ����һ��ֵд��ȥ��
                    ��otp_tim_en�Ĵ���ΪA5ʱ��OTP_TimCmd()��������ENABLEʱ����
                    ��ʹ��������������ã�����OTP_TimCmd()��������DISENABLE��
                    ʹ�ú������Լ������ã��Ƽ�ʹ�ú��Լ������ã�OTP_TimCmd()��������DISENABLE����
 * Input          : u8_1UsClk,u8_10NsCLK
 * Return         : NONE
******************************************************************************/
void OTP_SetLatency(uint8_t u8_1UsClk, uint8_t u8_10NsCLK)
{
	if (0 == u8_1UsClk)
	{
		OTP->TIM = ((OTP->TIM & ~(0xFF)) | (SYSCTRL->HCLK_1MS_VAL + 1000 - 1) / 1000);
	}
	else
	{
		OTP->TIM = ((OTP->TIM & ~(0xFF)) | u8_1UsClk);
	}
    if (0 == u8_10NsCLK)
    {
        OTP->TIM = ((OTP->TIM & ~(0x7 << 8)) | (SYSCTRL->HCLK_1MS_VAL / 100000 + 1));
    }
    else
    {
        OTP->TIM = ((OTP->TIM & ~(0x7 << 8)) | u8_10NsCLK);
    }
}

/******************************************************************************
* Function Name  : OTP_Unlock
* Description    : ��ȡд�����õ�����Կ
* Input          : NONE
* Return         : NONE
******************************************************************************/
void OTP_Unlock(void)
{
	gu32OTP_Key1 = OTP_KEY1;
	gu32OTP_Key2 = OTP_KEY2;
}

/******************************************************************************
* Function Name  : OTP_Lock
* Description    : ��д��������
* Input          : NONE
* Return         : NONE
******************************************************************************/
void OTP_Lock(void)
{
	gu32OTP_Key1 = ~OTP_KEY1;
	gu32OTP_Key2 = ~OTP_KEY2;
	OTP->PROT = OTP_KEY2;
}

/******************************************************************************
* Function Name  : OTP_IsWriteDone
* Description    : �ж�OTPд������Ƿ����
* Input          : NONE
* Return         : OTP_WrieDoneTypeDef:OTP_WriteDone/OTP_WriteNoDone
******************************************************************************/
OTP_WrieDoneTypeDef OTP_IsWriteDone(void)
{
    if ((OTP->CS & OTP_DONE_FLAG) == OTP_DONE_FLAG)
    {
        return OTP_WriteNoDone;
    }
    else
    {
        return OTP_WriteDone;
    }
}

/******************************************************************************
 * Function Name  : OTP_GetFlag
 * Description    : ��ȡ������ɺ��״̬��
 * Input          : NONE
 * Return         : OTP_StatusTypeDef:
                    OTP_Complete�˴β������쳣��
                    OTP_ReadOnProgramOrSleep�ڱ��/����״̬�¶�OTP���ж�����
                    OTP_ProgramIn_HiddenOrRO_Block������/ֻ��������б��
                    OTP_ProgramOutOfAddr��̵�ַ����OTP��Χ
                    OTP_ProgramOnSleep������״̬�½��б��
                    OTP_WakeUpOnNoSleep�ڷ�����״̬�½��л��Ѳ���
******************************************************************************/
OTP_StatusTypeDef OTP_GetFlag(void)
{
    uint32_t flag = 0;
    flag = (OTP->CS >> 1) & 0x7;
    
    switch(flag)
    {
        case OTP_Complete:
            return OTP_Complete;
        
        case OTP_ReadOnProgramOrSleep:
            return OTP_ReadOnProgramOrSleep;
        
        case OTP_ProgramIn_HiddenOrRO_Block:
            return OTP_ProgramIn_HiddenOrRO_Block;
        
        case OTP_ProgramOutOfAddr:
            return OTP_ProgramOutOfAddr;
        
        case OTP_ProgramOnSleep:
            return OTP_ProgramOnSleep;
        
        case OTP_WakeUpOnNoSleep:
            
            return OTP_WakeUpOnNoSleep;
    }
}

/******************************************************************************
 * Function Name  : OTP_ClearStatus
 * Description    : ���״̬�Ĵ�����ֵ
 * Input          : NONE
 * Return         : NONE
******************************************************************************/
void OTP_ClearStatus(void)
{
    OTP->CS &= ~(0x07 << 1);
}

/******************************************************************************
* Function Name  : WriteOtpWord
* Description    : OTP�����
* Input          : u32Addr����̵�ַ
                   u32Data��д�������
* Return         : OTP_StatusTypeDef
******************************************************************************/
OTP_StatusTypeDef OTP_WriteWord(uint32_t addr, uint32_t w)
{
    uint32_t Delay = 0;
    OTP_StatusTypeDef otp_status;
    
    assert_param(IS_OTP_ADDRESS(addr));
    assert_param(0 == (addr & 0x03));
    
    OTP->PDATA = w;
    OTP->ADDR = addr;
    
    OTP->PROT = gu32OTP_Key1;
    OTP->PROT = gu32OTP_Key2;
    
    OTP_Operate();
    
    Delay = 0xFFFF;
    while((OTP_IsWriteDone() == OTP_WriteNoDone) && (0 != --Delay));
    if(0 == Delay)
    {
        return OTP_TimeOut;
    }
    
    otp_status = OTP_GetFlag();
    if(OTP_Complete != otp_status)
    {
        OTP_ClearStatus();
        return otp_status;
    }
    
    while(OTP_ReadNotReady == OTP_IsReadReady());
    if((*(uint32_t *)addr) != w)
    {
        return OTP_DataWrong;
    }
    
    return OTP_Complete;
}

/******************************************************************************
* Function Name  : OTP_TimCmd
* Description    : �Ƿ�ʹ��otp_tim�Ĵ���
* Input          : FunctionalState 
* Return         : NONE
******************************************************************************/
void OTP_TimCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if(ENABLE == NewState)
    {
        OTP->TIM_EN = OTP_TIM_EN;
    }
    else
    {
        OTP->TIM_EN = ~OTP_TIM_EN;
    }
}

/******************************************************************************
 * Function Name  : OTP_HideBlock
 * Description    : ���ش����ַ���ڵĿ�
 * Input          : u32Addr��ַ
 * Return         : NONE
******************************************************************************/
void OTP_HideBlock(uint32_t u32Addr)
{
    uint32_t pu32Hide;

    assert_param(IS_OTP_ADDRESS(u32Addr));
    
    pu32Hide = (u32Addr - OTP_BASE) / 0x100;
    
    OTP->HIDE |= BIT(pu32Hide);
}

/******************************************************************************
 * Function Name  : OTP_ClearAllHiddenBlock
 * Description    : ȡ��������������
 * Input          : NONE
 * Return         : NONE
******************************************************************************/
void OTP_ClearAllHiddenBlock(void)
{
    SYSCTRL->SOFT_RST2 |= SYSCTRL_OTP_RESET;
}

/******************************************************************************
 * Function Name  : OTP_IsHide
 * Description    : �Ƿ����ش����ַ���ڵĿ�
 * Input          : u32Addr��ַ
 * Return         : OTP_HideTypeDef:OTP_Hidden/OTP_UnHidden
******************************************************************************/
OTP_HideTypeDef OTP_IsHide(uint32_t u32Addr)
{
    uint32_t pu32Hide;

    assert_param(IS_OTP_ADDRESS(u32Addr));
    
    pu32Hide = (u32Addr - OTP_BASE) / 0x100;
    
    if(BIT(pu32Hide) == (OTP->HIDE & BIT(pu32Hide)))
    {
        return OTP_Hidden;
    }
    else
    {
        return OTP_UnHidden;
    }
}

/******************************************************************************
* Function Name  : OTP_GetProtect
* Description    : ��ȡ����OTP���Ƿ�Ϊֻ��״̬
* Input          : NONE
* Return         : ����ֻ������״̬
******************************************************************************/
uint32_t OTP_GetProtect(void)
{
	return OTP->RO;
}

/******************************************************************************
* Function Name  : OTP_GetProtectLock
* Description    : ��ȡֻ�����Ķ�Ӧ��Ӳ������״̬
* Input          : NONE
* Return         : ��ȡֻ�����Ķ�Ӧ��Ӳ������״̬
******************************************************************************/
uint32_t OTP_GetProtectLock(void)
{
	return OTP->ROL;
}

/******************************************************************************
* Function Name  : OTP_SetProtect
* Description    : ���ö�ӦOTP��ַΪֻ��
* Input          : u32Addr
* Return         : NONE
******************************************************************************/
void OTP_SetProtect(uint32_t u32Addr)
{
    uint32_t pu32RO;
	assert_param(IS_OTP_ADDRESS(u32Addr));
    
    pu32RO = (u32Addr - OTP_BASE) / 0x100;
    
    OTP->RO |= BIT(pu32RO);
}

/******************************************************************************
* Function Name  : OTP_SetProtectLock
* Description    : ����OTP��ַ��Ӧ�Ĵ�����ֻ������Ӳ��������1������޷���0��
                   ��λ��Ӳ���Զ���0
* Input          : u32Addr
* Return         : NONE
******************************************************************************/
void OTP_SetProtectLock(uint32_t u32Addr)
{
	uint32_t pu32ROL;
	assert_param(IS_OTP_ADDRESS(u32Addr));
    
    OTP_SetProtect(u32Addr);
    pu32ROL = (u32Addr - OTP_BASE) / 0x100;
    
    OTP->ROL |= BIT(pu32ROL);
}

/******************************************************************************
* Function Name  : OTP_UnProtect
* Description    : ���ö�ӦOTP��ַΪ�ɲ�д
* Input          : u32Addr
* Return         : NONE
******************************************************************************/
void OTP_UnProtect(uint32_t u32Addr)
{
	uint32_t pu32RO;
	assert_param(IS_OTP_ADDRESS(u32Addr));
    
    pu32RO = (u32Addr - OTP_BASE) / 0x100;
    
    OTP->RO &= ~BIT(pu32RO);
}

/******************************************************************************
* Function Name  : OTP_IsReadReady
* Description    : �Ƿ���Զ�������OTP���ڱ��/����״̬ʱ���ɶ�
* Input          : void
* Return         : OTP_ReadReadyTypeDef:OTP_ReadReady/OTP_ReadNotReady
******************************************************************************/
OTP_ReadReadyTypeDef OTP_IsReadReady(void)
{
    if(BIT(31) == (OTP->CS & BIT(31)))
    {
        return OTP_ReadReady;
    }
    else
    {
        return OTP_ReadNotReady;
    }
}

/******************************************************************************
* Function Name  : OTP_IsProtect
* Description    : ��ȡ��Ӧ��ַ��ֻ�����Ƿ�Ϊ����״̬
* Input          : u32Addr
* Return         : OTP_LockTypeDef:OTP_Locked/OTP_UnLocked
******************************************************************************/
OTP_LockTypeDef OTP_IsProtect(uint32_t u32Addr)
{
	uint32_t pu32RO;
    
    assert_param(IS_OTP_ADDRESS(u32Addr));
	
    pu32RO = (u32Addr - OTP_BASE) / 0x100;
    
    if(BIT(pu32RO) == (OTP->RO & BIT(pu32RO)))
    {
        return OTP_Locked;
    }
    else
    {
        return OTP_UnLocked;
    }
}

/******************************************************************************
* Function Name  : OTP_IsProtectLock
* Description    : ��ȡ��Ӧ��ַ��ֻ������Ӳ�����Ƿ�Ϊ����״̬
* Input          : u32Addr
* Return         : OTP_LockTypeDef:OTP_Locked/OTP_UnLocked
******************************************************************************/
OTP_LockTypeDef OTP_IsProtectLock(uint32_t u32Addr)
{
	uint32_t pu32ROL;
    
    assert_param(IS_OTP_ADDRESS(u32Addr));
	
    pu32ROL = (u32Addr - OTP_BASE) / 0x100;
    
    if(BIT(pu32ROL) == (OTP->ROL & BIT(pu32ROL)))
    {
        return OTP_Locked;
    }
    else
    {
        return OTP_UnLocked;
    }
}


/******************************************************************************
* Function Name  : OTP_PowerOn
* Description    : ��OTP��Դ, �ϵ����Ҫ��2us�Ժ���ܶ�ȡOTP����
* Input          : 
* Return         : 
******************************************************************************/
void OTP_PowerOn(void)
{
	//����OTP��ʱ������, ʵ����ʱ��Ҫ�󳤺ܶ�
	uint32_t n = SYSCTRL->HCLK_1MS_VAL / 250;
	
	SYSCTRL->LDO25_CR &= ~BIT5;	//��OTP��Դ
	while (n--);
	SYSCTRL_AHBPeriphClockCmd(SYSCTRL_AHBPeriph_OTP, ENABLE);
}

/************************ (C) COPYRIGHT 2014 Megahuntmicro ****END OF FILE****/
