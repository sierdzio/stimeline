import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

Rectangle {
    property alias eventId: eventId.text
    property alias name: eventName.text
    property alias description: eventDescription.text
    property alias from: eventFrom.text
    property alias to: eventTo.text

    radius: 5
    border {
        width: 1
        color: "#000000"
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columnSpacing: 5
        rowSpacing: 5
        columns: 2

        Label {
            id: eventId
            text: "default"
            //Layout.columnSpan: 2
        }

        Label {
            id: eventName
            text: "default"
            //Layout.columnSpan: 2
        }

        Label {
            id: eventDescription
            text: "default"
            Layout.columnSpan: 2
        }

        Label {
            id: eventFrom
            text: "default"
        }

        Label {
            id: eventTo
            text: "default"
        }
    }
}
