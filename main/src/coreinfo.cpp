#include "coreinfo.hpp"
#include <QMediaPlayer>
#include <QDebug>

coreInfo::coreInfo(QObject *parent) : QObject(parent)
{

}

void coreInfo::parseHWHandShakeStatus(const QByteArray &dat, int tag)
{
    qDebug() << dat.toHex('-') << tag;

    if(tag ==0){
        qDebug() << "下滑系统控制器硬件握手结果:" << ((dat.at(1)>>4) & '\x01');
        qDebug() << "下滑横摇惯性单元硬件握手结果:" << ((dat.at(1)>>3) & '\x01');
        qDebug() << "下滑纵摇惯性单元硬件握手结果:" << ((dat.at(1)>>2) & '\x01');
        qDebug() << "下滑横摇电机驱动器硬件握手结果:" << ((dat.at(1)>>1) & '\x01');
        qDebug() << "下滑纵摇电机驱动器硬件握手结果:" << ((dat.at(1)>>0) & '\x01');
    } else if(tag == 1){
        qDebug() << "横摇系统控制器硬件握手结果:" << ((dat.at(1)>>4) & '\x01');
        qDebug() << "横摇惯性单元硬件握手结果:" << ((dat.at(1)>>3) & '\x01');
        qDebug() << "右固定灯光源驱动器硬件握手结果:" << ((dat.at(1)>>2) & '\x01');
        qDebug() << "左固定灯光源驱动器硬件握手结果:" << ((dat.at(1)>>1) & '\x01');
        qDebug() << "横摇电机驱动器硬件握手结果:" << ((dat.at(1)>>0) & '\x01');
    }
}

void coreInfo::parseInitSystemStatus(const QByteArray& dat, int tag)
{
     qDebug() << dat.toHex('-') <<tag;

     if(tag ==0){
         qDebug() << "下滑系统控制器初始化结果:" << ((dat.at(1)>>4) & '\x01');
         qDebug() << "下滑横摇惯性单元初始化结果:" << ((dat.at(1)>>3) & '\x01');
         qDebug() << "下滑纵摇惯性单元初始化结果:" << ((dat.at(1)>>2) & '\x01');
         qDebug() << "下滑横摇电机驱动器初始化结果:" << ((dat.at(1)>>1) & '\x01');
         qDebug() << "下滑纵摇电机驱动器初始化结果:" << ((dat.at(1)>>0) & '\x01');
     } else if(tag == 1){
         qDebug() << "横摇系统控制器初始化结果:" << ((dat.at(1)>>4) & '\x01');
         qDebug() << "横摇惯性单元初始化结果:" << ((dat.at(1)>>3) & '\x01');
         qDebug() << "右固定灯光源驱动器初始化结果:" << ((dat.at(1)>>2) & '\x01');
         qDebug() << "左固定灯光源驱动器初始化结果:" << ((dat.at(1)>>1) & '\x01');
         qDebug() << "横摇电机驱动器初始化结果:" << ((dat.at(1)>>0) & '\x01');
     }
}

void coreInfo::parsePowerOnOffStatus(const QByteArray& dat,int tag)
{
    qDebug() << dat.toHex('-') << tag;

    if(tag ==0){
        qDebug() << "下滑系统控制器开机/关机结果:" << ((dat.at(2)>>0) & '\x03');

        qDebug() << "下滑横摇惯性单元开机/关机结果:" << ((dat.at(1)>>6) & '\x03');
        qDebug() << "下滑纵摇惯性单元开机/关机结果:" << ((dat.at(1)>>4) & '\x03');
        qDebug() << "下滑横摇电机驱动器开机/关机结果:" << ((dat.at(1)>>2) & '\x03');
        qDebug() << "下滑纵摇电机驱动器开机/关机结果:" << ((dat.at(1)>>0) & '\x03');
    } else if(tag == 1){
        qDebug() << "横摇电机驱动器开机/关机结果:" << ((dat.at(2)>>0) & '\x03');

        qDebug() << "下滑横摇惯性单元开机/关机结果:" << ((dat.at(1)>>6) & '\x03');
        qDebug() << "左固定灯光源驱动器开机/关机结果:" << ((dat.at(1)>>4) & '\x03');
        qDebug() << "左固定灯光源驱动器开机/关机结果:" << ((dat.at(1)>>2) & '\x03');
        qDebug() << "横摇电机驱动器开机/关机结果:" << ((dat.at(1)>>0) & '\x03');
    }
}

