#ifndef SERIALPEER_HPP
#define SERIALPEER_HPP

#include <QObject>
#include <QSerialPort>
#include <QTimerEvent>

class serialPeer : public QObject
{
    Q_OBJECT
public:
    explicit serialPeer(QString name="/dev/ttytest1", int interval=1000, QObject *parent = nullptr);
    ~serialPeer();

protected:
    void timerEvent(QTimerEvent *event);

signals:

public slots:
    void onReadyRead();
    void onError(QSerialPort::SerialPortError);
private:
    QSerialPort *serial;
};

#endif // SERIALPEER_HPP
