import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Rectangle {
    id:rect
//    width: frame.implicitWidth + 10
//    height: frame.implicitHeight + 10
    color: "transparent"
    anchors.fill: parent
    property color textcolor: "white"
    property color backcolor: "#ff222222"
    signal closed();

    function formatText(count, modelData) {
        var data = count === 12 ? modelData + 1 : modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }

    FontMetrics {
        id: fontMetrics
    }

    Row {
        id: row
        anchors.centerIn: parent

        TextField {
            id: year
            text: "20"
            color:textcolor
            validator: IntValidator{bottom: -180; top: 180;}
            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                color: backcolor
                radius: width/5
                border.color: parent.focused ? "#21be2b" : "transparent"
            }
        }
        Text {
            text: qsTr("年")
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: month
            text: "20"
            color:textcolor
            validator: IntValidator{bottom: -180; top: 180;}
            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                color: backcolor
                radius: width/5
                border.color: parent.hovered ? "#21be2b" : "transparent"
            }
        }
        Text {
            text: qsTr("月")
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: day
            text: "20"
            color:textcolor
            validator: IntValidator{bottom: -180; top: 180;}
            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                color: backcolor
                radius: width/5
                border.color: parent.hovered ? "#21be2b" : "transparent"
            }
        }
        Text {
            text: qsTr("日")
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: hour
            text: "20"
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
            validator: IntValidator{bottom: -180; top: 180;}
            background: Rectangle {
                color: backcolor
                radius: width/5
                border.color: parent.hovered ? "#21be2b" : "transparent"
            }
        }
        Text {
            text: qsTr("时")
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: minitue
            text: "20"
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
            validator: IntValidator{bottom: -180; top: 180;}
            background: Rectangle {
                color: backcolor
                radius: width/5
                border.color: parent.hovered ? "#21be2b" : "transparent"
            }
        }
        Text {
            text: qsTr("分")
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: secs
            text: "20"
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
            validator: IntValidator{bottom: -180; top: 180;}
            background: Rectangle {
                color: backcolor
                radius: width/5
                border.color: parent.hovered ? "#21be2b" : "transparent"
            }
        }
        Text {
            text: qsTr("秒")
            color:textcolor
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Row {
        id: main
        anchors.horizontalCenter: rect.horizontalCenter
        y:rect.height*2/3
        spacing: rect.width/6
        SButton {
            text: qsTr("取消")
            width: rect.width/6
            height: rect.height/10
            onClicked: {
                console.log(text)
                backend.closeAll()
                popup.close()
            }
        }
        SButton {
            text: qsTr("确定")
            width: rect.width/6
            height: rect.height/10
            onClicked: {
                var tmp = new Date()
                tmp.setFullYear(year.text)
                tmp.setMonth(month.text-1)
                tmp.setDate(day.text)
                tmp.setHours(hour.text)
                tmp.getMinutes(minitue.text)
                tmp.getSeconds(secs.text)
                console.log(tmp.toLocaleString())
                backend.setDateTime(tmp)
                popup.close()
            }
        }
    }
    Timer {
        interval: 100;
        running: true;
//        repeat: true
        onTriggered: {
            var tmp = new Date()
            console.log(tmp.toLocaleString())
            year.text = tmp.getFullYear()
            month.text = tmp.getMonth()+1
            day.text = tmp.getDate()
            hour.text = tmp.getHours()
            minitue.text = tmp.getMinutes()
            secs.text = tmp.getSeconds()
        }
    }
}
