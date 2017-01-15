import QtQuick 2.8
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import Assistant 1.0

Frame {
    property alias objectId: objectIdLabel.text
    property alias type: typeLabel.text
    property alias name: nameLabel.text
    property alias picturePath: picturePathLabel.source
    property alias description: descriptionLabel.text
    property alias from: fromLabel.text
    property alias to: toLabel.text

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

        onClicked: Timeline.model(type).removeObject(objectId)
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columnSpacing: 5
        rowSpacing: 5
        columns: 2

        Label {
            id: objectIdLabel
            text: "default"
            visible: false
        }

        Label {
            id: typeLabel
            text: "No type"
            visible: false
        }

        Image {
            id: picturePathLabel
            source: ""
        }

        Label {
            id: nameLabel
            text: "default"
        }

        Label {
            id: descriptionLabel
            text: "default"
            Layout.columnSpan: 2
        }

        Label {
            id: fromLabel
            text: "default"
        }

        Label {
            id: toLabel
            text: "default"
        }
    }
}
