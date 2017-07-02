import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import Assistant 1.0

import "../items"

Dialog {
    property var dateTime: Assistant.defaultDateTime()

    id: root
    closePolicy: Popup.NoAutoClose
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

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

                TextField {
                    id: dtYear
                    text: dateTime.year
                    onTextChanged: dateTime.year = text
                    validator: IntValidator {}
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

                    currentIndex: dateTime.month - 1
                    onCurrentIndexChanged: {
                        dateTime.month = currentIndex + 1
                        dtDay.model = Timeline.calendar.daysInMonth(currentIndex)
                    }
                }

                STumbler {
                    id: dtDay
                    visibleItemCount: 3
                    currentIndex: dateTime.day - 1
                    onCurrentIndexChanged: dateTime.day = currentIndex + 1
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
                    currentIndex: dateTime.hour
                    onCurrentIndexChanged: dateTime.hour = currentIndex
                }
                Tumbler {
                    id: dtMinute
                    model: Timeline.calendar.minutesInHour
                    currentIndex: dateTime.minute
                    onCurrentIndexChanged: dateTime.minute = currentIndex
                }
                Tumbler {
                    id: dtSecond
                    model: Timeline.calendar.secondsInMinute
                    currentIndex: dateTime.second
                    onCurrentIndexChanged: dateTime.second = currentIndex
                }
            }
        }
    }
}
