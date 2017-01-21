import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import Assistant 1.0

Popup {
    property string objectId: ""
    property string type: ""
    property alias name: nameLabel.text
    property alias picturePath: picturePathLabel.path
    property alias description: descriptionLabel.text
    property alias from: fromLabel.text
    property alias to: toLabel.text
    property var __editControl: fromLabel
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

        ImageChooser {
            id: picturePathLabel
            Layout.columnSpan: 2
            // TODO: display proper image when editing an existing object!
        }

        Label {
            text: qsTr("Name")
        }

        TextField {
            id: nameLabel
        }

        Label {
            text: qsTr("Description")
        } 

        Flickable {
            TextArea.flickable: TextArea {
                id: descriptionLabel
                wrapMode: TextArea.Wrap
            }

            ScrollBar.vertical: ScrollBar { }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("From")
        }

        Label {
            id: fromLabel
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
            id: toLabel
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
