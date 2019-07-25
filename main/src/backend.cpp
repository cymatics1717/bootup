#include "backend.hpp"
#include <QDebug>
#include <QFileInfo>

backEnd::backEnd(QString config_file, QObject *parent) : QObject(parent)
  ,configfile(config_file),localServer(nullptr)
{
    endpoints.insert("local",qMakePair<QString,quint16>("129.168.1.5",1025));
    endpoints.insert("xiahua",qMakePair<QString,quint16>("129.168.1.6",1026));
    endpoints.insert("hengyao",qMakePair<QString,quint16>("129.168.1.7",1027));
    endpoints.insert("tatai",qMakePair<QString,quint16>("129.168.1.1",1021));
}

QString backEnd::getConfigfile() const
{
    return configfile;
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
        localServer = new udpServer(QString::fromStdString(item["ip"].asString()),quint16(item["port"].asInt()),this);
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

void backEnd::testQML(QString data)
{
    qDebug() << data;
}

void backEnd::hwHandShake()
{
    QByteArray data;
    data.append(MID_REQUEST_HARDWARE);
    data.append(currentTime().toUtf8());
    data.append(currentTime().toUtf8());
    data.append(currentTime().toUtf8());
    data.append('\n');

    writeToXiaHua(data);
    writeToHengYao(data);
}

void backEnd::writeToXiaHua(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("xiahua").first),endpoints.value("xiahua").second);

    gram.setData(data);
    uwriter.writeDatagram(gram);
}

void backEnd::writeToHengYao(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("hengyao").first),endpoints.value("hengyao").second);

    gram.setData(data);
    uwriter.writeDatagram(gram);
}

void backEnd::writeToTaTai(const QByteArray &data)
{
    QNetworkDatagram gram;
    gram.setSender(QHostAddress(endpoints.value("local").first),endpoints.value("local").second);
    gram.setDestination(QHostAddress(endpoints.value("tatai").first),endpoints.value("tatai").second);

    gram.setData(data);
    uwriter.writeDatagram(gram);
}

