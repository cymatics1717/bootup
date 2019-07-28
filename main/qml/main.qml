import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Window 2.13

ApplicationWindow {
    id: root
    property real ratio: .8
    visible: true
    width: Screen.width*ratio
    height: Screen.height*ratio
    opacity: 1
    title: qsTr("Stack")
    background: Rectangle {
//        color:"#FF202123"
        gradient: Gradient {
            GradientStop { position: 0; color: "#1e315b" }
            GradientStop { position: 1; color: "#1e335c" }
        }
    }

    header: Rectangle {
        id:headerbar
        color: "#565656"
        height: root.width/36
        Behavior on color {
            ColorAnimation { duration: 100 }
        }

        Text {
            id:title
            color: "white"
            text: qsTr("灯光助降系统")
            anchors {
                centerIn: parent
                verticalCenter: parent.verticalCenter
                margins: 10
            }
        }
        Label {
            id:timestamp
            color: "white"
            font.pixelSize: 20
            text: qsTr("初始化...")
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: 5
            }
        }
        Image {
            id:dateI
            source: "qrc:/res/date-icon.png"
            anchors {
                right: timestamp.left
                verticalCenter: parent.verticalCenter
                margins: 5
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "normalmode.qml"
        anchors.fill: parent
    }

    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            var tmp = new Date().toLocaleString(Qt.locale(),"yyyy/MM/dd hh:mm:ss")
            timestamp.text = tmp
            headerbar.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
            backend.hwHandShake()
        }
    }

    Item {
        id: keyHandler
        focus: true
        Keys.onPressed: {
            console.log('pressed Key '+ event.text);
            if (event.key === Qt.Key_Return || event.key === Qt.Key_F) {
                root.visibility === Window.FullScreen ? root.showNormal() : root.showFullScreen()
            } else if (event.key === Qt.Key_Q) {
                Qt.quit();
            }
        }
    }
}
