import QtQuick 2.12
import QtQuick.Controls 2.5
import ".."
Rectangle {
    id:rect
    anchors.fill: parent

//    color: "transparent"
    gradient: Gradient {
        GradientStop { position: 1; color: "#1e315b" }
        GradientStop { position: 0; color: "#22335c" }
    }

    Text {
        id: txt
        font {
            pointSize: 26
        }
        color: "white"
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
        SButton {
            text: qsTr("取消")
            width: rect.width/6
            height: rect.height/10
            onClicked: {
                console.log(text)
                backend.closeAll()
            }
        }
        SButton {
            text: qsTr("确定")
            width: rect.width/6
            height: rect.height/10
            onClicked: {
                console.log(text)
                backend.testQML(text)
            }
        }
    }
}
