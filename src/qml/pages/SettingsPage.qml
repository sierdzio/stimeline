import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import "../editors"

Page {
    id: root

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

    Flickable {
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: column.height
        contentWidth: column.width

        ColumnLayout {
            id: column
            width: root.width
            spacing: 15

            RowLayout {
                Layout.fillWidth: true

                Label {
                    text: qsTr("Author")
                }
                TextField {
                    placeholderText: qsTr("Name, surname or nickname")
                    text: Timeline.settings.author
                    onTextChanged: Timeline.settings.author = text
                }
            }
            RowLayout {
                Layout.fillWidth: true

                Label {
                    text: qsTr("Timeline name")
                }
                TextField {
                    placeholderText: qsTr("Name")
                    text: Timeline.settings.name
                    onTextChanged: Timeline.settings.name = text
                }
            }
            Label {
                text: qsTr("File location: %1").arg(Timeline.settings.lastOpenFilePath)
                wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                Layout.fillWidth: true
            }

            MenuSeparator { Layout.fillWidth: true }

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
            Button {
                text: qsTr("Export timeline")
                visible: Qt.platform.os === "android"
                onClicked: {
                    Timeline.exportSave()
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
}
