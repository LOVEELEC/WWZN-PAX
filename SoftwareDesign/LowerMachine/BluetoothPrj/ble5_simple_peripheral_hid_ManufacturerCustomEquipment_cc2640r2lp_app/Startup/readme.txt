Software Vision:

V0.0.1
	+ 移植emu_kbd项目到新建项目并能够正常工作
	
V0.0.2
	+ 实现数据的发送(暂未实现通过串口实现数据的收发操作)

V0.0.3
	+ 实现按键发送PenDown和PenUp数据
	
V0.0.4
	+ Implement bidirectional transmission and reception between UART and BLE(UART->Tx <==> BLE Write Service; 
      UART->Rx <==> BLE Notify Service)实现UART与蓝牙数据之间的双向收发功能
    + UART Baud Rate is 1Mbps;