#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QUdpSocket>
#include <QNetworkDatagram>

#include "serialpeer.hpp"

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

    //5.3.1 硬件握手结果查询报文
    void hwHandShake(int tag);
    void onGetHWHandShake(const QByteArray& dat,int tag);

    //5.3.3 初始化报文
    void initControlSystem(int tag);
    //5.3.4 初始化结果查询报文
    void getInitControlSystem();
    void onGetInitControlSystem(const QByteArray& dat, int tag);

    //5.3.9 工作模式设置报文
    void setWorkMode(qint8 status,int tag);

    //5.3.6 开机/关机报文
    void setPowerOnOff(bool on, int tag);
    //5.3.7 开机/关机结果查询报文
    void getXiaHuaPowerOnOffStatus();
    void getHengYaoPowerOnOffStatus();
    void onGetPowerOnOffStatus(const QByteArray& dat,int tag);

    //5.3.22 仰角设置报文
    void setPitch(qint32 pitch);
    //5.3.21 方位角设置报文
    void setAzimuth(qint32 azimuth);

    //5.3.20 光源控制报文
    void setLight(qint8 addr, qint8 lightvalue,qint8 flash = 6);


    //5.3.10 检视模式参数设置报文
    void setInspect(qint8 addr);

   //5.3.11 零位旋变值及惯性单元偏移量查询报文
    void getZeroOffset(qint8 addr);
    //5.3.13 零位旋变值及惯性单元偏移量平均值报文
    void getZeroOffsetAvg(qint8 addr);

   //5.3.14 标零结果查询报文
    void getCalibStatus(qint8 addr);

  //5.3.16 系统状态查询报文
    void getSystemStatus(int tag);

    void closeAll();

    void sysinfoUpload();

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
    QHash<QString,QVariant> pool;

    int controler_tag;
    int tataireportTimerID;
    int getSystemStatusTimerID;

};

#endif // BACKEND_HPP
