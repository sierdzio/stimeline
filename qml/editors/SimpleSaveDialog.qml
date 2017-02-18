import QtQuick 2.8
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import Assistant 1.0

Popup {
    property string absoluteFilePath: dirPath + "/" + fileName + "." + fileExtension
    property string dirPath: Assistant.directory(Timeline.settings.lastOpenFilePath)
    property alias fileName: fileNameText.text
    property string fileExtension: extensionJson.checked? Assistant.extensionUncompressed
                                                        : Assistant.extensionCompressed

    signal accepted()
    signal rejected()

    id: root
    height: 300
    width: 500
    closePolicy: Popup.NoAutoClose
    modal: true
    focus: true

    ColumnLayout {
        anchors.fill: parent

        Label {
            id: fnLabel
            text: qsTr("File name:")
            Layout.fillWidth: true
        }

        TextField {
            id: fileNameText
            placeholderText: fnLabel.text
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true
            RadioButton {
                id: extensionJson
                checked: true
                text: qsTr("Open timeline (.%1)").arg(Assistant.extensionUncompressed)

                ToolTip.visible: pressed
                ToolTip.text: qsTr("Timeline data is stored in JSON file, while all "
                                   + "attached pictures are stored in pictures/ directory "
                                   + "created in the same folder as the JSON file.")
            }
            RadioButton {
                id: extensionTmln
                text: qsTr("Compressed timeline (.%1)").arg(Assistant.extensionCompressed)

                ToolTip.visible: pressed
                ToolTip.text: qsTr("Timeline data and all attached pictures are stored "
                                   + "in a single ZIP archive.")
            }
        }

        DialogButtonBox {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

            onAccepted: {
                console.log("Accepted save: " + absoluteFilePath)
                root.accepted()
            }
            onRejected: {
                console.log("Rejected save")
                root.rejected()
            }
        }

        Label {
            text: qsTr("File will be saved to: %1").arg(absoluteFilePath)
            wrapMode: Label.WrapAnywhere
            Layout.fillWidth: true
        }
    }
}
