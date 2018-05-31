#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stdint.h"
#include "stdbool.h"
//#define DCMI_CROP     /*����Ϊ�ü�ģʽ*/
#define DCMI_IT_SET		/*����DCMI�ж�*/
//#define DCMI_UART_BMP /*�������ͼ�����ݣ����ڣ�*/
#define DCMI_SNAPSHOT /*��������ģʽ�����κ�Ϊѭ��ģʽ*/

//#define UART3_CONFIG 0

#if 0
#ifndef   DCMI_CROP  //752*480
	#define MT9V024_HEIGHT (480)
	#define MT9V024_WEIGHT (752)
	#define BDMASIZE  (0xBC0)
#else								//640*480
	#define MT9V024_HEIGHT (480)
	#define MT9V024_WEIGHT (640)
	#define BDMASIZE  (0xA00)
#endif //DCMI_CROP
#else
    #define BDMASIZE  (900)
    #define ORIG_WIN_LEN (60)
	#define OV7251_HEIGHT (ORIG_WIN_LEN)
	#define OV7251_WEIGHT (ORIG_WIN_LEN)
#endif

#endif
