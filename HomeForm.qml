import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Page {
    id:page
    title: qsTr("Home.Page")
    anchors.fill: parent
    //    background: Rectangle {
    //        color: "#272727"
    ////        color:Qt.rgba(39,39,39,255)
    //    }

    Rectangle {
        id: groupBox1
        width: parent.width * .3
        height: parent.height
        anchors.left: parent.left
        //        title: qsTr("Group")
        //        background: Rectangle {
        color: "#464646"
        //        }

        Column {
            id: row
            spacing: 50
            anchors.centerIn: parent
            TButton {
                tag: 1
                width: groupBox1.width * .7
                height: groupBox1.height * .1
//                highlighted: true
//                focusPolicy: Qt.NoFocus
                text: qsTr("全关")
            }
            TButton {
                tag: 1
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("下滑指示器")
            }
            TButton {
                tag: 1
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("横摇指示器")
            }
            TButton {
                tag: 1
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("故障指示灯")
            }
            TButton {
                tag: 1
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("起降信号灯")
            }
        }
    }


    Rectangle{
        id:ttt
        color: "#272727"
        anchors.left: groupBox1.right
        width: parent.width - 2 * groupBox1.width
        height: groupBox1.height*.031
    }
    Rectangle {
        color: "#272727"
        anchors.left: groupBox1.right
        anchors.top: ttt.bottom
        //        color: "red"
        width: parent.width - 2 * groupBox1.width
        height: groupBox1.height- ttt.height
        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "qrc:/res/boat.png"
        }
    }


    Rectangle {
        id: groupBox2
        width: parent.width * .3
        height: parent.height
        anchors.right: parent.right
        //            title: qsTr("Group Box")
        //            background: Rectangle {
        color: "#464646"
        //            }

        Column {
            id: row2
            spacing: 50
            anchors.centerIn: parent
            TButton {
                tag: -1
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("桅杆障碍灯")
            }
            TButton {
                tag: -1
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("塔台障碍灯")
            }
            TButton {
                tag: -1
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("机库障碍灯")
            }
            TButton {
                tag: -1
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("甲板泛光灯")
            }
            TButton {
                tag: -1
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("风向指示袋")
            }
        }
    }


    footer: ToolBar {
        id:bar
        contentHeight: root.height*.08
        TButton {
            id:left
            tag:0
            text: qsTr("‹")
            color: "#565656"
            radius: 0
            border.width: 0
            anchors.left: parent.left
            width: bar.width/10
            height: bar.height
            anchors.margins: 0
        }
        ToolSeparator {
            orientation: Qt.Vertical
            anchors.left: left.right
            height: bar.height
        }

        TextField {
            id: input
            text: qsTr("信息栏")
            anchors.centerIn: parent
            width: bar.width - left.width - right.width - 20
            height: bar.height*3/4
        }
        ToolSeparator {
            orientation: Qt.Vertical
            anchors.right: right.left
            height: bar.height
        }
        TButton {
            id: right
            tag:0
            text: qsTr("⋮")
            radius: 0
            border.width: 0
            color: "#565656"
            anchors.right: parent.right
            width: bar.width/10
            height: bar.height
            pWidth: bar.width/3
            pHeight: bar.height*2
            onClicked:{
                console.log("---------------")
            }
        }
        background: Rectangle {
            color: "#565656"
        }
    }
}
