import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    focus: true
// public
    property string text: 'text'
    property int tag
    property alias content: content
    property alias pWidth: popup.width
    property alias pHeight: popup.height
    property alias px: popup.x
    property alias py: popup.y
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
            popup.open()
            parent.clicked()
        }
    }

    Popup {
        id: popup
        modal: true
        dim: true
        focus: true
        x: tag==1? parent.x + parent.width: (tag==-1?parent.x - width: parent.width - width)
        y: tag==0?-height:0
        width: 2*parent.width
        height: 2*parent.height
//        anchors.centerIn: parent
//        bottomMargin:  parent.height
        onOpened: page.opacity = 0.4
        onClosed: page.opacity = 1
        contentItem: Loader {
             anchors.fill: parent
             id: content
        }
    }
}