void coreInfo::parseAlarmStatus(const QByteArray &data, int tag)
{
    qDebug() << data.toHex('-') << tag;

    if(tag==0){
        //第1行
        qDebug() << "下滑电源监控器2路过流报警:" << ((data.at(1)>>1) & '\x01');
        qDebug() << "下滑电源监控器2路过压报警:" << ((data.at(1)>>2) & '\x01');
        qDebug() << "下滑电源监控器1路过压报警:" << ((data.at(1)>>3) & '\x01');
        qDebug() << "下滑电源监控器1路过流报警:" << ((data.at(1)>>4) & '\x01');
        qDebug() << "下滑系统气压超限报警:" << ((data.at(1)>>5) & '\x01');
        qDebug() << "下滑系统湿度超限报警:" << ((data.at(1)>>6) & '\x01');
        qDebug() << "下滑系统温度超限报警:" << ((data.at(1)>>7) & '\x01');
        //第2行
        qDebug() << "下滑横摇行程开关超右量程:" << ((data.at(2)>>3) & '\x01');
        qDebug() << "下滑横摇行程开关超左量程:" << ((data.at(2)>>4) & '\x01');
        qDebug() << "下滑横摇惯性单元数据异常:" << ((data.at(2)>>5) & '\x01');
        qDebug() << "下滑横摇电机驱动器温度过高:" << ((data.at(2)>>6) & '\x01');
        qDebug() << "下滑横摇电机驱动器电流过大:" << ((data.at(2)>>7) & '\x01');
        //第3行
        qDebug() << "下滑纵摇行程开关超右量程:" << ((data.at(3)>>3) & '\x01');
        qDebug() << "下滑纵摇行程开关超左量程:" << ((data.at(3)>>4) & '\x01');
        qDebug() << "下滑纵摇惯性单元数据异常:" << ((data.at(3)>>5) & '\x01');
        qDebug() << "下滑纵摇电机驱动器温度过高:" << ((data.at(3)>>6) & '\x01');
        qDebug() << "下滑纵摇电机驱动器电流过大:" << ((data.at(3)>>7) & '\x01');
        //第4行
        qDebug() << "系统下滑横摇方向震动幅度过大:" << ((data.at(4)>>3) & '\x01');
        qDebug() << "下滑横摇惯性单元422通信未收到陀螺数据:" << ((data.at(4)>>4) & '\x01');
        qDebug() << "下滑横摇惯性单元422通信和校验错误:" << ((data.at(4)>>5) & '\x01');
        qDebug() << "下滑横摇惯性单元422通信帧头错误:" << ((data.at(4)>>6) & '\x01');
        qDebug() << "下滑横摇惯性单元超角度报警:" << ((data.at(4)>>7) & '\x01');
        //第5行;
        qDebug() << "系统下滑纵摇方向震动幅度过大:" << ((data.at(5)>>3) & '\x01');
        qDebug() << "下滑纵摇惯性单元422通信未收到陀螺数据:" << ((data.at(5)>>4) & '\x01');
        qDebug() << "下滑纵摇惯性单元422通信和校验错误:" << ((data.at(5)>>5) & '\x01');
        qDebug() << "下滑纵摇惯性单元422通信帧头错误:" << ((data.at(5)>>6) & '\x01');
        qDebug() << "下滑纵摇惯性单元超角度报警:" << ((data.at(5)>>7) & '\x01');

//        qint8 warn_flag_1 = ((data.at(2)>>3) & '\x01');
//        qint8 warn_flag_2 = ((data.at(2)>>4) & '\x01');
//        qint8 warn_flag_3 = ((data.at(3)>>3) & '\x01');
//        if(warn_flag_1 == 0 || warn_flag_2 == 0 || warn_flag_3 == 0){
//            playAbnormalSound(2);
//        }

    }else if(tag==1){
        //第1行
        qDebug() << "行程开关超右量程:" << ((data.at(1)>>0) & '\x01');
        qDebug() << "横摇电源监控器2路过压报警:" << ((data.at(1)>>1) & '\x01');
        qDebug() << "横摇电源监控器2路过流报警:" << ((data.at(1)>>2) & '\x01');
        qDebug() << "横摇电源监控器1路过压报警:" << ((data.at(1)>>3) & '\x01');
        qDebug() << "横摇电源监控器1路过流报警:" << ((data.at(1)>>4) & '\x01');
        qDebug() << "横摇系统温度超限报警:" << ((data.at(1)>>5) & '\x01');
        qDebug() << "横摇系统气压超限报警:" << ((data.at(1)>>6) & '\x01');
        qDebug() << "横摇系统湿度超限报警:" << ((data.at(1)>>7) & '\x01');
        //第2行
        qDebug() << "行程开关超左量程:" << ((data.at(2)>>0) & '\x01');
        qDebug() << "惯性单元422通信未收到陀螺数据:" << ((data.at(2)>>1) & '\x01');
        qDebug() << "惯性单元422通信和校验错误:" << ((data.at(2)>>2) & '\x01');
        qDebug() << "惯性单元422通信帧头错误:" << ((data.at(2)>>3) & '\x01');
        qDebug() << "惯性单元超角度报警:" << ((data.at(2)>>4) & '\x01');
        qDebug() << "惯性单元数据异常:" << ((data.at(2)>>5) & '\x01');
        qDebug() << "横摇电机驱动器温度过高:" << ((data.at(2)>>6) & '\x01');
        qDebug() << "横摇电机驱动器电流过大:" << ((data.at(2)>>7) & '\x01');
        //第3行
        qDebug() << "系统横摇方向震动幅度过大:" << ((data.at(3)>>7) & '\x01');
    }
}

