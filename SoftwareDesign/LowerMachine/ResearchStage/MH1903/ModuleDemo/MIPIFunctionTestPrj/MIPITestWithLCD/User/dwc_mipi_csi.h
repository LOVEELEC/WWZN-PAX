#ifndef DWC_MIPI_CSI_H_
#define DWC_MIPI_CSI_H_
/* register address begin(32-bits) */
#define VERSION                 0x0         // 只读寄存器，包含以32位ASCII码编码的DWC_mipi_csi2_host版本
#define N_LANES                 0x4         // 静态读写寄存器(配置DWC_mipi_csi2_host用来接收摄像机的活动通道数)
#define CSI2_RESETN             0x8         // 静态读写寄存器(控制DWC_mipi_csi2_host逻辑复位状态。激活时，控制器的内部逻辑进入复位状态。该寄存器不会
                                            // 将配置复位为默认值，而只会影响内部控制器逻辑)
#define INT_ST_MAIN             0xc         // 包含各个中断源的状态，不管相关的中断屏蔽寄存器的内容如何，所以可以通过轮询服务中断状态寄存器。读取INT_ST_MAIN寄存器清除中断引脚
#define DATA_IDS_1              0x10        // 
#define DATA_IDS_2              0x14
#define PHY_SHUTDOWNZ           0x40
#define DPHY_RSTZ               0x44
#define PHY_RX                  0x48
#define PHY_STOPSTATE           0x4c
#define PHY_TEST_CTRL0          0x50
#define PHY_TEST_CTRL1          0x54
#define PHY2_TEST_CTRL0         0x58
#define PHY2_TEST_CTRL1         0x5c
#define IPI_MODE                0x80
#define IPI_VCID                0x84
#define IPI_DATA_TYPE           0x88
#define IPI_MEM_FLUSH           0x8c
#define IPI_HSA_TIME            0x90        // 该寄存器配置视频水平同步主动(HSA)时间，该字段以pixclk周期配置水平同步主动周期。
#define IPI_HBP_TIME            0x94        // 该寄存器配置视频水平后沿(HBP)时间，此字段以pixclk周期配置水平后沿周期。
#define IPI_HSD_TIME            0x98        // 该寄存器配置视频书评同步延迟(HSD)时间，此字段以pixclk周期配置水平同步门限延迟时间段；
#define IPI_HLINE_TIME          0x9c        // 该寄存器配置每个视频行的总时间，此字段配置以pixclk周期计算的行时间的大小；
#define IPI_VSA_LINES           0xb0        // 该寄存器配置垂直同步活动(VSA)周期，此字段配置以水平行数测量的垂直同步活动时段；
#define IPI_VBP_LINES           0xb4        // 该寄存器配置垂直后沿(VBP)周期，此字段配置以水平线数量的垂直后沿周期
#define IPI_VFP_LINES           0xb8        // 该寄存器配置垂直前沿(VFP)周期,此字段配置垂直前沿期间测量的水平线的数量；
#define IPI_VACTIVE_LINES       0xbc        // 该寄存器配置视频的垂直分辨率，此字段配置以水平线数测量的垂直有效期；

#define INT_ST_PHY_FATAL        0xe0
#define INT_MSK_PHY_FATAL       0xe4
#define INT_FORCE_PHY_FATAL     0xe8

#define INT_ST_PKT_FATAL        0xf0
#define INT_MSK_PKT_FATAL       0xf4
#define INT_FORCE_PKT_FATAL     0xf8

#define INT_ST_FRAME_FATAL      0x100
#define INT_MSK_FRAME_FATAL     0x104
#define INT_FORCE_FRAME_FATAL   0x108

#define INT_ST_PHY              0x110
#define INT_MSK_PHY             0x114
#define INT_FORCE_PHY           0x118

#define INT_ST_PKT              0x120
#define INT_MSK_PKT             0x124
#define INT_FORCE_PKT           0x128

#define INT_ST_LINE             0x130
#define INT_MSK_LINE            0x134
#define INT_FORCE_LINE          0x138

#define INT_ST_IPI              0x140
#define MSK_INT_IPI             0x144
#define FORCE_INT_IPI           0x148
/*register address end*/


// Data Types begin P75
// 0x00 to 0x07      Short    Synchronization Short Packet Data Types
  #define CSI2_HOST_DT_FS         0x00
  #define CSI2_HOST_DT_FE         0x01
  #define CSI2_HOST_DT_LS         0x02
  #define CSI2_HOST_DT_LE         0x03
  #define CSI2_HOST_DT_RSRV1      0x04
  #define CSI2_HOST_DT_RSRV2      0x05
  #define CSI2_HOST_DT_RSRV3      0x06
  #define CSI2_HOST_DT_RSRV4      0x07

