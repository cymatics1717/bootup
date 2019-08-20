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
    void parseSystemStatus(const QByteArray &data, int tag);

};

#endif // COREINFO_HPP
