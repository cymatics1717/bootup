#ifndef SERIALOTHER_HPP
#define SERIALOTHER_HPP

#include <QSerialPort>
#include <QTimerEvent>
#include "common.hpp"

class serialOther : public QObject
{
    Q_OBJECT
public:
    explicit serialOther(const QString& name="/dev/ttytest2", int interval=1000, QObject *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event) override;

signals:

public slots:
    void onReadyRead();
    void onError(QSerialPort::SerialPortError);

    void writing(const QByteArray& dat);

    //3.1.4 系统开关状态返回报文
     void replyPowerStatus();
     //3.1.8 故障警示灯开关及光强状态返回报文
     void replyLightValue();
     //3.1.10 故障警示灯故障状态返回报文
     void replyLightEStatus();
private:
    QSerialPort *serial;
};

#endif // SERIALOTHER_HPP
