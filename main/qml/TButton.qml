import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    focus: true
// public
    property string text: 'text'

    signal clicked();

    border.color: "grey"
    border.width: 0.02 * height
    radius:       0.05  * height
    opacity:      enabled? 1: 0.3

    Text {
        text: parent.text
        font.pixelSize: 0.25 * parent.height
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered:  parent.opacity = .3
        onExited:   parent.opacity = 1
        onPressed:  parent.opacity = 1
        onReleased: parent.opacity = 1
        onCanceled: parent.opacity = 1
        onClicked:{
            parent.clicked()
        }
    }

}
