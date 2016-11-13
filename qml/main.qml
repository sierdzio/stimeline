import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("sTimeline - v") + Qt.application.version

    FileDialog {
        id: loadDialog
        title: "Please choose a timeline file"
        folder: Timeline.settings.lastOpenFilePath
        visible: false
        selectExisting : true
        selectFolder : false
        selectMultiple : false
        onAccepted: {
            console.log("You chose: " + loadDialog.fileUrls)
            Timeline.load(loadDialog.fileUrl)
        }
        onRejected: {
            console.log("File loading canceled")
        }
    }

    FileDialog {
        id: saveDialog
        title: "Please choose a timeline file"
        folder: Timeline.settings.lastSaveFilePath
        visible: false
        selectExisting : false
        selectFolder : false
        selectMultiple : false
        onAccepted: {
            console.log("You chose: " + saveDialog.fileUrls)
            Timeline.save(saveDialog.fileUrl)
        }
        onRejected: {
            console.log("File saving canceled")
        }
    }

    EventEditor {
        id: eventEditor

        onFinished: Timeline.eventModel.updateEvent(eventEditor.eventId,
                                                    eventEditor.name,
                                                    eventEditor.description,
                                                    eventEditor.from,
                                                    eventEditor.to
                                                    )
    }

    function openEditor(eventId, name, description, from, to) {
        eventEditor.eventId = eventId;
        if (typeof name !== "undefined") {
            eventEditor.name = name
            eventEditor.description = description
            eventEditor.from = from
            eventEditor.to = to
        }
        eventEditor.open();
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            ListView {
                spacing: 15
                anchors.fill: parent
                model: Timeline.eventModel
                delegate: EventCard {
                    eventId: model.id
                    name: model.name
                    description: model.description
                    from: model.from
                    to: model.to
                    width: 250
                    height: 120

                    onEdit: openEditor(eventId, name, description, from, to)
                }
            }

            Button {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 25
                text: "+"
                font.bold: true
                width: 30
                height: width
                //radius: 15

                onClicked: openEditor(Timeline.eventModel.addEvent())
            }
        }

        Page {
            Column {
                spacing: 15
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                Button {
                    text: qsTr("Load timeline")
                    onClicked: loadDialog.visible = true
                }
                Button {
                    text: qsTr("Save timeline")
                    onClicked: saveDialog.visible = true
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Timeline")
        }
        TabButton {
            text: qsTr("People")
        }
    }
}
