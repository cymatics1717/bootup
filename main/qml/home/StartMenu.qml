import QtQuick 2.13
import QtQuick.Controls 2.5

import ".."

Menu {
    id: menu
    modal: true
    dim:true
    property color leftColor: "#2c395f"
    property color rightColor: "#082355"
    property color ccolor: "#88888888"
    property var grad: Gradient {
        orientation: Gradient.Horizontal
        GradientStop { position: 1; color: leftColor }
        GradientStop { position: 0; color: rightColor }
    }
    property var gradddd: Gradient {
        orientation: Gradient.Horizontal
        GradientStop { position: 0; color: leftColor }
        GradientStop { position: 1; color: rightColor }
    }

    background: Rectangle {
        gradient: grad
    }
    font.pointSize: 15


    Menu {
        id: m1
        title: qsTr("信号源")
        font.pointSize: 15
        MenuItem {
            text: qsTr("内部");
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: parent.highlighted ? ccolor:"white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: menu.width
                implicitHeight: menu.height/5
                opacity: enabled ? 1 : 0.3
                gradient: menu.gradddd

                color: parent.highlighted ? leftColor : rightColor
            }

            onTriggered: {
                console.log(text)
            }
        }
        MenuItem {
            text: qsTr("外部");
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: parent.highlighted ? ccolor:"white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: menu.width
                implicitHeight: menu.height/5
                opacity: enabled ? 1 : 0.3
                gradient: menu.gradddd

                color: parent.highlighted ? leftColor : rightColor
            }
            onTriggered: {
                console.log(text)
            }
        }
        background: Rectangle {
            implicitWidth: menu.width
            implicitHeight: menu.height/5
            opacity: enabled ? 1 : 0.3
            gradient: menu.gradddd

            color: parent.highlighted ? leftColor : rightColor
        }

    }
    Action {
        text: qsTr("日间模式");
        onTriggered: {
            console.log(text)
        }
    }
    Menu {
        title: qsTr("故障警示灯")
        font.pointSize: 15
        background: Rectangle {
            implicitWidth: menu.width
            implicitHeight: menu.height/5
            opacity: enabled ? 1 : 0.3
            gradient: menu.gradddd

            color: parent.highlighted ? leftColor : rightColor
        }
        MenuItem {
            text: qsTr("夜视开关");
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: parent.highlighted ? ccolor:"white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: menu.width
                implicitHeight: menu.height/5
                opacity: enabled ? 1 : 0.3
                gradient: menu.gradddd

                color: parent.highlighted ? leftColor : rightColor
            }
            onTriggered: {
                console.log(text)
            }
        }
        MenuItem {
            text: qsTr("光强控制");
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: parent.highlighted ? ccolor:"white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: menu.width
                implicitHeight: menu.height/5
                opacity: enabled ? 1 : 0.3
                gradient: gradddd

                color: parent.highlighted ? leftColor : rightColor
            }
            onTriggered: {
                console.log(text)
            }
        }
    }
    Action {
        text: qsTr("重启");
        onTriggered: {
            console.log(text)
        }
    }
    Action {
        text: qsTr("关机");
        onTriggered: {
            console.log(text)
        }
    }

    delegate: MenuItem {
        implicitWidth: menu.width
        implicitHeight: menu.height/5

        contentItem: Text {
            text: parent.text
            font: parent.font
            opacity: enabled ? 1.0 : 0.3
            color: parent.highlighted ? ccolor:"white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: menu.width
            implicitHeight: menu.height/5
            opacity: enabled ? 1 : 0.3
            gradient: menu.grad

            color: parent.highlighted ? leftColor : rightColor
        }
    }
}


//Rectangle {
//    id:rect
//    anchors.fill: parent

//    gradient: Gradient {
//        GradientStop { position: 1; color: "#1e315b" }
//        GradientStop { position: 0; color: "#22335c" }
//    }

//    Column {

//        SButton {
//            border.width: 0
//            text: qsTr("信号源")
//            width: bar.width/10
//            height: bar.height
//            onClicked:{
//                console.log("---------------")
//                panel.text += new Date().toLocaleString(Qt.locale(),"yyyy/MM/dd hh:mm:ss.z") + "\n"
//            }
//        }
//        SButton {
//            border.width: 0
//            text: qsTr("日间模式")
//            width: bar.width/10
//            height: bar.height
//            onClicked:{
//                console.log("---------------")
//                panel.text += new Date().toLocaleString(Qt.locale(),"yyyy/MM/dd hh:mm:ss.z") + "\n"
//            }
//        }
//        SButton {
//            text: qsTr("故障警示灯")
//            anchors.right: parent.right
//            border.width: 0
//            width: bar.width/10
//            height: bar.height
//            onClicked:{
//                console.log("---------------")
//                panel.text += new Date().toLocaleString(Qt.locale(),"yyyy/MM/dd hh:mm:ss.z") + "\n"
//            }
//        }
//        SButton {
//            text: qsTr("重启")
//            border.width: 0
//            width: bar.width/10
//            height: bar.height
//            onClicked:{
//                console.log("---------------")
//                panel.text += new Date().toLocaleString(Qt.locale(),"yyyy/MM/dd hh:mm:ss.z") + "\n"
//            }
//        }
//        SButton {
//            text: qsTr("关机")
//            border.width: 0
//            width: bar.width/10
//            height: bar.height
//            onClicked:{
//                console.log("---------------")
//                panel.text += new Date().toLocaleString(Qt.locale(),"yyyy/MM/dd hh:mm:ss.z") + "\n"
//            }
//        }
//    }

//    Menu {
//        id: recentFilesSubMenu
//        title: qsTr("Recent Files")
//        enabled: recentFilesInstantiator.count > 0


//        MenuSeparator {}

//        MenuItem {
//            text: qsTr("Clear Recent Files")
//            onTriggered: settings.clearRecentFiles()
//        }
//    }
//}
