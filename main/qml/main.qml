import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Window 2.12

ApplicationWindow {
    id: root
    property real ratio: .8
    visible: true
    width: Screen.width*ratio
    height: Screen.height*ratio
    opacity: 1
    title: qsTr("灯光助降系统")

    property color leftColor: "#1e315b"
    property color rightColor: "#1e335c"
    property var grad: Gradient {
        orientation: Gradient.Horizontal
        GradientStop { position: 0; color: leftColor }
        GradientStop { position: 1; color: rightColor }
    }

    background:  Rectangle {
        gradient: grad
    }


    Popup {
        id: popup
        modal: true
        dim: true
//        focus: true
        property alias content: content
        background:Rectangle{
            gradient: root.grad
        }
        padding: 0
        contentItem: Loader {
             id: content
             anchors.fill: parent
        }
    }

    header: Rectangle {
        id:headerbar
        color: stackView.depth ==1 ? "transparent":"#020711"
        height: root.width/36
        property var fzise: 22
        Behavior on color {
            ColorAnimation { duration: 100 }
        }

        Button {
            id:title
            property alias banner: inner1.text
            property alias ccolor: inner1.color
            background:Rectangle{
                color: "transparent"
            }
            focusPolicy: Qt.NoFocus
            contentItem: Text{
                id:inner1
                text: qsTr("灯光助降系统")
                color: "white"
                font.pixelSize: headerbar.fzise
            }
            anchors {
                centerIn: parent
                verticalCenter: parent.verticalCenter
                margins: 10
            }
            onClicked: {
                popup.content.source = "qrc:/qml/DateSelector.qml"
                popup.width = root.width/3
                popup.height = root.height/3
                popup.x = root.width/2 - popup.width/2
                popup.y = root.height/2 -  popup.height/2
                popup.open()
            }
        }

        Button {
            id:timestamp
            property alias banner: inner.text
            property alias ccolor: inner.color
            background:Rectangle{
                color: "transparent"
            }
            focusPolicy: Qt.NoFocus
            contentItem: Text{
                id:inner
                text: qsTr("欢迎...")
                color: "white"
                font.pixelSize: headerbar.fzise
            }
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: 5
            }
            onClicked: {
                popup.content.source = "qrc:/qml/DateSelector.qml"
                popup.width = root.width/3
                popup.height = root.height/3
                popup.x = root.width/2 - popup.width/2
                popup.y = root.height/2 -  popup.height/2
                popup.open()
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
            timestamp.banner = tmp
            title.ccolor = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
//            backend.hwHandShake()
        }
    }

    Item {
        id: keyHandler
        focus: true
        Keys.onPressed: {
            console.log(stackView.depth+ 'pressed Key '+ event.text);
            if (event.key === Qt.Key_Return || event.key === Qt.Key_F) {
                root.visibility === Window.FullScreen ? root.showNormal() : root.showFullScreen()
            } else if (event.key === Qt.Key_Q) {
                Qt.quit();
            } else if (event.key === Qt.Key_1) {
                if(stackView.depth == 1){
                    stackView.push("qrc:/qml/DeviceVerify.qml")
                } else if(stackView.depth == 2){
                    stackView.pop()
                }
            }
        }
    }
}
