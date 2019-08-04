#include <QCoreApplication>
#include <QCommandLineParser>

#include "udppeer.hpp"
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

    QString QT_MESSAGE_PATTERN ="[%{threadid}-%{time yyyyMMdd hh:mm:ss.zzz}-"
                                "%{if-debug}D%{endif}"
                                "%{if-info}I%{endif}"
                                "%{if-warning}W%{endif}"
                                "%{if-critical}E%{endif}"
                                "%{if-fatal}F%{endif}]"
                                "%{if-warning} %{backtrace}%{endif}"
                                "%{if-critical} %{backtrace}%{endif}"
                                "%{if-fatal} %{backtrace}%{endif} "
                                "%{if-debug}%{function}:%{line}%{endif}"
                                "---%{message}";

    qSetMessagePattern(QT_MESSAGE_PATTERN);

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


    udpPeer xiahua("127.0.0.1",1026);
    udpPeer hengyao("127.0.0.1",1027);
    udpPeer tatai("127.0.0.1",1021);


    int t = 1000;
    if(p.isSet("t")&&p.value("t").toInt()>0){
        t = p.value("t").toInt();
    }
    QString path = "/dev/ttytest2";
    if(p.positionalArguments().size()>0){
        path = p.positionalArguments().at(0);
        if(p.positionalArguments().size()>1){
            t = p.positionalArguments().at(1).toInt();
        }
    }

//    serialPeer serial("/dev/ttytest1",t);
    serialOther other("/dev/ttytest2",t);

    return QCoreApplication::exec();
}
