import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import CustomItems 1.0
import Assistant 1.0

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
            editor.from = "1-1-1 1:1:1"
            editor.to = "1-1-1 1:1:1"
        } else {
            editor.name = name
            editor.picturePath = picturePath
            editor.description = description
            editor.from = from
            editor.to = to
        }

        editor.open()
    }

    FileDialogLoader {
        id: fileDialog
        isLoading: true
        useSimpleDialog: Timeline.settings.useSimpleFileDialog
        onAccepted: {
            if (isLoading) {
                Timeline.load(filePath)
            } else {
                Timeline.save(filePath)
            }
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

        //        Page {
        //            id: pageTimeline

        //            EventTimeline {
        //                id: eventTimeline
        //                height: parent.height/2
        //                focus: true
        //                anchors.fill: parent
        //            }
        //        }

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
                height: 140
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Event)
        }

        ObjectsPage {
            id: pageObjects
        }

        Page {
            id: pageCalendar
            Flickable {
                anchors.fill: parent
                flickableDirection: Flickable.VerticalFlick
                contentHeight: calendarColumn.height
                contentWidth: calendarColumn.width

                GridLayout {
                    id: calendarColumn
                    columns: 2

                    Label {
                        text: qsTr("Calendar name")
                    }
                    TextField {
                        placeholderText: qsTr("Name of the calendar system")
                        text: Timeline.calendar.name
                        onTextChanged: Timeline.calendar.name = text
                    }
                    Label {
                        text: qsTr("Days in a week")
                    }
                    TextField {
                        text: Timeline.calendar.daysInWeek
                        onTextChanged: Timeline.calendar.daysInWeek = text
                    }
                    Label {
                        text: qsTr("Days in a year")
                    }
                    TextField {
                        text: Timeline.calendar.daysInYear
                        onTextChanged: Timeline.calendar.daysInYear = text
                    }
                    Label {
                        text: qsTr("Months in a year")
                    }
                    TextField {
                        // TODO: Tumbler instead of TextField?
                        text: Timeline.calendar.monthsInYear
                        onTextChanged: Timeline.calendar.monthsInYear = text
                    }
                    Label {
                        text: qsTr("Months")
                    }
                    ListView {
                        height: 150
                        width: 150
                        //Layout.fillWidth: true
                        clip: true
                        model: Timeline.calendar.monthsInYear
                        delegate: Row {
                            TextField {
                                text: Timeline.calendar.monthName(index)
                                onTextChanged: Timeline.calendar.setMonthName(index, text)
                            }
                            TextField {
                                text: Timeline.calendar.daysInMonth(index)
                                onTextChanged: Timeline.calendar.setDaysInMonth(index, text)
                            }
                        }
                    }
                    Label {
                        text: qsTr("Leap days per year")
                    }
                    TextField {
                        placeholderText: "0.25 - one leap day per 4 years"
                        // TODO: validation!
                        text: Timeline.calendar.leapDayPerYear
                        onTextChanged: Timeline.calendar.leapDayPerYear = text
                    }
                    Label {
                        text: qsTr("Leap day in which month?")
                    }
                    TextField {
                        placeholderText: "2 - February"
                        text: Timeline.calendar.leapDayAddsToMonthNumber
                        onTextChanged: Timeline.calendar.leapDayAddsToMonthNumber = text
                    }
                    Label {
                        text: qsTr("Seconds in a minute")
                    }
                    TextField {
                        text: Timeline.calendar.secondsInMinute
                        onTextChanged: Timeline.calendar.secondsInMinute = text
                    }
                    Label {
                        text: qsTr("Minutes in an hour")
                    }
                    TextField {
                        text: Timeline.calendar.minutesInHour
                        onTextChanged: Timeline.calendar.minutesInHour = text
                    }
                    Label {
                        text: qsTr("Hours in a day")
                    }
                    TextField {
                        text: Timeline.calendar.hoursInDay
                        onTextChanged: Timeline.calendar.hoursInDay = text
                    }
                }
            }
        }

        Page {
            id: pageSettings
            ColumnLayout {
                spacing: 15

                RowLayout {
                    Label {
                        text: qsTr("Author")
                    }
                    TextField {
                        placeholderText: qsTr("Name, surname or nickname")
                        text: Timeline.settings.author
                        onTextChanged: Timeline.settings.author = text
                    }
                }
                Label {
                    text: qsTr("File location: %1").arg(Timeline.settings.lastOpenFilePath)
                }

                MenuSeparator {}

                Button {
                    text: qsTr("Load timeline")
                    onClicked: {
                        fileDialog.isLoading = true
                        fileDialog.open()
                    }
                }
                Button {
                    text: qsTr("Save timeline")
                    onClicked: {
                        fileDialog.isLoading = false
                        fileDialog.open()
                    }
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
                CheckBox {
                    text: qsTr("Use simple file dialog")
                    checked: Timeline.settings.useSimpleFileDialog
                    onCheckedChanged: Timeline.settings.useSimpleFileDialog = checked
                }
            }
        }

        Page {
            id: pageAbout

            Column {
                spacing: 15
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "sTimeline"
                    font {
                        bold: true
                        pointSize: 24
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Version %1").arg(Qt.application.version)
                }
                Item { height: 25; width: 1 }
                Text {
                    width: 350
                    wrapMode: Text.WordWrap
                    text: qsTr("This software uses Qt Framework. Visit qt.io for "
                               + "more information. It also uses QuaZIP library "
                               + "- see http://quazip.sourceforge.net. This "
                               + "software is free and open source, distributed "
                               + "under WTFPL license (see LICENSE.md file). You "
                               + "can find the source code at "
                               + "https://github.com/sierdzio/stimeline")
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

        //        TabButton {
        //            text: qsTr("Timeline")
        //        }
        TabButton {
            text: qsTr("Events")
        }
        // TODO: merge People, Artifacts, Places, Maps into a submenu - they
        // are less needed but clutter the view
        //        TabButton {
        //            text: qsTr("People")
        //        }
        //        TabButton {
        //            text: qsTr("Artifacts")
        //        }
        //        TabButton {
        //            text: qsTr("Places")
        //        }
        //        TabButton {
        //            text: qsTr("Maps")
        //        }
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
            //            MenuItem {
            //                text: tabBar.contentChildren[5].text
            //                onClicked: { tabBar.currentIndex = 5; drawer.close(); }
            //            }
            //            MenuItem {
            //                text: tabBar.contentChildren[6].text
            //                onClicked: { tabBar.currentIndex = 6; drawer.close(); }
            //            }
            //            MenuItem {
            //                text: tabBar.contentChildren[7].text
            //                onClicked: { tabBar.currentIndex = 7; drawer.close(); }
            //            }
            MenuSeparator {}
            MenuItem {
                text: qsTr("Quit")
                onClicked: { Qt.quit(); }
            }
        }
    }
}
