#include "coreinfo.hpp"
#include <QDebug>

coreInfo::coreInfo(QObject *parent) : QObject(parent)
{

}

void coreInfo::parseSystemStatus(const QByteArray &data, int tag)
{
    qDebug() << data;
    if(tag==0){

    } else if(tag==1){

    }
}
