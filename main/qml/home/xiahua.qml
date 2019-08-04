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
        title:qsTr("开关")
        height: parent.height*rect.rate
        width: parent.width- 2*parent.radius
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
    }
    IntegerControl {
        id: lightsetting
        color: "white"
        anchors {
            top: lightcontrol.bottom
            left: rect.left
        }
        title:qsTr("光强设置")
        value:qsTr("请输入角度值")
        height: rect.height*(rect.rate+0.02)
        width: rect.width - 2*rect.radius
    }

    IntegerControl {
        id: pitchAngleSetting
        color: "white"
        anchors {
            top: lightsetting.bottom
            left: parent.left
        }
        title:qsTr("仰角设置")
        value:qsTr("请输入角度值")
        height: rect.height*(rect.rate+0.02)
        width: rect.width - 2*rect.radius
    }
    IntegerControl {
        id: yawAngleSetting
        color: "white"
        anchors {
            top: pitchAngleSetting.bottom
            left: rect.left
        }
        title:qsTr("方位角设置")
        value:qsTr("请输入角度值")
        height: rect.height*(rect.rate+0.02)
        width: rect.width - 2*rect.radius
    }
    EnumControl {
        id: lightStatus
        color: "white"
        anchors {
            top: yawAngleSetting.bottom
            left: parent.left
        }
        title:qsTr("闪光状态")
        value:qsTr("当前状态")
        height: parent.height*(rect.rate+0.04)
        width: parent.width - 2*parent.radius
    }

    BooleanControl{
        id: deicingControl
        color: "white"
        anchors {
            top: lightStatus.bottom
            left: rect.left
        }
        title:qsTr("除冰控制")
        height: rect.height*rect.rate
        width: rect.width - 2*rect.radius
    }
}
