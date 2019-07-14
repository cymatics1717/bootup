#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <map>
#include <QTimerEvent>
class udpServer : public QObject
{
    Q_OBJECT
public:
    explicit udpServer(QString ip="127.0.0.1", quint16 port =10000, QObject *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event);
signals:
    void incoming(int);
public slots:
    void readPendingDatagrams();
    void onError(QAbstractSocket::SocketError socketError);
private:
    void processTheDatagram(const QNetworkDatagram &);
    QUdpSocket *udp;

    std::map<quint16,QHostAddress> peers;
    std::map<int,int> timers;
};

#endif // UDPSERVER_H
