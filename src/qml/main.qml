import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import CustomItems 1.0
import Assistant 1.0

import "pages"
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
            editor.from = Timeline.calendar.defaultDateTime
            editor.to = Timeline.calendar.defaultDateTime
        } else {
            editor.name = name
            editor.picturePath = picturePath
            editor.description = description
            editor.from = from
            editor.to = to
        }

        editor.open()
    }


    ObjectEditor {
        id: editor
        x: (parent.width/2) - (width/2)
        y: (parent.height/2) - (height/2)

        onAccepted: Timeline.model(editor.type).updateObject(editor.objectId,
                                                             editor.type,
                                                             editor.name,
                                                             editor.picturePath,
                                                             editor.description,
                                                             editor.from,
                                                             editor.to
                                                             )
    }

    SwipeView {
        focus: true
        Keys.onPressed: {
            if ((event.key === Qt.Key_S) && (event.modifiers & Qt.ControlModifier)) {
                console.log("Saving from shortcut: " + Timeline.settings.lastOpenFilePath);
                Timeline.save(Timeline.settings.lastOpenFilePath)
                event.accepted = true;
            }
        }

        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        //        Page {
        //            id: pageTimeline

        //            EventTimeline {
        //                id: eventTimeline
        //                height: parent.height/2
        //                focus: true
        //                anchors.fill: parent
        //            }
        //        }

        SObjectListPage {
            id: pageEvents
            model: Timeline.eventModelProxy
            onEditRequest: openEditor(objectId, type, name, picturePath, description, from, to)
            onAddObjectRequest: openEditor(Assistant.generateId(), SObject.Event)
        }

        ObjectsPage {
            id: pageObjects
        }

        CalendarPage {
            id: pageCalendar
        }

        SettingsPage {
            id: pageSettings
        }

        AboutPage {
            id: pageAbout
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

        //        TabButton {
        //            text: qsTr("Timeline")
        //        }
        TabButton {
            text: qsTr("Events")
        }
        TabButton {
            text: qsTr("Objects")
        }
        TabButton {
            text: qsTr("Calendar")
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
            MenuSeparator {}
            MenuItem {
                text: qsTr("Quit")
                onClicked: { Qt.quit(); }
            }
        }
    }
}
