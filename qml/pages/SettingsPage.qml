import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import "../editors"

Page {
    id: pageSettings

    FileDialogLoader {
        id: fileDialog
        isLoading: true
        useSimpleDialog: Timeline.settings.useSimpleFileDialog
        onAccepted: {
            if (isLoading) {
                Timeline.load(filePath)
            } else {
                Timeline.save(filePath)
            }
        }
    }

    ColumnLayout {
        spacing: 15

        RowLayout {
            Label {
                text: qsTr("Author")
            }
            TextField {
                placeholderText: qsTr("Name, surname or nickname")
                text: Timeline.settings.author
                onTextChanged: Timeline.settings.author = text
            }
        }
        Label {
            text: qsTr("File location: %1").arg(Timeline.settings.lastOpenFilePath)
        }

        MenuSeparator {}

        Button {
            text: qsTr("Load timeline")
            onClicked: {
                fileDialog.isLoading = true
                fileDialog.open()
            }
        }
        Button {
            text: qsTr("Save timeline")
            onClicked: {
                fileDialog.isLoading = false
                fileDialog.open()
            }
        }
        CheckBox {
            text: qsTr("Automatically load last opened file on startup")
            checked: Timeline.settings.autoLoadLastFile
            onCheckedChanged: Timeline.settings.autoLoadLastFile = checked
        }
        CheckBox {
            text: qsTr("Automatically save on exit")
            checked: Timeline.settings.autoSaveOnExit
            onCheckedChanged: Timeline.settings.autoSaveOnExit = checked
        }
        CheckBox {
            text: qsTr("Use simple file dialog")
            checked: Timeline.settings.useSimpleFileDialog
            onCheckedChanged: Timeline.settings.useSimpleFileDialog = checked
        }
    }
}
