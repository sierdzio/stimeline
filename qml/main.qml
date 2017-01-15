import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import Assistant 1.0
import CustomItems 1.0

import "views"
import "cards"
import "editors"

ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 800
    title: qsTr("sTimeline - v") + Qt.application.version

    function openEditor(objectId, type, name, picturePath, description, from, to) {
        editor.objectId = objectId
        editor.type = type

        if (typeof name === "undefined") {
            editor.name = ""
            editor.picturePath = ""
            editor.description = ""
            editor.from = ""
            editor.to = ""
        } else {
            editor.name = name
            editor.picturePath = picturePath
            editor.description = description
            editor.from = from
            editor.to = to
        }

        editor.open()
    }

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

    ObjectEditor {
        id: editor
        x: (parent.width/2) - (width/2)
        y: (parent.height/2) - (height/2)

        onFinished: Timeline.model(editor.type).updateObject(editor.objectId,
                                                             editor.type,
                                                             editor.name,
                                                             editor.picturePath,
                                                             editor.description,
                                                             editor.from,
                                                             editor.to
                                                             )
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            id: pageTimeline
            visible: false

            EventTimeline {
                id: eventTimeline
                height: parent.height/2
                focus: true
                anchors.fill: parent
            }
        }

        SItemListView {
            id: pageEvents
            model: Timeline.eventModelProxy
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Event
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 120
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Event)
        }

        SItemListView {
            id: pagePeople
            model: Timeline.personModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Person
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 120
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Person)
        }

        SItemListView {
            id: pageArtifacts
            model: Timeline.artifactModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Artifact
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 120
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Artifact)
        }

        SItemListView {
            id: pagePlaces
            model: Timeline.placeModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Place
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 120
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Place)
        }

        SItemListView {
            id: pageMaps
            model: Timeline.mapModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Map
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 120
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Map)
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
                CheckBox {
                    text: qsTr("Automatically load last opened file on startup")
                    checked: Timeline.settings.autoLoadLastFile
                    onCheckedChanged: Timeline.settings.autoLoadLastFile = checked
                }
                CheckBox {
                    text: qsTr("Automatically save on exit")
                    checked: Timeline.settings.autoSaveOnExit
                    onCheckedChanged: Timeline.settings.autoSaveOnExit = checked
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
                enabled: tabBar.previousIndex !== -1
                onClicked: tabBar.currentIndex = tabBar.previousIndex
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
        property int previousIndex: -1
        property int __tempIndex: 0

        id: tabBar
        currentIndex: swipeView.currentIndex
        onCurrentIndexChanged: {
            previousIndex = __tempIndex;
            __tempIndex = currentIndex;
        }

        TabButton {
            text: qsTr("Timeline")
        }
        TabButton {
            text: qsTr("Events")
        }
        TabButton {
            text: qsTr("People")
        }
        TabButton {
            text: qsTr("Artifacts")
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

        ColumnLayout {
            anchors.fill: parent

            MenuItem {
                text: tabBar.contentChildren[0].text
                onClicked: { tabBar.currentIndex = 0; drawer.close(); }
            }
            MenuItem {
                text: tabBar.contentChildren[1].text
                onClicked: { tabBar.currentIndex = 1; drawer.close(); }
            }
            MenuItem {
                text: tabBar.contentChildren[2].text
                onClicked: { tabBar.currentIndex = 2; drawer.close(); }
            }
            MenuItem {
                text: tabBar.contentChildren[3].text
                onClicked: { tabBar.currentIndex = 3; drawer.close(); }
            }
            MenuItem {
                text: tabBar.contentChildren[4].text
                onClicked: { tabBar.currentIndex = 4; drawer.close(); }
            }
            MenuItem {
                text: tabBar.contentChildren[5].text
                onClicked: { tabBar.currentIndex = 5; drawer.close(); }
            }
            MenuItem {
                text: tabBar.contentChildren[6].text
                onClicked: { tabBar.currentIndex = 6; drawer.close(); }
            }
            MenuItem {
                text: tabBar.contentChildren[7].text
                onClicked: { tabBar.currentIndex = 7; drawer.close(); }
            }
            MenuItem {
                text: qsTr("Quit")
                onClicked: { Qt.quit(); }
            }
        }
    }
}
