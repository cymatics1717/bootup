import QtQuick 2.12
import QtQuick.Controls 2.5
import ".."

Page {
    id:page
    anchors.fill: parent
    property var grad: Gradient {
        GradientStop { position: 0; color: "#020711" }
        GradientStop { position: 0; color: "#020711" }
    }

    property int slice: height/10



    background:Rectangle{
        gradient: grad
    }

    header: Rectangle {
        height: page.height/15
        width: page.width
        gradient: grad

        SButton {
            text: qsTr("下滑指示器调试")
            anchors.left: parent.left
            fontSize:18
            width: page.width*.1
            height:parent.height
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
            width: page.width*.1
            height:parent.height
            anchors.right: parent.right
            border.width: 1
            radius: height/2
            onClicked: {
                console.log(text)
                stackView.pop()
            }
        }
    }

        //////////////////////////////////////////////////////////////////////////////////////

    Text {
        id: title1
        color: "white"
        anchors.left: parent.left
//        horizontalAlignment: Text.AlignHCenter
//        font.pointSize: 20
        width: parent.width*.6
        height: slice
        text: qsTr("基本调试")
    }
    Grid {
        columns: 3
        spacing: 2
        anchors{
            left: page.left
            top: title1.bottom
        }
        Rectangle { color: "red"; width: 50; height: 50 }
        Rectangle { color: "green"; width: 20; height: 50 }
        Rectangle { color: "blue"; width: 50; height: 20 }
        Rectangle { color: "cyan"; width: 50; height: 50 }
        Rectangle { color: "magenta"; width: 10; height: 10 }
    }
    //////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////

}
