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
    property int margin: 16
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
        anchors.leftMargin: 5
        color: "white"
        anchors{
            left: parent.left
        }
    }
    Row {
        anchors.centerIn: parent
        spacing: root.width/20
        TButton{
            id:backward_quick
            radius: root.height/4
            y: root.height*.6-radius
            width: radius*2
            height: radius*2
            gradient: root.bgradient
            anchors.verticalCenter: parent.verticalCenter
            Image {
                source: "qrc:/res/left double-icon.png"
                anchors.centerIn:  parent
            }
            onClicked: {
                value.text = value.text - 10;
            }
        }
        TButton{
            id:backward
            color: ccolor
            radius: root.height/3
//            y: root.height*.6-radius
            width: radius*2
            height: radius*2
            gradient: root.bgradient
            anchors.verticalCenter: parent.verticalCenter
            Image {
                source: "qrc:/res/left-icon.png"
                anchors.centerIn:  parent
            }
            onClicked: {
                value.text --;
            }
        }

        TextField {
            id: value
//            color: "blue"
            width: root.width/6
            height: root.height/2
            horizontalAlignment: TextInput.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
//            height: root.height
            text: "20"
//            readOnly: false
            validator: IntValidator{bottom: -180; top: 180;}
            onTextChanged: {
                root.textChanged(text);
            }
            background: Rectangle {
                color: value.focus ? "white" : "grey"
                radius: width/10
                border.color: value.focus ? "#21be2b" : "grey"
                border.width: 1
            }
        }

        TButton {
            id:forward
            color: ccolor
            gradient: root.bgradient
            radius: root.height/3
//            y: root.height*.6-radius
            width: radius*2
            height: radius*2
            anchors.verticalCenter: parent.verticalCenter
            Image {
                source: "qrc:/res/right-icon.png"
                anchors.centerIn:  parent
            }
            onClicked: {
                value.text ++;
            }
        }
        TButton {
            id:forward_qick
            color: ccolor
            gradient: root.bgradient
            radius: root.height/4
//            y: root.height*.6-radius
            width: radius*2
            height: radius*2
            anchors.verticalCenter: parent.verticalCenter

            Image {
                source: "qrc:/res/right double-icon.png"
                anchors.centerIn:  parent
            }
            onClicked: {
                value.text = Number(value.text) + 10;
            }
        }
    }

}
