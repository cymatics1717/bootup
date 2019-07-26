import QtQuick 2.12
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

    color: "#111111"
    gradient: Gradient {
        orientation: Gradient.Horizontal
        GradientStop { position: 0.73; color: "#FF032154" }
        GradientStop { position: 0.0; color: "#FF2F3A60" }
    }
    Text {
        text: parent.text
        color: "white"
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
            rect.state === "on" ? rect.state = "off":rect.state = "off"
        }
    }
    states: [
        State {
            name: "on"
        },
        State {
            name: "off"
        },
        State {
            name: "active"
        }
    ]

}
