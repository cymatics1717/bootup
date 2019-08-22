#ifndef COREINFO_HPP
#define COREINFO_HPP

#include <QObject>

class coreInfo : public QObject
{
    Q_OBJECT
public:
    explicit coreInfo(QObject *parent = nullptr);

signals:

public slots:
    void parseHWHandShakeStatus(const QByteArray &dat, int tag);
    void parseInitSystemStatus(const QByteArray& dat, int tag);
    void parsePowerOnOffStatus(const QByteArray& dat,int tag);

    void parseAlarmStatus(const QByteArray &data, int tag);
    void parseBreakdownStatus(const QByteArray &data, int tag);
    void parseSystemStatus(const QByteArray &data, int tag);
    void parseLimitAngle(const QByteArray &data, int tag);
};

#endif // COREINFO_HPP
