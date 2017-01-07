import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import Assistant 1.0

Popup {
    property string objectId: ""
    property string type: ""
    property alias name: name.text
    property alias picturePath: picturePath.source
    property alias description: description.text
    property alias from: from.text
    property alias to: to.text
    property var __editControl: from
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

    DateTimeEditor {
        id: dateTimeEditor

        onFinished: __editControl.text = dateTimeEditor.dateTime;
    }

    GridLayout {
        anchors.fill: parent
        columns: 2

        Label {
            text: qsTr("Edit %1").arg(Assistant.typeToString(type)) // TODO: translate Type!
            Layout.columnSpan: 2
        }

        Image {
            id: picturePath
        }

        Label {
            text: qsTr("Name")
        }

        TextField {
            id: name
        }

        Label {
            text: qsTr("Description")
        }

        TextField {
            id: description
        }

        Label {
            text: qsTr("From")
        }

        Label {
            id: from
            text: "1-1-1 1:1:1"

            MouseArea {
                anchors.fill: parent
                onDoubleClicked: {
                    __editControl = parent;
                    dateTimeEditor.setDateTimeFromString(parent.text);
                    dateTimeEditor.open();
                }
            }
        }

        Label {
            text: qsTr("To")
        }

        Label {
            id: to
            text: "1-1-1 1:1:1"

            MouseArea {
                anchors.fill: parent
                onDoubleClicked: {
                    __editControl = parent;
                    dateTimeEditor.setDateTimeFromString(parent.text);
                    dateTimeEditor.open();
                }
            }
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
