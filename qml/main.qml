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

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Column {
                spacing: 15
                anchors.fill: parent
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
            ListView {
                spacing: 15
                anchors.fill: parent
                model: Timeline.eventModel
                delegate: Text {
                    text: name + "\n\t" + description + "\n\t" + from
                     + "\n\t" + to
                    width: 150
                    height: 60
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
