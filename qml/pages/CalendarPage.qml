import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../editors"

Page {
    DateTimeEditor {
        id: dateTimeEditor
        onFinished: {
            defaultDateTimeLabel.text = dateTimeEditor.dateTime
        }
    }

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
                text: qsTr("Default date and time")
            }
            Label {
                id: defaultDateTimeLabel
                text: Timeline.calendar.defaultDateTime
                onTextChanged: Timeline.calendar.defaultDateTime = text

                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: {
                        dateTimeEditor.setDateTimeFromString(parent.text);
                        dateTimeEditor.open();
                    }
                }
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
