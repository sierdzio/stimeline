import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import Assistant 1.0

Frame {
    property alias eventId: eventId.text
    property alias name: eventName.text
    property alias description: eventDescription.text
    property alias from: eventFrom.text
    property alias to: eventTo.text

    signal edit()

    MouseArea {
        anchors.fill: parent
        onDoubleClicked: edit();
    }

    Button {
        anchors {
            top: parent.top
            right: parent.right
            margins: 5
        }
        width: 35
        height: width
        text: "DEL"
        font.pointSize: 8

        onClicked: Timeline.eventModel.removeEvent(eventId.text)
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
            visible: false
        }

        Label {
            id: eventName
            text: "default"
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
