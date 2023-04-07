##	PC802 pcie performance test

1. Install PC802 User Plane Driver

	sudo dpkg -i PC802_User_Plane_Driver_arm64_2.3-eb3c9a25.deb
	sudo reboot

2. run pc802 pcie performance test app

	sudo npu_run.sh dpdk-test-pc802-perf
	#After normal startup, you can get the command line prompt: "PC802>>"
	#Performance test command example: "test pcie 250 10 0 0"
    #parameter 1 is the test packet length in K bytes (1K = 1024), the default value 0 will use 1K
    #parameter 2 is the test duration in second, the default value 0 will use 60 seconds
    #parameter 3 is the test channel bitmap, the default value 0 will use 0x70
    #parameter 4 is the test type, currently only use 0, other values are reserved

3. test result
	#After the start, each of the upstream and downstream performance test data will be output every second.

PC802>> test pcie 250 10 0 0

	Start pcie performance test ...
	Package len:	256000 byte
	Test channel:	70
	Test duration:	10 seconds
	Test type:	12
	UL core:	2


Core 2 acting as pc802 recv core 15 second.
0(1000):UL PPS: 6638, BPS: 13594624Kbits/sec ( 4: 3320, 6799360; 5: 1659, 3397632; 6: 1659, 3397632;)
0(1000):DL PPS: 10361, BPS: 21219328Kbits/sec ( 4: 3454, 7073792; 5: 3454, 7073792; 6: 3453, 7071744;)
1(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
1(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
2(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
2(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
3(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
3(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
4(1000):UL PPS: 6654, BPS: 13627392Kbits/sec ( 4: 3327, 6813696; 5: 1664, 3407872; 6: 1663, 3405824;)
4(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
5(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
5(1000):DL PPS: 9981, BPS: 20441088Kbits/sec ( 4: 3327, 6813696; 5: 3327, 6813696; 6: 3327, 6813696;)
6(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
6(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
7(1000):UL PPS: 6654, BPS: 13627392Kbits/sec ( 4: 3327, 6813696; 5: 1663, 3405824; 6: 1664, 3407872;)
7(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
8(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
8(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
9(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
9(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
10(1000):UL PPS: 780, BPS: 1597440Kbits/sec ( 4: 443, 907264; 5: 188, 385024; 6: 149, 305152;)
11(1000):UL PPS: 0, BPS: 0Kbits/sec ( 4: 0, 0; 5: 0, 0; 6: 0, 0;)
12(1000):UL PPS: 0, BPS: 0Kbits/sec ( 4: 0, 0; 5: 0, 0; 6: 0, 0;)
13(1000):UL PPS: 0, BPS: 0Kbits/sec ( 4: 0, 0; 5: 0, 0; 6: 0, 0;)
14(1000):UL PPS: 0, BPS: 0Kbits/sec ( 4: 0, 0; 5: 0, 0; 6: 0, 0;)
Rx total recv pkgs 67290.
Tx total send pkgs 100166.
PC802>>



1、该工具打印信息的具体含义？

此测试程序为PCIE软硬件性能测试程序，测试不同包长下pcie通道双向独立收发下吞吐量。

秒(毫秒):方向 PPS:每秒包数    BPS:每秒流量    ( 通道4:PPS, BPS;    通道5:PPS,BPS;    通道6:PPS,BPS;  )
2(1000):UL PPS: 6652, BPS: 13623296Kbits/sec ( 4: 3326, 6811648; 5: 1663, 3405824; 6: 1663, 3405824;)
2(1000):DL PPS: 9978, BPS: 20434944Kbits/sec ( 4: 3326, 6811648; 5: 3326, 6811648; 6: 3326, 6811648;)
“毫秒”指统计周期内毫秒计数，通常都是1000, 统计是基于时间差比较的，系统实时性不足时可能超过1000.

2、该工具能否看出PCIe通道是否有异常呢？

仅进行基本测试，有上行表示双向传输正常，速率大小反馈链路质量
