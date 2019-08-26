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
    /**
     * @brief coreInfo::*
     * @param data 系统控制器返回的数据
     * @param tag 下滑：0；横摇：1
     */
    void parseHWHandShakeStatus(const QByteArray &dat, int tag);
    void parseInitSystemStatus(const QByteArray& dat, int tag);
    void parsePowerOnOffStatus(const QByteArray& dat,int tag);

    void parseAlarmStatus(const QByteArray &data, int tag);
    void parseBreakdownStatus(const QByteArray &data, int tag);
    void parseSystemStatus(const QByteArray &data, int tag);
    void parseLimitAngle(const QByteArray &data, int tag);
    void parseCalibStatusReply(const QByteArray &data, int tag);
    void parseZeroOffsetReply(const QByteArray &data, int tag);

    /**
     * @brief backEnd::playAbnormalSound
     * @param abnormal 故障音效:01, 报警音效:其他
     */
    void playAbnormalSound(int abnormal);
    void matchWarningTable(const QByteArray &data, int tag);
    void matchBreakdownTable(const QByteArray &data, int tag);

};

#endif // COREINFO_HPP
