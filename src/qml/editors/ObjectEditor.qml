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
    closePolicy: Popup.NoAutoClose
    modal: true
    focus: true

    DateTimeEditor {
        id: dateTimeEditor
        onFinished: {
            __editControl.text = dateTimeEditor.dateTime
            if (!Timeline.calendar.isEarlier(fromLabel.text, toLabel.text)) {
                toLabel.text = fromLabel.text
            }
        }
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
                width: parent.width
                //height: 200
            }

            height: 200
            ScrollBar.vertical: ScrollBar { }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("From")
        }

        Button {
            id: fromLabel
            text: Timeline.calendar.defaultDateTime

            onClicked: {
                __editControl = fromLabel;
                dateTimeEditor.setDateTimeFromString(text);
                dateTimeEditor.open();
            }
        }

        Label {
            text: qsTr("To")
        }

        Button {
            id: toLabel
            text: Timeline.calendar.defaultDateTime

            onClicked: {
                __editControl = toLabel;
                dateTimeEditor.setDateTimeFromString(text);
                dateTimeEditor.open();
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
