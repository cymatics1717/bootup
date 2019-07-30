#include "backend.hpp"
#include <QDebug>
#include <QFileInfo>
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
//        sysinfoUpload();
        TaTaiReport();
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

    qDebug()<<"bind status:"<<udp.bind(QHostAddress(endpoints.value("local").first),
                                           endpoints.value("local").second/*,QAbstractSocket::ReuseAddressHint*/);
    connect(&udp,&QUdpSocket::hostFound,[](){qDebug() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::connected,[](){qDebug() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::disconnected,[](){qDebug() << __FUNCTION__;});
    connect(&udp,&QUdpSocket::readyRead,this,&backEnd::onReadyRead);
    connect(&udp, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &backEnd::onError);

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
    root["id"] = __FUNCTION__;
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
    qDebug() <<currentTime()<< "--"<<udp.errorString() << sender()<<socketError;
}

void backEnd::testQML(const QString& data)
{
    qDebug() << data;
}

void backEnd::TaTaiReport()
{
    //5.2.1 下滑系统状态上报报文 0x01
    QByteArray xiahua;
    xiahua.append(MID_REPORT_XIAHUA);

    send2TaTai_(xiahua);
    //5.2.2 横摇系统状态上报报文
    QByteArray heng;
    heng.append(MID_REPORT_HENGYAO);

    send2TaTai_(heng);
    //5.2.3 故障警示灯状态上报报文
    QByteArray light;
    light.append(MID_REPORT_WARNING_LIGHT);

    send2TaTai_(light);
}

void backEnd::hwHandShake()
{
    QByteArray data;
    data.append(MID_REQUEST_HARDWARE);
//    data.append(currentTime().toUtf8());
//    data.append('\n');

    send2XiaHua(data);
    send2HengYa(data);
    send2TaTai_(data);
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

void backEnd::send2XiaHua(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("xiahua").first),endpoints.value("xiahua").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

void backEnd::send2HengYa(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("hengyao").first),endpoints.value("hengyao").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

void backEnd::send2TaTai_(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("tatai").first),endpoints.value("tatai").second);

    gram.setData(data);
    udp.writeDatagram(gram);
    qDebug() <<"send: " << makeID(gram) << data/*.toHex('-')*/;
}

