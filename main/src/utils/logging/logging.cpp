#include "logging.hpp"

#include <QTime>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <iostream>

namespace UTILS
{
static QString logFileName;

void initLogFileName()
{
    logFileName = QString(logFolderName + "/Log_%1__%2.txt")
            .arg(QDate::currentDate().toString("yyyy_MM_dd"),QTime::currentTime().toString("hh_mm_ss"));
    //    .arg(QTime::currentTime().toString("hh_mm_ss_zzz"));
}

void deleteOldLogs()
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time | QDir::Reversed);
    dir.setPath(logFolderName);

    QFileInfoList list = dir.entryInfoList();
    if (list.size() > LOGFILES){
        for (int i = 0; i < (list.size() - LOGFILES); i++)
        {
            QString path = list.at(i).absoluteFilePath();
            QFile file(path);
            file.remove();
        }
    }
}

bool initLogging()
{
    if(!QDir(logFolderName).exists())
    {
        QDir().mkdir(logFolderName);
    }

    deleteOldLogs();
    initLogFileName();

    QFile outFile(logFileName);
    if(outFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qInstallMessageHandler(UTILS::myMessageHandler);
        return true;
    }   
        return false;
    
}

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString& txt)
{
    {
        QFile outFileCheck(logFileName);
        if (outFileCheck.size() > LOGSIZE)
        {
            deleteOldLogs();
            initLogFileName();
        }
    }

    QString ans = qFormatLogMessage(type,context,txt);
    QFile outFile(logFileName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << ans << endl;
    std::cerr << ans.toStdString() << std::endl;
}
}
