/************************ (C) COPYRIGHT Megahuntmicro *************************
 * File Name            : dwc_mipi_csi.c
 * Author               : Megahuntmicro
 * Version              : V1.0.0
 * Date                 : 04/24/2017
 * Description          : configure csi-2 host 
 *****************************************************************************/
 #include  "Mhscpu.h"
 #include  "stdint.h"
 #include "dwc_mipi_csi.h"
 #include "systick.h"
 //#include "spi.h"
static void dwc_mipi_csi_write(uint16_t address,uint32_t data)
{
 	/*spi write*/	
 	//spi_write(address,data);
	*((uint32_t *)(CSI2_BASE+address)) = data;
}


static uint32_t dwc_mipi_csi_read(uint16_t address)
{
	uint32_t data;
 	/*spi read*/
	//data=spi_read(address);
	
	data = *((uint32_t *)(address + CSI2_BASE));
 	return data;
}
 
static uint32_t dwc_mipi_csi_write_part(uint16_t address,uint32_t data,uint8_t shift,uint8_t width)
{
  	uint32_t mask = (1<<width)-1;
	uint32_t temp = dwc_mipi_csi_read(address);
	temp &=~(mask << shift);
	temp |= (data & mask)<<shift;
	dwc_mipi_csi_write(address,temp);
}

static void dwc_csi_host_reset(void)
{
	dwc_mipi_csi_write(CSI2_RESETN,0);
}

static void dwc_csi_host_release_reset(void)
{
	dwc_mipi_csi_write(CSI2_RESETN,0x1);
}

static void dwc_csi_phy_reset(void)
{
	dwc_mipi_csi_write(PHY_SHUTDOWNZ,0);
	dwc_mipi_csi_write(DPHY_RSTZ,0);
}

static void dwc_cis_phy_release_reset(void)
{
	dwc_mipi_csi_write(PHY_SHUTDOWNZ,0x1);
	dwc_mipi_csi_write(DPHY_RSTZ,0x1);
}

static void dwc_cis_host_set_err_mask(void)
{
#if 1
	dwc_mipi_csi_write(INT_MSK_PHY_FATAL,0xffffffff);
	dwc_mipi_csi_write(INT_MSK_PKT_FATAL,0xffffffff);
	dwc_mipi_csi_write(INT_MSK_FRAME_FATAL,0xffffffff);
	dwc_mipi_csi_write(INT_MSK_PHY,0xffffffff);
	dwc_mipi_csi_write(INT_MSK_PKT,0xffffffff);
	dwc_mipi_csi_write(INT_MSK_LINE,0xffffffff);
	dwc_mipi_csi_write(MSK_INT_IPI,0xffffffff);
#else
	dwc_mipi_csi_write(INT_MSK_PHY_FATAL,0x0);
	dwc_mipi_csi_write(INT_MSK_PKT_FATAL,0x0);
	dwc_mipi_csi_write(INT_MSK_FRAME_FATAL,0x0);
	dwc_mipi_csi_write(INT_MSK_PHY,0x0);
	dwc_mipi_csi_write(INT_MSK_PKT,0x0);
	dwc_mipi_csi_write(INT_MSK_LINE,0x0);
	dwc_mipi_csi_write(MSK_INT_IPI,0x0);
#endif
}

static void dwc_csi_host_set_vcid_and_dt(uint32_t ipi_vcid,uint32_t ipi_data_type)
{
	dwc_mipi_csi_write(IPI_VCID,ipi_vcid);
	dwc_mipi_csi_write(IPI_DATA_TYPE,ipi_data_type);
}

static void dwc_csi_host_set_horizontal_info(uint32_t ipi_hsa_time,uint32_t ipi_hbp_time,uint32_t ipi_hsd_time,uint32_t ipi_hline_time)
{
	dwc_mipi_csi_write(IPI_HSA_TIME,ipi_hsa_time);
	dwc_mipi_csi_write(IPI_HBP_TIME,ipi_hbp_time);
	dwc_mipi_csi_write(IPI_HSD_TIME,ipi_hsd_time);
	dwc_mipi_csi_write(IPI_HLINE_TIME,ipi_hline_time);
}

