import QtQuick 2.0

Rectangle {
    id:rect
    anchors.fill: parent
    border.color: "#eeeeee"
    border.width: 0
    radius: 3
    color: "transparent"
    property real rate: 1./3.1
    property bool firstTime: false

    BooleanControl{
        id: lightswitch
        color: "white"
        anchors {
            top: parent.top
            left: parent.left
        }
        title:qsTr("开关")
        height: parent.height*rect.rate
        width: parent.width- 2*parent.radius
        onCheck: {
            console.log("----------------"+checked)
            if(checked){
                if(!firstTime) {
                    backend.hwHandShake(3, 0);
                    firstTime = true;
                    console.log("@@@@@@@@@@@@@@@viktor@@@@@@@@@@@@@@@@@:" + firstTime)
                } else {
                    backend.setWorkMode(3, 0);
                    backend.__setHengyaoPowerOnOffDelays();
                    console.log("$$$$$$$$$$$$$$$$$$viktor$$$$$$$$$$$$$$$$$$$:" + firstTime)
                }
            } else {
                backend.setPowerOnOff(false,1);
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
        title:qsTr("光源控制")
        height: parent.height*rect.rate
        width: parent.width - 2*parent.radius
        onCheck: {
            console.log("----------------"+checked)
            backend.setLight(1, lightsetting.value, 4*(1+lightcontrol.checked)+(2-lightcontrol.checked), 3)
        }
    }
    IntegerControl {
        id: lightsetting
        color: "white"
        anchors {
            top: lightcontrol.bottom
            left: parent.left
        }
        title:qsTr("光强设置")
        value:qsTr("50")
        height: parent.height*rect.rate
        width: parent.width - 2*parent.radius
        onTextChanged: {
            console.log("####################"+text)
            backend.setLight(1, text,4*lightStatus.status+1, 3)
        }
    }
}
