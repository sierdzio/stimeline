import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Popup {
    // TODO: use separator from Tags class
    property string dateTime: year.text + "-" + (month.currentIndex+1) + "-" + (day.currentIndex+1)
                              + " " + (hour.currentIndex+1) + ":" + (minute.currentIndex+1) + ":" + (second.currentIndex+1) //"0001-01-01 01:01:01"

    property alias year: dtYear
    property alias month: dtMonth
    property alias day: dtDay
    property alias hour: dtHour
    property alias minute: dtMinute
    property alias second: dtSecond

    signal finished()
    signal canceled()

    onFinished: close()
    onCanceled: close()

    id: root
    width: 800
    height: 600
    closePolicy: Popup.NoAutoClose
    modal: true
    focus: true

    function setDateTimeFromString(dateTimeString) {
        // TODO: use separator from Tags class
        // Or use SDateTime object directly here...
        var dt = dateTimeString.split(" ");
        var dateStr = dt[0].split("-");
        var timeStr = dt[1].split(":")

        setDateTime(dateStr[0], dateStr[1], dateStr[2],
                    timeStr[0], timeStr[1], timeStr[2]);
    }

    function setDateTime(yyyy, MM, dd, hh, mm, ss) {
        dtYear.text = yyyy;
        dtMonth.currentIndex = MM+1;
        dtDay.currentIndex = dd+1;
        dtHour.currentIndex = hh+1;
        dtMinute.currentIndex = mm+1;
        dtSecond.currentIndex = ss+1;
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: qsTr("Edit date and time ") + dateTime
            Layout.columnSpan: 2
        }

        // Date
        GroupBox {
            title: qsTr("Date")

            RowLayout {
                Label {
                    text: qsTr("Year")
                }

                TextField {
                    id: dtYear
                    validator: IntValidator {}
                }

                Label {
                    text: qsTr("Month")
                }

                Tumbler {
                    id: dtMonth
                    model: Timeline.calendar.monthsInYear
                    visibleItemCount: 3
                    delegate: Text {
                        text: Timeline.calendar.monthName(index)
                        height: paintedHeight
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        opacity: 1 - Math.abs(Tumbler.displacement)
                    }
                }

                Label {
                    text: qsTr("Day")
                }

                Tumbler {
                    id: dtDay
                    model: Timeline.calendar.daysInMonth(dtMonth.currentIndex)
                }
            }
        }

        // Time
        GroupBox {
            title: qsTr("Time")

            RowLayout {
                Label {
                    text: qsTr("Hour")
                }

                Tumbler {
                    id: dtHour
                    model: Timeline.calendar.hoursInDay
                }

                Label {
                    text: qsTr("Minute")
                }

                Tumbler {
                    id: dtMinute
                    model: Timeline.calendar.minutesInHour
                }

                Label {
                    text: qsTr("Second")
                }

                Tumbler {
                    id: dtSecond
                    model: Timeline.calendar.secondsInMinute
                }
            }
        }

        Button {
            text: qsTr("OK")
            onClicked: root.finished()
        }

        Button {
            text: qsTr("Cancel")
            onClicked: root.canceled()
        }
    }
}
