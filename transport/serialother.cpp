#include "serialother.hpp"
#include <QDebug>
#include <QDateTime>

static QString currentTime(){
    return QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz");
}

serialOther::serialOther(QString name, int interval, QObject *parent) : QObject(parent)
  ,serial(new QSerialPort(name,this))
{
    qDebug() << name;
    serial->setBaudRate(QSerialPort::Baud9600);
    connect(serial, &QSerialPort::readyRead, this, &serialOther::onReadyRead);
    connect(serial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error),this, &serialOther::onError);

    if(serial->open(QIODevice::ReadWrite)){
        qDebug() << QString("opened %1:%2").arg(serial->portName()).arg(serial->baudRate());

    } else {
        qDebug() << QString("open failed %1:%2").arg(serial->error()).arg(serial->errorString());
    }

    startTimer(interval);
}

void serialOther::timerEvent(QTimerEvent *event)
{
    QString data = QString("%1--%2").arg(serial->portName()).arg(currentTime());
//    qDebug() <<  stamp;
//    serial->write(data.toUtf8());
}

void serialOther::onReadyRead()
{
    qDebug() <<"recv:"<< serial->readAll().toHex('-');
}

void serialOther::onError(QSerialPort::SerialPortError)
{
    qDebug() << serial->errorString();
}
