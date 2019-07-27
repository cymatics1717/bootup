import QtQuick 2.13
import QtQuick.Controls 2.5

Rectangle {
    focus: true
    property string text
    property int lightStatus: 0
    property color lightColor: "#ff00ff00"
    property color leftColor: "#2e3a60"
    property color rightColor: "#090d21"
    property var lgradient: Gradient {
        orientation: Gradient.Horizontal
        GradientStop { position: 0; color: leftColor }
        GradientStop { position: 1; color: rightColor }
    }
    property var rgradient: Gradient {
        orientation: Gradient.Horizontal
        GradientStop { position: 0; color: rightColor }
        GradientStop { position: 1; color: leftColor }
    }
//    property color lightColor: "grey"

    signal clicked();

    border.color: "grey"
    border.width: 0.02 * height
    radius:       0.05 * height
//    opacity:      enabled? 1: 0.3

    color: "#111111"

    gradient: lightStatus%2+1==2?rgradient:lgradient

    Text {
        text: parent.text
        color: "white"
        font.pixelSize: 0.25 * parent.height
        anchors.centerIn: parent
    }
    Rectangle {
        id: llight
        color: lightColor
        width: parent.width*.04
        height: parent.height*.4
        radius: width/2
        visible: lightStatus==1?true:false
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            margins: parent.width*.1
        }
    }
    Rectangle {
        id: rlight
        color: lightColor
        width: parent.width*.04
        height: parent.height*.4
        radius: width/2
        visible: lightStatus==2?true:false
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            margins: parent.width*.1
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered:  {
            parent.opacity = .3
            llight.rotation = 90
            rlight.rotation = 90
        }
        onExited:   {
            parent.opacity = 1
            page.opacity = 1
            llight.rotation = 0
            rlight.rotation = 0
        }
//        onPressed:  fenter()
//        onReleased: fleave()
//        onCanceled: fleave()
        onClicked:{
            console.log(parent.objectName + " clicked.")
            parent.clicked()
        }
    }

    Connections {
        target: popup
        onOpened: if(popup.content.source) fenter()
        onClosed: if(popup.content.source) fleave()
    }

    function fenter(){
//        console.log(popup.content.item+"++++++++++++"+objectName+"++"+popup.content.source)
//        console.log(typeof(JSON.stringify(popup.content.source)))
//        page.opacity = 0.1
        if(JSON.stringify(popup.content.source).includes(objectName) ){
            opacity = 1
            llight.rotation = 90
            rlight.rotation = 90
        } else {
            opacity = .1
        }

    }
    function fleave(){
//        console.log(popup.content.item.objectName+"---------------------"+objectName+"--"+popup.content.source)
        opacity = 1
        page.opacity = 1
        llight.rotation = 0
        rlight.rotation = 0
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
