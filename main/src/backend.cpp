#include "backend.hpp"
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <utility>
#include <math.h>
#include <QThread>

static QString makeID(const QNetworkDatagram gram){
    return QString("[%1:%2->%3:%4 %5]")
            .arg(gram.senderAddress().toString())
            .arg(gram.senderPort())
            .arg(gram.destinationAddress().toString())
            .arg(gram.destinationPort())
            .arg(gram.data().size(),4,10);
}

backEnd::backEnd(QString config_file, QObject *parent) : QObject(parent)
  ,configfile(std::move(config_file))
{
    endpoints.insert("local",qMakePair<QString,quint16>("192.168.1.5",1025));
    endpoints.insert("xiahua",qMakePair<QString,quint16>("192.168.1.6",1026));
    endpoints.insert("hengyao",qMakePair<QString,quint16>("192.168.1.7",1027));
    endpoints.insert("tatai",qMakePair<QString,quint16>("192.168.1.1",1021));

    tataireportTimerID = startTimer(1000);
//    getSystemStatusTimerID = startTimer(500);
}

QString backEnd::getConfigfile() const
{
    return configfile;
}

void backEnd::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == tataireportTimerID){
        TaTaiReport();
    } else if(event->timerId() == getSystemStatusTimerID){
        getSystemStatus(0);
        //getSystemStatus(1);
    }
}

int backEnd::loadConfig()
{
    try {
        // https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
        std::ifstream infile(configfile.toStdString());
        qDebug() << QFileInfo(configfile).absoluteFilePath();
        infile >> root;
    } catch (const std::exception &e) {
        std::cout << e.what()<<std::endl;
        return -1;
    }

//////////////////////////////////////////////////////////////////
    qDebug() <<"local host:"<< root["endpoints"]["touchpad"]["ip"].asString().c_str();
    qDebug() <<"xiahua server:"<< root["endpoints"]["xiahua"]["ip"].asString().c_str();
    qDebug() <<"hengyao server:"<< root["endpoints"]["hengyao"]["ip"].asString().c_str();
    qDebug() <<"tatai server" <<root["endpoints"]["tatai"]["ip"].asString().c_str();

    {
        Json::Value item = root["endpoints"]["touchpad"];
        endpoints.insert("local",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }
    {
        Json::Value item = root["endpoints"]["xiahua"];
        endpoints.insert("xiahua",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }
    {
        Json::Value item = root["endpoints"]["hengyao"];
        endpoints.insert("hengyao",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }
    {
        Json::Value item = root["endpoints"]["tatai"];
        endpoints.insert("tatai",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }

    // init server.

    qInfo()<<"bind status:"<<udp.bind(QHostAddress(endpoints.value("local").first),
                                           endpoints.value("local").second/*,QAbstractSocket::ReuseAddressHint*/);
    connect(&udp,&QUdpSocket::hostFound,[](){qInfo() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::connected,[](){qInfo() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::disconnected,[](){qInfo() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::readyRead,this,&backEnd::onReadyRead);
    connect(&udp, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &backEnd::onError);

    {
        Json::Value item = root["endpoints"]["controller"];
        QString dev = QString::fromStdString(item["device"].asString());
        if(dev.isEmpty()){
            dev = "/dev/ttyUSB0";
        }
        int interval = item["interval"].asInt();
        if(interval<1 ||interval>10000){
            interval = 200;
        }
//        controller = new serialPeer(dev,interval,this);
    }

//    controller->setPowerOnOff(true);
	
    return 0;
}

int backEnd::saveConfig()
{
    std::ofstream outfile(QString("%1/settings.json").arg(QFileInfo(configfile).path()).toStdString());
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "\t";
//    builder["commentStyle"] = "None";
    builder["commentStyle"] = "All";
    builder["enableYAMLCompatibility"] = true;
    builder["dropNullPlaceholders"] = false;
    builder["useSpecialFloats"] = false;
    root["id"] = "config file";
//    root["id"] = __FUNCTION__;
//    outfile << root;

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &outfile);
//    writer->write(root, &std::cerr);

//    std::string doc = Json::writeString(builder, root);
//    std::cerr << doc << std::endl;

    return 0;
}

void backEnd::onError(QAbstractSocket::SocketError socketError)
{
    qWarning() <<currentTime()<< "--"<<udp.errorString() << sender()<<socketError;
}

void backEnd::testQML(const QString& data)
{
    qInfo() << data;
}

void backEnd::setDateTime(const QDateTime &dt)
{
    qInfo() << dt;
}

/***触控面板与塔台相关协议信息标识***/
void backEnd::TaTaiReport()
{
    //5.2.1 系统状态上报报文塔台 0x01
    QByteArray tatai;
    tatai.append(MID_REPORT_SYS_STATUS_TATAI);

    send2TaTai_(tatai);
}

/***触控面板与系统控制器相关协议信息标识
*****************正常模式发送通用接口**************************/
//0. 内外部信号源选择
/**
 * @brief backEnd::signalSelect
 * @param sig 内部信号源（默认内部）:01,外部信号源:02
 */
void backEnd::signalSelect(int sig)
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_GYRO_SINGAL);

    if(sig == 2){
        data.append('\x02');
    } else {
        data.append('\x01');
    }

    send2Contrl(data,0);
    send2Contrl(data,1);
}

//1. 硬件握手
/**
 * @brief backEnd::hwHandShake
 * @param mode 工作模式
 * @param tag 下滑：0；横摇：1
 */
void backEnd::hwHandShake(int mode, int tag)
{
    workMode = mode;
    QByteArray data;
    data.append(MID_REQUEST_HARDWARE);

    send2Contrl(data,tag);
}

//2. 初始化
void backEnd::initControlSystem(int tag)
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_INIT);
    send2Contrl(data,tag);
    controler_tag = tag;
    QTimer::singleShot(60000, this, &backEnd::getInitControlSystem);
}

void backEnd::getInitControlSystem()
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_INIT_STATUS);

    send2Contrl(data,controler_tag);
}

