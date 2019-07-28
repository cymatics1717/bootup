#ifndef UDPPEER_H
#define UDPPEER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <map>
#include <QTimerEvent>
class udpPeer : public QObject
{
    Q_OBJECT
public:
    explicit udpPeer(const QString& ip="127.0.0.1", quint16 port =10000, QObject *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event) override;
signals:
    void incoming(int udata);
public slots:
    void readPendingDatagrams();
    void onError(QAbstractSocket::SocketError socketError);

private:
    void processTheDatagram(const QNetworkDatagram &);
    QUdpSocket *udp;

};

#endif // UDPPEER_H
