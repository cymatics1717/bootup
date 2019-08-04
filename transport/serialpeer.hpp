#ifndef SERIALPEER_HPP
#define SERIALPEER_HPP

#include <QSerialPort>
#include <QSet>
#include <QTimerEvent>
#include "common.hpp"

class serialPeer : public QObject
{
    Q_OBJECT
public:
    explicit serialPeer(const QString& name="/dev/ttytest1", int interval=1000, QObject *parent = nullptr);
    ~serialPeer() override;

protected:
    void timerEvent(QTimerEvent *event) override;

signals:

public slots:
    void onReadyRead();
    void writing(const QByteArray& dat);
    void onError(QSerialPort::SerialPortError);

    // 3.1.1 系统上电/断电报文
    void setPowerOnOff(bool on);
    //3.1.2 除冰装置开/关机报文
    void setDeIcingOnOff(bool on);
   //3.1.3 系统开关状态查询报文
    void getPowerStatus();
    void onGetPowerStatus(const QByteArray& dat);
   //3.1.5  故障警示灯(红灯)开/关机、调光报文
    void setVisibleRedLight(qint8 value, bool on);
    //3.1.6  故障警示灯(红外)开/关机、调光报文
    void setInfraRedLight(bool on);
    //3.1.7 故障警示灯开关及光强状态查询报文
    void getLightPowerAndLightValue();
    void onGetLightPowerAndLightValue(const QByteArray& dat);
    //3.1.9 故障警示灯故障状态查询报文
    void getLightErrorStatus();
    void onGetLightErrorStatus(const QByteArray& dat);
private:
    QSerialPort *serial;

    int timerID_PowerStatus;
    int timerID_LightPower;
    int timerID_LightErrorStatus;
};

#endif // SERIALPEER_HPP