void coreInfo::parseBreakdownStatus(const QByteArray &data, int tag)
{
    qDebug() << data.toHex('-') << tag;

    if(tag==0){
        //第1行
        qDebug() << "下滑系统控制器闪光电机霍尔传感器2故障:" << ((data.at(1)>>0) & '\x01');
        qDebug() << "下滑系统控制器闪光电机霍尔传感器1故障:" << ((data.at(1)>>1) & '\x01');
        qDebug() << "下滑系统控制器步进电机导致方位角故障:" << ((data.at(1)>>2) & '\x01');
        qDebug() << "下滑光源驱动器断路故障:" << ((data.at(1)>>5) & '\x01');
        qDebug() << "下滑光源驱动器短路故障:" << ((data.at(1)>>6) & '\x01');
        qDebug() << "下滑系统控制器通信故障:" << ((data.at(1)>>7) & '\x01');
        //第2行
        qDebug() << "下滑横摇PWM驱动故障:" << ((data.at(2)>>1) & '\x01');
        qDebug() << "下滑横摇右行程开关故障:" << ((data.at(2)>>2) & '\x01');
        qDebug() << "下滑横摇左行程开关故障:" << ((data.at(2)>>3) & '\x01');
        qDebug() << "下滑横摇电机驱动器与惯性单元通信故障:" << ((data.at(2)>>4) & '\x01');
        qDebug() << "下滑横摇旋变故障:" << ((data.at(2)>>5) & '\x01');
        qDebug() << "下滑横摇电机故障:" << ((data.at(2)>>6) & '\x01');
        qDebug() << "下滑横摇电机驱动器通信故障:" << ((data.at(2)>>7) & '\x01');
        //第3行
        qDebug() << "下滑纵摇PWM驱动故障:" << ((data.at(3)>>1) & '\x01');
        qDebug() << "下滑纵摇右行程开关故障:" << ((data.at(3)>>2) & '\x01');
        qDebug() << "下滑纵摇左行程开关故障:" << ((data.at(3)>>3) & '\x01');
        qDebug() << "下滑纵摇电机驱动器与惯性单元通信故障:" << ((data.at(3)>>4) & '\x01');
        qDebug() << "下滑纵摇旋变故障:" << ((data.at(3)>>5) & '\x01');
        qDebug() << "下滑纵摇电机故障:" << ((data.at(3)>>6) & '\x01');
        qDebug() << "下滑纵摇电机驱动器通信故障:" << ((data.at(3)>>7) & '\x01');
        //第4行
        qDebug() << "下滑横摇惯性单元通信故障:" << ((data.at(4)>>7) & '\x01');
        //第5行
        qDebug() << "下滑纵摇惯性单元通信故障:" << ((data.at(5)>>7) & '\x01');

    }else if(tag==1){
        //第1行
        qDebug() << "水平灯杆灯断路故障:" << ((data.at(1)>>5) & '\x01');
        qDebug() << "水平灯杆灯短路故障:" << ((data.at(1)>>6) & '\x01');
        qDebug() << "横摇系统控制器通信故障:" << ((data.at(1)>>7) & '\x01');
        //第2行
        qDebug() << "左固定灯负5度灯短路故障:" << ((data.at(2)>>0) & '\x01');
        qDebug() << "左固定灯0度灯断路故障:" << ((data.at(2)>>1) & '\x01');
        qDebug() << "左固定灯0度灯短路故障:" << ((data.at(2)>>2) & '\x01');
        qDebug() << "左固定灯正5度灯断路故障:" << ((data.at(2)>>3) & '\x01');
        qDebug() << "左固定灯正5度灯短路故障:" << ((data.at(2)>>4) & '\x01');
        qDebug() << "左固定灯正8度灯断路故障:" << ((data.at(2)>>5) & '\x01');
        qDebug() << "左固定灯正8度灯短路故障:" << ((data.at(2)>>6) & '\x01');
        qDebug() << "左固定灯光源驱动器通信故障:" << ((data.at(2)>>7) & '\x01');
        //第3行
        qDebug() << "右固定灯负5度灯断路故障:" << ((data.at(3)>>0) & '\x01');
        qDebug() << "右固定灯负8度灯短路故障:" << ((data.at(3)>>1) & '\x01');
        qDebug() << "右固定灯负8度灯断路故障:" << ((data.at(3)>>2) & '\x01');
        qDebug() << "左固定灯负8度灯断路故障:" << ((data.at(3)>>5) & '\x01');
        qDebug() << "左固定灯负8度灯短路故障:" << ((data.at(3)>>6) & '\x01');
        qDebug() << "左固定灯负5度灯断路故障:" << ((data.at(3)>>7) & '\x01');
        //第4行
        qDebug() << "右固定灯负5度灯短路故障:" << ((data.at(4)>>0) & '\x01');
        qDebug() << "右固定灯0度灯断路故障:" << ((data.at(4)>>1) & '\x01');
        qDebug() << "右固定灯0度灯短路故障:" << ((data.at(4)>>2) & '\x01');
        qDebug() << "右固定灯正5度灯断路故障:" << ((data.at(4)>>3) & '\x01');
        qDebug() << "右固定灯正5度灯短路故障:" << ((data.at(4)>>4) & '\x01');
        qDebug() << "右固定灯正8度灯断路故障:" << ((data.at(4)>>5) & '\x01');
        qDebug() << "右固定灯正8度灯短路故障:" << ((data.at(4)>>6) & '\x01');
        qDebug() << "右固定灯光源驱动器通信故障:" << ((data.at(4)>>7) & '\x01');
        //第5行
        qDebug() << "PWM驱动故障:" << ((data.at(5)>>1) & '\x01');
        qDebug() << "行程开关右行程开关故障:" << ((data.at(5)>>2) & '\x01');
        qDebug() << "行程开关左行程开关故障:" << ((data.at(5)>>3) & '\x01');
        qDebug() << "与惯性单元通信故障:" << ((data.at(5)>>4) & '\x01');
        qDebug() << "旋变故障:" << ((data.at(5)>>5) & '\x01');
        qDebug() << "电机故障:" << ((data.at(5)>>6) & '\x01');
        qDebug() << "电机驱动器通信故障:" << ((data.at(5)>>7) & '\x01');
        //第6行
        qDebug() << "横摇惯性单元信故障:" << ((data.at(6)>>7) & '\x01');
    }
}

