#include <QCoreApplication>
#include <QCommandLineParser>

#include "udpserver.hpp"
#include "udpclient.hpp"
#include "serialpeer.hpp"
#include "serialother.hpp"

/*
nc -u 127.0.0.1 10000
socat -d -d -d pty,link=/dev/ttytest1,raw pty,link=/dev/ttytest2,raw

*/

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("my-copy");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser p;
    p.setApplicationDescription("UDP network emulator");
    p.addHelpOption();
    p.addVersionOption();
    p.addOption({{"t", "timer inteval"}, "timer inteval. ms,default is 1000ms","t","1000"});
    p.addOption({{"i", "ip"}, "UDP host IP. string,default is 127.0.0.1","i","127.0.0.1"});
    p.addOption({{"p", "port"}, "UDP host port,int. default is 10000","p","10000"});
    p.addOption({{"V","verbose"}, "Verbose mode. Prints out more information."});
    p.addPositionalArgument("device", "device path.", "device");
    p.process(app);

    int t = 1000;
    if(p.isSet("t")&&p.value("t").toInt()>0){
        t = p.value("t").toInt();
    }
    QString path = "/dev/ttytest1";
    if(p.positionalArguments().size()>0){
        path = p.positionalArguments().at(0);
        if(p.positionalArguments().size()>1){
            t = p.positionalArguments().at(1).toInt();
        }
    }

    serialPeer serial("/dev/ttytest1",t);
    serialOther other("/dev/ttytest2",t);

    return app.exec();
}
