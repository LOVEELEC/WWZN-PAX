#ifndef _DCMI_OV7670_INITABLE_H
#define _DCMI_OV7670_INITABLE_H

typedef struct Reg
{
	unsigned char Address;			       /*寄存器地址*/
	unsigned short Value;		           /*寄存器值*/  //MT
}Reg_Info;
#define   W96X96		0
#define   W97X96		0
#define   W162X162		0
#define   W400BIN4		1
#define   W400BIN2		0
#define   W752X480		0

/* 寄存器参数配置 */

#define MT9V_REG_NUM  (sizeof(Sensor_Config)/sizeof(Sensor_Config[0]))	  //结构体数组成员数目
	
#define PIXEL_WIN_LEN      108  //Equal to 'PIXEL_MTRX_LEN' of 'image.h'!!!!
#define	SUBWIN							4   //Sub-windows-lenth = SUBWIN * 2 + 1
#define ORIG_WIN_LEN  			(PIXEL_WIN_LEN+SUBWIN*2)  //Note: DO NOT (PIXEL_MTRX_LEN+SUBWIN*2+1) !!

const Reg_Info Sensor_Config[] =
{
	{0x1B, 0x0003}, 
	#if W96X96
	{0x01, 0x00be}, 	// COL_WINDOW_START_CONTEXTA_REG         
 	{0x02, 0x00b8}, 	// ROW_WINDOW_START_CONTEXTA_REG 
	{0x03, ORIG_WIN_LEN}, 	// ROW_WINDOW_SIZE_CONTEXTA_REG          
 	{0x04, ORIG_WIN_LEN}, 	// COL_WINDOW_SIZE_CONTEXTA_REG   
	{0x05, 0x02eb}, 	//HORZ_BLANK_CONTEXTA_REG 
	{0x0D, 0x0300}, 	//READ_MODE_REG
	#endif
	#if W97X96
	{0x01, 0x0146}, 	// COL_WINDOW_START_CONTEXTA_REG         
 	{0x02, 0x00be}, 	// ROW_WINDOW_START_CONTEXTA_REG 
	{0x03, ORIG_WIN_LEN}, 	// ROW_WINDOW_SIZE_CONTEXTA_REG          
 	{0x04, ORIG_WIN_LEN+1}, 	// COL_WINDOW_SIZE_CONTEXTA_REG   
	{0x05, 0x02eb}, 	//HORZ_BLANK_CONTEXTA_REG 
	{0x0D, 0x0300}, 	//READ_MODE_REG
	#endif
	#if W162X162
	{0x01, 0x0146}, 	// COL_WINDOW_START_CONTEXTA_REG         
 	{0x02, 0x00be}, 	// ROW_WINDOW_START_CONTEXTA_REG  
	{0x03, 0x00A2}, 	// ROW_WINDOW_SIZE_CONTEXTA_REG          
 	{0x04, 0x00A2}, 	// COL_WINDOW_SIZE_CONTEXTA_REG   
	{0x05, 0x02A9}, 	//HORZ_BLANK_CONTEXTA_REG 
	{0x0D, 0x0300}, 	//READ_MODE_REG
	#endif
	#if W400BIN4
	{0x01, 0x0000}, 	// COL_WINDOW_START_CONTEXTA_REG         
 	{0x02, 0x0000}, 	// ROW_WINDOW_START_CONTEXTA_REG, 若原始图像大小为120*120,120*4=480,因此必须设成最小值4,否则会出黑边
 	{0x03, 108*4}, 	// ROW_WINDOW_SIZE_CONTEXTA_REG          
 	{0x04, 108*4}, 	// COL_WINDOW_SIZE_CONTEXTA_REG  
	{0x05, 0x03f4}, 	//HORZ_BLANK_CONTEXTA_REG 
	//{0x05, 0x03e7}, 	//HORZ_BLANK_CONTEXTA_REG 
	//{0x0D, 0x030a}, 	//READ_MODE_REG
	{0x0D, 0x031a}, 	//READ_MODE_REG, Row flip  针对首量3、4号镜头-单摄像头模组-的改变
	#endif
	#if W400BIN2
	{0x01, 0x00b0}, 	// COL_WINDOW_START_CONTEXTA_REG         
 	{0x02, 0x0028}, 	// ROW_WINDOW_START_CONTEXTA_REG  	
 	{0x03, ORIG_WIN_LEN*2}, 	// ROW_WINDOW_SIZE_CONTEXTA_REG          
 	{0x04, ORIG_WIN_LEN*2}, 	// COL_WINDOW_SIZE_CONTEXTA_REG  
	{0x05, 0x03e7}, 	//HORZ_BLANK_CONTEXTA_REG 
	{0x0D, 0x0305}, 	//READ_MODE_REG
	#endif
	#if W752X480
	{0x01, 0x0001}, 	// COL_WINDOW_START_CONTEXTA_REG         
 	{0x02, 0x0004}, 	// ROW_WINDOW_START_CONTEXTA_REG         
	{0x03, 0x01e0}, 	// ROW_WINDOW_SIZE_CONTEXTA_REG          
	{0x04, 0x02f0}, 	// COL_WINDOW_SIZE_CONTEXTA_REG 
	{0x05, 0x005e}, 	//HORZ_BLANK_CONTEXTA_REG 
	{0x0D, 0x0300}, 	//READ_MODE_REG
	#endif
//{0x06, 0x0039}, 	//VERT_BLANK_CONTEXTA_REG  
//	{0x06, 0x0060}, 	//VERT_BLANK_CONTEXTA_REG  图像79帧
	{0x06, 0x0078}, 	//VERT_BLANK_CONTEXTA_REG  图像70帧
//	{0x06, 0x00e0}, 	//VERT_BLANK_CONTEXTA_REG,图像48帧   

	{0x07, 0x0388}, 	//CONTROL_MODE_REG                           
	//{0x08, 0x0190}, 	//COARSE_SHUTTER_WIDTH_1_CONTEXTA            
	//{0x09, 0x01BD}, 	//COARSE_SHUTTER_WIDTH_2_CONTEXTA            
	//{0x0A, 0x0164}, 	//SHUTTER_WIDTH_CONTROL_CONTEXTA     
	{0x08, 0x000c}, 	//COARSE_SHUTTER_WIDTH_1_CONTEXTA, t1  end!!!   
	{0x09, 0x000c}, 	//COARSE_SHUTTER_WIDTH_2_CONTEXTA, t2  end!!!          
	{0x0A, 0x0064}, 	//SHUTTER_WIDTH_CONTROL_CONTEXTA     
	{0x0B, 0x000c}, 	//COARSE_SHUTTER_WIDTH_TOTAL_CONTEXTA        
	{0x0C, 0x0000}, 	//RESET_REG                                  
	//{0x0D, 0x0305}, 	//READ_MODE_REG , UP setup

	{0x0E, 0x0000}, 	//READ_MODE2_REG                             
	{0x0F, 0x0100}, 	//PIXEL_OPERATION_MODE                       
	{0x10, 0x0040}, 	//RAMP_START_DELAY                           
	{0x11, 0x8042}, 	//OFFSET_CONTROL                             
	{0x12, 0x0022}, 	//AMP_RESET_BAR_CONTROL                      
	{0x13, 0x2D2E}, 	//5T_PIXEL_RESET_CONTROL                     
	{0x14, 0x0E02}, 	//4T_PIXEL_RESET_CONTROL                     
	{0x15, 0x0E32}, 	//TX_CONTROL                                 
	{0x16, 0x2802}, 	//5T_PIXEL_SHS_CONTROL                       
	{0x17, 0x3E38}, 	//4T_PIXEL_SHS_CONTROL                       
	{0x18, 0x3E38}, 	//5T_PIXEL_SHR_CONTROL                       
	{0x19, 0x2802}, 	//4T_PIXEL_SHR_CONTROL                       
	{0x1A, 0x0428}, 	//COMPARATOR_RESET_CONTROL                   
	{0x1B, 0x0000}, 	//LED_OUT_CONTROL                            
	{0x1C, 0x0302}, 	//DATA_COMPRESSION                           
	{0x1D, 0x0040}, 	//ANALOG_TEST_CONTROL                        
	{0x1E, 0x0000}, 	//SRAM_TEST_DATA_ODD                         
	{0x1F, 0x0000}, 	//SRAM_TEST_DATA_EVEN                        
	{0x20, 0x03C7}, 	//BOOST_ROW_EN                               
	{0x21, 0x0020}, 	//I_VLN_CONTROL                              
	{0x22, 0x0020}, 	//I_VLN_AMP_CONTROL                          
	{0x23, 0x0010}, 	//I_VLN_CMP_CONTROL                          
	{0x24, 0x001B}, 	//I_OFFSET_CONTROL                           
	{0x25, 0x001A}, 	//I_BANDGAP_CONTROL                          
	{0x26, 0x0004}, 	//I_VLN_VREF_ADC_CONTROL                     
	{0x27, 0x000C}, 	//I_VLN_STEP_CONTROL                         
	{0x28, 0x0010}, 	//I_VLN_BUF_CONTROL                          
	{0x29, 0x0010}, 	//I_MASTER_CONTROL                           
	{0x2A, 0x0020}, 	//I_VLN_AMP_60MHZ_CONTROL                    
	{0x2B, 0x0003}, 	//VREF_AMP_CONTROL                           
	{0x2C, 0x0004}, 	//VREF_ADC_CONTROL                           
	{0x2D, 0x0004}, 	//VBOOST_CONTROL                             
	{0x2E, 0x0007}, 	//V_HI_CONTROL                               
	{0x2F, 0x0003}, 	//V_LO_CONTROL                               
	{0x30, 0x0003}, 	//V_AMP_CAS_CONTROL   

	//{0x31, 0x001F}, 	//V1_CONTROL_CONTEXTA                        
	//{0x32, 0x001A}, 	//V2_CONTROL_CONTEXTA                        
	//{0x33, 0x0012}, 	//V3_CONTROL_CONTEXTA      
	{0x31, 0x003F}, 	//V1_CONTROL_CONTEXTA       !!!                 
	{0x32, 0x0021}, 	//V2_CONTROL_CONTEXTA       !!!                 
	{0x33, 0x0006}, 	//V3_CONTROL_CONTEXTA 			!!!

	{0x34, 0x0003}, 	//V4_CONTROL_CONTEXTA                        
	//{0x35, 0x8010}, 	//GLOBAL_GAIN_CONTEXTA_REG      0.75 Anlog Gain !!!!!                     
	{0x35, 0x0040}, 	//GLOBAL_GAIN_CONTEXTA_REG                   
	{0x36, 0x0010}, 	//GLOBAL_GAIN_CONTEXTB_REG                   
	{0x37, 0x0000}, 	//VOLTAGE_CONTROL                            
	{0x38, 0x0000}, 	//IDAC_VOLTAGE_MONITOR                       
	{0x39, 0x0025}, 	//V1_CONTROL_CONTEXTB                        
	{0x3A, 0x0020}, 	//V2_CONTROL_CONTEXTB                        
	{0x3B, 0x0003}, 	//V3_CONTROL_CONTEXTB                        
	{0x3C, 0x0003}, 	//V4_CONTROL_CONTEXTB                        
	{0x46, 0x231D}, 	//DARK_AVG_THRESHOLDS                        
	{0x47, 0x0080}, 	//CALIB_CONTROL_REG (AUTO)                   
	{0x4C, 0x0002}, 	//STEP_SIZE_AVG_MODE                         
	//{0x70, 0x0000}, 	//ROW_NOISE_CONTROL 
	{0x70, 0x0000}, 	//ROW_NOISE_CONTROL 
	{0x71, 0x002a}, 	//NOISE_CONSTANT                             
	{0x72, 0x0012}, 	//PIXCLK_CONTROL                             
	{0x7F, 0x0000}, 	//TEST_DATA                                  
	{0x80, 0x04F4}, 	//TILE_X0_Y0                                 
	{0x81, 0x04F4}, 	//TILE_X1_Y0                                 
	{0x82, 0x04F4}, 	//TILE_X2_Y0                                 
	{0x83, 0x04F4}, 	//TILE_X3_Y0                                 
	{0x84, 0x04F4}, 	//TILE_X4_Y0                                 
	{0x85, 0x04F4}, 	//TILE_X0_Y1                                 
	{0x86, 0x04F4}, 	//TILE_X1_Y1                                 
	{0x87, 0x04F4}, 	//TILE_X2_Y1                                 
	{0x88, 0x04F4}, 	//TILE_X3_Y1                                 
	{0x89, 0x04F4}, 	//TILE_X4_Y1                                 
	{0x8A, 0x04F4}, 	//TILE_X0_Y2                                 
	{0x8B, 0x04F4}, 	//TILE_X1_Y2                                 
	{0x8C, 0x04F4}, 	//TILE_X2_Y2                                 
	{0x8D, 0x04F4}, 	//TILE_X3_Y2                                 
	{0x8E, 0x04F4}, 	//TILE_X4_Y2                                 
	{0x8F, 0x04F4}, 	//TILE_X0_Y3                                 
	{0x90, 0x04F4}, 	//TILE_X1_Y3                                 
	{0x91, 0x04F4}, 	//TILE_X2_Y3                                 
	{0x92, 0x04F4}, 	//TILE_X3_Y3                                 
	{0x93, 0x04F4}, 	//TILE_X4_Y3                                 
	{0x94, 0x04F4}, 	//TILE_X0_Y4                                 
	{0x95, 0x04F4}, 	//TILE_X1_Y4                                 
	{0x96, 0x04F4}, 	//TILE_X2_Y4                                 
	{0x97, 0x04F4}, 	//TILE_X3_Y4                                 
	{0x98, 0x04F4}, 	//TILE_X4_Y4    
	/****  BIN1  **********
	{0x99, 0x0000}, 	//X0_SLASH5                                  
	{0x9A, 0x0096}, 	//X1_SLASH5                                  
	{0x9B, 0x012C}, 	//X2_SLASH5                                  
	{0x9C, 0x01C2}, 	//X3_SLASH5                                  
	{0x9D, 0x0258}, 	//X4_SLASH5                                  
	{0x9E, 0x02F0}, 	//X5_SLASH5                                  
	{0x9F, 0x0000}, 	//Y0_SLASH5                                  
	{0xA0, 0x0060}, 	//Y1_SLASH5                                  
	{0xA1, 0x00C0}, 	//Y2_SLASH5                                  
	{0xA2, 0x0120}, 	//Y3_SLASH5                                  
	{0xA3, 0x0180}, 	//Y4_SLASH5                                  
	{0xA4, 0x01E0}, 	//Y5_SLASH5  
	*********BIN 1 END ****/
	/*-----BIN 4 --------------*/
	{0x99, 0x0000}, 	//X0_SLASH5                                  
	{0x9A, 0x004b}, 	//X1_SLASH5                                  
	{0x9B, 0x0096}, 	//X2_SLASH5                                  
	{0x9C, 0x00e1}, 	//X3_SLASH5                                  
	{0x9D, 0x012c}, 	//X4_SLASH5                                  
	{0x9E, 0x0178}, 	//X5_SLASH5                                  
	{0x9F, 0x0000}, 	//Y0_SLASH5                                  
	{0xA0, 0x0018}, 	//Y1_SLASH5                                  
	{0xA1, 0x0030}, 	//Y2_SLASH5                                  
	{0xA2, 0x0048}, 	//Y3_SLASH5                                  
	{0xA3, 0x0060}, 	//Y4_SLASH5                                  
	{0xA4, 0x0078}, 	//Y5_SLASH5     

	{0xA5, 0x003f}, 	//DESIRED_BIN                                
	//{0xA6, 0x0002}, 	//EXP_SKIP_FRM_H     
	{0xA6, 0x0000}, 	//EXP_SKIP_FRM_H     
	{0xA8, 0x0000}, 	//EXP_LPF                                    
	//{0xA9, 0x0002}, 	//GAIN_SKIP_FRM                              
	{0xA9, 0x0000}, 	//GAIN_SKIP_FRM                              
	{0xAA, 0x0002}, 	//GAIN_LPF_H                                 
	{0xAB, 0x0040}, 	//MAX_GAIN                                   
	{0xAC, 0x0001}, 	//MIN_COARSE_EXPOSURE                        
	{0xAD, 0x0006}, 	//MAX_COARSE_EXPOSURE                        
	{0xAE, 0x0014}, 	//BIN_DIFF_THRESHOLD                         
	//{0xAF, 0x0303}, 	//AUTO_BLOCK_CONTROL  
	{0xAF, 0x0000}, 	//AUTO_BLOCK_CONTROL
	{0xB0, 0xABE0}, 	//PIXEL_COUNT                                
	{0xB1, 0x0002}, 	//LVDS_MASTER_CONTROL                        
	{0xB2, 0x0010}, 	//LVDS_SHFT_CLK_CONTROL                      
	{0xB3, 0x0010}, 	//LVDS_DATA_CONTROL                          
	{0xB4, 0x0000}, 	//LVDS_DATA_STREAM_LATENCY                   
	{0xB5, 0x0000}, 	//LVDS_INTERNAL_SYNC                         
	{0xB6, 0x0000}, 	//LVDS_USE_10BIT_PIXELS                      
	{0xB7, 0x0000}, 	//STEREO_ERROR_CONTROL                       
	{0xBF, 0x0016}, 	//INTERLACE_FIELD_VBLANK                     
	{0xC0, 0x000A}, 	//IMAGE_CAPTURE_NUM                          
	//{0xC2, 0x18D0}, 	//ANALOG_CONTROLS   
	{0xC2, 0x0840}, 	//ANALOG_CONTROLS   
	{0xC3, 0x007F}, 	//AB_PULSE_WIDTH_REG                         
	{0xC4, 0x007F}, 	//TX_PULLUP_PULSE_WIDTH_REG                  
	{0xC5, 0x007F}, 	//RST_PULLUP_PULSE_WIDTH_REG                 
	{0xC6, 0x0000}, 	//NTSC_FV_CONTROL                            
	{0xC7, 0x4416}, 	//NTSC_HBLANK                                
	{0xC8, 0x4421}, 	//NTSC_VBLANK                                
	{0xC9, 0x0002}, 	//COL_WINDOW_START_CONTEXTB_REG              
	{0xCA, 0x0004}, 	//ROW_WINDOW_START_CONTEXTB_REG              
	{0xCB, 0x01E0}, 	//ROW_WINDOW_SIZE_CONTEXTB_REG               
	{0xCC, 0x02EE}, 	//COL_WINDOW_SIZE_CONTEXTB_REG               
	{0xCD, 0x0100}, 	//HORZ_BLANK_CONTEXTB_REG                    
	{0xCE, 0x0100}, 	//VERT_BLANK_CONTEXTB_REG                    
	{0xCF, 0x0190}, 	//COARSE_SHUTTER_WIDTH_1_CONTEXTB            
	{0xD0, 0x01BD}, 	//COARSE_SHUTTER_WIDTH_2_CONTEXTB            
	{0xD1, 0x0064}, 	//SHUTTER_WIDTH_CONTROL_CONTEXTB             
	{0xD2, 0x01C2}, 	//COARSE_SHUTTER_WIDTH_TOTAL_CONTEXTB        
	{0xD3, 0x0000}, 	//FINE_SHUTTER_WIDTH_1_CONTEXTA              
	{0xD4, 0x0000}, 	//FINE_SHUTTER_WIDTH_2_CONTEXTA              
	{0xD5, 0x0000}, 	//FINE_SHUTTER_WIDTH_TOTAL_CONTEXTA          
	{0xD6, 0x0000}, 	//FINE_SHUTTER_WIDTH_1_CONTEXTB              
	{0xD7, 0x0000}, 	//FINE_SHUTTER_WIDTH_2_CONTEXTB              
	{0xD8, 0x0000}, 	//FINE_SHUTTER_WIDTH_TOTAL_CONTEXTB          
	{0xD9, 0x0000}, 	//MONITOR_MODE_CONTROL              

};


