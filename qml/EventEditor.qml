import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Popup {
    property string eventId: ""
    property alias name: eventName.text
    property alias description: eventDescription.text
    property alias from: eventFrom.text
    property alias to: eventTo.text
    signal finished()
    signal canceled()

    onFinished: close()
    onCanceled: close()

    id: root
    width: 600
    height: 800
    closePolicy: Popup.NoAutoClose
    modal: true
    focus: true

    GridLayout {
        anchors.fill: parent
        columns: 2

        Label {
            text: qsTr("Edit event")
            Layout.columnSpan: 2
        }

        Label {
            text: qsTr("Name")
        }

        TextField {
            id: eventName
        }

        Label {
            text: qsTr("Description")
        }

        TextField {
            id: eventDescription
        }

        Label {
            text: qsTr("From")
        }

        TextField {
            id: eventFrom
        }

        Label {
            text: qsTr("To")
        }

        TextField {
            id: eventTo
        }

        Button {
            text: qsTr("OK")
            onClicked: root.finished()
        }


        Button {
            text: qsTr("Cancel")
            onClicked: root.canceled()
        }
    }
}
