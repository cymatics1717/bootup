import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

import "home"
Page {
    id:page
    title: qsTr("普通模式")
    anchors.fill: parent

    property color leftcolor: "#101220"
    property color rightcolor: "#0f1531"
    property color midcolor: "#020710"
    property real ratio: .5
    property real testv:0.3

    Popup {
        id: popup
        modal: true
//        dim: true
//        focus: true
        property alias content: content
        background:Rectangle{
            color: "transparent"
        }
        padding: 0
        contentItem: Loader {
             id: content
             anchors.fill: parent
        }
    }

    Rectangle {
        id: groupBox1
        width: parent.width * .3
        height: parent.height
        anchors.left: parent.left
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 1; color:  leftcolor}
            GradientStop { position: 0; color:  rightcolor}
        }


        Column {
            id: leftPanel
            spacing: groupBox1.height/20
            anchors.centerIn: parent

            TButton {
                id:xiahua
                objectName: "xiahua"
                lightStatus:2
//                lightColor: "grey"
                width: groupBox1.width * ratio
                height: groupBox1.height * .1
                text: qsTr("下滑指示器")
                onClicked: {
                    content.source = "qrc:/qml/home/xiahua.qml"
                    popup.parent = xiahua
                    popup.x = xiahua.width
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = page.height*.6
                    popup.open()
                }
            }
            TButton {
                id:hengyao
                objectName: "hengyao"
                lightStatus:2
                width: groupBox1.width * ratio
                height: groupBox1.height * .1
                text: qsTr("横摇指示器")
                onClicked: {
                    content.source = "qrc:/qml/home/hengyao.qml"
                    popup.parent = hengyao
                    popup.x = hengyao.width
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = page.height*.3
                    popup.open()
                }
            }

            TButton {
                id:jiaban
                objectName: "jiaban"
                lightStatus:2
                width: groupBox2.width * ratio
                height: groupBox2.height * .1
                text: qsTr("甲板平面泛光灯1组")
                onClicked: {
                    content.source = "qrc:/qml/home/jiaban.qml"
                    popup.parent = jiaban
                    popup.x = jiaban.width
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = page.height*.2
                    popup.open()
                }
            }

            TButton {
                id:qijiang
                objectName: "qijiang"
                lightStatus:2
                width: groupBox1.width * ratio
                height: groupBox1.height * .1
                text: qsTr("起降信号灯")
                onClicked: {
                    content.source = "qrc:/qml/home/qijiang.qml"
                    popup.parent = qijiang
                    popup.x = qijiang.width
                    popup.y = height-page.height*.29
                    popup.width = page.width/4
                    popup.height = page.height*.3
                    popup.open()
                }
            }
        }
    }


    TButton {
        objectName: "alloff"
        width: groupBox1.width * .3
        height: groupBox1.height * .1
        color:"#FF111111"
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 1; color: "#91B20000" }
            GradientStop { position: 0; color: "#91FF0000" }
        }

        y: groupBox1.height * .05

        anchors {
            horizontalCenter: groupBox1.horizontalCenter
        }
        text: qsTr("全关")
        onClicked: {
            popup.content.source = "qrc:/qml/home/alloff.qml"
            popup.parent = page
            popup.width = page.width/2
            popup.height = page.height/2
            popup.x = page.width/2 - popup.width/2
            popup.y = page.height/2 -  popup.height/2
            popup.open()
        }
    }

    Rectangle{
        id:ttt
        color: midcolor
        anchors.left: groupBox1.right
        width: parent.width - 2 * groupBox1.width
        height: groupBox1.height*.031
    }
    Rectangle {
        color: midcolor
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

        CircularGauge {
            id: fuelGauge1
            value: page.testv
            maximumValue: 1
            x:parent.width/2 - width*1.5
//            y: parent.height / 2 - height
            width: parent.width/4
            height: parent.height * 0.3

            style: IconGaugeStyle {
                id: fuelGaugeStyle1

//                icon: "qrc:/images/fuel-icon.png"
                minWarningColor: Qt.rgba(0.5, 0, 0, 1)

                tickmarkLabel: Text {
                    color: "white"
                    visible: styleData.value === 0 || styleData.value === 1
                    font.pixelSize: fuelGaugeStyle1.toPixels(0.225)
                    text: styleData.value === 0 ? "-10" : (styleData.value === 1 ? "10" : "")
                }
            }
        }

        CircularGauge {
            id: fuelGauge2
            value: page.testv
            maximumValue: 1
            x:parent.width/2 + width/2
//            y: parent.height / 2 - height
            width: parent.width/4
            height: parent.height * 0.3

            style: IconGaugeStyle {
                id: fuelGaugeStyle2

//                icon: "qrc:/images/fuel-icon.png"
                minWarningColor: Qt.rgba(0.5, 0, 0, 1)

                tickmarkLabel: Text {
                    color: "white"
                    visible: styleData.value === 0 || styleData.value === 1
                    font.pixelSize: fuelGaugeStyle2.toPixels(0.225)
                    text: styleData.value === 0 ? "-10" : (styleData.value === 1 ? "10" : "")
                }
            }
        }
        Text {
            text:qsTr("横摇表盘")
            color: "white"
            y:fuelGauge1.y+ fuelGauge1.height/2
            anchors {
//                top: fuelGauge1.bottom
                horizontalCenter: fuelGauge1.horizontalCenter
//                verticalCenter:  fuelGauge1.verticalCenter
            }
        }
        Text {
            text:qsTr("纵摇表盘")
            color: "white"
            y:fuelGauge2.y+ fuelGauge2.height/2
            anchors {
//                top: fuelGauge2.bottom
                horizontalCenter: fuelGauge2.horizontalCenter
//                verticalCenter:  fuelGauge2.verticalCenter
            }
        }
    }



    Rectangle {
        id: groupBox2
        width: parent.width * .3
        height: parent.height
        anchors.right: parent.right
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0; color:  leftcolor}
            GradientStop { position: 1; color:  rightcolor}
        }

        Column {
            id: row2
            spacing: 50
            anchors.centerIn: parent
            TButton {
                id:weigan
                objectName: "weigan"
                lightStatus:1
                width: groupBox2.width * ratio
                height: groupBox2.height * .1
                text: qsTr("桅杆障碍灯")
                onClicked: {
                    content.source = "qrc:/qml/home/weigan.qml"
                    popup.parent = weigan
                    popup.x = 10 - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = page.height*.2
                    popup.open()
                }
            }
            TButton {
                id:tatai
                objectName: "tatai"
                lightStatus:1
                width: groupBox2.width * ratio
                height: groupBox2.height * .1
                text: qsTr("塔台障碍灯")
                onClicked: {
                    content.source = "qrc:/qml/home/tatai.qml"
                    popup.parent = tatai
                    popup.x = 10 - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = page.height*.2
                    popup.open()
                }
            }
            TButton {
                id:jiku
                objectName: "jiku"
                lightStatus:1
                width: groupBox2.width * ratio
                height: groupBox2.height * .1
                text: qsTr("机库障碍灯")
                onClicked: {
                    content.source = "qrc:/qml/home/jiku.qml"
                    popup.parent = jiku
                    popup.x =10 - page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = page.height*.2
                    popup.open()
                }
            }

            TButton {
                id:fengxiang
                objectName: "fengxiang"
                lightStatus:1
                width: groupBox2.width * ratio
                height: groupBox2.height * .1
                text: qsTr("风向指示袋")
                onClicked: {
                    content.source = "qrc:/qml/home/fengxiang.qml"
                    popup.parent = fengxiang
                    popup.x = 10- page.width/4
                    popup.y = 0
                    popup.width = page.width/4
                    popup.height = page.height*.1
                    popup.open()
                }
            }
        }
    }


    footer: Rectangle {
        id:bar
        height: page.height*.08
        TButton {
            id:left
            text: qsTr("菜单")
            radius: 0
            border.width: 0
            anchors.left: parent.left
            width: bar.width/10
            height: bar.height
            onClicked: {
//                menu.source = "qrc:/qml/home/startmenu.qml"
                startm.width = left.width*1.2
                startm.height = bar.height*8
                startm.y = -startm.height
                startm.open()
            }

            StartMenu {
                id:startm
            }


//            Popup {
//                id: startm
//                modal: true
//                dim: true
//                property alias content: menu
//                contentItem: Loader {
//                     id: menu
//                     anchors.fill: parent
//                }
//            }
        }

        TButton {
            id: right
            text: qsTr("⋮")
            border.width: 0
            anchors.right: parent.right
            width: bar.width/10
            height: bar.height
            onClicked:{
                panel.text += new Date().toLocaleString(Qt.locale(),"yyyy/MM/dd hh:mm:ss.z") + "\n"
                content.source = "Page1Form.qml"
            }
        }

        ScrollView {
            id:panel
            property real ratio: 1
            property alias text: edit.text
            width: bar.width - left.width - right.width - 20
            height: ratio*bar.height
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            ScrollBar.vertical.width: width/40
            ScrollBar.vertical.contentItem: Rectangle {
                      color: parent.pressed ? "#5555ff" : "#55aaff"
                  }
            ScrollBar.horizontal.interactive: true
            ScrollBar.vertical.interactive: true
            clip: true
            anchors {
                bottom: parent.bottom
                left: left.right
                horizontalCenter: parent.horizontalCenter
//                verticalCenter:  parent.verticalCenter
            }
            background: Rectangle {
                gradient: left.rgradient
            }
            Label  {
                id: edit
                color: "red"
                font {
                    bold: true
                    pointSize: 15
                }
                height: parent.height
                anchors.fill: parent
                focus: false
            }
        }
        Button {
            id: togglebtn
            width: page.width/30
            height: page.height/20
            focusPolicy: Qt.NoFocus
            anchors{
                bottom: panel.top
                right: panel.right
            }
            contentItem: Rectangle {
                anchors.fill: parent
                gradient: left.lgradient
                Text {
                    id:innertxt
                    text:qsTr('\u2B06')
                    anchors.centerIn:  parent
                    font {
                        bold: true
                        pointSize: 30
                    }
                    color: "white"
                }
            }
            onClicked:{
                if(panel.ratio==1){
                    panel.ratio = 3;
                    innertxt.text =  qsTr('\u2B06')
                } else if(panel.ratio==3) {
                    panel.ratio = 6;
                    innertxt.text =  qsTr('\u2B07')
                } else if(panel.ratio==6) {
                    panel.ratio = 1;
                    innertxt.text =  qsTr('\u2B06')
                }
            }
        }
    }

}
