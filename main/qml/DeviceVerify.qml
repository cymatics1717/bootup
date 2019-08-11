import QtQuick 2.12
import QtQuick.Controls 2.5
import ".."
Rectangle {
    id:rect
    anchors.fill: parent

//    color: "transparent"
    gradient: Gradient {
        GradientStop { position: 1; color: "#1e315b" }
        GradientStop { position: 0; color: "#22335c" }
    }

    SButton {
        text: qsTr("返回")
        fontSize:18
        width: rect.width*.1
        height: rect.height/20
        gradient: Gradient {
            GradientStop { position: 0; color: "transparent" }
        }
        border.width: 0
        source: "qrc:/res/left-icon.png"
        onClicked: {
            console.log(text)
            stackView.pop(null)
        }
    }

    Text {
        id: txt
        color: "white"
        anchors.horizontalCenter: rect.horizontalCenter
        y: parent.height*.3
        font.pointSize: 20
        text: qsTr("设备验证")
    }

    TextField {
        id: value
        placeholderText: qsTr("点击输入密码")
        font.pointSize: 18
//        color: "green"
//        echoMode: TextInput.PasswordEchoOnEdit
        echoMode: TextInput.Password
        horizontalAlignment: TextInput.AlignHCenter
//        validator: IntValidator{bottom: ; top: 180;}
        height: rect.height/15
        width: rect.width/4
        anchors.top: txt.bottom
        anchors.topMargin: height*3/2
        anchors.horizontalCenter: parent.horizontalCenter
        background: Rectangle {
            color: value.focus ? "white" : "grey"
            radius: width/10
            border.color: value.focus ? "#21be2b" : "grey"
            border.width: 1
        }
    }

    SButton {
        text: qsTr("登录")
        fontSize: 18
        width: value.width
        height: value.height
        anchors.top: value.bottom
        anchors.horizontalCenter: rect.horizontalCenter
        anchors.topMargin: height/2
        radius: width/10

        onClicked: {
            console.log(value.text)
            backend.testQML(value.text)
            stackView.push("qrc:/qml/SelectMode.qml")
        }
    }
}
