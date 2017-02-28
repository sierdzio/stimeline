import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import "../items"

Popup {
    // TODO: use separator from Tags class
    property string dateTime: dtYear.value + "-" + (dtMonth.currentIndex+1) + "-"
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
        dtYear.value = yyyy;
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
            Layout.fillWidth: true
        }

        // Date
        GroupBox {
            title: qsTr("Date")
            Layout.fillWidth: true

            GridLayout {
                columns: 3
                Label {
                    text: qsTr("Year")
                }
                Label {
                    text: qsTr("Month")
                }
                Label {
                    text: qsTr("Day")
                }

                SpinBox {
                    id: dtYear
                    editable: true
                    from: -100000
                    to: 100000
                    Layout.minimumWidth: 140
                    Layout.preferredWidth: 160
                    Layout.maximumWidth: 200
                }
                Tumbler {
                    id: dtMonth
                    model: Timeline.calendar.monthsInYear
                    visibleItemCount: 3
                    delegate: Text {
                        text: Timeline.calendar.monthName(modelData)
                        height: paintedHeight
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        opacity: 1.0 - Math.abs(Tumbler.displacement)
                                 / (Tumbler.tumbler.visibleItemCount / 2)
                    }
                }
                STumbler {
                    id: dtDay
                    visibleItemCount: 3
                    model: Timeline.calendar.daysInMonth(dtMonth.currentIndex)
                }
            }
        }

        // Time
        GroupBox {
            title: qsTr("Time")
            Layout.fillWidth: true

            GridLayout {
                Label {
                    text: qsTr("Hour")
                }
                Label {
                    text: qsTr("Minute")
                }
                Label {
                    text: qsTr("Second")
                }

                Tumbler {
                    id: dtHour
                    model: Timeline.calendar.hoursInDay
                }
                Tumbler {
                    id: dtMinute
                    model: Timeline.calendar.minutesInHour
                }
                Tumbler {
                    id: dtSecond
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
