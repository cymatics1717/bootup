import QtQuick 2.0

Rectangle {
    id:rect
    anchors.fill: parent
    border.color: "#eeeeee"
    border.width: 0
    radius: 3
    color: "grey"
    property real rate: 1./2.1

    BooleanControl{
        id: lightswitch
        color: "white"
        anchors {
            top: parent.top
            left: parent.left
        }
        title:qsTr("夜视开关")
        value:qsTr("当前状态：关闭")
        height: parent.height*rect.rate
        width: parent.width- 2*parent.radius
    }
    IntegerControl {
        id: lightsetting
        color: "white"
        anchors {
            top: lightswitch.bottom
            left: parent.left
        }
        title:qsTr("光强设置")
        value:qsTr("请输入角度值")
        height: parent.height*rect.rate
        width: parent.width - 2*parent.radius
    }
}
