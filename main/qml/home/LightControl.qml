import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    radius: 3
    color: "white"
    property alias title: title.text
    property alias value: info.text
    property int rradius: 20
    property int margin: 20
    border.color: "grey"
    border.width: 0.02 * height
//    anchors.margins: 3
//    anchors.rightMargin: 3
    gradient: Gradient {
        GradientStop { position: 1; color: "#1e315b" }
        GradientStop { position: 0; color: "#22335c" }
    }

    Text {
        id:title
        anchors.leftMargin: 5
        color: "white"
        anchors{
            left: parent.left
//            leftMargin: margin
        }
    }
    Text {
        id:info
        color: "grey"
        anchors{
            left: title.right
        }
    }

    Rectangle {
        id:none
        color: "green"
        radius: rradius
        width: radius*2
        height: radius*2
        anchors{
            left: parent.left
            top: title.bottom
            leftMargin: margin
        }
        Text {
            text: qsTr("不闪")
            anchors.leftMargin: 5
            color: "white"
            anchors.top: parent.bottom
        }
    }

    Rectangle {
        id:all
        color: "#ff7700"
        radius: rradius
        width: radius*2
        height: radius*2
        anchors{
            left: none.right
            top: title.bottom
            leftMargin: margin
        }
        Text {
            text: qsTr("全闪")
            anchors.leftMargin: 5
            color: "white"
            anchors.top: parent.bottom
        }
    }
    Rectangle {
        id:single
        color: "#ff0000"
        radius: rradius
        width: radius*2
        height: radius*2
        anchors{
            left: all.right
            top: title.bottom
            leftMargin: margin
        }
        Text {
            text: qsTr("单闪")
            anchors.leftMargin: 5
            color: "white"
            anchors.top: parent.bottom
        }
    }
}