void coreInfo::parseSystemStatus(const QByteArray &data, int tag)
{
    qDebug() << data.toHex('-') << tag;

    if(tag==0){
        //第1行
        qDebug() << "下滑电源监控器1路过压报警:" << ((data.at(1)>>0) & '\x01');
        qDebug() << "下滑电源监控器1路过流报警:" << ((data.at(1)>>1) & '\x01');
        qDebug() << "下滑系统气压超限报警:" << ((data.at(1)>>2) & '\x01');
        qDebug() << "下滑系统湿度超限报警:" << ((data.at(1)>>3) & '\x01');
        qDebug() << "下滑系统温度超限报警:" << ((data.at(1)>>4) & '\x01');
        qDebug() << "下滑光源驱动器断路故障:" << ((data.at(1)>>5) & '\x01');
        qDebug() << "下滑光源驱动器短路故障:" << ((data.at(1)>>6) & '\x01');
        qDebug() << "下滑系统控制器通信故障:" << ((data.at(1)>>7) & '\x01');
        //第2行
        qDebug() << "下滑电源监控器2路过流报警:" << ((data.at(2)>>6) & '\x01');
        qDebug() << "下滑电源监控器2路过压报警:" << ((data.at(2)>>7) & '\x01');
        //第3行
        qDebug() << "方位角零位限位开关:" << ((data.at(3)>>0) & '\x01');
        qDebug() << "下滑系统控制器右机械限位:" << ((data.at(3)>>1) & '\x01');
        qDebug() << "下滑系统控制器左机械限位:" << ((data.at(3)>>2) & '\x01');
        qDebug() << "下滑纵摇方向伺服超差:" << ((data.at(3)>>3) & '\x01');
        qDebug() << "下滑横摇方向伺服超差:" << ((data.at(3)>>4) & '\x01');
        qDebug() << "下滑系统控制器闪光电机霍尔传感器2故障:" << ((data.at(3)>>5) & '\x01');
        qDebug() << "下滑系统控制器闪光电机霍尔传感器1故障:" << ((data.at(3)>>6) & '\x01');
        qDebug() << "下滑系统控制器步进电机导致方位角故障:" << ((data.at(3)>>7) & '\x01');
        //第4行
        qDebug() << "下滑横摇电机驱动器温度过高:" << ((data.at(4)>>0) & '\x01');
        qDebug() << "下滑横摇电机驱动器电流过大:" << ((data.at(4)>>1) & '\x01');
        qDebug() << "下滑横摇电机驱动器与下滑横摇惯性单元通信故障:" << ((data.at(4)>>2) & '\x01');
        qDebug() << "下滑横摇右行程开关故障:" << ((data.at(4)>>3) & '\x01');
        qDebug() << "下滑横摇左行程开关故障:" << ((data.at(4)>>4) & '\x01');
        qDebug() << "下滑横摇旋变故障:" << ((data.at(4)>>5) & '\x01');
        qDebug() << "下滑横摇电机故障:" << ((data.at(4)>>6) & '\x01');
        qDebug() << "下滑横摇电机驱动器通信故障:" << ((data.at(4)>>7) & '\x01');
        //第5行
        qDebug() << "下滑纵摇惯性单元数据异常:" << ((data.at(5)>>0) & '\x01');
        qDebug() << "下滑横摇惯性单元数据异常:" << ((data.at(5)>>1) & '\x01');
        qDebug() << "下滑纵摇PWM驱动故障:" << ((data.at(5)>>2) & '\x01');
        qDebug() << "下滑横摇PWM驱动故障:" << ((data.at(5)>>3) & '\x01');
        qDebug() << "下滑横摇行程开关超右量程:" << ((data.at(5)>>4) & '\x01');
        qDebug() << "下滑横摇行程开关超左量程:" << ((data.at(5)>>5) & '\x01');
        qDebug() << "下滑纵摇行程开关超右量程:" << ((data.at(5)>>6) & '\x01');
        qDebug() << "下滑纵摇行程开关超左量程:" << ((data.at(5)>>7) & '\x01');
        //第6行
        qDebug() << "下滑纵摇电机驱动器温度过高:" << ((data.at(6)>>0) & '\x01');
        qDebug() << "下滑纵摇电机驱动器电流过大:" << ((data.at(6)>>1) & '\x01');
        qDebug() << "下滑纵摇电机驱动器与下滑纵摇惯性单元通信故障:" << ((data.at(6)>>2) & '\x01');
        qDebug() << "下滑纵摇右行程开关故障:" << ((data.at(6)>>3) & '\x01');
        qDebug() << "下滑纵摇左行程开关故障:" << ((data.at(6)>>4) & '\x01');
        qDebug() << "下滑纵摇旋变故障:" << ((data.at(6)>>5) & '\x01');
        qDebug() << "下滑纵摇电机故障:" << ((data.at(6)>>6) & '\x01');
        qDebug() << "下滑纵摇电机驱动器通信故障:" << ((data.at(6)>>7) & '\x01');
        //第7行
        qDebug() << "系统下滑横摇方向震动幅度过大:" << ((data.at(7)>>2) & '\x01');
        qDebug() << "下滑横摇惯性单元422通信未收到陀螺数据:" << ((data.at(7)>>3) & '\x01');
        qDebug() << "下滑横摇惯性单元422通信和校验错误:" << ((data.at(7)>>4) & '\x01');
        qDebug() << "下滑横摇惯性单元422通信帧头错误:" << ((data.at(7)>>5) & '\x01');
        qDebug() << "下滑横摇惯性单元超角度报警:" << ((data.at(7)>>6) & '\x01');
        qDebug() << "下滑横摇惯性单元通信故障:" << ((data.at(7)>>7) & '\x01');
        //第8行
        qDebug() << "系统下滑纵摇方向震动幅度过大:" << ((data.at(8)>>2) & '\x01');
        qDebug() << "下滑纵摇惯性单元422通信未收到陀螺数据:" << ((data.at(8)>>3) & '\x01');
        qDebug() << "下滑纵摇惯性单元422通信和校验错误:" << ((data.at(8)>>4) & '\x01');
        qDebug() << "下滑纵摇惯性单元422通信帧头错误:" << ((data.at(8)>>5) & '\x01');
        qDebug() << "下滑纵摇惯性单元超角度报警:" << ((data.at(8)>>6) & '\x01');
        qDebug() << "下滑纵摇惯性单元通信故障:" << ((data.at(8)>>7) & '\x01');

        //第9行:at(9)-at(12)
        qDebug() << "方位角状态值包（4字节）:" << (data.mid(9,4));
        //第10行:at(13)-at(16)
        qDebug() << "仰角状态值包（4字节）:" << (data.mid(13,4));
        //第11行:at(17)-at(20)
        qDebug() << "下滑纵摇角度信息包（4字节）:" << (data.mid(17,4));
        //第12行:at(21)-at(24)
        qDebug() << "下滑纵摇角度误差值信息包（4字节）:" << (data.mid(21,4));
        //第13行:at(25)-at(28)
        qDebug() << "下滑横摇角度信息包（4字节）:" << (data.mid(25,4));
        //第14行:at(29)-at(32)
        qDebug() << "下滑横摇角度误差值信息包（4字节）:" << (data.mid(29,4));
        //第15行:at(33)-at(34)
        qDebug() << "第1路电压值(总电压24v),单位mv（2字节）:" << ((data.at(34))<<8)+(data.at(33))<<"mv";
        //第16行:at(35)-at(36)
        qDebug() << "第2路电压值(隔离24v),单位mv（2字节））:" << ((data.at(36))<<8)+(data.at(35))<<"mv";
        //第17行:at(37)-at(38)
        qDebug() << "第1路电流值,单位ma（2字节）:" << ((data.at(38))<<8)+(data.at(37))<<"ma";
        //第18行:at(39)-at(40)
        qDebug() << "第2路电流值,单位ma（2字节））:" << ((data.at(40))<<8)+(data.at(39))<<"ma";

        //第19-20行
        qDebug() << "温度值:" << (((float)((data.at(42))<<8)+(data.at(41)))/100) <<"℃";
        //第21-22行
        qDebug() << "湿度值:" << (((float)((data.at(44))<<8)+(data.at(43)))/100) <<"RH";
        //第23行
        qDebug() << "气压值(低8位):" << (data.at(45));
        //第24行
        qDebug() << "气压值:" << (data.at(46));
        //第25行
        qDebug() << "气压值:" << (data.at(47));
        //第26行
        qDebug() << "气压值(高8位):" << (data.at(48));

        //第27行::at(49)-at(52)
        qDebug() << "下滑横摇惯性单元角度值（4字节）:" << (data.mid(49,4));
        //第28行::at(53)-at(56)
        qDebug() << "下滑纵摇惯性单元角度值（4字节）:" << (data.mid(53,4));

        //第29行
        qDebug() << "光强等级（1字节）:" << (data.at(57));
        //第30行
        qDebug() << "下滑光源开关状态开:01关:10:" << ((data.at(58)>>0) & '\x03');
        qDebug() << "闪光状态(三闪:11单闪:10不闪：01):" << ((data.at(58)>>2) & '\x03');
        //第31行
        qDebug() << "系统控制器工作模式:" << (data.at(59));
        //第32行
        qDebug() << "系统控制器工作状态:" << (data.at(60));

    } else if(tag==1){
        //第1行
        qDebug() << "横摇电源监控器1路过压报警:" << ((data.at(1)>>0) & '\x01');
        qDebug() << "横摇电源监控器1路过流报警:" << ((data.at(1)>>1) & '\x01');
        qDebug() << "横摇系统温度超限报警:" << ((data.at(1)>>2) & '\x01');
        qDebug() << "横摇系统气压超限报警:" << ((data.at(1)>>3) & '\x01');
        qDebug() << "横摇系统湿度超限报警:" << ((data.at(1)>>4) & '\x01');
        qDebug() << "水平灯杆灯断路故障:" << ((data.at(1)>>5) & '\x01');
        qDebug() << "水平灯杆灯短路故障:" << ((data.at(1)>>6) & '\x01');
        qDebug() << "横摇系统控制器通信故障:" << ((data.at(1)>>7) & '\x01');
        //第2行
        qDebug() << "机械开关1状态（1锁紧，0开锁）:" << ((data.at(2)>>5) & '\x01');
        qDebug() << "横摇电源监控器2路过压报警:" << ((data.at(2)>>6) & '\x01');
        qDebug() << "横摇电源监控器2路过流报警:" << ((data.at(2)>>7) & '\x01');
        //第3行
        qDebug() << "左负5度灯短路故障:" << ((data.at(3)>>0) & '\x01');
        qDebug() << "左0度灯断路故障:" << ((data.at(3)>>1) & '\x01');
        qDebug() << "左0度灯短路故障:" << ((data.at(3)>>2) & '\x01');
        qDebug() << "左正5度灯断路故障:" << ((data.at(3)>>3) & '\x01');
        qDebug() << "左正5度灯短路故障:" << ((data.at(3)>>4) & '\x01');
        qDebug() << "左正8度灯断路故障:" << ((data.at(3)>>5) & '\x01');
        qDebug() << "左正8度灯短路故障:" << ((data.at(3)>>6) & '\x01');
        qDebug() << "左固定灯光源驱动器通信故障:" << ((data.at(3)>>7) & '\x01');
        //第4行
        qDebug() << "右负5度灯断路故障:" << ((data.at(4)>>0) & '\x01');
        qDebug() << "右负8度灯短路故障:" << ((data.at(4)>>1) & '\x01');
        qDebug() << "右负8度灯断路故障:" << ((data.at(4)>>2) & '\x01');
        qDebug() << "左负8度灯断路故障:" << ((data.at(4)>>5) & '\x01');
        qDebug() << "左负8度灯短路故障:" << ((data.at(4)>>6) & '\x01');
        qDebug() << "左负5度灯断路故障:" << ((data.at(4)>>7) & '\x01');
        //第5行
        qDebug() << "右负5度灯短路故障:" << ((data.at(5)>>0) & '\x01');
        qDebug() << "右0度灯断路故障:" << ((data.at(5)>>1) & '\x01');
        qDebug() << "右0度灯短路故障:" << ((data.at(5)>>2) & '\x01');
        qDebug() << "右正5度灯断路故障:" << ((data.at(5)>>3) & '\x01');
        qDebug() << "右正5度灯短路故障:" << ((data.at(5)>>4) & '\x01');
        qDebug() << "右正8度灯断路故障:" << ((data.at(5)>>5) & '\x01');
        qDebug() << "右正8度灯短路故障:" << ((data.at(5)>>6) & '\x01');
        qDebug() << "右固定灯光源驱动器通信故障:" << ((data.at(5)>>7) & '\x01');
        //第6行
        qDebug() << "PWM驱动故障:" << ((data.at(6)>>2) & '\x01');
        qDebug() << "右行程开关故障:" << ((data.at(6)>>3) & '\x01');
        qDebug() << "左行程开关故障:" << ((data.at(6)>>4) & '\x01');
        qDebug() << "电机驱动器与惯性单元通信故障:" << ((data.at(6)>>5) & '\x01');
        qDebug() << "旋变故障:" << ((data.at(6)>>6) & '\x01');
        qDebug() << "电机故障:" << ((data.at(6)>>7) & '\x01');
        //第7行
        qDebug() << "横摇伺服超差:" << ((data.at(7)>>1) & '\x01');
        qDebug() << "行程开关超右限:" << ((data.at(7)>>2) & '\x01');
        qDebug() << "行程开关超左限:" << ((data.at(7)>>3) & '\x01');
        qDebug() << "惯性单元数据异常:" << ((data.at(7)>>4) & '\x01');
        qDebug() << "电机驱动器温度过高（超80℃）:" << ((data.at(7)>>5) & '\x01');
        qDebug() << "电机驱动器电流过大:" << ((data.at(7)>>6) & '\x01');
        qDebug() << "电机驱动器通信故障:" << ((data.at(7)>>7) & '\x01');
        //第8行
        qDebug() << "系统横摇方向震动幅度过大:" << ((data.at(8)>>2) & '\x01');
        qDebug() << "横摇惯性单元422通信未收到陀螺数据:" << ((data.at(8)>>3) & '\x01');
        qDebug() << "横摇惯性单元422通信和校验错误:" << ((data.at(8)>>4) & '\x01');
        qDebug() << "横摇惯性单元422通信帧头错误:" << ((data.at(8)>>5) & '\x01');
        qDebug() << "惯性单元超角度报警:" << ((data.at(8)>>6) & '\x01');
        qDebug() << "横摇惯性单元信故障:" << ((data.at(8)>>7) & '\x01');
        //第9行
        qDebug() << "光强等级（1字节）:" << (data.at(9));
        //第10行
        qDebug() << "左固定0度灯开关状态（开:01关:10）:" << ((data.at(10)>>0) & '\x03');
        qDebug() << "左固定灯正5度灯开关状态（开:01关:10）:" << ((data.at(10)>>2) & '\x03');
        qDebug() << "左固定灯正8度灯开关状态（开:01关:10）:" << ((data.at(10)>>4) & '\x03');
        qDebug() << "左固定灯正8度灯开关状态（开:01关:10）:" << ((data.at(10)>>6) & '\x03');
        //第11行
        qDebug() << "右固定正5度灯开关状态（开:01关:11）:" << ((data.at(11)>>0) & '\x03');
        qDebug() << "右固定正8度灯开关状态（开:01关:11）:" << ((data.at(11)>>2) & '\x03');
        qDebug() << "左固定负8度灯开关状态（开:01关:11）:" << ((data.at(11)>>4) & '\x03');
        qDebug() << "左固定灯负5度灯开关状态（开:01关:11）:" << ((data.at(11)>>6) & '\x03');
        //第12行
        qDebug() << "右固定负8度灯开关状态（开:01关:11）:" << ((data.at(12)>>0) & '\x03');
        qDebug() << "右固定负5度灯开关状态（开:01关:11）:" << ((data.at(12)>>2) & '\x03');
        qDebug() << "右固定灯0度开关状态（开:01关:11）:" << ((data.at(12)>>4) & '\x03');

        //第13行:at(13)-at(16)
        qDebug() << "横摇角度信息包（4字节）:" << (data.mid(13,4));
        //第14行:at(17)-at(20)
        qDebug() << "横摇角度误差值信息包（4字节）:" << (data.mid(17,4));

        //第15行:at(21)-at(22)
        qDebug() << "第1路电压值(总电压24v),单位mv（2字节）:" << ((data.at(22))<<8)+(data.at(21))<<"mv";
        //第16行:at(23)-at(24)
        qDebug() << "第2路电压值(隔离24v),单位mv（2字节））:" << ((data.at(24))<<8)+(data.at(23))<<"mv";
        //第17行:at(25)-at(26)
        qDebug() << "第1路电流值,单位ma（2字节）:" << ((data.at(26))<<8)+(data.at(25))<<"ma";
        //第18行:at(27)-at(28)
        qDebug() << "第2路电流值,单位ma（2字节）:" << ((data.at(28))<<8)+(data.at(27))<<"ma";

        //第19行
//        qDebug() << "温度值(低8位):" << (data.at(29));
//        //第20行
//        qDebug() << "温度值(高8位):" << (data.at(30));
        qDebug() << "温度值:" << (((float)((data.at(30))<<8)+(data.at(29)))/100) <<"℃";
        //第21行
        qDebug() << "湿度值(低8位):" << (data.at(31));
        //第22行
        qDebug() << "湿度值(高8位):" << (data.at(32));
        //第23行
        qDebug() << "气压值(低8位):" << (data.at(33));
        //第24行
        qDebug() << "气压值:" << (data.at(34));
        //第25行
        qDebug() << "气压值:" << (data.at(35));
        //第26行
        qDebug() << "气压值(高8位):" << (data.at(36));

        //第27行:at(37)-at(40)
        qDebug() << "惯性单元角度值（4字节）:" << (data.mid(37,4));
        //第28行
        qDebug() << "系统控制器工作模式:" << (data.at(41));
        //第29行
        qDebug() << "系统控制器工作状态:" << (data.at(42));
    }
}

