import QtQuick 2.8
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1

Item {
    property string absoluteFilePath: dirpath + "/" + fileName + fileExtension
    property string dirPath: "" // TODO: add default path. Some sane default like standardpaths
    property alias fileName: fileNameText.text
    property string fileExtension: extensionJson.checked? ".json" : ".tmln"

    ColumnLayout {
        Label {
            id: fnLabel
            text: qsTr("File name:")
        }

        TextField {
            id: fileNameText
            placeholderText: fnLabel.text
        }

        RowLayout {
            RadioButton {
                id: extensionJson
                checked: true
                text: qsTr("Open timeline (.json)")

                ToolTip.visible: pressed
                ToolTip.text: qsTr("Timeline data is stored in JSON file, while all "
                                   + "attached pictures are stored in pictures/ directory "
                                   + "created in the same folder as the JSON file.")
            }
            RadioButton {
                id: extensionTmln
                text: qsTr("Compressed timeline (.tmln)")

                ToolTip.visible: pressed
                ToolTip.text: qsTr("Timeline data and all attached pictures are stored "
                                   + "in a single ZIP archive.")
            }
        }

        DialogButtonBox {
            standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

            // TODO: expose onAccepted and onRejected to external usage
            onAccepted: console.log("Ok clicked")
            onRejected: console.log("Cancel clicked")
        }
    }
}
