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
    queryPowerStatus();
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
    stream << CHECKSUM::crc32(data);

    qDebug() <<"sent:"<< data.toHex('-');
    serial->write(data);
}

void serialPeer::onError(QSerialPort::SerialPortError)
{
    qDebug() << serial->errorString();
}

void serialPeer::powerOnOff(bool on)
{
    QByteArray data;
    data.append(qint8(0x0D));
    data.append(qint8(0x0F));
    data.append(qint8(0x00));
    data.append(qint8(0x20));
    data.append(qint8(0x00));
    if(on){
        data.append(qint8(0x03));
        data.append(qint8(0x01));
        data.append(qint8(0x07));
    } else {
        data.append(qint8(0x04));
        data.append(qint8(0x01));
        data.append(qint8(0x00));
    }

    writing(data);
}

void serialPeer::DeIcingOnOff(bool on)
{
    QByteArray data;
    data.append(qint8(0x0D));
    data.append(qint8(0x05));
    data.append(qint8(0x00));
    data.append(qint8(0x23));
    if(on){
        data.append(qint8(0xFF));
        data.append(qint8(0x00));
    } else {
        data.append(qint8(0x00));
        data.append(qint8(0x00));
    }
    writing(data);
}

void serialPeer::queryPowerStatus()
{
    QByteArray data;
    data.append(qint8(0x0D));
    data.append(qint8(0x01));
    data.append(qint8(0x00));
    data.append(qint8(0x20));
    data.append(qint8(0x00));
    data.append(qint8(0x04));

    writing(data);
}
