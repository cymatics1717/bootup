import QtQuick 2.0

Rectangle {
    id:rect
    anchors.fill: parent
    border.color: "#eeeeee"
    border.width: 0
    radius: 3
    color: "transparent"
    property real rate: 1./3.1

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
            left: parent.left
        }
        title:qsTr("光强设置")
        value:qsTr("50")
        height: parent.height*rect.rate
        width: parent.width - 2*parent.radius
    }
}
