#include "serialother.hpp"
#include <QDebug>
#include <QDateTime>
#include <QDataStream>


serialOther::serialOther(const QString& name, int interval, QObject *parent) : QObject(parent)
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

void serialOther::timerEvent(QTimerEvent * /*event*/)
{
//    QString data = QString("%1--%2").arg(serial->portName(),currentTime());
//    qDebug() <<  stamp;
//    serial->write(data.toUtf8());
}

void serialOther::onReadyRead()
{
    auto reply = serial->readAll();
    qDebug() <<"recv:"<< reply.toHex('-');
    if(reply.size()>0){
        if(reply.at(0)=='\x0D' && reply.at(1)=='\x01'){
            replyPowerStatus();
            reply.remove(0,10);
        }
    }

    if(reply.size()>0){
        if(reply.at(0)=='\x0B' && reply.at(1)=='\x03'){
            replyLightValue();
            reply.remove(0,10);
        }
    }

    if(reply.size()>0){
        if(reply.at(0)=='\x0B' && reply.at(1)=='\x03'){
            replyLightEStatus();
            reply.remove(0,10);
        }
    }

//    else if(reply.at(0)=='\x0B' && reply.at(1)=='\x03'){
//        replyLightValue();
//    } else if(reply.at(0)=='\x0B' && reply.at(1)=='\x03'){
//        replyLightEStatus();
//    }
}

void serialOther::writing(const QByteArray& dat)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.writeRawData(dat,dat.size());
    stream << mmmcrc32(data);

    serial->write(data);
    serial->flush();
//    serial->waitForBytesWritten(10);
}

void serialOther::replyPowerStatus()
{
    QByteArray data;
    data.append('\x0D');
    data.append('\x01');
    data.append('\x01');
    //全开
    data.append('\x07');

    qDebug() << QString(40,'-') <<"sent:"<< data.toHex('-');
    writing(data);
}

void serialOther::replyLightValue()
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x03');
    data.append('\x04');
    //故障警示灯(红外)光强
    qint8 v1 = 7;
    data.append(v1);
    //故障警示灯(红外) 开关状态
    data.append('\x01');
    //故障警示灯(红灯)光强
    qint8 v2 = 7;
    data.append(v2);
    //故障警示灯(红灯) 开关状态
    data.append('\x01');

    qDebug() << QString(40,'-') <<"sent:"<< data.toHex('-');

    writing(data);
}

void serialOther::replyLightEStatus()
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x03');
    data.append('\x04');

    data.append('\x01');
    data.append('\x01');
    data.append('\x01');
    data.append('\x01');

    qDebug() << QString(40,'-') <<"sent:"<< data.toHex('-');

    writing(data);
}

void serialOther::onError(QSerialPort::SerialPortError)
{
    qDebug() << serial->errorString();
}
