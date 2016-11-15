import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("sTimeline - v") + Qt.application.version

    FileDialog {
        id: loadDialog
        title: qsTr("Please choose a timeline file")
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
        title: qsTr("Please choose a timeline file")
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
            id: pageTimeline
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

            // TODO: use RoundedButton from Qt 5.8
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
            id: pagePeople
        }

        Page {
            id: pageObjects
        }

        Page {
            id: pagePlaces
        }

        Page {
            id: pageMaps
        }

        Page {
            id: pageSettings
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

        Page {
            id: pageAbout

            Column {
                spacing: 15
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width

                Text {
                    //Layout.alignment: Qt.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "sTimeline"
                    font {
                        bold: true
                        pointSize: 24
                    }
                }
                Text {
                    //Layout.alignment: Qt.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Version %1").arg(Qt.application.version)
                }
                Item { height: 25; width: 1 }
                Text {
                    //Layout.alignment: Qt.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 600
                    width: 350
                    wrapMode: Text.WordWrap
                    text: qsTr("This software uses Qt Framework. Visit qt.io for more information. This software is free and open source, distributed under WTFPL license (see LICENSE.md file). You can find the source code at https://github.com/sierdzio/stimeline")
                }
            }
        }
    }

    PageIndicator {
        id: indicator

        count: swipeView.count
        currentIndex: swipeView.currentIndex

        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                id: backButton
                text: "<"
                font.bold: true
                font.pointSize: 16
                //enabled: stack.depth > 1
                //onClicked: stack.pop()
            }
            ToolButton {
                id: hamburgerButton
                text: "\u2261"
                font.bold: true
                font.pointSize: 16
                onClicked: drawer.open()
            }
            Text {
                text: qsTr("sTimeline - %1").arg(Qt.application.version)
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }
            Item {
                // Just some padding
                width: backButton.width + hamburgerButton.width
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
        TabButton {
            text: qsTr("Objects")
        }
        TabButton {
            text: qsTr("Places")
        }
        TabButton {
            text: qsTr("Maps")
        }
        TabButton {
            text: qsTr("Settings")
        }
        TabButton {
            text: qsTr("About")
        }
    }

    Drawer {
        id: drawer
        width: 350
        height: window.height
        edge: Qt.LeftEdge

        Menu {
            MenuItem {
                text: qsTr("Timeline")
            }
            MenuItem {
                text: qsTr("People")
            }
            MenuItem {
                text: qsTr("Objects")
            }
            MenuItem {
                text: qsTr("Places")
            }
            MenuItem {
                text: qsTr("Maps")
            }
            MenuItem {
                text: qsTr("Settings")
            }
            MenuItem {
                text: qsTr("About")
            }
        }
    }
}
