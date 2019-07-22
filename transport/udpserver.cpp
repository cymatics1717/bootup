#include "udpserver.hpp"

#include <QDateTime>

static QString currentTime(){
    return QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz");
}

udpServer::udpServer(QString ip, quint16 port, QObject *parent) : QObject(parent),udp(new QUdpSocket(this))
{
    qDebug()<<"bind status:"<<udp->bind(QHostAddress(ip), port/*,QAbstractSocket::ReuseAddressHint*/);
    connect(udp, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &udpServer::onError);
    connect(udp,&QUdpSocket::hostFound,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::connected,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::disconnected,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::readyRead,this, &udpServer::readPendingDatagrams);

    {
        int inteval = 1000;
        timers.emplace(inteval,startTimer(inteval));
    }

    {
        int inteval = 200;
        timers.emplace(inteval,startTimer(inteval));
    }
}

void udpServer::timerEvent(QTimerEvent *event)
{
    static int cnt = 0;
    cnt++;
//    if(event->timerId()==timers.at(200))
//    for(auto peer:peers){
//        auto reply = QString("%1-%2\n").arg(cnt,5,10,QChar('0')).arg(currentTime());
//        udp->writeDatagram(reply.toUtf8(), peer.second, peer.first);
//    }

    {
        auto reply = QString("%1-%2\n").arg(100*cnt,5,10,QChar('0')).arg(currentTime());
        udp->writeDatagram(reply.toUtf8(), QHostAddress("127.0.0.1"), 10001);
    }
    {
        auto reply = QString("%1-%2\n").arg(10000*cnt,5,10,QChar('0')).arg(currentTime());
        udp->writeDatagram(reply.toUtf8(), QHostAddress("127.0.0.1"), 10002);
    }
}

void udpServer::readPendingDatagrams()
{
    while (udp->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void udpServer::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() <<currentTime()<< "----"<<udp->errorString() << sender()<<socketError;
    static int cnt = 0;
    for(auto peer:peers){
        auto reply = QString("%1-%2\n").arg(++cnt,5,10,QChar('0')).arg(currentTime());
        udp->connectToHost(peer.second, peer.first);
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

    peers.emplace(quint16(gram.senderPort()),gram.senderAddress());

    int tmp = QString(dat.trimmed()).toInt();
    emit incoming(tmp);
}

