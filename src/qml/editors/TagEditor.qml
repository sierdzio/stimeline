import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import Assistant 1.0

Dialog {
    property alias tag: result.text
    property var object

    id: root
    closePolicy: Popup.NoAutoClose
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        Label {
            text: qsTr("New tag name")
        }
        TextField {
            id: result
        }
    }
}
