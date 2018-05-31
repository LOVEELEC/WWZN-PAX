/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : timeOut.c
 * Author               : MEGAHUNT Application Team
 * Version              : V1.0.0
 * Date                 : 05-September-2016
 * Description          : time out interface function.
 *****************************************************************************/
/* Include ------------------------------------------------------------------*/
#include "timeOut.h"
#include "string.h"
/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/	
/* Private macro ------------------------------------------------------------*/	
/* Private variables --------------------------------------------------------*/	
static TimeOutParameterDef timeOutParameter;
/* Ptivate function prototypes ----------------------------------------------*/	
static void TimeOut_Init(void);
static void TimeOut_TickTimer(void);
static void Stop_timeOut_tick(TIMETYPE timeOutType);
static void Set_timeOut_tick(tick time, TIMETYPE timeOutType);
static uint8_t is_timeout(void);
static bool GetTypeTimeOutSign(TIMETYPE timeOutType);
static bool TimeOut_IsTypeActive(TIMETYPE timeOutType);
static tick get_tick(void);
static tick get_diff_tick(tick cur_tick, tick prior_tick);


iTimeOut_Struct iTimeOut = {
	TimeOut_Init,
	TimeOut_TickTimer,
	Stop_timeOut_tick,
	Set_timeOut_tick,
	is_timeout,
	GetTypeTimeOutSign,
	TimeOut_IsTypeActive
};
piTimeOut_Struct piTimeOut = &iTimeOut;
/******************************************************************************
* Function Name  : TimeOut_Init
* Description    : ³õÊ¼»¯³¬Ê±¹¦ÄÜ²ÎÊý
* Input          : NONE
* Output         : NONE
* Return         : NONE
******************************************************************************/
#define USE_SOFTWARE_WATCHDOG
static void TimeOut_Init(void)
{
	
	/* Setup SysTick Timer for 10 msec interrupts.
	 ------------------------------------------
	1. The SysTick_Config() function is a CMSIS function which configure:
	   - The SysTick Reload register with value passed as function parameter.
	   - Configure the SysTick IRQ priority to the lowest value (0x0F).
	   - Reset the SysTick Counter register.
	   - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
	   - Enable the SysTick Interrupt.
	   - Start the SysTick Counter.

	2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
	   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
	   SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
	   inside the misc.c file.

	3. You can change the SysTick IRQ priority by calling the
	   NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
	   call. The NVIC_SetPriority() is defined inside the core_cm3.h file.

	4. To adjust the SysTick time base, use the following formula:
							
		 Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)

	   - Reload Value is the parameter to be passed for SysTick_Config() function
	   - Reload Value should not exceed 0xFFFFFF
	*/
	SYSCTRL_ClocksTypeDef RCC_Clocks;
	memset(&timeOutParameter, 0x00, sizeof(timeOutParameter));
	SYSCTRL_GetClocksFreq(&RCC_Clocks);
	if (SysTick_Config(RCC_Clocks.CPU_Frequency / 100))
	{ 
		/* Capture error */ 
		while (1);
	}
    #ifdef USE_SOFTWARE_WATCHDOG
	SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;         /* Enable SysTick IRQ and SysTick Timer */
    #else
    SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;        /* Disable SysTick IRQ and SysTick Timer */
    #endif
}

/******************************************************************************
* Function Name  : TimeOut_TickTimer
* Description    : Ê±¼ä¼ÆÊýÆ÷
* Input          : NONE
* Output         : NONE
* Return         : NONE
******************************************************************************/
static void TimeOut_TickTimer(void)
{
	if (0xFFFFFFFF == timeOutParameter.Systick_current_time)
	{
		timeOutParameter.Systick_current_time = 0;
	}else{	
		timeOutParameter.Systick_current_time++;
	}
}
/*****************************************************************************
 * Name		: Set_timeOut_tick
 * Function	: Set time out time interval.
 * ---------------------------------------------------------------------------
* Input Parameters:time:time interval
 * Output Parameters:None
 * Return Value:
 * ---------------------------------------------------------------------------
 * Description:
 * 
 *****************************************************************************/
