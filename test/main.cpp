#include <QCoreApplication>
#include <QCommandLineParser>

#include "udpserver.hpp"
#include "udpclient.hpp"
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
    p.addOption({{"u", "use time"}, "use massage timer inteval. ms","u",""});
    p.addOption({{"I", "message id"}, "message ID. int,default is 91","I","91"});
    p.addOption({{"s", "signal idx"}, "signal idx. int,default is 0","s"});
    p.addOption({{"n", "no run"}, "do not increment,default is 0","n","0"});
    p.addOption({{"i", "ip"}, "UDP host IP. string,default is 127.0.0.1","i","127.0.0.1"});
    p.addOption({{"p", "port"}, "UDP host port,int. default is 10000","p","10000"});
    p.addOption({{"V","verbose"}, "Verbose mode. Prints out more information."});
    p.addPositionalArgument("input", "DBC file.", "input");
    p.process(app);

    if(p.isSet("u")&&p.value("u").toInt()>0){
        new udpServer("127.0.0.1",10000,&app);
    } else {
        new udpClient("127.0.0.1",10000,&app);
    }

    return app.exec();
}