//3. 设置工作模式
void backEnd::setWorkMode(int status,int tag)
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_WORKING_MODE);
    // 01:调试模式 10:检视模式 11:正常工作模式
    if(status == 3){
        dat.append('\x03');
    } else if(status == 2){
        dat.append('\x02');
    } else if(status == 1){
        dat.append('\x01');
    }

    send2Contrl(dat,tag);
}

//4. 开关机
void backEnd::setPowerOnOff(bool on, int tag)
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_POWER);
    if(on){
        data.append('\x01');
    } else {
        data.append('\x02');
    }

    send2Contrl(data,tag);
    if(tag ==0){
        QTimer::singleShot(10000 , this, &backEnd::getXiaHuaPowerOnOffStatus);
    } else if(tag ==1){
        QTimer::singleShot(10000 , this, &backEnd::getHengYaoPowerOnOffStatus);
    }
}

void backEnd::setXiahuaPowerOnOffDelays()
{
    setPowerOnOff(true,0);
}

void backEnd::__setXiahuaPowerOnOffDelays() {

    QTimer::singleShot(50 , this, &backEnd::setXiahuaPowerOnOffDelays);
}

void backEnd::setHengyaoPowerOnOffDelays()
{
    setPowerOnOff(true,1);
}

void backEnd::__setHengyaoPowerOnOffDelays() {

    QTimer::singleShot(50 , this, &backEnd::setHengyaoPowerOnOffDelays);
}

void backEnd::getXiaHuaPowerOnOffStatus()
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_POWER_STATUS);
    send2Contrl(data,0);
}

void backEnd::getHengYaoPowerOnOffStatus()
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_POWER_STATUS);
    send2Contrl(data,1);
}

//5. 光源控制
/**
 * @brief backEnd::setLight
 * @param tag 下滑：0；横摇：1
 * @param lightvalue 光强
 * @param flash 闪光模式 0x11:多闪, 0x10:单闪, 0x01:不闪
 * @param mode 工作模式 0x11:正常工作模式, 0x10:检视模式, 0x01:调试模式
 */
void backEnd::setLight(int tag, qint8 lightvalue, qint8 flash, qint8 mode)
{
    qDebug() << lightvalue << lightvalue *5/2<< flash <<tag <<mode;
    QByteArray dat;
    dat.append(MID_REQUEST_LIGHT_CONTROL);
    if(tag==0){
        //光强等级设置 光强等级0:00000000 光强等级1:0000
        dat.append(qint8(lightvalue*2.5));
        // 闪光状态设置(三闪:11开:01单闪:10关:10不闪:01)   下滑光源开关设置 开:01 关:10
        dat.append(flash);
        send2Contrl(dat, tag);
    } else if(tag==1){
        //光强等级设置 光强等级0:00000000 光强等级1:0000
        dat.append(lightvalue);
        // 横摇灯杆开关设置 开:01关:10
        if(true){
            dat.append('\x40');
        } else {
            dat.append('\x80');
        }
        if (mode == 1) {
            // 左固定灯黄灯开关设置 开:01关:10  左固定灯红灯开关设置 开:01关:10 右固定灯黄灯开关设置 开:01关:10  右固定灯红灯开关设置 开:01关:10
            dat.append('\x40');
            dat.append('\x02');
        }
        send2Contrl(dat, tag);
    }
}

