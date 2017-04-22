import QtQuick 2.8
import QtQuick.Dialogs 1.2

Rectangle {
    property string path
    property string __fileName: "defaultObject.png"
    property string __pathBase: "qrc:/defaults/pics/"
    id: root
    border.width: 1
    border.color: "#55555555"
    width: 300
    height: 200

    onVisibleChanged: {
        if (visible) {
            if (path !== "") {
                __pathBase = "file://" + Timeline.basePicturePath() + "/"
                __fileName = path
                image.source = root.__pathBase + root.__fileName
            } else {
                __pathBase = "qrc:/defaults/pics/"
                __fileName = "defaultObject.png"
                image.source = root.__pathBase + root.__fileName
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onDoubleClicked: dialog.open()
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
            root.__pathBase = "file://" + Timeline.basePicturePath() + "/"
            root.__fileName = Timeline.loadPicture(dialog.fileUrls)
            image.source = root.__pathBase + root.__fileName
            root.path = root.__fileName
            console.log("You chose picture: " + dialog.fileUrls
                        + "Changing picture to: " + image.source)
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
