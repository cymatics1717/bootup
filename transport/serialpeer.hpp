#ifndef SERIALPEER_HPP
#define SERIALPEER_HPP

#include <QSerialPort>
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
