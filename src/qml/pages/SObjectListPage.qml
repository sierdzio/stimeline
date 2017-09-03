import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import CustomItems 1.0
import Assistant 1.0
import "../cards"

Page {
    // TODO: use type enum
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

    ColumnLayout {
        spacing: 15
        width: buttonEra.width

        anchors {
            bottom: parent.bottom
            right: parent.right
            margins: Assistant.buttonMargin
        }

        RoundButton {
            width: 35
            height: width
            text: qsTr("Delete")
            radius: Assistant.buttonMargin
            opacity: listView.selectionMode? 1.0 : 0.0
            Behavior on opacity {
                NumberAnimation {}
            }

            onClicked: Timeline.model(root.type).removeSelectedObjects()
        }

        RoundButton {
            id: buttonEra
            text: qsTr("Add era")
            radius: Assistant.buttonMargin
            opacity: listView.selectionMode? 1.0 : 0.0
            Behavior on opacity {
                NumberAnimation {}
            }

            onClicked: {
                console.log("Opening era editor")
                eraEditor.type = root.type
                eraEditor.open()
            }
        }

        RoundButton {
            id: buttonPlot
            text: qsTr("Add plot")
            radius: Assistant.buttonMargin
            opacity: listView.selectionMode? 1.0 : 0.0
            Behavior on opacity {
                NumberAnimation {}
            }

            onClicked: {
                console.log("Opening plot editor")
                plotEditor.type = root.type
                plotEditor.open()
            }
        }

        RoundButton {
            id: button
            // No translation needed.
            text: "+"
            font.bold: true
            radius: 15

            onClicked: root.addObjectRequest()
        }

    }
}