static void dwc_csi_host_set_vertical_info(uint32_t ipi_vsa_lines,uint32_t ipi_vbp_lines,uint32_t ipi_vfp_lines,uint32_t ipi_vactive_lines)
{
	
	dwc_mipi_csi_write(IPI_VSA_LINES,ipi_vsa_lines);
	dwc_mipi_csi_write(IPI_VBP_LINES,ipi_vbp_lines);
	dwc_mipi_csi_write(IPI_VFP_LINES,ipi_vfp_lines);
	dwc_mipi_csi_write(IPI_VACTIVE_LINES,ipi_vactive_lines);
}

void dwc_csi_mask_irq_power_off(void)
{
	dwc_mipi_csi_write(N_LANES,0);
	dwc_mipi_csi_write(INT_MSK_PHY_FATAL,0x0);
	dwc_mipi_csi_write(INT_MSK_PKT_FATAL,0x0);
	dwc_mipi_csi_write(INT_MSK_FRAME_FATAL,0x0);
	dwc_mipi_csi_write(INT_MSK_PHY,0x0);
	dwc_mipi_csi_write(INT_MSK_PKT,0x0);
	dwc_mipi_csi_write(INT_MSK_LINE,0x0);
	dwc_mipi_csi_write(MSK_INT_IPI,0x0);
	dwc_mipi_csi_write(CSI2_RESETN,0x0);
}

void dwc_mipi_csi_irq_status(viod)
{
	uint32_t int_status,i_sts;
	int_status=dwc_mipi_csi_read(INT_ST_MAIN);
	if(int_status & CSI2_INT_PHY_FATAL)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PHY_FATAL);
		//debug_printf("INT_ST_PHY_FATAL%x\n",i_sts);
	}
	if(int_status & CSI2_INT_PKT_FATAL)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PKT_FATAL);
		//debug_printf("INT_ST_PKT_FATAL%x\n",i_sts);
	}
	if(int_status & CSI2_INT_FRAME_FATAL)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_FRAME_FATAL);
		//debug_printf("INT_ST_FRAME_FATAL%x\n",i_sts);
	}
	if(int_status & CSI2_INT_PHY)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PHY);
		//debug_printf("INT_ST_PHY%x\n",i_sts);
	}
	if(int_status & CSI2_INT_PKT)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PKT);
		//debug_printf("INT_ST_PKT%x\n",i_sts);
	}
	if(int_status & CSI2_INT_LINE)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_LINE);
		//debug_printf("INT_ST_LINE%x\n",i_sts);
	}
	if(int_status & CSI2_INT_IPI)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_IPI);
		//debug_printf("INT_ST_IPI%x\n",i_sts);
	}
}

   //1903封装后的中断为 INT41:csi2_intp
void dw_csi_irq(void)
{
	#if 1 
	uint32_t global_int_status,i_sts;
	global_int_status =  dwc_mipi_csi_read(INT_ST_MAIN);
	if(global_int_status&CSI2_INT_PHY_FATAL)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PHY_FATAL);
//		printf("CSI INT INT_ST_PHY_FATAL:%08x\r\n",i_sts);
	}
	if(global_int_status&CSI2_INT_PKT_FATAL)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PKT_FATAL);
//		printf("CSI INT INT_ST_PKT_FATAL:%08x\r\n",i_sts);
	}
	if(global_int_status&CSI2_INT_FRAME_FATAL)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_FRAME_FATAL);
//		printf("CSI INT INT_ST_FRAME_FATAL:%08x\r\n",i_sts);
	}
	if(global_int_status&CSI2_INT_PHY)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PHY);
//		printf("CSI INT INT_ST_PHY:%08x\r\n",i_sts);
	}
	if(global_int_status&CSI2_INT_PKT)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_PKT);
//		printf("CSI INT INT_ST_PKT:%08x\r\n",i_sts);
	}
	if(global_int_status&CSI2_INT_LINE)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_LINE);
