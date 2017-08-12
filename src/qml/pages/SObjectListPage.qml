import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import CustomItems 1.0
import Assistant 1.0
import "../cards"

Page {
    property alias model: listView.model
    property alias buttonVisible: button.visible
    signal addObjectRequest()
    signal editRequest()

    id: root

    ListView {
        property bool selectionMode: false

        id: listView
        anchors.fill: parent
        spacing: 15
        clip: true
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }

        delegate: ObjectCard {
            object: sobject.me()
            width: (ListView.view.width > Assistant.cardWidth)? Assistant.cardWidth : ListView.view.width
            height: 200
            selectionMode: ListView.view.selectionMode
            selected: model.selected
            onEdit: openEditor(object)
            onSelectedChanged: {
                model.selected = selected
                ListView.view.selectionMode = (model.selectedCount !== 0)
            }
        }
    }

    RoundButton {
        id: button
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: Assistant.buttonMargin
        text: "+" // No translation needed.
        font.bold: true
        radius: 15

        onClicked: root.addObjectRequest()
    }

    // TODO: add context menu to header. Not here.
    RoundButton {
        id: buttonTempEra
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: Assistant.buttonMargin
        anchors.bottomMargin: Assistant.buttonMargin * 3
        text: "Add era"
        font.bold: true
        radius: 25

        onClicked: {
            //Timeline.model(model.type)
            Timeline.eras.insert("Test1", from, to)
        }
    }
}
