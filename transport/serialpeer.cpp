#include "serialpeer.hpp"
#include <QDebug>
#include <QDateTime>
#include <QDataStream>
#include <QTimer>

serialPeer::serialPeer(const QString& name, int interval, QObject *parent) : QObject(parent)
  ,serial(new QSerialPort(name,this))
{
    qInfo() << name;
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);


    connect(serial, &QSerialPort::readyRead, this, &serialPeer::onReadyRead);
    connect(serial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error),this, &serialPeer::onError);

    if(serial->open(QIODevice::ReadWrite)){
        qInfo() << QString("opened %1:%2").arg(serial->portName()).arg(serial->baudRate());

    } else {
        qWarning() << QString("open failed %1:%2").arg(serial->error()).arg(serial->errorString());
    }

    timerID_PowerStatus = startTimer(interval);

//    QTimer::singleShot(interval/3 , this, [=](){
//        timerID_LightPower = startTimer(interval);
//    });
//    QTimer::singleShot(interval*2/3, this, [=](){
//        timerID_LightEStatus = startTimer(interval);
//    });

}

serialPeer::~serialPeer()
{
    qInfo() <<"";
}

void serialPeer::timerEvent(QTimerEvent */*event*/)
{
    QString data = QString("%1--%2").arg(serial->portName()).arg(currentTime());

    getPowerStatus();
    getLightValue();
    getLightEStatus();
//    if(event->timerId() == timerID_PowerStatus ){
//        getPowerStatus();
//        qInfo() <<"timerID_PowerStatus = " << timerID_PowerStatus;
//    } else if(event->timerId() == timerID_LightPower ){
//        qInfo() <<"timerID_LightPower = " << timerID_LightPower;
//        getLightValue();
//    } else if(event->timerId() == timerID_LightEStatus ){
//        getLightEStatus();
//        qInfo() <<"timerID_LightEStatus = " << timerID_LightEStatus;
//    }
}

void serialPeer::onReadyRead()
{
    static int status = 0;
    auto reply = serial->readAll();
    qDebug() <<"recv:"<<reply.size()<< reply.toHex('-');

    if(reply.size()>=6 && reply.at(0)=='\x0D' && reply.at(1)=='\x01'){
        onGetPowerStatus(reply.left(8));
        reply.remove(0,8);
        status = 1;
        qDebug() <<"+++++++++++"<<reply.size()<< reply.toHex('-');
    }

    if(reply.size()>=11 &&reply.at(0)=='\x0B' && reply.at(1)=='\x03'){
        if(status ==1 ){
            onGetLightValue(reply.left(11));
            status = 0;
            reply.remove(0,11);
        } else {
            status =2;
        }
        qDebug() <<"+++++++++++"<<reply.size()<< reply.toHex('-');
    }

    if(reply.size()>=11 &&reply.at(0)=='\x0B' && reply.at(1)=='\x03'){
        onGetLightEStatus(reply.left(11));
        reply.remove(0,11);
        status =0;
        qDebug() <<"+++++++++++"<<reply.size()<< reply.toHex('-');
    }
}

void serialPeer::writing(const QByteArray& dat)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    stream << mmmcrc16(data);

    qInfo() << data.toHex('-');

    serial->write(data);
    serial->flush();
//    serial->waitForBytesWritten(10);
}

void serialPeer::onError(QSerialPort::SerialPortError)
{
    qWarning() << serial->errorString();
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
        data.append('\x04');
        data.append('\x01');
        data.append('\x0F');
    } else {
        data.append('\x04');
        data.append('\x01');
        data.append('\x00');
    }

    qInfo() <<"sent:"<< data.toHex('-');
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
    qInfo() <<"sent:"<< data.toHex('-');
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

void serialPeer::onGetPowerStatus(const QByteArray& dat)
{

    bool check = checkEquality(dat);
    qDebug() << dat.toHex('-') << check;
    if(check){
        //除冰装置电源开关状态
        qDebug() << "除冰装置电源开关状态:" << ((dat.at(3)>>3) & '\x01');
        //下滑指示器电源开关状态
        qDebug() << "下滑指示器电源开关状态:" << ((dat.at(3)>>2) & '\x01');
        //横摇指示器电源开关状态
        qDebug() << "横摇指示器电源开关状态:" << ((dat.at(3)>>1) & '\x01');
        //故障警示灯电源开关状态
        qDebug() << "故障警示灯电源开关状态:" << ((dat.at(3)>>0) & '\x01');
    }
}

void serialPeer::setVisibleRedLight(qint8 value, bool on)
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x06');
    data.append('\x00');
    data.append('\x01');
    data.append(value);

    if(on){
        data.append('\x01');
    } else {
        data.append('\x00');
    }
    qInfo() <<"sent:"<< data.toHex('-');
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
    qInfo() <<"sent:"<< data.toHex('-');
    writing(data);
}

void serialPeer::getLightValue()
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x03');
    data.append('\x00');
    data.append('\x01');
    data.append('\x00');
    data.append('\x02');
    qInfo() <<"sent:"<< data.toHex('-');

    writing(data);
}

void serialPeer::onGetLightValue(const QByteArray& dat)
{
    bool check = checkEquality(dat);
    qDebug() << dat.toHex('-') << check;
    if(check){
        //故障警示灯(红外)光强
        qDebug() << "故障警示灯(红外)光强 :" << (dat.at(3) & '\xFF');
        //故障警示灯(红外)再开关
        qDebug() << "故障警示灯(红外)开关:" << (dat.at(4) & '\x01');
        //故障警示灯(红灯)光强
        qDebug() << "故障警示灯(红灯)光强:" << (dat.at(5) & '\xFF') ;
        //故障警示灯(红灯)开关
        qDebug() << "故障警示灯(红灯)开关:" << (dat.at(6) & '\x01');
    }
}

void serialPeer::getLightEStatus()
{
    QByteArray data;
    data.append('\x0B');
    data.append('\x03');
    data.append('\x00');
    data.append('\x03');
    data.append('\x00');
    data.append('\x02');

    qInfo() <<"sent:"<< data.toHex('-');
    writing(data);
}

void serialPeer::onGetLightEStatus(const QByteArray& dat)
{
    bool check = checkEquality(dat);
    qDebug() << dat.toHex('-') << check;
    if(check){
        // 红灯短路故障
        qDebug() << "红灯短路故障:" << (dat.at(3) & '\x01');
        //红灯断路故障
        qDebug() << "红灯断路故障:" << (dat.at(4) & '\x01');
        //红外灯短路故障
        qDebug() << "红外灯短路故障:" << (dat.at(5) & '\x01');
        //红外灯断路故障
        qDebug() << "红外灯断路故障:" << (dat.at(6) & '\x01');
    }
}

