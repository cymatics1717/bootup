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

protected:
    void timerEvent(QTimerEvent *event) override;

signals:

public slots:
    int loadConfig();
    int saveConfig();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
    void testQML(const QString& data);

//    5.3.1     硬件握手结果查询报文
    void hwHandShake();

    void closeAll();

    void sysinfoUpload();

private:
    void send2XiaHua(const QByteArray &data);
    void send2HengYa(const QByteArray &data);
    void send2TaTai_(const QByteArray &data);
    QString configfile;
    Json::Value root;

    QUdpSocket udp;
    QHash<QString,QPair<QString,quint16>> endpoints;

    int tataireportTimerID;

};

#endif // BACKEND_HPP
