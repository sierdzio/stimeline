import QtQuick 2.8
import QtQuick.Dialogs 1.2
import Assistant 1.0

/*!
 * Loads the appropriate file dialog: QtQuick one, or simple dialogs (for
 * Android).
 */
Loader {
    property bool isLoading: true
    property bool useSimpleDialog: false

    signal accepted(string filePath)
    signal rejected()

    onAccepted: {
        console.log("You chose: " + filePath)
        close()
    }

    onRejected: {
        if (isLoading) {
            console.log("File loading canceled")
        } else {
            console.log("File saving canceled")
        }

        close()
    }

    function open() {
        if (useSimpleDialog) {
            if (isLoading) {
                sourceComponent = simpleLoadDialog
                console.log("Opening simple load dialog")
            } else {
                sourceComponent = simpleSaveDialog
                console.log("Opening simple save dialog")
            }
        } else {
            sourceComponent = normalFileDialog
            console.log("Opening standard file dialog. Loading? " + isLoading)
        }

        visible = true
    }

    function close() {
        sourceComponent = undefined
        visible = false
    }

    id: root
    sourceComponent: undefined

    Component {
        id: normalFileDialog
        FileDialog {
            title: qsTr("Please choose a timeline file")
            folder: Timeline.settings.lastOpenFilePath
            nameFilters: ["Open timeline (*." + Assistant.extensionUncompressed + ")",
                "Compressed timeline (*." + Assistant.extensionCompressed + ")"]
            visible: true
            selectExisting: root.isLoading
            selectFolder: false
            selectMultiple: false
            onAccepted: root.accepted(fileUrl)
            onRejected: root.rejected()
        }
    }

    Component {
        id: simpleLoadDialog

        SimpleLoadDialog {
            id: sld
            onAccepted: root.accepted(absoluteFilePath)
            onRejected: root.rejected()
            Component.onCompleted: sld.open()
        }
    }

    Component {
        id: simpleSaveDialog

        SimpleSaveDialog {
            id: ssd
            onAccepted: root.accepted(absoluteFilePath)
            onRejected: root.rejected()
            Component.onCompleted: ssd.open()
        }
    }

}
