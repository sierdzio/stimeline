import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../editors"

Page {
    id: root
    property string _empty: ""

    DateTimeEditor {
        id: dateTimeEditor
        onFinished: {
            defaultDateTimeLabel.text = dateTimeEditor.dateTime
        }
    }

    FileDialogLoader {
        id: fileDialog
        isLoading: true
        useSimpleDialog: true
        allowCompressedSave: false
        startDir: Timeline.settings.configDir

        onAccepted: {
            if (isLoading) {
                root._empty = "1"
                Timeline.loadCalendar(filePath)
                // Reset months model
                root._empty = ""
            } else {
                Timeline.saveCalendar(filePath)
            }
        }
    }

    Flickable {
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: calendarColumn.height
        contentWidth: calendarColumn.width

        GridLayout {
            id: calendarColumn
            width: root.width
            columns: 2

            Row {
                Layout.columnSpan: 2

                Label {
                    text: qsTr("Calendar definition")
                }

                Button {
                    text: qsTr("Load")
                    onClicked: {
                        fileDialog.isLoading = true
                        fileDialog.open()
                    }
                }
                Button {
                    text: qsTr("Save")
                    onClicked: {
                        fileDialog.isLoading = false
                        fileDialog.open()
                    }
                }
            }
            Label {
                text: qsTr("Calendar name")
            }
            TextField {
                placeholderText: qsTr("Name of the calendar system")
                text: Timeline.calendar.name
                onTextChanged: Timeline.calendar.name = text
            }
            Label {
                text: qsTr("Default date and time")
            }
            Button {
                id: defaultDateTimeLabel
                text: Timeline.calendar.defaultDateTime
                onTextChanged: Timeline.calendar.defaultDateTime = text

                onClicked: {
                    dateTimeEditor.setDateTimeFromString(text);
                    dateTimeEditor.open();
                }
            }
            Label {
                text: qsTr("Days in a week")
            }
            TextField {
                text: Timeline.calendar.daysInWeek
                onTextChanged: Timeline.calendar.daysInWeek = text
                validator: IntValidator { bottom: 0 }
            }
            Label {
                text: qsTr("Days in a year")
            }
            TextField {
                text: Timeline.calendar.daysInYear
                onTextChanged: Timeline.calendar.daysInYear = text
                validator: IntValidator { bottom: 0 }
            }
            Label {
                text: qsTr("Months in a year")
            }
            TextField {
                text: Timeline.calendar.monthsInYear
                onTextChanged: Timeline.calendar.monthsInYear = text
                validator: IntValidator { bottom: 0 }
            }
            Label {
                text: qsTr("Months")
            }
            ListView {
                id: monthView
                height: 150
                width: 150
                clip: true
                model: Timeline.calendar.monthsInYear
                delegate: Row {
                    TextField {
                        text: Timeline.calendar.monthName(index) + root._empty
                        onTextChanged: Timeline.calendar.setMonthName(index, text)
                    }
                    TextField {
                        text: Timeline.calendar.daysInMonth(index) + root._empty
                        onTextChanged: Timeline.calendar.setDaysInMonth(index, text)
                    }
                }
            }
            Label {
                text: qsTr("Leap days per year")
            }
            TextField {
                placeholderText: "0.25 - one leap day per 4 years"
                text: Timeline.calendar.leapDayPerYear
                onTextChanged: Timeline.calendar.leapDayPerYear = text
                validator: DoubleValidator {}
            }
            Label {
                text: qsTr("Leap day in which month?")
            }
            TextField {
                placeholderText: "2 - February"
                text: Timeline.calendar.leapDayAddsToMonthNumber
                onTextChanged: Timeline.calendar.leapDayAddsToMonthNumber = text
                validator: IntValidator { bottom: 0 }
            }
            Label {
                text: qsTr("Seconds in a minute")
            }
            TextField {
                text: Timeline.calendar.secondsInMinute
                onTextChanged: Timeline.calendar.secondsInMinute = text
                validator: IntValidator { bottom: 0 }
            }
            Label {
                text: qsTr("Minutes in an hour")
            }
            TextField {
                text: Timeline.calendar.minutesInHour
                onTextChanged: Timeline.calendar.minutesInHour = text
                validator: IntValidator { bottom: 0 }
            }
            Label {
                text: qsTr("Hours in a day")
            }
            TextField {
                text: Timeline.calendar.hoursInDay
                onTextChanged: Timeline.calendar.hoursInDay = text
                validator: IntValidator { bottom: 0 }
            }
        }
    }
}
