#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QObject>
#include "udpclient.hpp"
#include "udpserver.hpp"
#include "serialpeer.hpp"

#include <iostream>
#include <fstream>
#include "json/json.h"

class backEnd : public QObject
{
    Q_OBJECT
public:
    explicit backEnd(QString config_file, QObject *parent = nullptr);

    QString getConfigfile() const;
signals:

public slots:
    int loadConfig();
    int saveConfig();

    void testQML(QString data);

private:
    udpServer server;
    udpClient client;

    QString configfile;
    Json::Value root;
};

#endif // BACKEND_HPP