//6. 全关系统控制器和静态灯
void backEnd::allPowerOff()
{
    setPowerOnOff(false,0);
    setPowerOnOff(false,1);
    //add:关闭所有静态灯
}

/*****************正常模式下滑特有接口*************************/
//下滑特有接口 -- 设置仰角
void backEnd::setPitch(qint32 pitch)
{
    qDebug() <<pitch;
    QByteArray dat,data;
    dat.append(MID_REQUEST_PITCH);
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    stream << pitch*1000;

    send2XiaHua(data);
}

void backEnd::setAzimuth(qint32 azimuth)
{
    qDebug() <<azimuth;
    QByteArray dat,data;
    dat.append(MID_REQUEST_AZIMUTH);
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    stream << azimuth*1000;

    send2XiaHua(data);
}

/*****************UDP接收通用接口**************************/
void backEnd::onReadyRead()
{
    while(udp.hasPendingDatagrams()){
        QNetworkDatagram gram = udp.receiveDatagram();
        QByteArray dat = gram.data();
        qDebug() <<"recv: " << makeID(gram) << dat.toHex('-');

        showMessage( makeID(gram) );

        //fix crash.
         /***单开和一起开测试***/
        if(dat.size()>0){

            int tag = -2;
            if(gram.senderAddress().toString() == endpoints.value("xiahua").first) {
                tag = 0;
            } else if(gram.senderAddress().toString() == endpoints.value("hengyao").first){
                tag = 1;
            }
//            else if(gram.senderAddress().toString() == endpoints.value("tatai").first){
//                tag = -1;
//            }

             if(dat.at(0) == MID_REPLY_ERROR_REPORT) {
                 //故障信息主动上报
                 core.parseBreakdownStatus(dat,tag);
                 qDebug() <<"********YYQ:parseBreakdownStatus reply success********"<<dat.size()<< dat.toHex('-');
             }else if(dat.at(0) == MID_REPLY_WARN_REPORT) {
                 //报警信息主动上报
                 core.parseAlarmStatus(dat,tag);
                 qDebug() <<"********YYQ:parseAlarmStatus reply success********"<<dat.size()<< dat.toHex('-');

             }else if(dat.at(0)==MID_REPLY_SYSTEM_STATUS){
                 //系统状态查询回复
                 core.parseSystemStatus(dat,tag);
                 qDebug() <<"********YYQ:parseSystemStatus reply success********"<<dat.size()<< dat.toHex('-');

             }else if(dat.at(0)==MID_REPLY_HARDWARE){
                //硬件握手回复
                core.parseHWHandShakeStatus(dat,tag);
                qDebug() <<"********YYQ:hwHandShake reply success********"<<dat.size()<< dat.toHex('-');
                initControlSystem(tag);

             } else if(dat.at(0) == MID_REPLY_INIT_STATUS) {
                //初始化查询回复
                core.parseInitSystemStatus(dat,tag);
                qDebug() <<"********YYQ:GetInitControlSystem reply success********"<<dat.size()<< dat.toHex('-');
                setWorkMode(workMode,tag);
                //延时 if taita
                if(tag == 0){
                    __setXiahuaPowerOnOffDelays();
                }else if(tag == 1){
                    __setHengyaoPowerOnOffDelays();
                }
            } else if(dat.at(0) == MID_REPLY_POWER_STATUS) {
                //开机结果查询回复
                core.parsePowerOnOffStatus(dat,tag);
                qDebug() <<"********YYQ:getPowerOnOffStatus reply success********"<<dat.size()<< dat.toHex('-');
//                //reqLimitTest(0x03, 0x02, 0); //测试限位角
//                reqCalibActivate(0x03, 0); //测试下滑横摇进入标零 0x19 0x03
//                QThread::msleep(200);
//                //reqCalibStatus(0x03, 0); //测试标零结果查询
//                //reqZeroOffset(0x03, 0); //测试零位旋变值及惯性单元偏移量查询报文
//                //reqZeroOffsetAvg(0x03, 0); //测试零位旋变值及惯性单元偏移量平均值报文
//                reqCalibDeactivate(0x03, 0); //测试下滑横摇退出标零 0x1A 0x03
                //getSystemStatusTimerID = startTimer(500);
             } else if (dat.at(0) == MID_REPLY_LIMIT_ANGLE) {
                // 限位角度报文回复
                core.parseLimitAngle(dat,tag);
                qDebug() <<"@@@@@@@@@@@@@viktor:parseLimitAngle reply success********"<<dat.size()<< dat.toHex('-');
            } else if (dat.at(0) == MID_REPLY_CALIB_STATUS) {
                // 标零结果报文
                core.parseCalibStatusReply(dat,tag);
                qDebug() <<"@@@@@@@@@@@@@viktor:parseCalibStatusReply reply success********"<<dat.size()<< dat.toHex('-');
            } else if (dat.at(0) == MID_REPLY_ZERO_OFFSET) {
                // 零位旋变值及惯性单元偏移量报文
                core.parseZeroOffsetReply(dat, tag);
                qDebug() <<"@@@@@@@@@@@@@viktor:parseZeroOffsetReply reply success********"<<dat.size()<< dat.toHex('-');
            }

        }
    }
}

