#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QAbstractSocket>
class udpServer : public QObject
{
    Q_OBJECT
public:
    explicit udpServer(QString ip="127.0.0.1", quint16 port =10000, QObject *parent = nullptr);

signals:
    void incoming(int);
public slots:
    void readPendingDatagrams();
private:
    void processTheDatagram(const QNetworkDatagram &);
    QUdpSocket *udp;
};

#endif // UDPSERVER_H
