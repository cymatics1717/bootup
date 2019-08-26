#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QUdpSocket>
#include <QNetworkDatagram>

#include "serialpeer.hpp"
#include "coreinfo.hpp"

#include <iostream>
#include <fstream>
#include "json/json.h"

class backEnd : public QObject
{
    Q_OBJECT
public:
    explicit backEnd(QString config_file, QObject *parent = nullptr);

    QString getConfigfile() const;

protected:
    void timerEvent(QTimerEvent *event) override;

signals:
    void showMessage(QString msg);

public slots:
    int loadConfig();
    int saveConfig();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
    void testQML(const QString& data);
    void setDateTime(const QDateTime &dt);

    void TaTaiReport();

    //5.3.31 内外部信号源选择
    void signalSelect(int sig);

    //5.3.1 硬件握手结果查询报文
    void hwHandShake(int mode, int tag);

    //5.3.3 初始化报文
    void initControlSystem(int tag);
    //5.3.4 初始化结果查询报文
    void getInitControlSystem();

    //5.3.9 工作模式设置报文
    void setWorkMode(int status,int tag);

    //5.3.6 开机/关机报文
    void setPowerOnOff(bool on, int tag);
    void setXiahuaPowerOnOffDelays();
    void setHengyaoPowerOnOffDelays();
    void __setXiahuaPowerOnOffDelays();
    void __setHengyaoPowerOnOffDelays();

    //5.3.7 开机/关机结果查询报文
    void getXiaHuaPowerOnOffStatus();
    void getHengYaoPowerOnOffStatus();

    //5.3.10 检视模式参数设置报文
    void reqSetInspect(qint8 slaveAddr, qint8 amp, qint8 period, int tag);

    //5.3.22 仰角设置报文
    void setPitch(qint32 pitch);
    //5.3.21 方位角设置报文
    void setAzimuth(qint32 azimuth);

    //5.3.20 光源控制报文
    void setLight(int tag, qint8 lightvalue, qint8 flash, qint8 mode);

    //5.3.26 进入标零报文
    void reqCalibActivate(qint8 slaveAddr,int tag);
    //5.3.11 零位旋变值及惯性单元偏移量查询报文
    void reqZeroOffset(qint8 slaveAddr,int tag);
    //5.3.13 零位旋变值及惯性单元偏移量平均值报文
    void reqZeroOffsetAvg(qint8 slaveAddr,int tag);
    //5.3.14 标零结果查询报文
    void reqCalibStatus(qint8 slaveAddr,int tag);
    //5.3.27 退出标零报文
    void reqCalibDeactivate(qint8 slaveAddr,int tag);

    // 限位角报文
    void reqLimitTest(qint8 slaveAddr,qint8 leftRight,int tag);
    void reqLimitAngleStatus(qint8 slaveAddr, qint8 leftRight, int tag);
    void reqXiaHuaLeftLimitAngleStatus();
    void reqXiaHuaRightLimitAngleStatus();
    void reqHengYaoLeftLimitAngleStatus();
    void reqHengYaoRightLimitAngleStatus();

    //5.3.16 系统状态查询报文
    void getSystemStatus(int tag);

    //全关系统控制器和静态灯
    void allPowerOff();

private:
    void send2Contrl(const QByteArray &data, int tag);
    void send2XiaHua(const QByteArray &data);
    void send2HengYa(const QByteArray &data);
    void send2TaTai_(const QByteArray &data);
    QString configfile;
    Json::Value root;
    QHash<QString,QPair<QString,quint16>> endpoints;

    QUdpSocket udp;
    serialPeer *controller;
    coreInfo core;
    QHash<QString,QVariant> pool;

    int controler_tag;
    int tataireportTimerID;
    int getSystemStatusTimerID;
    int workMode; //工作模式:01:调试模式;10:检视模式;11:正常工作模式
};

#endif // BACKEND_HPP
