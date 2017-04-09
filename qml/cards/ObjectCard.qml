import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import Assistant 1.0
import "../items"

Frame {
    property alias objectId: objectIdLabel.text
    property alias type: typeLabel.text
    property alias name: nameLabel.text
    property alias picturePath: picturePathLabel.relativeSource
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

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

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

        SImage {
            id: picturePathLabel
            width: 40
            height: 40
            visible: relativeSource.length !== 0
        }

        Label {
            id: nameLabel
            text: "default"
        }

        // TODO: make description small & fading away when it is big.
        // Add a button to show it all
        Label {
            id: descriptionLabel
            text: "default"
            elide: Text.ElideRight
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 2
            //Layout.columnSpan: 2
        }

        RowLayout {
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
}
