import QtQuick 2.8
import QtQuick.Dialogs 1.2

Rectangle {
    property string path: "qrc:/defaults/pics/defaultObject.png"
    id: root
    border.width: 1
    width: 100
    height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: dialog.open()
    }

    FileDialog {
        id: dialog
        title: qsTr("Please choose a picture")
        folder: Timeline.settings.lastOpenFilePath
        nameFilters: ["Pictures (*.png *.jpeg *.jpg)"]
        visible: false
        selectExisting : true
        selectFolder : false
        selectMultiple : false
        onAccepted: {
            console.log("You chose picture: " + dialog.fileUrls)
            root.path = Timeline.loadPicture(dialog.fileUrls)
            image.source = "file://" + Timeline.basePicturePath() + "/" + root.path
        }
        onRejected: {
            console.log("Picture loading canceled")
        }
    }

    Image {
        id: image
        anchors.fill: parent
    }
}
