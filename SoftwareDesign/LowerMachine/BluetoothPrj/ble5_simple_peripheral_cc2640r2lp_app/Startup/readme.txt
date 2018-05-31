Software version record:

V0.0.1
    + Implement bidirectional transmission and reception between UART and BLE(UART->Tx <==> BLE Write Service; 
      UART->Rx <==> BLE Notify Service)实现UART与蓝牙数据之间的双向收发功能
    + UART Baud Rate is 1Mbps;
    + The length of data sent/received must be 20;
    + Two tasks: one for receiving UART data and one for BLE;

V0.0.2
	+ 只保留Write和Notify服务

V0.0.3
	+ 将数据存储变成循环队列，长度可调
	+ 支持小于20字节的任意长度的报文格式
	+ 目前还未将Characteristic Value指向的位置变成循环队列的数据入口