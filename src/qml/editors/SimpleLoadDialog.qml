import QtQuick 2.8
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import Qt.labs.folderlistmodel 2.1
import Assistant 1.0

Dialog {
    property string absoluteFilePath: (folderView.currentItem? dirPath + "/" + folderView.currentItem.text : dirPath)
    property string dirPath: Assistant.directory(Timeline.settings.lastOpenFilePath)

    id: root
    closePolicy: Popup.NoAutoClose
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        id: layout
        anchors.fill: parent

        Label {
            text: qsTr("Current dir: %1").arg(dirPath)
            wrapMode: Label.WrapAnywhere
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("Choose file to load:")
            Layout.fillWidth: true
        }

        ListView {
            id: folderView
            height: 150
            //clip: true
            focus: true
            highlightFollowsCurrentItem: true
            highlight: Rectangle {
                color: "#552222ff"
                width: folderView.width
            }
            delegate: Text {
                text: fileName
                height: contentHeight
                width: parent.width

                MouseArea {
                    anchors.fill: parent
                    onClicked: folderView.currentIndex = index
                }
            }
            model: FolderListModel {
                showDirs: false
                folder: "file://" + dirPath
                nameFilters: ["*." + Assistant.extensionUncompressed,
                    "*." + Assistant.extensionCompressed]
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("File to load: %1").arg(absoluteFilePath)
            wrapMode: Label.WrapAnywhere
            Layout.fillWidth: true
        }
    }
}