void coreInfo::parseLimitAngle(const QByteArray &data, int tag) {
    qDebug() << data.toHex('-') << tag;

    if(tag==0){
        if (data.at(1) == 1) {
            qDebug() << "限位过程角度值:" << (data.at(1));
        } else if (data.at(1) == 2) {
            qDebug() << "限位角度值:" << (data.at(1));
        }
        qDebug() << "对应从机设备地址:" << (data.at(2));
        if (data.at(2)==1) {
            qDebug() << "左(上)限位:" << (data.at(2));
        } else if (data.at(2)==2) {
            qDebug() << "右(下)限位:" << (data.at(2));
        }
        qDebug() << "限位角度:" << (data.at(3));
    } else if (tag==1) {
        if (data.at(1) == 1) {
            qDebug() << "限位过程角度值:" << (data.at(1));
        } else if (data.at(1) == 2) {
            qDebug() << "限位角度值:" << (data.at(1));
        }
        qDebug() << "对应从机设备地址:" << (data.at(2));
        if (data.at(2)==1) {
            qDebug() << "左(上)限位:" << (data.at(2));
        } else if (data.at(2)==2) {
            qDebug() << "右(下)限位:" << (data.at(2));
        }
        qDebug() << "限位角度:" << (data.at(3));
    }
}