//		printf("CSI INT INT_ST_LINE:%08x\r\n",i_sts);
	}
	if(global_int_status&CSI2_INT_IPI)
	{
		i_sts = dwc_mipi_csi_read(INT_ST_IPI);
//		printf("CSI INT INT_ST_IPI:%08x\r\n",i_sts);
	}
	#endif 
	
}


void dwc_csi_check_clk_lane_status(void)
{
	uint32_t data=0;
	data=dwc_mipi_csi_read(PHY_STOPSTATE);
	if(data&(1<<16))
	{
		printf("clock lane is detected in stop state \r\n");
	}else
	{
		printf("clock lane is detected in normal state \r\n");
	}
}

void dwc_csi_check_data_lane_status(void)
{
	uint32_t data=0,i;
	data=dwc_mipi_csi_read(PHY_STOPSTATE);
	for(i=0;i<7;i++)
	{
		if(data&(1<<i))
		{
			printf("data lane%d is detected in stop state \r\n",i);
		}else
		{
			printf("data lane%d is detected in normal state \r\n",i);
		}
	}
	
}

void dwc_csi_check_clk_lane_in_HS_mode(void)
{
	uint32_t data=0;
	data=dwc_mipi_csi_read(PHY_RX);
	if(data&(1<<17))
	{
		printf("high-speed clock signal \r\n");
	}else
	{
		printf("not high-speed clock signal \r\n");
	}
}

void dwc_csi_check_ULPM(void)
{
	uint32_t data=0,i;
	data=dwc_mipi_csi_read(PHY_RX);
	if(data&(1<<16))
	{
		printf("clk lane is detected in not ULPM\r\n");
	}else
	{
		printf("clk lane is detected in ULPM\r\n");
	}
	for(i=0;i<7;i++)
	{
		if(data&(1<<i))
		{
			printf("data lane%d is detected in ULPM\r\n",i);
		}else
		{
			printf("data lane%d is detected in not ULPM  \r\n",i);
		}
	}
	
}

void dwc_csi_check_status(void)
{
	dwc_csi_check_clk_lane_status();
	dwc_csi_check_data_lane_status();
	dwc_csi_check_clk_lane_in_HS_mode();
	dwc_csi_check_ULPM();
	
	//dw_csi_irq(); //检查是否有中断
}

