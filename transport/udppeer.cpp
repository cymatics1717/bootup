#include "udppeer.hpp"

#include <QDateTime>

static QString currentTime(){
    return QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz");
}

static QString makeID(const QNetworkDatagram gram){
    return QString("[%1:%2->%3:%4 %5]")
            .arg(gram.senderAddress().toString())
            .arg(gram.senderPort())
            .arg(gram.destinationAddress().toString())
            .arg(gram.destinationPort())
            .arg(gram.data().size(),4,10);
}

udpPeer::udpPeer(const QString& ip, quint16 port, QObject *parent) : QObject(parent),udp(new QUdpSocket(this))
{
    qDebug()<<"bind status:"<<udp->bind(QHostAddress(ip), port/*,QAbstractSocket::ReuseAddressHint*/);
    connect(udp, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &udpPeer::onError);
    connect(udp,&QUdpSocket::hostFound,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::connected,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::disconnected,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::readyRead,this, &udpPeer::readPendingDatagrams);

}

void udpPeer::timerEvent(QTimerEvent * /*event*/)
{
    static int cnt = 0;
    cnt++;

}

void udpPeer::readPendingDatagrams()
{
    while (udp->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void udpPeer::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() <<currentTime()<< "----"<<udp->errorString() << sender()<<socketError;
}

void udpPeer::processTheDatagram(const QNetworkDatagram &gram)
{
    QByteArray dat = gram.data();
    qDebug() <<"server recv: " << makeID(gram) << dat;

    udp->writeDatagram(gram.makeReply(dat));

//    int tmp = QString(dat.trimmed()).toInt();
//    emit incoming(tmp);


}

