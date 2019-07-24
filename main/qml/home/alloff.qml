import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id:rect
    anchors.fill: parent
    Text {
        id: txt
        anchors {
            centerIn: parent
            margins: 20
        }
        text: qsTr("是否关闭全部灯具")
    }
    Row {
        id: main
        anchors.horizontalCenter: rect.horizontalCenter
        y:rect.height*2/3
        spacing: rect.width/6
        Button {
            text: qsTr("取消")
            width: rect.width/6
            height: rect.height/10
            onClicked: {
                console.log(text)
            }
        }
        Button {
            text: qsTr("确定")
            width: rect.width/6
            height: rect.height/10
            onClicked: {
                uclient.handshake()
            }
        }
    }
}
