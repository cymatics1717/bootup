import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id:rect
    radius: 3
    color: "transparent"
    property alias title: title.text
    property alias value: control.text
    property alias checked: control.checked
    border.color: "grey"
    border.width: 0.02 * height
//    anchors.margins: 3
//    anchors.rightMargin: 6
    gradient: Gradient {
        GradientStop { position: 1; color: "#1e315b" }
        GradientStop { position: 0; color: "#22335c" }
    }

    signal check();

    Text {
        id:title
        anchors.leftMargin: 5
        color: "white"
        anchors{
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
    }
//    Text {
//        id:value
//        color: "transparent"
//        anchors{
//            top: title.bottom
//            left: parent.left
//        }
//    }

    SwitchDelegate {
          id: control
//          text: qsTr("SwitchDelegate")
          checked: false
          anchors{
              left: title.right
              verticalCenter: parent.verticalCenter
          }
          contentItem: Text {
              rightPadding: control.indicator.width + control.spacing
              text: control.text
              font: control.font
              opacity: enabled ? 1.0 : 0.3
              color: control.down ? "#17a81a" : "#21be2b"
              elide: Text.ElideRight
              verticalAlignment: Text.AlignVCenter
          }

          indicator: Rectangle {
              implicitWidth: 60
              implicitHeight: 30
              x: control.width - width - control.rightPadding
              y: parent.height / 2 - height / 2
              radius: height/2
              color: control.checked ? "#FF02881D" : "transparent"
              border.color: control.checked ? "#17a81a" : "#cccccc"

              Text {
                text: qsTr("On")
                color: "white"
                anchors{
                    leftMargin: parent.radius/4
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
              }

              Rectangle {
                  x: control.checked ? parent.width - width : 0
                  width: parent.height
                  height: parent.height
                  radius: height/2
                  color: control.down ? "black" : "white"
                  border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
              }
          }

          background: Rectangle {
              implicitWidth: 100
              implicitHeight: 40
              visible: control.down || control.highlighted
              color: control.down ? "#bdbebf" : "#eeeeee"
          }
          onCheckedChanged: {
            rect.check()
          }
      }
}
