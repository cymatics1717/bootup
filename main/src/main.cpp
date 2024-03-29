#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDebug>
#include <QFileInfo>
#include <QQmlContext>

#include "logging.hpp"
#include "backend.hpp"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QString QT_MESSAGE_PATTERN =""
//                                "[%{threadid}-"
                                "%{time yyyyMMdd hh:mm:ss.zzz}-"
                                "%{if-debug}D%{endif}"
                                "%{if-info}I%{endif}"
                                "%{if-warning}W%{endif}"
                                "%{if-critical}E%{endif}"
                                "%{if-fatal}F%{endif}]"
                                "%{if-warning} %{backtrace}%{endif}"
                                "%{if-critical} %{backtrace}%{endif}"
                                "%{if-fatal} %{backtrace}%{endif} "
                                "%{if-info}%{function}:%{line}%{endif}"
                                "%{if-debug}%{function}:%{line}%{endif}"
                                "---%{message}";

    qSetMessagePattern(QT_MESSAGE_PATTERN);

    UTILS::initLogging();

    QGuiApplication app(argc, argv);

//    QString root =  app.applicationFilePath();
    QString root =  QFileInfo(__FILE__).absolutePath()+"/../../";
//    QString root =  "./";
    qDebug() <<"root path: "<< root;

    backEnd backend(root+"conf/test.json");
    //backEnd backend("/home/user/xhhy_project/conf/test.json");
//    backEnd backend("/coding/bootup/conf/test.json");
    if(backend.loadConfig()!=0)
    {
        QGuiApplication::quit();
        qInfo() <<"no such file, or invalid json file format? -->" << backend.getConfigfile();
        return -1;
    }
    backend.saveConfig();

    QTranslator translator;
    if(translator.load("zh_CN.qm", root + "lang"))
        qApp->installTranslator(&translator);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    engine.rootContext()->setContextProperty("backend",&backend);

    return QGuiApplication::exec();
}
