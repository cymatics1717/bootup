import QtQuick 2.12
import QtQuick.Controls 2.5
import ".."

Rectangle {
    id:rect
//    anchors.fill: parent

    property var grad: Gradient {
        GradientStop { position: 0; color: "#17274c" }
        GradientStop { position: 0; color: "#11244b" }
    }

    gradient: Gradient {
        GradientStop { position: 1; color: "#020711" }
        GradientStop { position: 0; color: "#020711" }
    }

    SButton {
        text: qsTr("静态灯光调试")
        fontSize:18
        width: rect.width*.1
        height: rect.height/20
        gradient: Gradient {
            GradientStop { position: 0; color: "transparent" }
        }
        border.width: 0
        source: "qrc:/res/left-icon.png"
        onClicked: {
            console.log(text)
            stackView.pop()
        }
    }

    SButton {
        text: qsTr("退出")
        fontSize:18
        width: rect.width*.1
        height: rect.height/20
        anchors.right: rect.right
        border.width: 1
        radius: height/2

//        gradient: lgradient
        onClicked: {
            console.log(text)
            stackView.pop()
        }
    }


}
