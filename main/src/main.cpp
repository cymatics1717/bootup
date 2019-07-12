#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDebug>
#include <QFileInfo>

#include <iostream>
#include <fstream>
#include "logging.hpp"
#include "json/json.h"

static void loadConfig(QString config_file){
    // https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
    std::ifstream infile(config_file.toStdString());
    Json::Value root;
    infile >> root;
    std::cerr << root << std::endl;

    ////////
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "\t";
    builder["commentStyle"] = "None";
//    builder["commentStyle"] = "All";
    builder["enableYAMLCompatibility"] = true;
    builder["dropNullPlaceholders"] = false;
    builder["useSpecialFloats"] = false;
    std::string doc = Json::writeString(builder, root);
    std::cerr << doc << std::endl;

}

int main(int argc, char *argv[])
{

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QString QT_MESSAGE_PATTERN ="[%{threadid}-%{time yyyyMMdd-hh:mm:ss.zzz}-"
                                "%{if-debug}D%{endif}"
                                "%{if-info}I%{endif}"
                                "%{if-warning}W%{endif}"
                                "%{if-critical}E%{endif}"
                                "%{if-fatal}F%{endif}]"
                                "%{if-warning} %{backtrace}%{endif}"
                                "%{if-critical} %{backtrace}%{endif}"
                                "%{if-fatal} %{backtrace}%{endif} "
                                "%{if-debug}%{function}:%{line}"
                                "---%{message}";

    qSetMessagePattern(QT_MESSAGE_PATTERN);

    UTILS::initLogging();

    QGuiApplication app(argc, argv);

//    QString root =  app.applicationFilePath();
    QString root =  QFileInfo(__FILE__).absolutePath()+"/../../";
    qDebug() <<"root path: "<< root;

    loadConfig(root+"conf/test.json");

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
