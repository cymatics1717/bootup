#include "udpserver.h"
#include <QDateTime>
#include <QFile>
#include <QNetworkDatagram>

udpServer::udpServer(QString ip, quint16 port, QObject *parent) : QObject(parent),udp(new QUdpSocket(this))
{
    qDebug()<<"bind status:"<<udp->bind(QHostAddress(ip), port/*,QAbstractSocket::ReuseAddressHint*/);
    connect(udp, SIGNAL(readyRead()),SLOT(readPendingDatagrams()));
}

void udpServer::readPendingDatagrams()
{
    while (udp->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void udpServer::processTheDatagram(const QNetworkDatagram &gram)
{
    QByteArray dat = gram.data();
    QString id = QString("[%1:%2->%3:%4 %5]")
            .arg(gram.senderAddress().toString())
            .arg(gram.senderPort())
            .arg(gram.destinationAddress().toString())
            .arg(gram.destinationPort())
            .arg(gram.data().size(),4,10);
    qDebug() <<"server recv: " << id << dat;

    int tmp = QString(dat.trimmed()).toInt();
    emit incoming(tmp);
}

