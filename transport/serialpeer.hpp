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

    void powerOnOff(bool on);
    void DeIcingOnOff(bool on);
    void queryPowerStatus();

private:
    QSerialPort *serial;
};

#endif // SERIALPEER_HPP
