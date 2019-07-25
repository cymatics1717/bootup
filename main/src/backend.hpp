#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QUdpSocket>
#include <QNetworkDatagram>

#include "serialpeer.hpp"

#include <iostream>
#include <fstream>
#include "json/json.h"

class backEnd : public QObject
{
    Q_OBJECT
public:
    explicit backEnd(QString config_file, QObject *parent = nullptr);

    QString getConfigfile() const;
signals:

public slots:
    int loadConfig();

    int saveConfig();

    void testQML(QString data);

//    5.3.1     硬件握手结果查询报文
    void hwHandShake();

private:
    void writeToXiaHua(const QByteArray &data);
    void writeToHengYao(const QByteArray &data);
    void writeToTaTai(const QByteArray &data);
    QString configfile;
    Json::Value root;

    QUdpSocket udp;
    QHash<QString,QPair<QString,quint16>> endpoints;
};

#endif // BACKEND_HPP
