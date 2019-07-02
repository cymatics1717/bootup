import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    anchors.fill: parent

    title: qsTr("Page 1")

    TextField {
        id: textField
        anchors.fill: parent

        text: qsTr("Text Field")
    }
    Component.onCompleted: {
        console.info(objectName +" loaded.")
    }
}
