import QtQuick 2.12
import QtQuick.Controls 2.5
import ".."

Rectangle {
    id:rect
    anchors.fill: parent


    property var grad: Gradient {
        GradientStop { position: 0; color: "#17274c" }
        GradientStop { position: 0; color: "#11244b" }
    }

    gradient: Gradient {
        GradientStop { position: 1; color: "#020711" }
        GradientStop { position: 0; color: "#020711" }
    }

    SButton {
        text: qsTr("选择模式")
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
            stackView.pop(null)
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
            stackView.pop(null)
        }
    }


    Row {
        anchors.centerIn: parent
        spacing: rect.width/8
        //////////////////////////////////////////////////////////////////////////////////////

        Rectangle {
            id:debug
            width: rect.width/3
            height: rect.height*.6

            //    color: "transparent"
            gradient: grad

            Text {
                id: title_i
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                y: parent.height*.2
                width: parent.width*.6
                height: parent.width*.1
                font.pointSize: 20
                text: qsTr("调试模式")
            }

            Column {
                anchors.top: title_i.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: height/4
                spacing: title_i.height/2

                SButton {
                    text: qsTr("下滑指示器调试")
                    fontSize: 18
                    width: title_i.width
                    height: title_i.height
                    radius: width/10
                    onClicked: {
                        console.log(text)
                        backend.testQML(text)
                        stackView.push("qrc:/qml/XHTS.qml")
                    }
                }
                SButton {
                    text: qsTr("横摇指示器调试")
                    fontSize: 18
                    width: title_i.width
                    height: title_i.height
                    radius: width/10

                    onClicked: {
                        console.log(text)
                        backend.testQML(text)
                        stackView.push("qrc:/qml/HYTS.qml")

                    }
                }
                SButton {
                    text: qsTr("静态灯光调试")
                    fontSize: 18
                    width: title_i.width
                    height: title_i.height
                    radius: width/10

                    onClicked: {
                        console.log(text)
                        backend.testQML(text)
                        stackView.push("qrc:/qml/JTTS.qml")

                    }
                }
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////

        Rectangle {
            id:inspect
            width: rect.width/3
            height: rect.height*.6

            //    color: "transparent"
            gradient: grad


            Text {
                id: title_d
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                y: parent.height*.3
                font.pointSize: 20
                width: parent.width*.6
                height: parent.width*.1
                text: qsTr("检视模式")
            }

            SButton {
                text: qsTr("检视模式")
                anchors.top: title_d.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: height/2
                anchors.margins: title_d.height

                fontSize: 18
                width: title_d.width
                height: title_d.height
                radius: width/10

                onClicked: {
                    console.log(text)
                    backend.testQML(text)
                    stackView.push("qrc:/qml/JSMS.qml")

                }
            }
        }
    //////////////////////////////////////////////////////////////////////////////////////
    }

}
