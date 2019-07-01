#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDebug>
#include <QFile>
#include "logging.hpp"

int main(int argc, char *argv[])
{

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QString QT_MESSAGE_PATTERN ="[%{threadid}-%{time yyyyMMdd-hh:mm:ss.zzz}-"
                                "%{if-debug}D%{endif}"
                                "%{if-info}I%{endif}"
                                "%{if-warning}W%{endif}"
                                "%{if-critical}C%{endif}"
                                "%{if-fatal}F%{endif}]"
                                "%{if-warning} %{backtrace}%{endif}"
                                "%{if-critical} %{backtrace}%{endif}"
                                "%{if-fatal} %{backtrace}%{endif} "
                                "%{function}:%{line}---%{message}";

    qSetMessagePattern(QT_MESSAGE_PATTERN);

    LOGTOOL::initLogging();

    QGuiApplication app(argc, argv);

    QTranslator translator;
    if(translator.load("zh_CN.qm","/home/wayne/qt/bootup/lang"))
        qApp->installTranslator(&translator);


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    qDebug() <<"ddddddddddd";
    qInfo() <<"ddddddddddd";
    qWarning() <<"ddddddddddd";
    qCritical() <<"ddddddddddd";
    qDebug() <<"ddddddddddd";
    qInfo() <<"ddddddddddd";
    qWarning() <<"ddddddddddd";
    qCritical() <<"ddddddddddd";

    return app.exec();
}
