import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
//    focus: false
    property string text
    property alias fontSize:txt.font.pixelSize
    property alias source:icon.source
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

    FontMetrics {
        id: fontMetrics
//        font.family: "Arial"
    }

    Image {
        id:icon
        anchors.right: txt.left
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: txt
        text: parent.text
        color: "white"
        font.pixelSize: fontMetrics.font*3
        anchors.left: icon.right
        anchors.centerIn:  parent
    }


    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered:  {
            parent.opacity = .3
        }
        onExited:   {
            parent.opacity = 1
//            page.opacity = 1
        }
        onPressed:  fenter()
        onReleased: fleave()
//        onCanceled: fleave()
        onClicked:{
            console.log(parent.objectName + " clicked.")
            parent.clicked()
        }
    }

    function fenter(){
        if(objectName && objectName.length>0){
//            console.log(popup.content.item+"++++++++++++"+objectName+"++"+popup.content.source)
            if(JSON.stringify(popup.content.source).includes(objectName) ){
                opacity = 1
            } else {
                opacity = .1
            }
        }
    }
    function fleave(){
        if(objectName && objectName.length>0){
//            console.log(popup.content.item.objectName+"---------------------"+objectName+"--"+popup.content.source)
            opacity = 1
            page.opacity = 1
        }
    }
}
