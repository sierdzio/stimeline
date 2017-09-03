import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import Assistant 1.0

Dialog {
    property int type: -1
    property alias label: labelControl.text
    property alias text: result.text
    property var object

    id: root
    closePolicy: Popup.NoAutoClose
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        Label {
            id: labelControl
            text: qsTr("Name")
        }

        TextField {
            id: result
        }
    }
}
