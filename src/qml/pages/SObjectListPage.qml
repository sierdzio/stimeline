import QtQuick 2.8
import QtQuick.Controls 2.1
import CustomItems 1.0
import Assistant 1.0
import "../cards"

Page {
    property alias model: view.model
    property alias buttonVisible: button.visible
    signal addObjectRequest()
    signal editRequest()

    id: root

    ListView {
        id: view
        anchors.fill: parent
        spacing: 15
        clip: true
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }

        delegate: ObjectCard {
            objectId: model.id
            type: SObject.Event
            name: model.name
            picturePath: model.picturePath
            description: model.description
            from: model.from
            to: model.to
            width: (view.width > Assistant.cardWidth)? Assistant.cardWidth : view.width
            height: 200
            onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
        }
    }

    RoundButton {
        id: button
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: Assistant.buttonMargin
        text: "+"
        font.bold: true
        radius: 15

        onClicked: root.addObjectRequest()
    }
}