// 0x08 to 0x0F      Short    Generic Short Packet Data Types
  #define CSI2_HOST_DT_G_SP1      0x08
  #define CSI2_HOST_DT_G_SP2      0x09
  #define CSI2_HOST_DT_G_SP3      0x0A
  #define CSI2_HOST_DT_G_SP4      0x0B
  #define CSI2_HOST_DT_G_SP5      0x0C
  #define CSI2_HOST_DT_G_SP6      0x0D
  #define CSI2_HOST_DT_G_SP7      0x0E
  #define CSI2_HOST_DT_G_SP8      0x0F

// 0x10 to 0x17      Long     Generic Long Packet Data Types
  #define CSI2_HOST_DT_NULL       0x10
  #define CSI2_HOST_DT_BLANK      0x11
  #define CSI2_HOST_DT_EMBED      0x12
  #define CSI2_HOST_DT_RSRV5      0x13
  #define CSI2_HOST_DT_RSRV6      0x14
  #define CSI2_HOST_DT_RSRV7      0x15
  #define CSI2_HOST_DT_RSRV8      0x16
  #define CSI2_HOST_DT_RSRV9      0x17

// 0x18 to 0x1F      Long     YUV Data
  #define CSI2_HOST_DT_YUV420_8   0x18
  #define CSI2_HOST_DT_YUV420_10  0x19
  #define CSI2_HOST_DT_YUV420_8L  0x1A
  #define CSI2_HOST_DT_RSRV10     0x1B
  #define CSI2_HOST_DT_YUV420_8C  0x1C
  #define CSI2_HOST_DT_YUV420_10C 0x1D
  #define CSI2_HOST_DT_YUV422_8   0x1E
  #define CSI2_HOST_DT_YUV422_10  0x1F

// 0x20 to 0x27      Long     RGB Data
  #define CSI2_HOST_DT_RGB444     0x20
  #define CSI2_HOST_DT_RGB555     0x21
  #define CSI2_HOST_DT_RGB565     0x22
  #define CSI2_HOST_DT_RGB666     0x23
  #define CSI2_HOST_DT_RGB888     0x24
  #define CSI2_HOST_DT_RSRV11     0x25
  #define CSI2_HOST_DT_RSRV12     0x26
  #define CSI2_HOST_DT_RSRV13     0x27

// 0x28 to 0x2F      Long     RAW Data
  #define CSI2_HOST_DT_RAW6       0x28
  #define CSI2_HOST_DT_RAW7       0x29
  #define CSI2_HOST_DT_RAW8       0x2A
  #define CSI2_HOST_DT_RAW10      0x2B
  #define CSI2_HOST_DT_RAW12      0x2C
  #define CSI2_HOST_DT_RAW14      0x2D
  #define CSI2_HOST_DT_RSRV14     0x2E
  #define CSI2_HOST_DT_RSRV15     0x2F

// 0x30 to 0x37      Long     User Defined Byte-based Data
  #define CSI2_HOST_DT_U_DEF1     0x30
  #define CSI2_HOST_DT_U_DEF2     0x31
  #define CSI2_HOST_DT_U_DEF3     0x32
  #define CSI2_HOST_DT_U_DEF4     0x33
  #define CSI2_HOST_DT_U_DEF5     0x34
  #define CSI2_HOST_DT_U_DEF6     0x35
  #define CSI2_HOST_DT_U_DEF7     0x36
  #define CSI2_HOST_DT_U_DEF8     0x37


// 0x38 to 0x3F      --       Reserved
  #define CSI2_HOST_DT_RSRV16     0x38
  #define CSI2_HOST_DT_RSRV17     0x39
  #define CSI2_HOST_DT_RSRV18     0x3A
  #define CSI2_HOST_DT_RSRV19     0x3B
  #define CSI2_HOST_DT_RSRV20     0x3C
  #define CSI2_HOST_DT_RSRV21     0x3D
  #define CSI2_HOST_DT_RSRV22     0x3E
  #define CSI2_HOST_DT_RSRV23     0x3F
//data type end

enum interrupt_type
{
	CSI2_INT_PHY_FATAL = 1<<0,
	CSI2_INT_PKT_FATAL = 1<<1,
	CSI2_INT_FRAME_FATAL = 1<<2,
	CSI2_INT_PHY = 1<<16,
	CSI2_INT_PKT = 1<<17,
	CSI2_INT_LINE = 1<<18,
	CSI2_INT_IPI = 1<<19,
};

/*color mode*/
#define CSI2_COLOR_MODE_48BIT	(0x0)
#define CSI2_COLOR_MODE_16BIT	(0x1)

/*IPI timing */
#define  CSI2_CAMERA_TIMING_MODE	    (0x0)
#define  CSI2_CONTROLLER_TIMING_MODE	(0x1)
void dwc_csi_host_reset_pin_config(void);
void dwc_csi_host_reset_enable(void);
void dwc_csi_host_reset_release(void);
void dwc_csi_host_init(void);
void dwc_csi_check_status(void);

#endif
