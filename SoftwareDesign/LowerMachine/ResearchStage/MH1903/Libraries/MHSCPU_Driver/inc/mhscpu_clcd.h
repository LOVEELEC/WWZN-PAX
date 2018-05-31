/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : mhscpu_clcd.h
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                : 21-October-2014
 * @brief               : This file contains all the functions prototypes for the CLCD firmware library
 *****************************************************************************/
 
#ifndef MHSMCU_CLCD
#define MHSMCU_CLCD

#ifdef __cplusplus
extern "C"
{
#endif

#include "mhscpu.h"

//#define CLCD_printf	printf
#define CLCD_printf	

/* The number of bits used for each colour */
#define CLCD_PALETTE_GUN_WIDTH   (5)

/* The number of bits we need to create to fill the byte colour values */
#define CLCD_PALETTE_PAD_BITS    (8 - CLCD_PALETTE_GUN_WIDTH)
#define CLCD_PALETTE_ENTRY_SIZE  (16)

#define CLCD_MBERRORMIS	(1<<4)
#define CLCD_VCOMPMIS		(1<<3)
#define CLCD_LNBUMIS		(1<<2)
#define CLCD_FUFMIS			(1<<1)

typedef enum CLCD_xType
{
    CLCD_STN = 0, // Selects an Super Twisted Nematic display
    CLCD_TFT = 1  // Selects a Thin Film Transistor display
} CLCD_eType;

typedef enum CLCD_xColorOrder 
{
    CLCD_RGB   = 0,     // Pixels are in R/G/B format
    CLCD_BGR   = 1      // Pixels are in B/G/R format
} CLCD_eColorOrder;

typedef enum CLCD_xReload 
{
    CLCD_RELOAD_EARLY = 0,    // Load more data when FIFO has 4 slots
    CLCD_RELOAD_LATE  = 1     // Load more data when FIFO has 8 slots
} CLCD_eReload;

typedef enum CLCD_xClockSource 
{
    CLCD_INTERNAL_CLOCK   = 0,  // Clock is HCLCK
    CLCD_EXTERNAL_CLOCK   = 1   // Clock is external source
} CLCD_eClockSource;

typedef enum CLCD_xVSync_Active 
{
    CLCD_LCDFP_H = 0,   // LcdFP pin is active high, inactive low
    CLCD_LCDFP_L = 1    // LcdFP pin is active low, inactive high
} CLCD_eVSync_Active;

typedef enum CLCD_xHSync_Active 
{
    CLCD_LCDLP_H = 0,    // LcdLP pin is active high, inactive low
    CLCD_LCDLP_L = 1     // LcdLP pin is active low, inactive high
} CLCD_eHSync_Active;


typedef enum CLCD_xDataDrive 
{
    CLCD_CLCP_R = 0,  // Data driven on rising edge of CLCP
    CLCD_CLCP_F = 1   // Data driven on falling edge of CLCP
} CLCD_eDataDrive;

 typedef enum CLCD_xOEnable 
{
    CLCD_CLAC_H = 0,  // CLAC pin is active high in TFT mode
    CLCD_CLAC_L = 1   // CLAC pin is active low in TFT mode
} CLCD_eOEnable;

typedef enum CLCD_xSTN_CType 
{
    CLCD_STN_COLOR = 0,   // STN LCD is color
    CLCD_STN_MONO  = 1    // STN LCD is monochrome
} CLCD_eSTN_CType;

typedef enum CLCD_xSTN_Iface 
{
    CLCD_STN_4BIT = 0,    // 4 bit parallel interface
    CLCD_STN_8BIT = 1     // 8 bit parallel interface
} CLCD_eSTN_Iface;
 

typedef enum CLCD_xSTN_Panel 
{
    CLCD_STN_SINGLE = 0,  // Selects a single panel STN LCD
    CLCD_STN_DUAL   = 1   // Selects a dual panel STN LCD
} CLCD_eSTN_Panel;

typedef enum CLCD_xVComp_ITime 
{
    CLCD_VSYNC    = 0,            // Start of VSync
    CLCD_BACK_P   = 1,            // Start of Back Porch
    CLCD_ACTIVE_V = 2,            // Start of Active Video
    CLCD_FRONT_P  = 3             // Start of Front Porch
} CLCD_eVComp_ITime;

typedef enum CLCD_xPixelOrder 
{
    CLCD_LITTLE_ENDIAN_BYTES = 0,     // Leftmost pixel is at bit 0
    CLCD_BIG_ENDIAN_BYTES    = 1      // Leftmost pixel is at bit 7
} CLCD_ePixelOrder;

typedef enum CLCD_xBpp 
{
    CLCD_1BPP  = 0,
    CLCD_2BPP  = 1,
    CLCD_4BPP  = 2,
    CLCD_8BPP  = 3,
    CLCD_16BPP = 4,
    CLCD_24BPP = 5,
    CLCD_16BPP_565_MODE = 6,  //For internal use only for PL111
    CLCD_16BPP_444_MODE = 7   //For internal use only for PL111
} CLCD_eBpp;

typedef enum CLCD_xPixelMode 
{
    CLCD_NORMAL_MODE  = 0,
    CLCD_565_MODE     = 1,
    CLCD_444_MODE     = 2
} CLCD_ePixelMode;

typedef enum CLCD_xInterrupts 
{
    CLCD_NO_INTERRUPTS = (uint32_t)0,      // Mask with all interrupts clear
    CLCD_FUF           = (uint32_t)0x2,    // FIFO underflow
    CLCD_NEXT_BASE_UP  = (uint32_t)0x4,    // DMA base address update
    CLCD_VCOMP         = (uint32_t)0x8,    // Vertical compare
    CLCD_MBERR         = (uint32_t)0x10,   // AHB Master error
    CLCD_CURSOR        = (uint32_t)0x20,   // Callback for cursor interrupt
    CLCD_ALL_INTERRUPTS= (uint32_t)0x1E    // Mask with all interrupts set
} CLCD_eInterrupts;

typedef enum CLCD_xError
{
    CLCD_PALETTE_TOO_BIG = 1,
    CLCD_INCORRECT_WIDTH,         // Conflicting LCD setting. Display
                                    // width must be a multiple of 16 pixels
    CLCD_NO_SETTING,              // Required configuration value missing
    CLCD_INVALID_DISPLAY_TYPE,    // Display options incompatible or wrong
    CLCD_NO_AC_BIAS,              // STN displays must have AC bias
    CLCD_INVALID_BPP,             // Bits Per Pixel cannot be achieved, greater than
                                    // 24 for STN, or greater than 16 for TFT display
    CLCD_VCOMP_TIMEOUT            // Vcomp was not set during time-out period                                
                                    
} CLCD_eError;

typedef void (*CLCD_Function_Delay) (uint32_t ms);

typedef struct 
{
                     /*** These should not be needed after initialisation  ***/
    CLCD_eType         eType;        /* LCD display type                   */
    CLCD_eColorOrder   eColorOrder;  /* RGB or BGR                         */
    CLCD_eReload       eReload;      /* FIFO reload timing                 */
    CLCD_eClockSource  eClockSource; /* LCD clock source                   */
    uint32_t              ACBias;       /* number of line clock periods       */
                                       /* between each toggle of AC-bias pin */
    CLCD_eVSync_Active eVSyncActive; /* LcdFP pin active state             */
    CLCD_eHSync_Active eHSyncActive; /* LcdLP pin active state             */
    CLCD_eDataDrive    eDataDrive;   /* edge data driven on                */
    CLCD_eOEnable      eTftClac;     /* CLAC pin setting in TFT mode       */
    uint32_t              ClleDelay;    /* Delay before line end pulse...     */
                                       /* ...(0 to disable)                  */

                    /**** These are needed if the refresh rate is changed ****/
    CLCD_eSTN_CType    eColorType;   /* STN LCD color type                 */
    CLCD_eSTN_Iface    eInterface;   /* STN LCD x-bit interface            */
    CLCD_eSTN_Panel    ePanel;       /* STN LCD single or double panel     */
    uint32_t              Clock;        /* LCD controller clock in Hz         */
    uint32_t              VSync;        /* vertical sync pulse width          */
    uint32_t              VFront;       /* vertical front porch               */
    uint32_t              VBack;        /* vertical back porch                */
    uint32_t              HSync;        /* horizontal sync pulse width        */
    uint32_t              HFront;       /* horizontal front porch             */
    uint32_t              HBack;        /* horizontal back porch              */

/*** These may change after initialisation if the configuration is altered ***/
    uint32_t              Refresh;      /* LCD screen refresh rate in Hz      */
/*** This is needed because the driver must check the type of Vertical       */
/*   Compare interrupt requested by the user.                                */
/*** It is held internally in the driver ***/
    CLCD_eVComp_ITime  eVCInterTime; /* Vertical Compare interrupt timing  */

/*** These six are needed by drawing functions to address DMA memory       ***/
/*** LineWidth and NumLines are also needed if the refresh rate is changed ***/
/*** They are held internally in the driver    ***/
    uint32_t              DMABase;      /* Base address of screen memory      */
    uint32_t              LineWidth;    /* line length, multiple of 16 pixels */
    uint32_t              NumLines;     /* total height of the screen         */
    CLCD_ePixelOrder   ePixelOrder;  /* pixel ordering within a byte       */
    CLCD_eBpp          eBpp;     /* bits per pixel. This might change...   */
                 /* ...after initialisation if the configuration is altered  */
    CLCD_ePixelMode    ePixelMode;    /* Special mode for pixel format      */
/*** Power switching parameters specific to the LCD panel  ***/
    uint32_t              PowerUpDelay;    /* Delay between LcdEn & LcdPwr on    */
    uint32_t              PowerDownDelay;  /* Delay between LcdPwr & LcdEn off   */	
   CLCD_Function_Delay delay;
} CLCD_DisplayParams;

typedef  struct 
{                               
	volatile uint32_t status;
	volatile uint32_t count;
}CLCD_Status;

typedef  struct 
{                               
	CLCD_DisplayParams Params;
	uint32_t Palette[128];       /* 128 word-wide palette entries           0x200 */
	CLCD_Status clcd_status;
}CLCD_InitTypeDef;

#define BIT_BUILD(x,y)	(((y)&(((uint32_t)1<<(x##_bw))-1))<<(x##_bs))
#define BIT_SET(z,x,y)	((z)=((z)&(~((((uint32_t)1<<(x##_bw))-1)<<(x##_bs))))|BIT_BUILD(x,y))
#define BIT_MASK(x)	((((uint32_t)1<<(x##_bw))-1)<<(x##_bs))
#define BIT_CLEAR(x,y)	((x)&=((~((((uint32_t)1<<(y##_bw))-1)<<(y##_bs)))))
#define BIT_GET(x,y)		((x)&(BIT_MASK(y)))


/*********** Timing 0 register bitfields ****************/
/* Pixels per line */
#define CLCD_TIMING0_PPL_bw    6
#define CLCD_TIMING0_PPL_bs    2
#define CLCD_TIMING0_PPL_bm    BIT_MASK(CLCD_TIMING0_PPL)

/* Horiz. sync pulse width */
#define CLCD_TIMING0_HSW_bw    8
#define CLCD_TIMING0_HSW_bs    8
#define CLCD_TIMING0_HSW_bm    BIT_MASK(CLCD_TIMING0_HSW)

/* Horiz. front porch */
#define CLCD_TIMING0_HFP_bw    8
#define CLCD_TIMING0_HFP_bs    16
#define CLCD_TIMING0_HFP_bm    BIT_MASK(CLCD_TIMING0_HFP)

/* Horiz. back porch */
#define CLCD_TIMING0_HBP_bw    8
#define CLCD_TIMING0_HBP_bs    24
#define CLCD_TIMING0_HBP_bm    BIT_MASK(CLCD_TIMING0_HBP)

/*********** Timing 1 register bitfields ****************/
/* Lines per screen */
#define CLCD_TIMING1_LPP_bw    10
#define CLCD_TIMING1_LPP_bs    0
#define CLCD_TIMING1_LPP_bm    BIT_MASK(CLCD_TIMING1_LPP)

/* Vertical sync pulse width */
#define CLCD_TIMING1_VSW_bw    6
#define CLCD_TIMING1_VSW_bs    10
#define CLCD_TIMING1_VSW_bm    BIT_MASK(CLCD_TIMING1_VSW)

/* Vertical front porch */
#define CLCD_TIMING1_VFP_bw    8
#define CLCD_TIMING1_VFP_bs    16
#define CLCD_TIMING1_VFP_bm    BIT_MASK(CLCD_TIMING1_VFP)

/* Vertical back porch */
#define CLCD_TIMING1_VBP_bw    8
#define CLCD_TIMING1_VBP_bs    24
#define CLCD_TIMING1_VBP_bm    BIT_MASK(CLCD_TIMING1_VBP)

/*********** Timing 2 register bitfields ****************/
/* Panel clock divisor ls 5 bits*/
#define CLCD_TIMING2_PCD_LO_bw    5
#define CLCD_TIMING2_PCD_LO_bs    0
#define CLCD_TIMING2_PCD_LO_bm    BIT_MASK(CLCD_TIMING2_PCD_LO)

/* Clock selector */
#define CLCD_TIMING2_CLKSEL_bw 1
#define CLCD_TIMING2_CLKSEL_bs 5
#define CLCD_TIMING2_CLKSEL_bm BIT_MASK(CLCD_TIMING2_CLKSEL)

/* AC bias pin frequency */
#define CLCD_TIMING2_ACB_bw    5
#define CLCD_TIMING2_ACB_bs    6
#define CLCD_TIMING2_ACB_bm    BIT_MASK(CLCD_TIMING2_ACB)

/* Invert Vsync */
#define CLCD_TIMING2_IVS_bw    1
#define CLCD_TIMING2_IVS_bs    11
#define CLCD_TIMING2_IVS_bm    BIT_MASK(CLCD_TIMING2_IVS)

/* Interc Hsync */
#define CLCD_TIMING2_IHS_bw    1
#define CLCD_TIMING2_IHS_bs    12
#define CLCD_TIMING2_IHS_bm    BIT_MASK(CLCD_TIMING2_IHS)

/* Invert Panel Clock */
#define CLCD_TIMING2_IPC_bw    1
#define CLCD_TIMING2_IPC_bs    13
#define CLCD_TIMING2_IPC_bm    BIT_MASK(CLCD_TIMING2_IPC)

/* Invert Output Enable */
#define CLCD_TIMING2_IEO_bw    1
#define CLCD_TIMING2_IEO_bs    14
#define CLCD_TIMING2_IEO_bm    BIT_MASK(CLCD_TIMING2_IEO)

/* Clocks per line */
#define CLCD_TIMING2_CPL_bw    10
#define CLCD_TIMING2_CPL_bs    16
#define CLCD_TIMING2_CPL_bm    BIT_MASK(CLCD_TIMING2_CPL)

/* Bypass panel clock divider */
#define CLCD_TIMING2_BCD_bw    1
#define CLCD_TIMING2_BCD_bs    26
#define CLCD_TIMING2_BCD_bm    BIT_MASK(CLCD_TIMING2_BCD)

/* Panel clock divisor ms 5 bits*/
#define CLCD_TIMING2_PCD_HI_bw    5
#define CLCD_TIMING2_PCD_HI_bs    27
#define CLCD_TIMING2_PCD_HI_bm    BIT_MASK(CLCD_TIMING2_PCD_HI)

/*********** Timing 3 register bitfields ****************/
/* Frame end delay */
#define CLCD_TIMING3_LED_bw    7
#define CLCD_TIMING3_LED_bs    0
#define CLCD_TIMING3_LED_bm    BIT_MASK(CLCD_TIMING3_LED)

/* Frame end enable */
#define CLCD_TIMING3_LEE_bw    1
#define CLCD_TIMING3_LEE_bs    16
#define CLCD_TIMING3_LEE_bm    BIT_MASK(CLCD_TIMING3_LEE)

/*********** Status/Mask/Interrupt Register bitfields *************/
/* FIFO underflow */
#define CLCD_STATUS_FUF_bw     1
#define CLCD_STATUS_FUF_bs     1
#define CLCD_STATUS_FUF_bm     BIT_MASK(CLCD_STATUS_FUF)

/* Next base update */
#define CLCD_STATUS_LNBU_bw    1
#define CLCD_STATUS_LNBU_bs    2
#define CLCD_STATUS_LNBU_bm    BIT_MASK(CLCD_STATUS_LNBU)

/* Vertical compare */
#define CLCD_STATUS_VCOMP_bw   1
#define CLCD_STATUS_VCOMP_bs   3
#define CLCD_STATUS_VCOMP_bm   BIT_MASK(CLCD_STATUS_VCOMP)

/* Master bus error */
#define CLCD_STATUS_MBERROR_bw 1
#define CLCD_STATUS_MBERROR_bs 4
#define CLCD_STATUS_MBERROR_bm BIT_MASK(CLCD_STATUS_MBERROR)

/**************** Control register bitfields ***************/
/* Enable CLCD controller */
#define CLCD_CONTROL_LCDEN_bw        1
#define CLCD_CONTROL_LCDEN_bs        0
#define CLCD_CONTROL_LCDEN_bm        BIT_MASK(CLCD_CONTROL_LCDEN)

/* Bits per pixel */
#define CLCD_CONTROL_LCDBPP_bw       3
#define CLCD_CONTROL_LCDBPP_bs       1
#define CLCD_CONTROL_LCDBPP_bm       BIT_MASK(CLCD_CONTROL_LCDBPP)

/* STN LCD is monochrome */
#define CLCD_CONTROL_LCDBW_bw        1
#define CLCD_CONTROL_LCDBW_bs        4
#define CLCD_CONTROL_LCDBW_bm        BIT_MASK(CLCD_CONTROL_LCDBW)

/* LCD is TFT */
#define CLCD_CONTROL_LCDTFT_bw       1
#define CLCD_CONTROL_LCDTFT_bs       5
#define CLCD_CONTROL_LCDTFT_bm      BIT_MASK(CLCD_CONTROL_LCDTFT)

/* 4 or 8 bit interface for mono LCD */
#define CLCD_CONTROL_LCDMONO8_bw     1
#define CLCD_CONTROL_LCDMONO8_bs    6
#define CLCD_CONTROL_LCDMONO8_bm     BIT_MASK(CLCD_CONTROL_LCDMONO8)

/* Dual panel mode */
#define CLCD_CONTROL_LCDDUAL_bw      1
#define CLCD_CONTROL_LCDDUAL_bs      7
#define CLCD_CONTROL_LCDDUAL_bm      BIT_MASK(CLCD_CONTROL_LCDDUAL)

/* Swap red and blue */
#define CLCD_CONTROL_BGR_bw          1
#define CLCD_CONTROL_BGR_bs          8
#define CLCD_CONTROL_BGR_bm          BIT_MASK(CLCD_CONTROL_BGR)

/* Little/bigendian byte order */
#define CLCD_CONTROL_BEBO_bw         1
#define CLCD_CONTROL_BEBO_bs         9
#define CLCD_CONTROL_BEBO_bm         BIT_MASK(CLCD_CONTROL_BEBO)

/* Pixel order within byte*/
#define CLCD_CONTROL_BEPO_bw         1
#define CLCD_CONTROL_BEPO_bs         10
#define CLCD_CONTROL_BEPO_bm         BIT_MASK(CLCD_CONTROL_BEPO)

/* Power enable */
#define CLCD_CONTROL_LCDPWR_bw       1
#define CLCD_CONTROL_LCDPWR_bs       11
#define CLCD_CONTROL_LCDPWR_bm       BIT_MASK(CLCD_CONTROL_LCDPWR)

/* Interrupt generation */
#define CLCD_CONTROL_LCDVCOMP_bw     2
#define CLCD_CONTROL_LCDVCOMP_bs     12
#define CLCD_CONTROL_LCDVCOMP_bm     BIT_MASK(CLCD_CONTROL_LCDVCOMP)

/* DMA FIFO test access */
#define CLCD_CONTROL_LDMAFIFOTME_bw  1
#define CLCD_CONTROL_LDMAFIFOTME_bs  15
#define CLCD_CONTROL_LDMAFIFOTME_bm  BIT_MASK(CLCD_CONTROL_LDMAFIFOTME)

/* FIFO reload watermark */
#define CLCD_CONTROL_WATERMARK_bw    1
#define CLCD_CONTROL_WATERMARK_bs    16
#define CLCD_CONTROL_WATERMARK_bm    BIT_MASK(CLCD_CONTROL_WATERMARK)

/*********** Address register bitfields *****************/
/* This defines the valid bits in the 4 DMA base address registers */
#define CLCD_ADDRESS_bw    30
#define CLCD_ADDRESS_bs    2
#define CLCD_ADDRESS_bm    BIT_MASK(CLCD_ADDRESS)

/************* Palette register bitfields ****************/
/* Red */
#define CLCD_PALETTE_R_bw  5
#define CLCD_PALETTE_R_bs  0
#define CLCD_PALETTE_R_bm  BIT_MASK(CLCD_PALETTE_R)

/* Green */
#define CLCD_PALETTE_G_bw  5
#define CLCD_PALETTE_G_bs  5
#define CLCD_PALETTE_G_bm  BIT_MASK(CLCD_PALETTE_G)

/* Blue */
#define CLCD_PALETTE_B_bw  5
#define CLCD_PALETTE_B_bs  10
#define CLCD_PALETTE_B_bm  BIT_MASK(CLCD_PALETTE_B)

/* Intensity */
#define CLCD_PALETTE_I_bw  1
#define CLCD_PALETTE_I_bs  15
#define CLCD_PALETTE_I_bm  BIT_MASK(CLCD_PALETTE_I)

/*********** Hardware Cursor register bitfields *****************/

/*********** Cursor Control register bitfields *****************/
#define CLCD_CURSOR_CONTROL_ON_bs        0
#define CLCD_CURSOR_CONTROL_ON_bw        1
#define CLCD_CURSOR_CONTROL_IMAGE_bs     4
#define CLCD_CURSOR_CONTROL_IMAGE_bw     2

/*********** Cursor Configuration register bitfields *****************/
#define CLCD_CURSOR_CONFIG_SIZE_bs     0
#define CLCD_CURSOR_CONFIG_SIZE_bw     1
#define CLCD_CURSOR_CONFIG_SYNC_bs     1
#define CLCD_CURSOR_CONFIG_SYNC_bw     1

/************* Cursor Palette register bitfields ****************/
/* Red */
#define CLCD_CURSOR_PALETTE_R_bs  0
#define CLCD_CURSOR_PALETTE_R_bw  8
#define CLCD_CURSOR_PALETTE_R_bm  BIT_MASK(CLCD_CURSOR_PALETTE_R)

/* Green */
#define CLCD_CURSOR_PALETTE_G_bs  8
#define CLCD_CURSOR_PALETTE_G_bw  8
#define CLCD_CURSOR_PALETTE_G_bm  BIT_MASK(CLCD_CURSOR_PALETTE_G)

/* Blue */
#define CLCD_CURSOR_PALETTE_B_bs  16
#define CLCD_CURSOR_PALETTE_B_bw  8
#define CLCD_CURSOR_PALETTE_B_bm  BIT_MASK(CLCD_CURSOR_PALETTE_B)

/*********** Cursor XY position register bitfields *****************/
#define CLCD_CURSOR_POSITION_X_bs     0
#define CLCD_CURSOR_POSITION_X_bw     12
#define CLCD_CURSOR_POSITION_Y_bs     16
#define CLCD_CURSOR_POSITION_Y_bw     12

/*********** Cursor clip position register bitfields *****************/
#define CLCD_CURSOR_CLIP_X_bs     0
#define CLCD_CURSOR_CLIP_X_bw     6
#define CLCD_CURSOR_CLIP_Y_bs     8
#define CLCD_CURSOR_CLIP_Y_bw     6

/****** Cursor Interrupt Mask Set and Clear Register bitfields *******/
#define CLCD_CURSOR_INTERRUPT_bs     0
#define CLCD_CURSOR_INTERRUPT_bw     1

uint32_t CLCD_Init(CLCD_TypeDef *ClCD, CLCD_InitTypeDef *CLCD_InitStruct);
void CLCD_InterruptEventsEnable(CLCD_TypeDef *ClCD, uint32_t Interrupts);
void CLCD_InterruptEventsDisable(CLCD_TypeDef *ClCD, uint32_t Interrupts);
void  CLCD_PowerUp(CLCD_TypeDef *ClCD, CLCD_DisplayParams *  pParams);
void CLCD_PowerDown(CLCD_TypeDef *ClCD, CLCD_DisplayParams *  pParams);
void CLCD_VCompEventsEnable(CLCD_TypeDef *ClCD,CLCD_eVComp_ITime eVCompEvent);
uint32_t CLCD_BppSet(CLCD_TypeDef *ClCD, CLCD_DisplayParams * pState,uint32_t Bpp);
void CLCD_DrawCLS(CLCD_TypeDef *ClCD, CLCD_DisplayParams * pState,uint32_t c);
void CLCD_PaletteInitialise(CLCD_TypeDef *ClCD, uint32_t *Palette);
void CLCD_ColorOrderSet(CLCD_TypeDef * ClCD,CLCD_DisplayParams *  pParams);
void CLCD_DMAFrameBufferSet(CLCD_TypeDef *ClCD, CLCD_DisplayParams *  pParams);
uint32_t CLCD_BytesPer_Panel(CLCD_DisplayParams *  pParams);
uint32_t CLCD_RefreshSet(CLCD_TypeDef *  pBase,CLCD_DisplayParams *  pParams,uint32_t Refresh);

#ifdef __cplusplus
}
#endif

#endif


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
