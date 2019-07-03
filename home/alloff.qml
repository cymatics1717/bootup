import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id:rect
    anchors.fill: parent
    Text {
        id: txt
        anchors.bottom: main.top
        x: parent.width/2 - width/2
        y: parent.height/3
        text: qsTr("是否关闭全部灯具")
//        font.pointSize: 20
//        color: "red"
    }
    Row {
        id: main
        anchors.centerIn: parent
        spacing: 100
          Button {
              text: qsTr("取消")
              width: rect.width/6
              height: rect.height/10
              onClicked: {
                console.log(text)
              }
          }
          Button {
              text: qsTr("确定")
              width: rect.width/6
              height: rect.height/10
              onClicked: {
                console.log(text)
              }
          }
      }
}
