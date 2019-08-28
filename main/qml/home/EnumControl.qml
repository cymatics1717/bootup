import QtQuick 2.0
import QtQuick.Controls 2.5
import ".."
Rectangle {
    id: root
    radius: 3
    color: "white"
    property alias title: title.text
    property alias value: info.text
    property int rradius: height/5
    property int margin: 20
    property int status: 9 // 默认单闪：0x1001

    border.color: "grey"
    border.width: 0.02 * height
    signal clicked()

//    anchors.margins: 3
//    anchors.rightMargin: 6
    gradient: Gradient {
        GradientStop { position: 1; color: "#1e315b" }
        GradientStop { position: 0; color: "#22335c" }
    }

    function reset(){
        all.opacity = 1
        single.opacity = 1
        none.opacity = 1
    }

    Text {
        id:title
        anchors.leftMargin: 5
        color: "white"
        anchors{
            left: parent.left
//            leftMargin: margin
        }
    }
    Text {
        id:info
        color: "grey"
        anchors{
            left: title.right
        }
    }

    Rectangle {
        id:none
        color: "green"
        radius: rradius
        width: radius*3
        height: radius*3

        anchors{
            left: parent.left
            top: title.bottom
            leftMargin: margin
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered:  {
                parent.opacity = .3
            }
            onExited:   {
                if(root.status!=5){
                    parent.opacity = 1
                }
            }
            onClicked:{
//                console.log(parent.objectName + " clicked.")
                reset()
                root.status = 5 //不闪：0x0101
                parent.opacity = .1
                root.clicked()
            }
        }
        Text {
            text: qsTr("不闪")
            x: parent.radius/4
            anchors.leftMargin: 5
            color: "white"
            anchors{
                centerIn: parent
            }
        }
    }

    Rectangle {
        id:all
        color: "#ff7700"
        radius: rradius
        width: radius*3
        height: radius*3
        anchors{
            left: none.right
            top: title.bottom
            leftMargin: margin
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered:  {
                parent.opacity = .3
            }
            onExited:   {
                if(root.status!=13){
                    parent.opacity = 1
                }
            }
            onClicked:{
//                console.log(parent.objectName + " clicked.")
                reset()
                root.status = 13 //全闪：0x1101
                parent.opacity = .1
                root.clicked()
            }
        }
        Text {
            text: qsTr("全闪")
            anchors.leftMargin: 5
            color: "white"
            x: parent.radius/4
            anchors.centerIn: parent
        }

    }
    Rectangle {
        id:single
        color: "#ff0000"
        radius: rradius
        width: radius*3
        height: radius*3
        anchors{
            left: all.right
            top: title.bottom
            leftMargin: margin
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered:  {
                parent.opacity = .3
            }
            onExited:   {
                if(root.status!=9){
                    parent.opacity = 1
                }
            }
            onClicked:{
//                console.log(parent.objectName + " clicked.")
                reset()
                root.status = 9 //单闪：0x1001
                parent.opacity = .1
                root.clicked()
            }
        }
        Text {
            text: qsTr("单闪")
            anchors.leftMargin: 5
            color: "white"
            x: parent.radius/4
            anchors.centerIn: parent
        }
    }
}
