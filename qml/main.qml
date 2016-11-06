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
        id: fileDialog
        title: "Please choose a timeline file"
        folder: shortcuts.home
        visible: false
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            Timeline.load(fileDialog.fileUrl)
            console.log(JSON.stringify(Timeline.events()))
            mainLabel.text = Timeline.events().name
            //Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            //Qt.quit()
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Column {
                anchors.centerIn: parent
                Label {
                    text: qsTr("First page")
                }
                Button {
                    text: qsTr("Load timeline")
                    onClicked: fileDialog.visible = true
                }
                Label {
                    id: mainLabel
                    text: {
                        console.log(JSON.stringify(Timeline.events()));
                        return Timeline.events().name;
                    }
                }
            }
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
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
