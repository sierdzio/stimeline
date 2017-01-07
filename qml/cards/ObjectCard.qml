import QtQuick 2.8
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import Assistant 1.0

Frame {
    property alias objectId: objectId.text
    property alias type: type.text
    property alias name: name.text
    property alias picturePath: picturePath.source
    property alias description: description.text
    property alias from: from.text
    property alias to: to.text

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
        text: qsTr("DEL")
        font.pointSize: 8

        onClicked: Timeline.eventModel.removeEvent(objectId.text)
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columnSpacing: 5
        rowSpacing: 5
        columns: 2

        Label {
            id: objectId
            text: "default"
            visible: false
        }

        Label {
            id: type
            text: "None"
            visible: false
        }

        Image {
            id: picturePath
            source: ""
        }

        Label {
            id: name
            text: "default"
        }

        Label {
            id: description
            text: "default"
            Layout.columnSpan: 2
        }

        Label {
            id: from
            text: "default"
        }

        Label {
            id: to
            text: "default"
        }
    }
}
