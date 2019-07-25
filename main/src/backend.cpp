#include "backend.hpp"
#include <QDebug>
#include <QFileInfo>
backEnd::backEnd(QString config_file, QObject *parent) : QObject(parent),configfile(config_file){

}

QString backEnd::getConfigfile() const
{
    return configfile;
}

int backEnd::loadConfig()
{
    // https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
    std::ifstream infile(configfile.toStdString());
    try {
        infile >> root;
    } catch (const std::exception &e) {
        std::cout << e.what()<<std::endl;
        return -1;
    }

    std::cout << root["endpoints"]["touchpad"]["ip"]<<std::endl;
    std::cout << root["endpoints"]["xiahua"]["ip"]<<std::endl;
    std::cout << root["endpoints"]["hengyao"]["ip"]<<std::endl;
    std::cout << root["endpoints"]["tatai"]["ip"]<<std::endl;
////////////////////////////////////////////////////////////////
    qDebug() << root["endpoints"]["touchpad"]["ip"].asString().c_str();
    qDebug() << root["endpoints"]["xiahua"]["ip"].asString().c_str();
    qDebug() << root["endpoints"]["hengyao"]["ip"].asString().c_str();
    qDebug() << root["endpoints"]["tatai"]["ip"].asString().c_str();

    return 0;
}

int backEnd::saveConfig()
{
    std::ofstream outfile(QString("%1/settings.json").arg(QFileInfo(configfile).path()).toStdString());
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "\t";
//    builder["commentStyle"] = "None";
    builder["commentStyle"] = "All";
    builder["enableYAMLCompatibility"] = true;
    builder["dropNullPlaceholders"] = false;
    builder["useSpecialFloats"] = false;
    root["id"] = "config file";
    root["id"] = __FUNCTION__;
//    outfile << root;

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &outfile);
//    writer->write(root, &std::cerr);

//    std::string doc = Json::writeString(builder, root);
//    std::cerr << doc << std::endl;

    return 0;
}

void backEnd::testQML(QString data)
{
    qDebug() << data;
}