static void Stop_timeOut_tick(TIMETYPE timeOutType)
{
    #ifndef USE_SOFTWARE_WATCHDOG
    SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;         /* Disable SysTick IRQ and SysTick Timer */
    #endif
	timeOutParameter.Systick_start_time[timeOutType] = 0;
	timeOutParameter.Systick_time_out_interval[timeOutType] = 0;
	timeOutParameter.timeOuttype &= ~(1 << timeOutType);
}
/*****************************************************************************
 * Name		: Set_timeOut_tick
 * Function	: Set time out time interval.
 * ---------------------------------------------------------------------------
* Input Parameters:time:time interval
 * Output Parameters:None
 * Return Value:
 * ---------------------------------------------------------------------------
 * Description:
 * 
 *****************************************************************************/
static void Set_timeOut_tick(tick time, TIMETYPE timeOutType)
{
	timeOutParameter.Systick_start_time[timeOutType] = get_tick();
	timeOutParameter.Systick_time_out_interval[timeOutType] = time;
	timeOutParameter.timeOuttype |= 1 << timeOutType;
    #ifndef USE_SOFTWARE_WATCHDOG
	SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;         /* Enable SysTick IRQ and SysTick Timer */
    #endif
}

static bool TimeOut_IsTypeActive(TIMETYPE timeOutType)
{
	if (timeOutParameter.timeOuttype & (1 << timeOutType))
	{
		return (true);
	}
	return (false);
}
/*****************************************************************************
 * Name		: get_tick
 * Function	: Get current tick.
 * ---------------------------------------------------------------------------
 * Input Parameters:None
 * Output Parameters:None
 * Return Value:
 * ---------------------------------------------------------------------------
 * Description:
 * 
 *****************************************************************************/
static tick get_tick(void)
{
	return (timeOutParameter.Systick_current_time);
}


/*****************************************************************************
 * Name		: GetTypeTimeOutSign
 * Function	: ¼ì²âÄ³ÖÖÀàÐÍµÄ³¬Ê±ÊÇ·ñ´¥·¢
 * ---------------------------------------------------------------------------
 * Input Parameters:None
 * Output Parameters: NONE
 * Return Value: true£º³¬Ê±£»false£ºÎ´³¬Ê±
 * ---------------------------------------------------------------------------
 * Description:
 * 
 *****************************************************************************/
static bool GetTypeTimeOutSign(TIMETYPE timeOutType)
{
	if (timeOutParameter.timeOuttype & (1 << timeOutType))
	{
		if (get_diff_tick(get_tick(), timeOutParameter.Systick_start_time[timeOutType]) >= \
									timeOutParameter.Systick_time_out_interval[timeOutType])
		{
			return (true);
		}
	}
	return (false);
}

/*****************************************************************************
 * Name		: get_diff_tick
 * Function	: Get the time interval (unit is 1ms) for two tick.
 * ---------------------------------------------------------------------------
 * Input Parameters:
 *			cur_tick		lastest tick
 *			prior_tick		prior tick
 * Output Parameters:None
 * Return Value:
 *			Return the ticks of two tick difference.
 * ---------------------------------------------------------------------------
 * Description:
 * 
 *****************************************************************************/
static tick get_diff_tick(tick cur_tick, tick prior_tick)
{
	if (cur_tick < prior_tick){
		return (cur_tick + (~prior_tick));
	}
	else{
		return (cur_tick - prior_tick);
	}
}

/*****************************************************************************
 * Name		: is_timeout
 * Function	: Determine whether the timeout that millisecond.
 * ---------------------------------------------------------------------------
 * Input Parameters:
 *			start_time	start time
 *			interval		time interval
 * Output Parameters:None
 * Return Value:
 *			TRUE		timeout
 *			FALSE		It is not timeout
 * ---------------------------------------------------------------------------
 * Description:
 * 	
 *****************************************************************************/
static uint8_t is_timeout(void)
{
	if (timeOutParameter.timeOuttype)
	{
		uint8_t i = 0;
		uint8_t timeOutSign = 0x00;
		for (i = 0; i < MAX_TIMEOUT_CNT; i++)
		{
			if (timeOutParameter.timeOuttype & (1 << i))
			{
				if (get_diff_tick(get_tick(), timeOutParameter.Systick_start_time[i]) >= \
											timeOutParameter.Systick_time_out_interval[i])
				{
					timeOutSign |= 1 << i;
				}
			}
		}
		return (timeOutSign);
	}else{
        #ifndef USE_SOFTWARE_WATCHDOG
        SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;         /* Disable SysTick IRQ and SysTick Timer */
        #endif
		return (0);
	}
}
/****************** (C) COPYRIGHT MEGAHUNT EmbeddedTeam ******END OF FILE*****/