/*****************系统状态查询************************/
/**
 * @brief backEnd::getSystemStatus
 * @param tag : 下滑：0；横摇：1
 */
void backEnd::getSystemStatus(int tag)
{
    qDebug() <<"";
    QByteArray dat;
    dat.append(MID_REQUEST_SYSTEM_STATUS);

    send2Contrl(dat,tag);
}

/*****************检视模式和调试模式接口 start************************/
/**
 * @brief backEnd::reqSetInspect
 * @param slaveAddr : 从机地址
 * @param amp : 幅值大于 15°时,自动填入 15°
 * @param period : 最小周期=|幅值|*2π/正弦最大速度(正弦最大速度取 11.7°/s)
 * ,如果设置的周期值小于最小周期,自动填入大于最小周期的整数。
 * @param tag : 下滑：0；横摇：1
 */
void backEnd::reqSetInspect(qint8 slaveAddr, qint8 amp, qint8 period, int tag)
{
    qDebug() <<"@@@@@@@@@@@@@@@@@viktor@@@@@@@@@@@@" << slaveAddr << amp << period << tag;
    QByteArray data;
    data.append(MID_REQUEST_SET_INSPECT_MODE);

    // 下滑系统控制器 0x07, tag:0
    // 横摇系统控制器 0x08, tag:1
    data.append(slaveAddr);
    // 幅值(单位:°)
    if (amp > 15) {
        amp = 15;
    }
    data.append(amp);
    // 周期(大于最小周期值,单位为s)
    // 最小周期
    double minPeriod = (double)(qAbs(amp) * 2 * M_PI) / 11.7;
    if (period < minPeriod) {
        period = ceil(minPeriod);
    }
    data.append(period);
    send2Contrl(data, tag);
}
/*****************检视模式和调试模式接口 end************************/

/*****************标零报文接口 start************************/
//2. 进入标零报文
/**
 * @brief backEnd::reqCalibActivate
 * @param slaveAddr 从机地址
 * @param tag 下滑：0；横摇：1
 */
void backEnd::reqCalibActivate(qint8 slaveAddr,int tag) {
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_CALIB_ACTIVATE);
    data.append(slaveAddr);

    send2Contrl(data,tag);
}

// 零位旋变值及惯性单元偏移量查询报文
/**
 * @brief backEnd::reqZeroOffset
 * @param slaveAddr 从机地址
 * @param tag 下滑：0；横摇：1
 */
void backEnd::reqZeroOffset(qint8 slaveAddr,int tag)
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_ZERO_OFFSET);
    data.append(slaveAddr);

    send2Contrl(data,tag);
}

// 零位旋变值及惯性单元偏移量平均值报文（可能没意义）
/**
 * @brief backEnd::reqZeroOffsetAvg
 * @param slaveAddr 从机地址
 * @param tag 下滑：0；横摇：1
 */
void backEnd::reqZeroOffsetAvg(qint8 slaveAddr,int tag)
{
    qDebug() <<"";
    QByteArray dat,data;
    data.append(MID_REQUEST_ZERO_OFFSET_AVG);
    data.append(slaveAddr);

    qint32 avg = 1000;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    stream  << avg;

    send2Contrl(data,tag);
}

// 标零结果查询报文
/**
 * @brief backEnd::reqCalibStatus
 * @param slaveAddr 从机地址
 * @param tag 下滑：0；横摇：1
 */
void backEnd::reqCalibStatus(qint8 slaveAddr,int tag)
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_CALIB_STATUS);
    data.append(slaveAddr);

    send2Contrl(data,tag);
}

// 退出标零报文
/**
 * @brief backEnd::reqCalibDeactivate
 * @param slaveAddr 从机地址
 * @param tag 下滑：0；横摇：1
 */
