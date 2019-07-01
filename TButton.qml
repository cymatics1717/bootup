import QtQuick 2.0

Rectangle {
    id: root
    focus: true
// public
    property string text: 'text'
//    property string color: 'color'
    signal clicked();

// private
//    width: 250;  height: 50
    border.color: "grey"
    border.width: 0.02 * root.height
    radius:       0.05  * root.height
    opacity:      enabled? 1: 0.3

    Text {
        text: root.text
        font.pixelSize: 0.25 * root.height
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered:  parent.opacity = .3
        onExited:   parent.opacity = 1
        onPressed:  parent.opacity = .5
        onReleased: parent.opacity = 1
        onCanceled: parent.opacity = 1
        onClicked:  root.clicked() // emit
    }
}
