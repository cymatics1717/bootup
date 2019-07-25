#include "udpclient.hpp"

#include <QDateTime>


udpClient::udpClient(QString ip, quint16 port , QObject *parent) :
    QObject(parent),udp(new QUdpSocket(this)),saddr(ip),sport(port)
{

    udp->connectToHost(QHostAddress(ip),port,QIODevice::ReadWrite);
    connect(udp, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &udpClient::onError);
    connect(udp,&QUdpSocket::hostFound,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::connected,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::disconnected,[](){qDebug() << __FUNCTION__;});
    connect(udp,&QUdpSocket::readyRead,this, &udpClient::onReadyRead);

    startTimer(1000);
}

udpClient::~udpClient()
{
//    qDebug() << __FUNCTION__;
}

void udpClient::timerEvent(QTimerEvent *event)
{
    static int cnt = 0;
    auto reply = QString("%1-%2\n").arg(++cnt,5,10,QChar('0')).arg(currentTime());
    udp->writeDatagram(reply.toUtf8(),saddr,sport);
}

void udpClient::onReadyRead()
{
    while (udp->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void udpClient::onError()
{
    qDebug() << __FUNCTION__ << udp->errorString();
}

void udpClient::writing(QByteArray dat)
{
//    QNetworkDatagram gram(dat,QH);
    udp->write(dat);
    qDebug() << __FUNCTION__ ;

}

void udpClient::getSysinfo()
{
    QByteArray data;
    data.append('\x1B');
    writing(data);
}

void udpClient::processTheDatagram(const QNetworkDatagram &gram)
{
    QByteArray dat = gram.data();
    QString id = QString("[%1:%2->%3:%4 %5]")
            .arg(gram.senderAddress().toString())
            .arg(gram.senderPort())
            .arg(gram.destinationAddress().toString())
            .arg(gram.destinationPort())
            .arg(gram.data().size(),4,10);
    qDebug() <<"client recv: " << id << dat;
}
