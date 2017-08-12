import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import CustomItems 1.0
import Assistant 1.0
import "../cards"

Page {
    property int type: -1
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

        Component {
            id: sectionHeading
            Rectangle {
                width: listView.width
                height: childrenRect.height
                color: "lightsteelblue"

                Text {
                    text: Timeline.eras.name(section)
                    font.bold: true
                    font.pixelSize: 20
                }
            }
        }

        section {
            property: "era"
            criteria: ViewSection.FullString
            delegate: sectionHeading
        }

        delegate: ObjectCard {
            object: sobject.me()
            width: (ListView.view.width > Assistant.cardWidth)? Assistant.cardWidth : ListView.view.width
            height: 200
            selectionMode: ListView.view.selectionMode
            selected: model.selected
            onEdit: openEditor(object)
            onSelectionSignal: {
                model.selected = isSelected
                ListView.view.selectionMode = (model.selectedCount !== 0)
            }
        }
    }

    RoundButton {
        id: button
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: Assistant.buttonMargin
        // No translation needed.
        text: "+"
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
        text: qsTr("Add era")
        font.bold: true
        radius: 25

        onClicked: Timeline.model(root.type).createEraFromSelection("Test1")
    }
}
