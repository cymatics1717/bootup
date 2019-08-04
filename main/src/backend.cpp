#include "backend.hpp"
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <utility>

static QString makeID(const QNetworkDatagram gram){
    return QString("[%1:%2->%3:%4 %5]")
            .arg(gram.senderAddress().toString())
            .arg(gram.senderPort())
            .arg(gram.destinationAddress().toString())
            .arg(gram.destinationPort())
            .arg(gram.data().size(),4,10);
}

backEnd::backEnd(QString config_file, QObject *parent) : QObject(parent)
  ,configfile(std::move(config_file))
{
    endpoints.insert("local",qMakePair<QString,quint16>("129.168.1.5",1025));
    endpoints.insert("xiahua",qMakePair<QString,quint16>("129.168.1.6",1026));
    endpoints.insert("hengyao",qMakePair<QString,quint16>("129.168.1.7",1027));
    endpoints.insert("tatai",qMakePair<QString,quint16>("129.168.1.1",1021));

    tataireportTimerID = startTimer(1000);
}

QString backEnd::getConfigfile() const
{
    return configfile;
}

void backEnd::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == tataireportTimerID){
        TaTaiReport();
    } else if(event->timerId() == getSystemStatusTimerID){
        getSystemStatus();
    }
}

int backEnd::loadConfig()
{
    try {
        // https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
        std::ifstream infile(configfile.toStdString());
        qDebug() << QFileInfo(configfile).absoluteFilePath();
        infile >> root;
    } catch (const std::exception &e) {
        std::cout << e.what()<<std::endl;
        return -1;
    }

//////////////////////////////////////////////////////////////////
    qDebug() <<"local host:"<< root["endpoints"]["touchpad"]["ip"].asString().c_str();
    qDebug() <<"xiahua server:"<< root["endpoints"]["xiahua"]["ip"].asString().c_str();
    qDebug() <<"hengyao server:"<< root["endpoints"]["hengyao"]["ip"].asString().c_str();
    qDebug() <<"tatai server" <<root["endpoints"]["tatai"]["ip"].asString().c_str();

    {
        Json::Value item = root["endpoints"]["touchpad"];
        endpoints.insert("local",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }
    {
        Json::Value item = root["endpoints"]["xiahua"];
        endpoints.insert("xiahua",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }
    {
        Json::Value item = root["endpoints"]["hengyao"];
        endpoints.insert("hengyao",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }
    {
        Json::Value item = root["endpoints"]["tatai"];
        endpoints.insert("tatai",qMakePair(QString::fromStdString(item["ip"].asString()) ,item["port"].asInt()));
    }

    // init server.

    qInfo()<<"bind status:"<<udp.bind(QHostAddress(endpoints.value("local").first),
                                           endpoints.value("local").second/*,QAbstractSocket::ReuseAddressHint*/);
    connect(&udp,&QUdpSocket::hostFound,[](){qInfo() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::connected,[](){qInfo() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::disconnected,[](){qInfo() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::readyRead,this,&backEnd::onReadyRead);
    connect(&udp, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &backEnd::onError);

    {
        Json::Value item = root["endpoints"]["controller"];
        QString dev = QString::fromStdString(item["device"].asString());
        if(dev.isEmpty()){
            dev = "/dev/ttytest1";
        }
        int interval = item["interval"].asInt();
        if(interval<1 ||interval>10000){
            interval = 200;
        }
        controller = new serialPeer(dev,interval,this);
    }

    controller->setPowerOnOff(true);

    initSystem();

    return 0;
}

int backEnd::saveConfig()
{
    std::ofstream outfile(QString("%1/settings.json").arg(QFileInfo(configfile).path()).toStdString());
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "\t";
//    builder["commentStyle"] = "None";
    builder["commentStyle"] = "All";
    builder["enableYAMLCompatibility"] = true;
    builder["dropNullPlaceholders"] = false;
    builder["useSpecialFloats"] = false;
    root["id"] = "config file";
//    root["id"] = __FUNCTION__;
//    outfile << root;

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &outfile);
//    writer->write(root, &std::cerr);

//    std::string doc = Json::writeString(builder, root);
//    std::cerr << doc << std::endl;

    return 0;
}

void backEnd::onReadyRead()
{
    while(udp.hasPendingDatagrams()){
        QNetworkDatagram gram = udp.receiveDatagram();
        QByteArray dat = gram.data();
        qDebug() <<"recv: " << makeID(gram) << dat/*.toHex('-')*/;
    }
}

void backEnd::onError(QAbstractSocket::SocketError socketError)
{
    qWarning() <<currentTime()<< "--"<<udp.errorString() << sender()<<socketError;
}

void backEnd::testQML(const QString& data)
{
    qInfo() << data;
}

void backEnd::setDateTime(const QDateTime &dt)
{
    qInfo() << dt;
}

void backEnd::TaTaiReport()
{
    //5.2.1 下滑系统状态上报报文 0x01
    QByteArray xiahua;
    xiahua.append(MID_REPORT_XIAHUA);

    send2TaTai_(xiahua);
}

void backEnd::hwHandShake()
{
    QByteArray data;
    data.append(MID_REQUEST_HARDWARE);
//    data.append(currentTime().toUtf8());
//    data.append('\n');

    send2Contrl(data);

    //    send2TaTai_(data);
}


void backEnd::initSystem()
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_INIT);
    send2XiaHua(dat);
//    方位角初始值(4字节)(扩大1000倍,小端传输,有符号数)
    qint32 azimuth = 1000;
//    仰角初始值(4字节)(扩大1000倍,小端传输,有符号数)
    qint32 pitch = 2000;

    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    stream << azimuth << pitch;

    send2Contrl(data);
    QTimer::singleShot(40000 , this, &backEnd::getInitSystemStatus);
}

void backEnd::getInitSystemStatus()
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_INIT_STATUS);
    send2Contrl(dat);
}

void backEnd::setPowerOnOff(bool on)
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_POWER);
    if(on){
        dat.append('\x01');
    } else {
        dat.append('\x02');
    }
    send2Contrl(dat);
    QTimer::singleShot(10000 , this, &backEnd::getPowerOnOffStatus);
}

