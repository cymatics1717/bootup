import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Page {
    id:page
    title: qsTr("Home.Page")
    anchors.fill: parent

    Popup {
        id: popup
        modal: true
        dim: true
        focus: true
        property alias content: content

//        anchors.centerIn: parent
        padding: 0
        onOpened: {
            page.opacity = 0.1
        }
        onClosed: page.opacity = 1
        contentItem: Loader {
             id: content
        }
    }

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
            id: leftPanel
            spacing: groupBox1.height/20
            anchors.centerIn: parent
            TButton {
                width: groupBox1.width * .7
                height: groupBox1.height * .1
//                highlighted: true
//                focusPolicy: Qt.NoFocus
                text: qsTr("全关")
                onClicked: {
                    popup.content.source = "qrc:/qml/home/alloff.qml"
                    popup.parent = page
                    popup.width = page.width/3
                    popup.height = page.height/3
                    popup.x = page.width/2 - popup.width/2
                    popup.y = popup.height
                    popup.open()
                }
            }
            TButton {
                id:xiahua
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("下滑指示器")
                onClicked: {
                    content.source = "qrc:/qml/home/xiahua.qml"
                    popup.parent = xiahua
                    popup.x = xiahua.width
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.6
                    popup.open()
                }
            }
            TButton {
                id:hengyao
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("横摇指示器")
                onClicked: {
                    content.source = "qrc:/qml/home/hengyao.qml"
                    popup.parent = hengyao
                    popup.x = hengyao.width
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.3
                    popup.open()
                }
            }
            TButton {
                id:guzhang
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("故障指示灯")
                onClicked: {
                    content.source = "qrc:/qml/home/guzhangjingshi.qml"
                    popup.parent = guzhang
                    popup.x = guzhang.width
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.2
                    popup.open()
                }
            }
            TButton {
                id:qijiang
                width: groupBox1.width * .7
                height: groupBox1.height * .1
                text: qsTr("起降信号灯")
                onClicked: {
                    content.source = "qrc:/qml/home/qijiang.qml"
                    popup.parent = qijiang
                    popup.x = qijiang.width
                    popup.y = height-root.height*.3
                    popup.width = page.width/4
                    popup.height = root.height*.3
                    popup.open()
                }
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
                id:weigan
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("桅杆障碍灯")
                onClicked: {
                    content.source = "qrc:/qml/home/weigan.qml"
                    popup.parent = weigan
                    popup.x = - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.2
                    popup.open()
                }
            }
            TButton {
                id:tatai
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("塔台障碍灯")
                onClicked: {
                    content.source = "qrc:/qml/home/tatai.qml"
                    popup.parent = tatai
                    popup.x = - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.2
                    popup.open()
                }
            }
            TButton {
                id:jiku
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("机库障碍灯")
                onClicked: {
                    content.source = "qrc:/qml/home/jiku.qml"
                    popup.parent = jiku
                    popup.x = - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.2
                    popup.open()
                }
            }
            TButton {
                id:jiaban
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("甲板泛光灯")
                onClicked: {
                    content.source = "qrc:/qml/home/jiaban.qml"
                    popup.parent = jiaban
                    popup.x = - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.2
                    popup.open()
                }
            }
            TButton {
                id:fengxiang
                width: groupBox2.width * .7
                height: groupBox2.height * .1
                text: qsTr("风向指示袋")
                onClicked: {
                    content.source = "qrc:/qml/home/fengxiang.qml"
                    popup.parent = fengxiang
                    popup.x = - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = root.height*.1
                    popup.open()
                }
            }
        }
    }


    footer: ToolBar {
        id:bar
        contentHeight: root.height*.08
        TButton {
            id:left
            text: qsTr("‹")
            color: "#565656"
            radius: 0
            border.width: 0
            anchors.left: parent.left
            width: bar.width/10
            height: bar.height
            anchors.margins: 0
            onClicked: {
                content.source = "qrc:/qml/home/leftbottom.qml"
                popup.width = page.width/2
                popup.height = page.height/2
                popup.open()
            }
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
            text: qsTr("⋮")
            radius: 0
            border.width: 0
            color: "#565656"
            anchors.right: parent.right
            width: bar.width/10
            height: bar.height
            onClicked:{
                console.log("---------------")
                content.source = "Page1Form.qml"

            }
        }
        background: Rectangle {
            color: "#565656"
        }
    }
}
