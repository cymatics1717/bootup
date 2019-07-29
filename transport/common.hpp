#ifndef COMMON_HPP
#define COMMON_HPP

#include <QByteArray>
#include <QDateTime>

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

//5.2.1 下滑系统状态上报报文 0x01
#define MID_REPORT_XIAHUA '\x01'
//5.2.2 横摇系统状态上报报文
#define MID_REPORT_HENGYAO '\x02'
//5.2.3 故障警示灯状态上报报文
#define MID_REPORT_WARNING_LIGHT '\x03'

//5.3.1 硬件握手结果查询报文
#define MID_REQUEST_HARDWARE '\x1B'
//5.3.2 硬件握手结果报文
#define MID_REPLY_HARDWARE '\x1B'
//5.3.3 初始化报文
#define MID_REQUEST_INIT '\x04'
//5.3.4 初始化结果查询报文
#define MID_REQUEST_INIT_STATUS '\x0E'
//5.3.5 初始化结果报文
#define MID_REPLY_INIT_STATUS '\x0E'
//5.3.6 开机/关机报文
#define MID_REQUEST_POWER '\x05'
//5.3.7 开机/关机结果查询报文
#define MID_REQUEST_POWER_STATUS '\x0F'
//5.3.8 开机/关机结果报文
#define MID_REPLY_POWER_STATUS '\x0F'
//5.3.9 工作模式设置报文
#define MID_REQUEST_WORKING_MODE '\x13'
//5.3.10 检视模式参数设置报文
#define MID_REQUEST_SET_INSPECT_MODE '\x14'
//5.3.11 零位旋变值及惯性单元偏移量查询报文
#define MID_REQUEST_ZERO_OFFSET '\x15'
//5.3.12 零位旋变值及惯性单元偏移量报文
#define MID_REPLY_ZERO_OFFSET '\x15'
//5.3.13 零位旋变值及惯性单元偏移量平均值报文
#define MID_REQUEST_ZERO_OFFSET_AVG '\x16'
//5.3.14 标零结果查询报文
#define MID_REQUEST_CALIB_STATUS '\x17'
//5.3.15 标零结果报文
#define MID_REPLY_CALIB_STATUS '\x17'
//5.3.16 系统状态查询报文
#define MID_REQUEST_SYSTEM_STATUS '\x07'
//5.3.17 系统状态报文
#define MID_REPLY_SYSTEM_STATUS '\x01'
//5.3.18 故障信息主动上报报文
#define MID_REPLY_ERROR_REPORT '\x00'
//5.3.19 报警信息主动上报报文
#define MID_REPLY_WARN_REPORT '\x01'
//5.3.20 光源控制报文
#define MID_REQUEST_LIGHT_CONTROL '\x08'
//5.3.21 方位角设置报文
#define MID_REQUEST_AZIMUTH '\x09'
//5.3.22 仰角设置报文
#define MID_REQUEST_ELEVATION '\x0A'
//5.3.23 确认收到报文
#define MID_ACK '\x06'
//5.3.24 待机保护报文
#define MID_REQUEST_STANDBY_ON '\x02'
//5.3.25 取消待机保护报文
#define MID_REQUEST_STANDBY_OFF '\x03'
//5.3.26 进入标零报文
#define MID_REQUEST_CALIB_ACTIVATE '\x19'
//5.3.27 退出标零报文
#define MID_REQUEST_CALIB_DEACTIVATE '\x1A'
//5.3.28 限位测试报文
#define MID_REPLY_LIMIT_TEST '\x01'
//5.3.29 限位角度查询报文
#define MID_REPLY_LIMIT_ANGLE_STATUS '\x1C'
//5.3.30 限位角度报文
#define MID_REQUEST_LIMIT_ANGLE '\x1C'
//5.3.31 陀螺信号源选择报文
#define MID_REQUEST_GYRO_SINGAL '\x1D'

QString currentTime();

#endif // COMMON_HPP