void backEnd::getPowerOnOffStatus()
{
    qDebug() <<"";
    QByteArray dat;
    dat.append(MID_REQUEST_POWER_STATUS);
    send2Contrl(dat);

    getSystemStatusTimerID = startTimer(500);
}

void backEnd::setWorkMode(qint8 tag)
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_WORKING_MODE);
    // 01:调试模式 10:检视模式 11:正常工作模式
    if(tag == 3){
        dat.append('\x03');
    } else if(tag == 2){
        dat.append('\x02');
    } else if(tag == 1){
        dat.append('\x01');
    }
    send2Contrl(dat);
}

void backEnd::setInspect(qint8 addr)
{
    qDebug() <<"";
    QByteArray dat;
    dat.append(MID_REQUEST_SET_INSPECT_MODE);

//    下滑系统控制器 0x07
//    横摇系统控制器 0x08
    dat.append(addr);
//    幅值(单位:°)
    qint8 amp = 10;
//    周期(大于最小周期值,单位为s)
    qint8 period = 20;
    dat.append(amp);
    dat.append(period);
    if(addr=='\x07'){
        send2XiaHua(dat);
    } else if(addr=='\x08'){
        send2HengYa(dat);
    }
}

void backEnd::getZeroOffset(qint8 addr)
{
    qDebug() <<"";
    QByteArray dat;
    dat.append(MID_REQUEST_ZERO_OFFSET);
    if(addr=='\x07'){
        send2XiaHua(dat);
    } else if(addr=='\x08'){
        send2HengYa(dat);
    }
}

void backEnd::getZeroOffsetAvg(qint8 addr)
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_ZERO_OFFSET_AVG);
    if(addr=='\x07'|| addr=='\x08'){
        dat.append(addr);
    }
    //平均值(4字节) (惯性单元偏移量平均值扩大1000倍,小端传输,有符号数)

    qint32 avg = 2000;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    stream  << avg;

    if(addr=='\x07'){
        send2XiaHua(data);
    } else if(addr=='\x08'){
        send2HengYa(data);
    }
}

void backEnd::getCalibStatus(qint8 addr)
{
    qDebug() <<"";
    QByteArray dat;
    dat.append(MID_REQUEST_CALIB_STATUS);
    if(addr=='\x07'){
        send2XiaHua(dat);
    } else if(addr=='\x08'){
        send2HengYa(dat);
    }
}

void backEnd::getSystemStatus()
{
    qDebug() <<"";
    QByteArray dat;
    dat.append(MID_REQUEST_SYSTEM_STATUS);
    send2Contrl(dat);
}

void backEnd::setLight(qint8 addr)
{
    qDebug() <<"";
    QByteArray dat;
    dat.append(MID_REQUEST_LIGHT_CONTROL);
    if(addr=='\x07'){
        //光强等级设置 光强等级0:00000000 光强等级1:0000
        dat.append('\x22');
        // 横摇灯杆开关设置 开:01关:10
        if(true){
            dat.append('\x40');
        } else {
            dat.append('\x80');
        }
        //      左固定灯黄灯开关设置 开:01关:10  左固定灯红灯开关设置 开:01关:10 右固定灯黄灯开关设置 开:01关:10  右固定灯红灯开关设置 开:01关:10
        dat.append('\x40');
        dat.append('\x02');

        send2XiaHua(dat);
    } else if(addr=='\x08'){
        //光强等级设置 光强等级0:00000000 光强等级1:0000
        dat.append('\x22');
        //      闪光状态设置(三闪:11开:01单闪:10关:10不闪:01)   下滑光源开关设置 开:01 关:10
        dat.append('\x42');

        send2HengYa(dat);
    }
}

void backEnd::setAzimuth()
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_AZIMUTH);
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    qint32 azimuth =1000;
    stream << azimuth;

    send2XiaHua(data);
}

void backEnd::setPitch()
{
    qDebug() <<"";
    QByteArray dat,data;
    dat.append(MID_REQUEST_PITCH);
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(dat,dat.size());
    qint32 pitch =1000;
    stream << pitch;

    send2XiaHua(data);
}


void backEnd::closeAll()
{

}

void backEnd::sysinfoUpload()
{
    QByteArray data;
    data.append(MID_REQUEST_HARDWARE);
//    data.append(currentTime().toUtf8());
//    data.append('\n');

    send2TaTai_(data);
}

void backEnd::send2Contrl(const QByteArray &data)
{
    send2XiaHua(data);
    send2HengYa(data);
}

void backEnd::send2XiaHua(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("xiahua").first),endpoints.value("xiahua").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    udp.flush();
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

void backEnd::send2HengYa(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("hengyao").first),endpoints.value("hengyao").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    udp.flush();
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

void backEnd::send2TaTai_(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("tatai").first),endpoints.value("tatai").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    udp.flush();
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