void Write_test_code_configuration(uint8_t address, uint8_t content)
{
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL1,(1<<16)|address);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x2);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x0);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL1,content);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x2);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x0);
	mdelay(2);
}
uint8_t Read_test_code_configuration(uint8_t address)
{
	uint32_t data;
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL1,(1<<16)|address);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x2);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x0);
	mdelay(2);
	//dwc_mipi_csi_write(PHY_TEST_CTRL1,content);
	data=dwc_mipi_csi_read(PHY_TEST_CTRL1);
	mdelay(2);
	dwc_mipi_csi_write(PHY_TEST_CTRL1,0x0);
	mdelay(2);
	
	return ((data&0xff00)>>8);
}

 /******************************************************************************
* Function Name  : dwc_csi_host_init
* Description    : init mipi csi-2 host controller
* Return         : NONE
******************************************************************************/
void dwc_csi_host_init(void)
{
	uint32_t ipi_timing_mode,ipi_color_mode;
	uint32_t ipi_hsa_time, ipi_hbp_time, ipi_hsd_time, ipi_hline_time;
	uint32_t ipi_vsa_lines,ipi_vbp_lines,ipi_vfp_lines,ipi_vactive_lines;
	uint32_t num_lanes;
	uint32_t ipi_vcid, ipi_data_type;
	uint32_t data=0,i;
	uint8_t test_data;

	/* 
		program refer to DesignWare Cores MIPI CSI-2 Host Controller User Guide P51
		register set DWC_mipi_csi2_host_databook.pdf 	P107
	*/
	/*databook P120,user guide P61*/
	ipi_timing_mode=CSI2_CAMERA_TIMING_MODE;
	ipi_color_mode=CSI2_COLOR_MODE_16BIT;
	
#ifdef GC0310MIPI
	ipi_hsa_time=0;
	ipi_hbp_time=0;
	ipi_hsd_time=0;
	ipi_hline_time=640;
    
	ipi_vsa_lines=0;
	ipi_vbp_lines=0;
	ipi_vfp_lines=0;
	ipi_vactive_lines=480;
#else
	/*user guide P61*/
	ipi_hsa_time=1350;      /* databook P122 */
	ipi_hbp_time=0;         /* databook P123 */
	ipi_hsd_time=0;         /* databook P123 */
	ipi_hline_time=1600;    /* databook P123 */
	
	ipi_vsa_lines=30;       /* databook P124 */
	ipi_vbp_lines=0;        /* databook P124 */
	ipi_vfp_lines=0;        /* databook P124 */
	ipi_vactive_lines=1200; /* databook P124 */
#endif
	num_lanes = 1;/*databook P108*/
	ipi_vcid = 0;/*databook P120*/
	//ipi_data_type = CSI2_HOST_DT_YUV422_8;
	ipi_data_type = CSI2_HOST_DT_RAW10;/*databook P120*/
	/*user guide P52,P53*/
	dwc_csi_phy_reset();
	dwc_csi_host_reset();
	mdelay(1000);
	//dwc_mipi_csi_write(PHY_TEST_CTRL1,0x0);  //?phy_testclr 高脉冲上升沿复位
	//mdelay(10);
	//dwc_mipi_csi_write(PHY_TEST_CTRL0,0x1);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x0);
	mdelay(100);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x1);  //?phy_testclr 高脉冲上升沿复位
	mdelay(100);
	dwc_mipi_csi_write(PHY_TEST_CTRL0,0x0);
	dwc_cis_phy_release_reset();
	dwc_csi_host_release_reset();
	Write_test_code_configuration(0x34,14);
	mdelay(100);
	Write_test_code_configuration(0x44,14);
	mdelay(100);
	Write_test_code_configuration(0x54,14);
	mdelay(100);
    
    /*  以下设置clk lane,data0 lane,data1 lane等频率范围   */
    Write_test_code_configuration(0x44,2<<1);
	mdelay(1000);
	Write_test_code_configuration(0x34,2<<1);
    mdelay(1000);
	Write_test_code_configuration(0x54,2<<1);
	mdelay(1000);
    
	/*configure lanes User Guide P53*/
	dwc_mipi_csi_write(N_LANES,num_lanes-1);   //使用的1个数据lane
	
	dwc_cis_host_set_err_mask(); //屏蔽所有中断，后面查询中断状态

	/*optional auto flush databook 121*/
	//dwc_mipi_csi_write_part(IPI_MEM_FLUSH ,1,8,1);

	/*optional configure data id values*/
	//dwc_mipi_csi_write(DATA_IDS_1,((ipi_data_type)|(ipi_data_type<<8)));

	/*config Config VC and DT  IPI*/
	dwc_csi_host_set_vcid_and_dt(ipi_vcid, ipi_data_type);  //根据摄像头配置vcid,data_type及数据输出格式

	/*Config IPI color mode  CSI2_COLOR_MODE_48BIT or CSI2_COLOR_MODE_16BIT */
	dwc_mipi_csi_write_part(IPI_MODE,ipi_color_mode,8,1);   //ipi输出接口选择
	
	/*config ipi mode timing CSI2_CAMERA_TIMING_MODE or CSI2_CONTROLLER_TIMING_MODE*/
	dwc_mipi_csi_write_part(IPI_MODE,ipi_timing_mode,0,1);  //ipi时序选择，camera跟随模式

	/*Config IPI Horizontal frame info*/ //配置ipi行场信息
	dwc_csi_host_set_horizontal_info(ipi_hsa_time,ipi_hbp_time,ipi_hsd_time,ipi_hline_time);

	if(ipi_timing_mode == CSI2_CONTROLLER_TIMING_MODE)
	{
		/*Config IPI Vertical frame info, 时序由控制产生时需要 */
		dwc_csi_host_set_vertical_info(ipi_vsa_lines,ipi_vbp_lines,ipi_vfp_lines,ipi_vactive_lines);
	}
	data = dwc_mipi_csi_read(VERSION);
	printf("mipi version 0x%x\r\n",data);	
}
