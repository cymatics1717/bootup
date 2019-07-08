import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    radius: 3
    color: "white"
    property alias title: title.text
    property alias value: value.text
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
        id:value
        color: "grey"
        anchors{
            top: title.bottom
            left: parent.left
//            leftMargin: margin
        }
    }
    Image {
        width: parent.width/10
        source: "qrc:/res/icon.png"
        fillMode: Image.PreserveAspectFit
        anchors{
            top: parent.top
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
    }
}
