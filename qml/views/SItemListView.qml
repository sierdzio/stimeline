import QtQuick 2.7
import QtQuick.Controls 2.1
import Assistant 1.0

Page {
    default property alias delegate: view.delegate
    property alias model: view.model
    property alias buttonVisible: button.visible
    signal clicked()

    id: root

    ListView {
        id: view
        anchors.fill: parent
        spacing: 15
        clip: true
    }

    RoundButton {
        id: button
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: Assistant.buttonMargin
        text: "+"
        font.bold: true
        radius: 15

        onClicked: root.clicked()
    }
}
