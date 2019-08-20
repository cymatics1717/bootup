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
                backend.hwHandShake(0);
		lightStatus.status = 2;
//                lightswitch.enabled = false;
//                lightswitch.opacity = .3
            } else {
                backend.setPowerOnOff(false,0);
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
            console.log("----------------"+checked)
//            backend.setLight(7, lightsetting.value,4*2+(2-lightcontrol.checked))
            backend.setLight(7, lightsetting.value,4*(1+lightcontrol.checked)+(2-lightcontrol.checked))
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
            backend.setLight(7, text,4*lightStatus.status+1)
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
            backend.setPitch(text)
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
        onClicked: {
            console.log(lightcontrol.checked+"-------"+status)
//            backend.setLight(7, lightsetting.value, 4*status+(1+lightcontrol.checked))
            backend.setLight(7, lightsetting.value, 4*status+(2-lightcontrol.checked))
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
