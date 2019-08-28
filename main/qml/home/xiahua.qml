import QtQuick 2.0

Rectangle {
    id:rect
    anchors.fill: parent
    border.color: "#eeeeee"
    border.width: 0
    radius: 3
    color: "transparent"
    anchors.margins: 0
    property real rate: 1./8
    property bool firstTime: false
    BooleanControl{
        id: lightswitch
        color: "white"
        anchors {
            top: parent.top
            left: parent.left
        }
        title:qsTr("开机")
        height: parent.height*rect.rate
        width: parent.width- 2*parent.radius
        onCheck: {
            console.log("----------------"+checked)
            if(checked){
                if(!firstTime) {
                    backend.hwHandShake(3, 0)
                    firstTime = true;
                    console.log("@@@@@@@@@@@@@@@viktor@@@@@@@@@@@@@@@@@:" + firstTime)
                } else {
                    backend.setWorkMode(3, 0)
                    backend.__setXiahuaPowerOnOffDelays();
                    console.log("$$$$$$$$$$$$$$$$$$viktor$$$$$$$$$$$$$$$$$$$:" + firstTime)
                }
            } else {
                backend.setPowerOnOff(false,0)
            }
        }
    }
    BooleanControl{
        id: lightcontrol
        color: "white"
        anchors {
            top: lightswitch.bottom
            left: parent.left
        }
        title:qsTr("光源")
        height: parent.height*rect.rate
        width: parent.width - 2*parent.radius
        onCheck: {
            console.log("---------lightcontrol-------"+checked)
            if(checked) {
                backend.setLight(0, lightsetting.value, lightStatus.status, 3)
            } else {
                backend.setLight(0, lightsetting.value, 6, 3) //关闭光源：0x0110
            }
        }
    }
    IntegerControl {
        id: lightsetting
        color: "white"
        anchors {
            top: lightcontrol.bottom
            left: rect.left
        }
        title:qsTr("光强")
        value:qsTr("50")
        height: rect.height*(rect.rate+0.02)
        width: rect.width - 2*rect.radius
        onTextChanged: {
            console.log("####################"+text)
            backend.setLight(0, text, lightStatus.status, 3)
        }
    }

    Integer {
        id: pitchAngleSetting
        color: "white"
        anchors {
            top: lightsetting.bottom
            left: parent.left
        }
        title:qsTr("仰角")
        value:qsTr("4")
        min:2
        max:8

        height: rect.height*(rect.rate+0.02)
        width: rect.width - 2*rect.radius
        onTextChanged: {
            console.log("####################"+text)
            backend.setPitch(text - 4)
        }
    }
    Integer {
        id: yawAngleSetting
        color: "white"
        anchors {
            top: pitchAngleSetting.bottom
            left: rect.left
        }
        title:qsTr("方位角")
        value:qsTr("0")
        min:-90
        max:90
        height: rect.height*(rect.rate+0.02)
        width: rect.width - 2*rect.radius
        onTextChanged: {
            console.log("####################"+text)
            backend.setAzimuth(text)
        }
    }
    EnumControl {
        id: lightStatus
        color: "white"
        anchors {
            top: yawAngleSetting.bottom
            left: parent.left
        }
        title:qsTr("闪光")
        height: parent.height*(rect.rate+0.04)
        width: parent.width - 2*parent.radius
        status:9 //单闪：9/0x1001, 多闪：13/0x1101, 不闪：5/0x0101
        onClicked: {
            console.log(lightcontrol.checked+"!!!!!!!lightStatus.status!!!!!"+status)
            backend.setLight(0, lightsetting.value, lightStatus.status, 3)
        }
    }

    BooleanControl{
        id: deicingControl
        color: "white"
        anchors {
            top: lightStatus.bottom
            left: rect.left
        }
        title:qsTr("除冰")
        height: rect.height*rect.rate
        width: rect.width - 2*rect.radius
    }

}
