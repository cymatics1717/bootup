import QtQuick 2.0
import QtQuick.Controls 2.5
import ".."

Rectangle {
    id:root
    radius: 3
    color: "white"
    property alias title: title.text
    property alias value: info.text
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

    Text {
        id:title
        anchors.leftMargin: 5
        color: "white"
        anchors{
            left: parent.left
        }
    }
    Text {
        id:info
        color: ccolor
        anchors{
            left: title.right
        }
    }

    TButton{
        id:backward_quick
        radius: root.height/4
        y: root.height*.6-radius
        width: radius*2
        height: radius*2
        gradient: root.bgradient
        anchors{
            left: root.left
            margins: margin
        }
        Text {
          text: qsTr("\u21DA")
          font.pointSize: 25
          color: "white"
          anchors{
              leftMargin: parent.radius/4
              left: parent.left
              verticalCenter: parent.verticalCenter
          }
        }
        onClicked: {
            value.text = value.text - 10;
        }
    }
    TButton{
        id:backward
        color: ccolor
        radius: root.height/3
        y: root.height*.6-radius
        width: radius*2
        height: radius*2
        gradient: root.bgradient
        anchors{
            left: backward_quick.right
            leftMargin: margin
        }
        Text {
          text: qsTr("\u2190")
          font.pointSize: 35
          color: "white"
          anchors{
              leftMargin: parent.radius/4
              left: parent.left
              verticalCenter: parent.verticalCenter
          }
        }
        onClicked: {
            value.text --;
        }
    }

    TextInput {
        id: value
        color: "#777777"
        width: root.width/8
        height: root.height
        text: "20"
        readOnly: false
        font.pixelSize: 50
        validator: IntValidator{bottom: -180; top: 180;}

        x: root.width/2 - 10
        anchors{
            verticalCenter : backward.verticalCenter
            rightMargin: margin

        }
    }

    TButton {
        id:forward
        color: ccolor
        gradient: root.bgradient
        radius: root.height/3
        y: root.height*.6-radius
        width: radius*2
        height: radius*2
        anchors{
            right: forward_qick.left
            rightMargin: margin
        }
        Text {
          text: qsTr("\u2192")
          font.pointSize: 35
          color: "white"
          anchors{
              leftMargin: parent.radius/4
              left: parent.left
              verticalCenter: parent.verticalCenter
          }
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
        y: root.height*.6-radius
        width: radius*2
        height: radius*2
        anchors{
            right: parent.right
            margins: margin
        }
        Text {
          text: qsTr("\u21DB")
          font.pointSize: 25
          color: "white"
          anchors{
              leftMargin: parent.radius/4
              left: parent.left
              verticalCenter: parent.verticalCenter
          }
        }
        onClicked: {
            value.text = Number(value.text) + 10;
        }
    }
}
