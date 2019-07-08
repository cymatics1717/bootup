import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id:root
    radius: 3
    color: "white"
    property alias title: title.text
    property alias value: info.text
    property color ccolor: "#aaaaaa"
    property int margin: 16
    anchors.margins: 3
    anchors.rightMargin: 6
    Text {
        id:title
        anchors{
            left: parent.left
//            leftMargin: margin
        }
    }
    Text {
        id:info
        color: ccolor
        anchors{
            left: title.right
//            leftMargin: margin
        }
    }

    Rectangle {
        id:backward_quick
        color: ccolor
        radius: 20
        y: 50-radius
        width: radius*2
        height: radius*2
        anchors{
            left: root.left
//            bottom: parent.bottom
            margins: margin
        }
    }
    Rectangle {
        id:backward
        color: ccolor
        radius: 25
        y: 50-radius
        width: radius*2
        height: radius*2
        anchors{
            left: backward_quick.right
//            bottom: parent.bottom
            leftMargin: margin
        }
    }
    TextInput {
        id: value
//        focus: true
        color: "#777777"
        width: root.width/8
        height: root.height
        text: "20"
        readOnly: false
        font.pixelSize: 50
        x: root.width/2 - 10
//        horizontalAlignment:TextInput.AlignHCenter
        anchors{
            verticalCenter : backward.verticalCenter
            rightMargin: margin

        }
    }

    Rectangle {
        id:forward
        color: ccolor
        radius: 25
        y: 50-radius
        width: radius*2
        height: radius*2
        anchors{
            right: forward_qick.left
            rightMargin: margin
//            bottom: parent.bottom
        }
    }
    Rectangle {
        id:forward_qick
        color: ccolor
        radius: 20
        y: 50-radius
        width: radius*2
        height: radius*2
        anchors{
            right: parent.right
            margins: margin
//            bottom: parent.bottom
        }
    }
}