void backEnd::reqCalibDeactivate(qint8 slaveAddr,int tag)
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_CALIB_DEACTIVATE);

    data.append(slaveAddr);
    send2Contrl(data,tag);
}
/*****************标零报文接口 end************************/

/*****************限位角报文接口 start************************/
//2. 限位角 Limit angle
/**
 * @brief backEnd::reqLimitTest
 * @param slaveAddr 从机地址
 * @param leftRight 0x01:左(上)限位; 0x02:右(下)限位
 * @param tag 下滑：0；横摇：1
 */
void backEnd::reqLimitTest(qint8 slaveAddr,qint8 leftRight,int tag)
{
    qDebug() <<"";

    QByteArray data;
    data.append(MID_REQUEST_LIMIT_TEST);
    data.append(slaveAddr);
    data.append(leftRight);

    send2Contrl(data,tag);

    if(tag == 0) {
        if(leftRight == 1) {
            QTimer::singleShot(500, this, &backEnd::reqXiaHuaLeftLimitAngleStatus);
        } else if (leftRight == 2) {
            QTimer::singleShot(500, this, &backEnd::reqXiaHuaRightLimitAngleStatus);
        }
    } else if (tag == 1) {
        if(leftRight == 1) {
            QTimer::singleShot(500, this, &backEnd::reqHengYaoLeftLimitAngleStatus);
        } else if (leftRight == 2) {
            QTimer::singleShot(500, this, &backEnd::reqHengYaoRightLimitAngleStatus);
        }
    }
}

/**
 * @brief backEnd::reqLimitAngleStatus
 * @param slaveAddr 从机地址
 * @param leftRight 0x01:左(上)限位; 0x02:右(下)限位
 * @param tag 下滑：0；横摇：1
 */
void backEnd::reqLimitAngleStatus(qint8 slaveAddr, qint8 leftRight, int tag)
{
    qDebug() <<"";
    QByteArray data;
    data.append(MID_REQUEST_LIMIT_ANGLE_STATUS);
    data.append(slaveAddr);
    data.append(leftRight);

    send2Contrl(data,tag);
}

void backEnd::reqXiaHuaLeftLimitAngleStatus()
{
    qDebug() <<"@@@@@@@@viktor->reqXiaHuaLeftLimitAngleStatus";
    QByteArray data;
    data.append(MID_REQUEST_LIMIT_ANGLE_STATUS);
    // TODO 从机地址，限位方向需要填充
//    data.append(slaveAddr);
    data.append(0x03);
//    data.append(leftRight);
    data.append(0x01);
//    send2Contrl(data,tag);
    send2Contrl(data, 0);
}

void backEnd::reqXiaHuaRightLimitAngleStatus()
{
    qDebug() <<"@@@@@@@@viktor->reqXiaHuaRightLimitAngleStatus";
    QByteArray data;
    data.append(MID_REQUEST_LIMIT_ANGLE_STATUS);
    // TODO 从机地址，限位方向需要填充
//    data.append(slaveAddr);
    data.append(0x03);
//    data.append(leftRight);
    data.append(0x02);
//    send2Contrl(data,tag);
    send2Contrl(data, 0);
}

void backEnd::reqHengYaoLeftLimitAngleStatus()
{
    qDebug() <<"@@@@@@@@viktor->reqHengYaoLeftLimitAngleStatus";
    QByteArray data;
    data.append(MID_REQUEST_LIMIT_ANGLE_STATUS);
    // TODO 从机地址，限位方向需要填充
//    data.append(slaveAddr);
//    data.append(leftRight);

//    send2Contrl(data,tag);
}

void backEnd::reqHengYaoRightLimitAngleStatus()
{
    qDebug() <<"@@@@@@@@viktor->reqHengYaoRightLimitAngleStatus";
    QByteArray data;
    data.append(MID_REQUEST_LIMIT_ANGLE_STATUS);
    // TODO 从机地址，限位方向需要填充
//    data.append(slaveAddr);
//    data.append(leftRight);

//    send2Contrl(data,tag);
}
/*****************限位角报文接口 end************************/

/*****************UDP通用发送接口************************/
void backEnd::send2Contrl(const QByteArray &data, int tag)
{
    if(tag == 0){
        send2XiaHua(data);
    } else if(tag == 1){
        send2HengYa(data);
    }
}

void backEnd::send2XiaHua(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("xiahua").first),endpoints.value("xiahua").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    udp.flush();
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

void backEnd::send2HengYa(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("hengyao").first),endpoints.value("hengyao").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    udp.flush();
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

void backEnd::send2TaTai_(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("tatai").first),endpoints.value("tatai").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    udp.flush();
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