void coreInfo::parseCalibStatusReply(const QByteArray &data, int tag) {
    qDebug() << data.toHex('-') << tag;

    if (tag == 0) {
        qDebug() << "对应从机设备地址:" << (data.at(1) & '\xFF');
        qDebug() << "标零信息:" << (data.at(2) & '\xFF')
                               + (data.at(3) << 8 & '\xFF')
                               + (data.at(4) << 16 & '\xFF')
                               + (data.at(5) << 24 & '\xFF');
    } else if (tag == 1) {
        qDebug() << "对应从机设备地址:" << (data.at(1) & '\xFF');
        qDebug() << "标零信息:" << (data.at(2) & '\xFF')
                               + (data.at(3) << 8 & '\xFF')
                               + (data.at(4) << 16 & '\xFF')
                               + (data.at(5) << 24 & '\xFF');
    }
}

void coreInfo::parseZeroOffsetReply(const QByteArray &data, int tag) {
    qDebug() << data.toHex('-') << tag;

    if (tag == 0) {
        qDebug() << "对应从机设备地址:" << (data.at(1) & '\xFF');
        qDebug() << "惯性单元偏移量或零位旋变值:" << (data.at(2) & '\xFF')
                                            + (data.at(3) << 8 & '\xFF')
                                            + (data.at(4) << 16 & '\xFF')
                                            + (data.at(5) << 24 & '\xFF');
    } else if (tag == 1) {
        qDebug() << "对应从机设备地址:" << (data.at(1) & '\xFF');
        qDebug() << "惯性单元偏移量或零位旋变值:" << (data.at(2) & '\xFF')
                                            + (data.at(3) << 8 & '\xFF')
                                            + (data.at(4) << 16 & '\xFF')
                                            + (data.at(5) << 24 & '\xFF');
    }
}


void coreInfo::playAbnormalSound(int abnormal)
{
    QMediaPlayer *p= new QMediaPlayer();

    if(abnormal == 1){
        p->setMedia(QUrl::fromLocalFile("/home/yyq/projects/bootup/audio/error.wav"));
    }else{
        p->setMedia(QUrl::fromLocalFile("/home/yyq/projects/bootup/audio/warn.wav"));
    }
    p->play();
}

