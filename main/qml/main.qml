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
        gradient: Gradient {
            GradientStop { position: 0; color: "black" }
            GradientStop { position: 1; color: "#aaaaaa" }
        }
    }

    header: Rectangle {
        id:headerbar
        color: "#565656"
        height: root.width/36
        Behavior on color {
            ColorAnimation { duration: 1000 }
        }

        Text {
            id:title
            color: "white"
            text: qsTr("灯光助降系统")
            anchors{
                left: parent.left
                verticalCenter: parent.verticalCenter
                margins: 10
            }
        }
        Label {
            id:timestamp
            color: "white"
            font.pixelSize: 20
            anchors.right: date_.left
            text: qsTr("ddd")
            anchors.verticalCenter: parent.verticalCenter
        }
        Label {
            id:date_
            color: "white"
            anchors.right: parent.right
//            width: groupBox1.width * .7
//            height: groupBox1.height * .1
//            text: qsTr("f")
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.qml"
        anchors.fill: parent
    }

    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            var tmp = new Date().toLocaleString(Qt.locale(),"dddd yyyy-MM-dd hh:mm:ss.z")
            timestamp.text = tmp
            headerbar.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
        }
    }


    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: root.height
        width: root.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: root.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
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
