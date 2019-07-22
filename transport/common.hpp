#ifndef COMMON_HPP
#define COMMON_HPP

#include <QByteArray>

quint32 mmmcrc32(const QByteArray &data);

#define LOCAL_IP "127.0.0.1"
#define LOCAL_PORT "1025"

#define XIAHUA_IP "127.0.0.1"
#define XIAHUA_PORT "1026"

#define HENGYAO_IP "127.0.0.1"
#define HENGYAO_PORT "1027"

#define TATAI_IP "127.0.0.1"
#define TATAI_PORT "1021"
//////////////////////////////////////

#define MID_HARD ''

/*
1) 故障信息主动上报报文信息标识为 0x00,
2) 报警信息主动上报报文信息标识为 0x01,
3) 待机保护报文信息标识为 0x02,
4) 取消待机保护报文信息标识为 0x03,
5) 初始化报文信息标识为 0x04,
6) 开机/关机报文信息标识为 0x05,
7) 确认收到报文信息标识为 0x06,
8) 系统状态查询报文信息标识为 0x07,
9) 系统状态报文信息标识为 0x07,
10) 光源控制报文信息标识为 0x08,
11) 方位角设置报文信息标识为 0x09,
12) 仰角设置报文信息标识为 0x0A,
13) 初始化结果查询报文信息标识为 0x0E,
14) 初始化结果报文信息标识为 0x0E,
15) 开机/关机结果查询报文信息标识为 0x0F,
16) 开机/关机结果报文信息标识为 0x0F,
17) 工作模式设置报文信息标识为 0x13,
18) 检视模式参数设置报文信息标识为 0x14,
19) 零位旋变值及惯性单元偏移量查询报文信息标识为 0x15,
20) 零位旋变值及惯性单元偏移量报文信息标识为 0x15,
21) 零位旋变值及惯性单元偏移量平均值报文信息标识为 0x16,
22) 标零结果查询报文信息标识为 0x17,
23) 标零结果报文信息标识为 0x17,
24) 限位测试报文信息标识为 0x18,
25) 进入标零指令报文信息标识为 0x19,
26) 退出标零指令报文信息标识为 0x1A,
27) 硬件握手结果查询报文信息标识为 0x1B,
28) 硬件握手结果报文信息标识为 0x1B,
29) 限位角度查询报文信息标识为 0x1C,
30) 限位角度报文信息标识为 0x1C,
31) 陀螺信号源选择报文信息标识为 0x1D。
*/

// 5.2.1 下滑系统状态上报报文 0x01
#define MID_REPORT_LIGHT '\x01'
//5.3.1 硬件握手结果查询报文
#define MID_REQUEST_HARDWARE '\x01'
//5.3.3 初始化报文
#define MID_REQUEST_INIT '\x01'
//5.3.4 初始化结果查询报文
#define MID_REQUEST_INIT_STATUS '\x01'
//5.3.6 开机/关机报文
#define MID_REQUEST_POWER '\x01'
// 5.3.7 开机/关机结果查询报文
#define MID_REQUEST_POWER_STATUS '\x01'
// 5.3.9 工作模式设置报文
#define MID_REQUEST_POWER_STATUS '\x01'


QByteArray hardwareHandShake();


#endif // COMMON_HPP
