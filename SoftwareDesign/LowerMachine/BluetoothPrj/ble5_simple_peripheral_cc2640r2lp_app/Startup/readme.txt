Software version record:

V0.0.1
    + Implement bidirectional transmission and reception between UART and BLE(UART->Tx <==> BLE Write Service; 
      UART->Rx <==> BLE Notify Service)ʵ��UART����������֮���˫���շ�����
    + UART Baud Rate is 1Mbps;
    + The length of data sent/received must be 20;
    + Two tasks: one for receiving UART data and one for BLE;

V0.0.2
	+ ֻ����Write��Notify����