void coreInfo::matchWarningTable(const QByteArray &data, int tag) {
    qDebug() << data.toHex('-') << tag;

    if(tag == 0) {  //xiahua
        //第1行
        if(!((data.at(1)>>1) & '\x01')) {
            qDebug() << "下滑电源监控器2路过流报警!";
        }
        if(!((data.at(1)>>2) & '\x01')) {
            qDebug() << "下滑电源监控器2路过压报警!";
        }
        if(!((data.at(1)>>3) & '\x01')) {
            qDebug() << "下滑电源监控器1路过压报警!";
        }
        if(!((data.at(1)>>4) & '\x01')) {
            qDebug() << "下滑电源监控器1路过流报警!";
        }
        if(!((data.at(1)>>5) & '\x01')) {
            qDebug() << "下滑系统气压超限报警!";
        }
        if(!((data.at(1)>>6) & '\x01')) {
            qDebug() << "下滑系统湿度超限报警!";
        }
        if(!((data.at(1)>>7) & '\x01')) {
            qDebug() << "下滑系统温度超限报警!";
        }
        //第2行
        if(!((data.at(2)>>3) & '\x01')) {
            qDebug() << "下滑横摇行程开关超右量程!";
        }
        if(!((data.at(2)>>4) & '\x01')) {
            qDebug() << "下滑横摇行程开关超左量程!";
        }
        if(!((data.at(2)>>5) & '\x01')) {
            qDebug() << "下滑横摇惯性单元数据异常!";
        }
        if(!((data.at(2)>>6) & '\x01')) {
            qDebug() << "下滑横摇电机驱动器温度过高!";
        }
        if(!((data.at(2)>>7) & '\x01')) {
            qDebug() << "下滑横摇电机驱动器电流过大!";
        }
        //第3行
        if(!((data.at(3)>>3) & '\x01')) {
            qDebug() << "下滑纵摇行程开关超右量程!";
        }
        if(!((data.at(3)>>4) & '\x01')) {
            qDebug() << "下滑纵摇行程开关超左量程!";
        }
        if(!((data.at(3)>>5) & '\x01')) {
            qDebug() << "下滑纵摇惯性单元数据异常!";
        }
        if(!((data.at(3)>>6) & '\x01')) {
            qDebug() << "下滑纵摇电机驱动器温度过高!";
        }
        if(!((data.at(3)>>7) & '\x01')) {
            qDebug() << "下滑纵摇电机驱动器电流过大!";
        }
        //第4行
        if(!((data.at(4)>>3) & '\x01')) {
            qDebug() << "系统下滑横摇方向震动幅度过大!";
        }
        if(!((data.at(4)>>4) & '\x01')) {
            qDebug() << "下滑横摇惯性单元422通信未收到陀螺数据!";
        }
        if(!((data.at(4)>>5) & '\x01')) {
            qDebug() << "下滑横摇惯性单元422通信和校验错误!";
        }
        if(!((data.at(4)>>6) & '\x01')) {
            qDebug() << "下滑横摇惯性单元422通信帧头错误!";
        }
        if(!((data.at(4)>>7) & '\x01')) {
            qDebug() << "下滑横摇惯性单元超角度报警!";
        }
        //第5行;
        if(!((data.at(5)>>3) & '\x01')) {
            qDebug() << "系统下滑纵摇方向震动幅度过大!";
        }
        if(!((data.at(5)>>4) & '\x01')) {
            qDebug() << "下滑纵摇惯性单元422通信未收到陀螺数据!";
        }
        if(!((data.at(5)>>5) & '\x01')) {
            qDebug() << "下滑纵摇惯性单元422通信和校验错误!";
        }
        if(!((data.at(5)>>6) & '\x01')) {
            qDebug() << "下滑纵摇惯性单元422通信帧头错误!";
        }
        if(!((data.at(5)>>7) & '\x01')) {
            qDebug() << "下滑纵摇惯性单元超角度报警!";
        }
    } else if (tag == 1) {  //hengyao
        //第1行
        if(!((data.at(1)>>0) & '\x01')) {
            qDebug() << "行程开关超右量程!";
        }
        if(!((data.at(1)>>1) & '\x01')) {
            qDebug() << "横摇电源监控器2路过压报警!";
        }
        if(!((data.at(1)>>2) & '\x01')) {
            qDebug() << "横摇电源监控器2路过流报警!";
        }
        if(!((data.at(1)>>3) & '\x01')) {
            qDebug() << "横摇电源监控器1路过压报警!";
        }
        if(!((data.at(1)>>4) & '\x01')) {
            qDebug() << "横摇电源监控器1路过流报警!";
        }
        if(!((data.at(1)>>5) & '\x01')) {
            qDebug() << "横摇系统温度超限报警!";
        }
        if(!((data.at(1)>>6) & '\x01')) {
            qDebug() << "横摇系统气压超限报警!";
        }
        if(!((data.at(1)>>7) & '\x01')) {
            qDebug() << "横摇系统湿度超限报警!";
        }
        //第2行
        if(!((data.at(2)>>0) & '\x01')) {
            qDebug() << "行程开关超左量程!";
        }
        if(!((data.at(2)>>1) & '\x01')) {
            qDebug() << "惯性单元422通信未收到陀螺数据!";
        }
        if(!((data.at(2)>>2) & '\x01')) {
            qDebug() << "惯性单元422通信和校验错误!";
        }
        if(!((data.at(2)>>3) & '\x01')) {
            qDebug() << "惯性单元422通信帧头错误!";
        }
        if(!((data.at(2)>>4) & '\x01')) {
            qDebug() << "惯性单元超角度报警!";
        }
        if(!((data.at(2)>>5) & '\x01')) {
            qDebug() << "惯性单元数据异常!";
        }
        if(!((data.at(2)>>6) & '\x01')) {
            qDebug() << "横摇电机驱动器温度过高!";
        }
        if(!((data.at(2)>>7) & '\x01')) {
            qDebug() << "横摇电机驱动器电流过大!";
        }
        //第3行
        if(!((data.at(3)>>7) & '\x01')) {
            qDebug() << "系统横摇方向震动幅度过大!";
        }
    }
}

