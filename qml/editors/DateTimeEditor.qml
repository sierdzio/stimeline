import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import "../items"

Popup {
    // TODO: use separator from Tags class
    property string dateTime: dtYear.text + "-" + (dtMonth.currentIndex+1) + "-"
                              + (dtDay.currentIndex+1) + " "
                              + (dtHour.currentIndex) + ":"
                              + (dtMinute.currentIndex) + ":"
                              + (dtSecond.currentIndex) //"0001-01-01 01:01:01"

    signal finished()
    signal canceled()

    onFinished: close()
    onCanceled: close()

    id: root
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
        dtMonth.currentIndex = MM-1;
        dtDay.currentIndex = dd-1;
        dtHour.currentIndex = hh;
        dtMinute.currentIndex = mm;
        dtSecond.currentIndex = ss;
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: qsTr("Edit date and time ") + dateTime
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        // Date
        GroupBox {
            title: qsTr("Date")
            Layout.fillWidth: true

            RowLayout {
                Label {
                    id: yearLabel
                    text: qsTr("Year")
                }

                TextField {
                    id: dtYear
                    width: 40
                    horizontalAlignment: TextField.AlignRight
                    validator: IntValidator {}
                }

                Label {
                    text: qsTr("Month")
                }

                Tumbler {
                    id: dtMonth
                    height: yearLabel.height
                    model: Timeline.calendar.monthsInYear
                    visibleItemCount: 3
                    delegate: Text {
                        text: Timeline.calendar.monthName(modelData)
                        height: paintedHeight
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        opacity: 1 - Math.abs(Tumbler.displacement)
                    }
                }

                Label {
                    text: qsTr("Day")
                }

                STumbler {
                    id: dtDay
                    height: yearLabel.height
                    model: Timeline.calendar.daysInMonth(dtMonth.currentIndex)
                }
            }
        }

        // Time
        GroupBox {
            title: qsTr("Time")
            Layout.fillWidth: true
            height: hourLabel.height

            RowLayout {
                Label {
                    id: hourLabel
                    text: qsTr("Hour")
                }

                Tumbler {
                    id: dtHour
                    height: hourLabel.height
                    model: Timeline.calendar.hoursInDay
                }

                Label {
                    text: qsTr("Minute")
                }

                Tumbler {
                    id: dtMinute
                    height: hourLabel.height
                    model: Timeline.calendar.minutesInHour
                }

                Label {
                    text: qsTr("Second")
                }

                Tumbler {
                    id: dtSecond
                    height: hourLabel.height
                    model: Timeline.calendar.secondsInMinute
                }
            }
        }

        DialogButtonBox {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

            onAccepted: {
                root.finished()
            }
            onRejected: {
                root.canceled()
            }
        }
    }
}
