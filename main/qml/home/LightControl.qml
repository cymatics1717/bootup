import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    radius: 3
    color: "white"
    property alias title: title.text
    property alias value: info.text
    property int rradius: 20
    property int margin: 20
    anchors.margins: 3
    anchors.rightMargin: 3
    Text {
        id:title
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
            anchors.top: parent.bottom
        }
    }
}
