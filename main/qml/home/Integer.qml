import QtQuick 2.12
import QtQuick.Controls 2.5
import ".."

Rectangle {
    id:root
    radius: 3
    color: "white"
    property alias title: title.text
    property alias value: value.text
    property color ccolor: "#aaaaaa"
    property alias validator: value.validator
//    property int margin: 16
    property int min: 0
    property int max: 100
    border.color: "grey"
    border.width: 0.02 * height

    property var cgradient: Gradient {
        GradientStop { position: 1; color: "#1e315b" }
        GradientStop { position: 0; color: "#22335c" }
    }

    property var bgradient: Gradient {
        GradientStop { position: 0; color: "#914F95FF" }
        GradientStop { position: 0.5; color: "#910049B7" }
        GradientStop { position: 1; color: "#910366ED" }
    }

    gradient: cgradient
    signal textChanged(string text);

    Text {
        id:title
//        anchors.leftMargin: root.width/10
        color: "white"
        width: root.width/3
        height: root.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
//            anchors{
//                left: parent.left
//            }
    }
    TextField {
        id: value
//            color: "blue"
        width: root.width/4
//            height: root.height/2
        horizontalAlignment: TextInput.AlignHCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: title.right

//            height: root.height
//            text: "50"
//            readOnly: false
//            validator: DoubleValidator{bottom: root.min; top: root.max;decimals:1}
        validator: IntValidator{bottom: root.min; top: root.max;}
        inputMethodHints: Qt.ImhDigitsOnly

        background: Rectangle {
            color: value.focus ? "white" : "grey"
            radius: width/10
            border.color: value.focus ? "#21be2b" : "grey"
            border.width: 1
        }
    }

    SButton {
        text: qsTr("设置")
        width: root.width/6
        height: root.height/2
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: root.width/8
        onClicked: {
            if(value.text<root.min){
                value.text = root.min
            }
            if(value.text>root.max){
                value.text = root.max
            }
            root.textChanged(value.text)
        }
    }
}
