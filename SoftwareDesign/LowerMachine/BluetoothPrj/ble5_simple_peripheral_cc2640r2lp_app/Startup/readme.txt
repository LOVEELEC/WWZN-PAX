Software version record:

V0.0.1
    + Implement bidirectional transmission and reception between UART and BLE(UART->Tx <==> BLE Write Service; 
      UART->Rx <==> BLE Notify Service)ʵ��UART����������֮���˫���շ�����
    + UART Baud Rate is 1Mbps;
    + The length of data sent/received must be 20;
    + Two tasks: one for receiving UART data and one for BLE;

V0.0.2
	+ ֻ����Write��Notify����

V0.0.3
	+ �����ݴ洢���ѭ�����У����ȿɵ�
	+ ֧��С��20�ֽڵ����ⳤ�ȵı��ĸ�ʽ
	+ Ŀǰ��δ��Characteristic Valueָ���λ�ñ��ѭ�����е��������