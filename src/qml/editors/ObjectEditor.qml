import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import Assistant 1.0

import "../items"

Dialog {
    property var object: Assistant.defaultObject()
    property var __editControl: fromLabel

    id: root
    closePolicy: Popup.NoAutoClose
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    DateTimeEditor {
        id: dateTimeEditor
        onAccepted: {
            __editControl.text = dateTimeEditor.dateTime.toString()
            if (!Timeline.calendar.isEarlier(fromLabel.text, toLabel.text)) {
                toLabel.text = fromLabel.text
            }

            object.from = Assistant.dateFromString(fromLabel.text)
            object.to = Assistant.dateFromString(toLabel.text)
        }
    }

    GridLayout {
        anchors.fill: parent
        columns: 2

        Label {
            text: qsTr("Edit %1").arg(Assistant.typeToString(object.type))
            Layout.columnSpan: 2
        }

        ImageChooser {
            id: picturePathLabel
            Layout.columnSpan: 2
            path: object.picturePath
            onPathChanged: object.picturePath = path
        }

        Label {
            text: qsTr("Name")
        }

        TextField {
            id: nameLabel
            text: object.name
            onTextChanged: object.name = text
        }

        Label {
            text: qsTr("Description")
        } 

        Flickable {
            TextArea.flickable: TextArea {
                id: descriptionLabel
                wrapMode: TextArea.Wrap
                width: parent.widthS
                text: object.description
                onTextChanged: object.description = text
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
            text: object.from.toString()

            onClicked: {
                __editControl = fromLabel
                dateTimeEditor.dateTime = Assistant.dateFromString(text)
                dateTimeEditor.open()
            }
        }

        Label {
            text: qsTr("To")
        }

        Button {
            id: toLabel
            text: object.to.toString()

            onClicked: {
                __editControl = toLabel
                dateTimeEditor.dateTime = Assistant.dateFromString(text)
                dateTimeEditor.open()
            }
        }

        Label {
            text: qsTr("Tags")
        }

        TagContainer {
            id: tagsLabel
            object: root.object
            onTagRemoved: {
                Timeline.removeTag(object, tagId)
                root.object = Timeline.model(object.type).object(object.id)
            }
        }

        Label {
            text: qsTr("Plots")
        }

        PlotContainer {
            id: plotsLabel
            object: root.object
            onPlotRemoved: {
                // TODO: implement
                Timeline.removePlot(object, plotId)
                root.object = Timeline.model(object.type).object(object.id)
            }
        }
    }
}
