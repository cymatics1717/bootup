#ifndef SERIALPEER_HPP
#define SERIALPEER_HPP

#include <QSerialPort>
#include <QTimerEvent>
#include "common.hpp"

class serialPeer : public QObject
{
    Q_OBJECT
public:
    explicit serialPeer(QString name="/dev/ttytest1", int interval=1000, QObject *parent = nullptr);
    ~serialPeer();

protected:
    void timerEvent(QTimerEvent *event);

signals:

public slots:
    void onReadyRead();
    void writing(QByteArray dat);
    void onError(QSerialPort::SerialPortError);

    void setPowerOnOff(bool on);
    void setDeIcingOnOff(bool on);
    void setVisibleRedLight(bool on);
    void setInfraRedLight(bool on);

    void getPowerStatus();
    void getErrorLightStatus();
    void getErrorLight();

private:
    QSerialPort *serial;
};

#endif // SERIALPEER_HPP
