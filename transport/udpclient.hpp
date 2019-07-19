#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>

class udpClient : public QObject
{
    Q_OBJECT
public:
    explicit udpClient(QString ip="127.0.0.1", quint16 port =10000, QObject *parent = nullptr);
    ~udpClient();
signals:
protected:
    void timerEvent(QTimerEvent *event);
public slots:
    void onReadyRead();
    void onError();
private:
    void processTheDatagram(const QNetworkDatagram &gram);
    QUdpSocket *udp;

    QHostAddress saddr;
    quint16 sport;
};

#endif // UDPCLIENT_HPP