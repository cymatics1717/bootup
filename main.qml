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

    title: qsTr("Stack")
    background: Rectangle {
        color: "black"
    }
    //    Drawer {
//        id: drawer
//        width: root.width * 0.66
//        height: root.height

//        Column {
//            anchors.fill: parent

//            ItemDelegate {
//                text: qsTr("Page 1")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page1Form.ui.qml")
//                    drawer.close()
//                }
//            }
//            ItemDelegate {
//                text: qsTr("Page 2")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page2Form.ui.qml")
//                    drawer.close()
//                }
//            }
//        }
//    }

    StackView {
        id: stackView
        initialItem: "HomeForm.qml"
        anchors.fill: parent
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
