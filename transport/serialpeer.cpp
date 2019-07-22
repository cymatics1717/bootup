#include "serialpeer.hpp"
#include <QDebug>
#include <QDateTime>
#include <QDataStream>

static QString currentTime(){
    return QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz");
}

serialPeer::serialPeer(QString name, int interval, QObject *parent) : QObject(parent)
  ,serial(new QSerialPort(name,this))
{
    qDebug() << name;
    serial->setBaudRate(QSerialPort::Baud9600);
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
//    serial->write(data.toUtf8());
//    powerOnOff(true);
//    powerOnOff(false);
//    DeIcingOnOff(true);
    getPowerStatus();
}

void serialPeer::onReadyRead()
{
    qDebug() <<"recv:"<< serial->readAll() ;
}

void serialPeer::writing(QByteArray dat)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.writeRawData(dat,dat.size());
    stream << mmmcrc32(data);

    qDebug() <<"sent:"<< data.toHex('-');
    serial->write(data);
}

void serialPeer::onError(QSerialPort::SerialPortError)
{
    qDebug() << serial->errorString();
}

void serialPeer::setPowerOnOff(bool on)
{
    QByteArray data;
    data.append('\x0D');
    data.append('\x0F');
    data.append('\x00');
    data.append('\x20');
    data.append('\x00');

    if(on){
        data.append('\x03');
        data.append('\x01');
        data.append('\x07');
    } else {
        data.append('\x04');
        data.append('\x01');
        data.append('\x00');
    }

    writing(data);
}

void serialPeer::setDeIcingOnOff(bool on)
{
    QByteArray data;
    data.append('\x0D');
    data.append('\x05');
    data.append('\x00');
    data.append('\x23');
    if(on){
        data.append('\xFF');
        data.append('\x00');
    } else {
        data.append('\x00');
        data.append('\x00');
    }
    writing(data);
}

void serialPeer::setVisibleRedLight(bool on)
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x06');
    data.append('\x00');
    data.append('\x01');
//    data.append('\x00');
    if(on){
        data.append('\x01');
    } else {
        data.append('\x00');
    }
    writing(data);
}

void serialPeer::setInfraRedLight(bool on)
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x06');
    data.append('\x00');
    data.append('\x02');
//    data.append('\x00');
    if(on){
        data.append('\x01');
    } else {
        data.append('\x00');
    }
    writing(data);
}


void serialPeer::getPowerStatus()
{
    QByteArray data;
    data.append('\x0D');
    data.append('\x01');
    data.append('\x00');
    data.append('\x20');
    data.append('\x00');
    data.append('\x04');
    writing(data);
}

void serialPeer::getErrorLightStatus()
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x03');
    data.append('\x00');
    data.append('\x03');
    data.append('\x00');
    data.append('\x02');

    writing(data);
}

void serialPeer::getErrorLight()
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x03');
    data.append('\x00');
    data.append('\x01');
    data.append('\x00');
    data.append('\x02');

    writing(data);
}

