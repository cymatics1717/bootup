#include <QCoreApplication>
#include <QTranslator>
#include <QDebug>
#include <QFile>

#include "udpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    udpServer server;
    return app.exec();
}
