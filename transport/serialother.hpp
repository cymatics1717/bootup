#ifndef SERIALOTHER_HPP
#define SERIALOTHER_HPP

#include <QSerialPort>
#include <QTimerEvent>
#include "common.hpp"

class serialOther : public QObject
{
    Q_OBJECT
public:
    explicit serialOther(QString name="/dev/ttytest2", int interval=1000, QObject *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event);

signals:

public slots:
    void onReadyRead();
    void onError(QSerialPort::SerialPortError);


private:
    QSerialPort *serial;
};

#endif // SERIALOTHER_HPP