#define CHANGE_REG_NUM 168

const unsigned char change_reg[CHANGE_REG_NUM][2]=
{
    {0x3a, 0x0c},
        {0x40, 0xd0},
        {0x12, 0x14},
  //      {0x32, 0x80},
  //      {0x17, 0x16},
  //      {0x18, 0x04},
  //      {0x19, 0x02},//ó°?ì
  //      {0x1a, 0x7a},//0x7a,
  //      {0x03, 0x03},//ó°?ì
				{0x32, 0x80},
				{0x17, 0x64},
        {0x18, 0x64+ORIG_WIN_LEN},
        {0x19, 0x64},
        {0x1a, 0x64+ORIG_WIN_LEN},
        {0x03, 0x00},

        {0x3e, 0x00},//
        {0x70, 0x00},
        {0x71, 0x00},
        {0x72, 0x11},
        {0x73, 0x00},//
        {0xa2, 0x02},
        {0x11, 0x01},
        {0x7a, 0x20},
        {0x7b, 0x1c},
        {0x7c, 0x28},
        {0x7d, 0x3c},
        {0x7e, 0x55},
        {0x7f, 0x68},
        {0x80, 0x76},
        {0x81, 0x80},
        {0x82, 0x88},
        {0x83, 0x8f},
        {0x84, 0x96},
        {0x85, 0xa3},
        {0x86, 0xaf},
        {0x87, 0xc4},
        {0x88, 0xd7},
        {0x89, 0xe8},
        {0x13, 0xe7},
        {0x00, 0x00},//AGC
        {0x10, 0x00},
        {0x0d, 0x00},
        {0x14, 0x20},//0x38, limit the max gain
        {0xa5, 0x05},
        {0xab, 0x07},
        {0x24, 0x75},
        {0x25, 0x63},
        {0x26, 0xA5},
        {0x9f, 0x78},
        {0xa0, 0x68},
        {0xa1, 0x03},
        {0xa6, 0xdf},
        {0xa7, 0xdf},
        {0xa8, 0xf0},
        {0xa9, 0x90},
        {0xaa, 0x94},
        {0x13, 0xe7},
        {0x0e, 0x61},
        {0x0f, 0xcb},
        {0x16, 0x02},
        {0x1e, 0x17},
        {0x21, 0x02},
        {0x22, 0x91},
        {0x29, 0x07},
        {0x33, 0x0b},
        {0x35, 0x0b},
        {0x37, 0x1d},
        {0x38, 0x71},
        {0x39, 0x2a},//
        {0x3c, 0x78},
        {0x4d, 0x40},
        {0x4e, 0x20},
        {0x69, 0x0c},
        {0x6b, 0x00},//PLL
        {0x74, 0x19},
        {0x8d, 0x4f},
        {0x8e, 0x00},
        {0x8f, 0x00},
        {0x90, 0x00},
        {0x91, 0x00},
        {0x92, 0x00},
        {0x96, 0x00},
        {0x9a, 0x80},
        {0xb0, 0x84},
        {0xb1, 0x0c},
        {0xb2, 0x0e},
        {0xb3, 0x82},
        {0xb8, 0x0a},
        {0x43, 0x14},
        {0x44, 0xf0},
        {0x45, 0x34},
        {0x46, 0x58},
        {0x47, 0x28},
        {0x48, 0x3a},
        {0x59, 0x88},
        {0x5a, 0x88},
        {0x5b, 0x44},
        {0x5c, 0x67},
        {0x5d, 0x49},
        {0x5e, 0x0e},
        {0x64, 0x04},
        {0x65, 0x20},
        {0x66, 0x05},
        {0x94, 0x04},
        {0x95, 0x08},
        {0x6c, 0x0a},
        {0x6d, 0x55},
        {0x6e, 0x11},
        {0x6f, 0x9f},//0x9e for advance AWB
        {0x6a, 0x40},
        {0x01, 0x40},
        {0x02, 0x40},
        {0x13, 0xe7},
        {0x15, 0x08},
        {0x4f, 0x80},
        {0x50, 0x80},
        {0x51, 0x00},
        {0x52, 0x22},
        {0x53, 0x5e},
        {0x54, 0x80},
        {0x58, 0x9e},        
        {0x41, 0x08},
        {0x3f, 0x00},
        {0x75, 0x05},
        {0x76, 0xe1},
        {0x4c, 0x00},
        {0x77, 0x01},
        {0x3d, 0xc0},
        {0x4b, 0x09},
        {0xc9, 0x60},
        {0x41, 0x38},
        {0x56, 0x40},        
        {0x34, 0x11},
        {0x3b, 0x02},
        {0xa4, 0x89},
        {0x96, 0x00},
        {0x97, 0x30},
        {0x98, 0x20},
        {0x99, 0x30},
        {0x9a, 0x84},
        {0x9b, 0x29},
        {0x9c, 0x03},
        {0x9d, 0x4c},
        {0x9e, 0x3f},
        {0x78, 0x04},        
        {0x79, 0x01},
        {0xc8, 0xf0},
        {0x79, 0x0f},
        {0xc8, 0x00},
        {0x79, 0x10},
        {0xc8, 0x7e},
        {0x79, 0x0a},
        {0xc8, 0x80},
        {0x79, 0x0b},
        {0xc8, 0x01},
        {0x79, 0x0c},
        {0xc8, 0x0f},
        {0x79, 0x0d},
        {0xc8, 0x20},
        {0x79, 0x09},
        {0xc8, 0x80},
        {0x79, 0x02},
        {0xc8, 0xc0},
        {0x79, 0x03},
        {0xc8, 0x40},
        {0x79, 0x05},
        {0xc8, 0x30},
        {0x79, 0x26},
        {0x09, 0x03},
        {0x55, 0x00},
        {0x56, 0x40},        
        {0x3b, 0x42},
        {0x07, 0x08},
        {0x10, 0x80},
};

#endif
