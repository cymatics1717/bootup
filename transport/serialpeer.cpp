#include "serialpeer.hpp"
#include <QDebug>
#include <QDateTime>

static QString currentTime(){
    return QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz");
}

serialPeer::serialPeer(QString name, int interval, QObject *parent) : QObject(parent)
  ,serial(new QSerialPort(name,this))
{
    qDebug() << name;
//    serial->setBaudRate(QSerialPort::Baud9600);
    connect(serial, &QSerialPort::readyRead, this, &serialPeer::onReadyRead);
    connect(serial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error),this, &serialPeer::onError);

    if(serial->open(QIODevice::ReadWrite)){
        qDebug() << QString("opened %1:%2").arg(serial->portName()).arg(serial->baudRate());

    } else {
        qDebug() << QString("open failed %1:%2").arg(serial->error()).arg(serial->errorString());
    }

    startTimer(interval);
}

serialPeer::~serialPeer()
{
    qDebug() <<"";
}

void serialPeer::timerEvent(QTimerEvent *event)
{
    QString data = QString("%1--%2").arg(serial->portName()).arg(currentTime());
//    qDebug() <<  stamp;
    serial->write(data.toUtf8());
}

void serialPeer::onReadyRead()
{
    qDebug() << serial->readAll();
}

void serialPeer::onError(QSerialPort::SerialPortError)
{
    qDebug() << serial->errorString();
}
