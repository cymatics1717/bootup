import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    anchors.fill: parent


    title: qsTr("Page 2")

    Label {
        text: qsTr("You are on Page 2.")
        anchors.centerIn: parent
    }
    Component.onCompleted: {
        console.info(objectName +" loaded.")
    }
}