void coreInfo::matchBreakdownTable(const QByteArray &data, int tag) {
    qDebug() << data.toHex('-') << tag;

    if(tag == 0) {
        //第1行
        if(!((data.at(1)>>0) & '\x01')) {
            qDebug() << "下滑系统控制器闪光电机霍尔传感器2故障!";
        }
        if(!((data.at(1)>>1) & '\x01')) {
            qDebug() << "下滑系统控制器闪光电机霍尔传感器1故障!";
        }
        if(!((data.at(1)>>2) & '\x01')) {
            qDebug() << "下滑系统控制器步进电机导致方位角故障!";
        }
        if(!((data.at(1)>>5) & '\x01')) {
            qDebug() << "下滑光源驱动器断路故障!";
        }
        if(!((data.at(1)>>6) & '\x01')) {
            qDebug() << "下滑光源驱动器短路故障!";
        }
        if(!((data.at(1)>>7) & '\x01')) {
            qDebug() << "下滑系统控制器通信故障!";
        }
        //第2行
        if(!((data.at(2)>>1) & '\x01')) {
            qDebug() << "下滑横摇PWM驱动故障!";
        }
        if(!((data.at(2)>>2) & '\x01')) {
            qDebug() << "下滑横摇右行程开关故障!";
        }
        if(!((data.at(2)>>3) & '\x01')) {
            qDebug() << "下滑横摇左行程开关故障!";
        }
        if(!((data.at(2)>>4) & '\x01')) {
            qDebug() << "下滑横摇电机驱动器与惯性单元通信故障!";
        }
        if(!((data.at(2)>>5) & '\x01')) {
            qDebug() << "下滑横摇旋变故障!";
        }
        if(!((data.at(2)>>6) & '\x01')) {
            qDebug() << "下滑横摇电机故障!";
        }
        if(!((data.at(2)>>7) & '\x01')) {
            qDebug() << "下滑横摇电机驱动器通信故障!";
        }
        //第3行
        if(!((data.at(3)>>1) & '\x01')) {
            qDebug() << "下滑纵摇PWM驱动故障!";
        }
        if(!((data.at(3)>>2) & '\x01')) {
            qDebug() << "下滑纵摇右行程开关故障!";
        }
        if(!((data.at(3)>>3) & '\x01')) {
            qDebug() << "下滑纵摇左行程开关故障!";
        }
        if(!((data.at(3)>>4) & '\x01')) {
            qDebug() << "下滑纵摇电机驱动器与惯性单元通信故障!";
        }
        if(!((data.at(3)>>5) & '\x01')) {
            qDebug() << "下滑纵摇旋变故障!";
        }
        if(!((data.at(3)>>6) & '\x01')) {
            qDebug() << "下滑纵摇电机故障!";
        }
        if(!((data.at(3)>>7) & '\x01')) {
            qDebug() << "下滑纵摇电机驱动器通信故障!";
        }
        //第4行
        if(!((data.at(4)>>7) & '\x01')) {
            qDebug() << "下滑横摇惯性单元通信故障!";
        }
        //第5行
        if(!((data.at(5)>>7) & '\x01')) {
            qDebug() << "下滑纵摇惯性单元通信故障!";
        }
    } else if (tag == 1) {
        //第1行
        if(!((data.at(1)>>5) & '\x01')) {
            qDebug() << "水平灯杆灯断路故障!";
        }
        if(!((data.at(1)>>6) & '\x01')) {
            qDebug() << "水平灯杆灯短路故障!";
        }
        if(!((data.at(1)>>7) & '\x01')) {
            qDebug() << "横摇系统控制器通信故障!";
        }
        //第2行
        if(!((data.at(2)>>0) & '\x01')) {
            qDebug() << "左固定灯负5度灯短路故障!";
        }
        if(!((data.at(2)>>1) & '\x01')) {
            qDebug() << "左固定灯0度灯断路故障!";
        }
        if(!((data.at(2)>>2) & '\x01')) {
            qDebug() << "左固定灯0度灯短路故障!";
        }
        if(!((data.at(2)>>3) & '\x01')) {
            qDebug() << "左固定灯正5度灯断路故障!";
        }
        if(!((data.at(2)>>4) & '\x01')) {
            qDebug() << "左固定灯正5度灯短路故障!";
        }
        if(!((data.at(2)>>5) & '\x01')) {
            qDebug() << "左固定灯正8度灯断路故障!";
        }
        if(!((data.at(2)>>6) & '\x01')) {
            qDebug() << "左固定灯正8度灯短路故障!";
        }
        if(!((data.at(2)>>7) & '\x01')) {
            qDebug() << "左固定灯光源驱动器通信故障!";
        }
        //第3行
        if(!((data.at(3)>>0) & '\x01')) {
            qDebug() << "右固定灯负5度灯断路故障!";
        }
        if(!((data.at(3)>>1) & '\x01')) {
            qDebug() << "右固定灯负8度灯短路故障!";
        }
        if(!((data.at(3)>>2) & '\x01')) {
            qDebug() << "右固定灯负8度灯断路故障!";
        }
        if(!((data.at(3)>>5) & '\x01')) {
            qDebug() << "左固定灯负8度灯断路故障!";
        }
        if(!((data.at(3)>>6) & '\x01')) {
            qDebug() << "左固定灯负8度灯短路故障!";
        }
        if(!((data.at(3)>>7) & '\x01')) {
            qDebug() << "左固定灯负5度灯断路故障!";
        }
        //第4行
        if(!((data.at(4)>>0) & '\x01')) {
            qDebug() << "右固定灯负5度灯短路故障!";
        }
        if(!((data.at(4)>>1) & '\x01')) {
            qDebug() << "右固定灯0度灯断路故障!";
        }
        if(!((data.at(4)>>2) & '\x01')) {
            qDebug() << "右固定灯0度灯短路故障!";
        }
        if(!((data.at(4)>>3) & '\x01')) {
            qDebug() << "右固定灯正5度灯断路故障!";
        }
        if(!((data.at(4)>>4) & '\x01')) {
            qDebug() << "右固定灯正5度灯短路故障!";
        }
        if(!((data.at(4)>>5) & '\x01')) {
            qDebug() << "右固定灯正8度灯断路故障!";
        }
        if(!((data.at(4)>>6) & '\x01')) {
            qDebug() << "右固定灯正8度灯短路故障!";
        }
        if(!((data.at(4)>>7) & '\x01')) {
            qDebug() << "右固定灯光源驱动器通信故障!";
        }
        //第5行
        if(!((data.at(5)>>1) & '\x01')) {
            qDebug() << "PWM驱动故障!";
        }
        if(!((data.at(5)>>2) & '\x01')) {
            qDebug() << "行程开关右行程开关故障!";
        }
        if(!((data.at(5)>>3) & '\x01')) {
            qDebug() << "行程开关左行程开关故障!";
        }
        if(!((data.at(5)>>4) & '\x01')) {
            qDebug() << "与惯性单元通信故障!";
        }
        if(!((data.at(5)>>5) & '\x01')) {
            qDebug() << "旋变故障!";
        }
        if(!((data.at(5)>>6) & '\x01')) {
            qDebug() << "电机故障!";
        }
        if(!((data.at(5)>>7) & '\x01')) {
            qDebug() << "电机驱动器通信故障!";
        }
        //第6行
        if(!((data.at(6)>>7) & '\x01')) {
            qDebug() << "横摇惯性单元信故障!";
        }
    }
}
