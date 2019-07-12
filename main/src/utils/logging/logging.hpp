#ifndef LOGGING_HPP
#define LOGGING_HPP

#define LOGSIZE 10 * 1024 * 1024
#define LOGFILES 100

#include <QObject>
#include <QString>
#include <QDebug>
#include <QDate>
#include <QTime>

namespace UTILS
{
    const QString logFolderName = "logs";

    bool initLogging();
    void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString& msg);
}


#endif // LOGGING_HPP
