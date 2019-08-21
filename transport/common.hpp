#ifndef COMMON_HPP
#define COMMON_HPP

#include <QByteArray>
#include <QDateTime>
#include <QDataStream>

quint16 mmmcrc16(const QByteArray &data);
quint32 mmmcrc32(const QByteArray &data);

/*****************从机地址**************************/
#define SLAVE_BROADCAST '\x00'

#define SLAVE_XIAHUA_ZONGYAO_DIANJI     '\x01'
#define SLAVE_HENGYAO_DIANJI            '\x02'
#define SLAVE_XIAHUA_HENGYAO_DIANJI     '\x03'
#define SLAVE_XIAHUA_ZONGYAO_GUANXING   '\x04'
#define SLAVE_HENGYAO_GUANXING          '\x05'
#define SLAVE_XIAHUA_HENGYAO_GUANXING   '\x06'


/***触控面板与系统控制器相关协议信息标识
**************内部信号和外部信号选择****************/
//5.3.31 陀螺信号源选择报文
#define MID_REQUEST_GYRO_SINGAL '\x1D'

/***触控面板与塔台相关协议信息标识***/
//5.2.1 系统状态上报报文 0x01
#define MID_REPORT_SYS_STATUS_TATAI '\x01'

/***触控面板与系统控制器相关协议信息标识
*****************正常模式**************************/
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
//5.3.20 光源控制报文
#define MID_REQUEST_LIGHT_CONTROL '\x08'
//5.3.21 方位角设置报文
#define MID_REQUEST_AZIMUTH '\x09'
//5.3.22 仰角设置报文
#define MID_REQUEST_PITCH '\x0A'
//5.3.16 系统状态查询报文
#define MID_REQUEST_SYSTEM_STATUS '\x07'
//5.3.17 系统状态报文
#define MID_REPLY_SYSTEM_STATUS '\x07'
//5.3.18 故障信息主动上报报文
#define MID_REPLY_ERROR_REPORT '\x00'
//5.3.19 报警信息主动上报报文
#define MID_REPLY_WARN_REPORT '\x01'
//5.3.23 确认收到报文
#define MID_ACK '\x06'
//5.3.24 待机保护报文
#define MID_REQUEST_STANDBY_ON '\x02'
//5.3.25 取消待机保护报文
#define MID_REQUEST_STANDBY_OFF '\x03'


/***触控面板与系统控制器相关协议信息标识
*****************检视模式和调试模式**************************/
//5.3.10 检视模式参数设置报文
#define MID_REQUEST_SET_INSPECT_MODE '\x14'
//5.3.26 进入标零报文
#define MID_REQUEST_CALIB_ACTIVATE '\x19'
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
//5.3.27 退出标零报文
#define MID_REQUEST_CALIB_DEACTIVATE '\x1A'
//5.3.28 限位测试报文
#define MID_REPLY_LIMIT_TEST '\x18'
//5.3.29 限位角度查询报文
#define MID_REPLY_LIMIT_ANGLE_STATUS '\x1C'
//5.3.30 限位角度报文
#define MID_REQUEST_LIMIT_ANGLE '\x1C'

QString currentTime();
bool checkEquality(const QByteArray &dat);

#endif // COMMON_HPP
