import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400

    title: qsTr("Page 1")

    TextField {
        id: textField
        x: 137
        y: 124
        width: 279
        height: 71
        text: qsTr("Text Field")
    }
}
