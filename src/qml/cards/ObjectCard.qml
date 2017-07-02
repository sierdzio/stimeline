import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import Assistant 1.0
import "../items"

Frame {
    property var object: Assistant.defaultObject()

    signal edit()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        Label {
            text: object.id
            visible: false
            Layout.fillWidth: true
        }

        Label {
            text: object.type
            visible: false
            Layout.fillWidth: true
        }

        SImage {
            width: 40
            height: 40
            visible: relativeSource.length !== 0
            relativeSource: object.picturePath
        }

        Label {
            text: object.name
            font.bold: true
            Layout.fillWidth: true
        }

        // Add a button to show whole description
        Label {
            text: object.description
            elide: Text.ElideRight
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 4
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RowLayout {
            Label {
                text: object.from.toString()
            }

            Label {
                text: " | "
            }

            Label {
                text: object.to.toString()
            }
        }
    }    

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

        onClicked: Timeline.model(object.type).removeObject(object.id)
    }
}
