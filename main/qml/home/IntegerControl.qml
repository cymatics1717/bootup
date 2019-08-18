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
    property int margin: 16
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
                if(value.text!=root.min){
                    value.text = value.text - 10;
                    if(value.text<root.min){
                        value.text = root.min
                    }
                    root.textChanged(value.text)
                }
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
                if(value.text!=root.min){
                    value.text = value.text -1;
                    if(value.text<root.min){
                        value.text = root.min
                    }
                    root.textChanged(value.text)
                }
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
            onEditingFinished:{
                root.textChanged(text)
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
                if(value.text!=root.max){
                    value.text = Number(value.text) + 1;
                    if(value.text>root.max){
                        value.text = root.max
                    }
                    root.textChanged(value.text)
                }
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
                if(value.text!=root.max){
                    value.text = Number(value.text) + 10;
                    if(value.text>root.max){
                        value.text = root.max
                    }
                    root.textChanged(value.text)
                }
            }
        }
    }
}
