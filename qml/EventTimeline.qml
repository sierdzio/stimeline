import QtQuick 2.7
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import CustomItems 1.0
import Assistant 1.0

RadialGradient {
    id: eventTimelineGradient

    gradient: Gradient {
        GradientStop { position: 0.0; color: "white" }
        GradientStop { position: 0.8; color: "gray" }
    }

    Rectangle {
        id: topBar
        width: 4
        height: 12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
    }

    Rectangle {
        id: bottomBar
        width: 4
        height: 12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }

    EventTimelineView {
        id: etlv
        anchors.fill: parent
        height: parent.height
    }

    Row {
        Button {
            text: qsTr("<-")
            onClicked: etlv.scrollLeft(200)
        }
        Button {
            text: qsTr("->")
            onClicked: etlv.scrollRight(200)
        }
    }

    Text {
        id: scaleInfo
        text: qsTr("Scale: %1%").arg(etlv.scale * 100)
        color: "#555555"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        height: paintedHeight
        width: paintedWidth
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: Assistant.buttonMargin/2
        }

        onTextChanged: scaleInfo.state = Assistant.Visible
        Component.onCompleted: state = Assistant.Hidden

        states: [
            State {
                name: Assistant.Hidden
                PropertyChanges { target: scaleInfo; opacity: 0.01 }
            },
            State {
                name: Assistant.Visible
                PropertyChanges { target: scaleInfo; opacity: 1.0 }
            }
        ]

        transitions: [
            Transition {
                from: Assistant.Hidden; to: Assistant.Visible
                SequentialAnimation {
                    NumberAnimation {
                        properties: "opacity"
                        duration: 50
                    }
                    ScriptAction {
                        script: scaleInfo.state = Assistant.Hidden
                    }
                }
            },
            Transition {
                from: Assistant.Visible; to: Assistant.Hidden
                NumberAnimation {
                    properties: "opacity"
                    duration: 2100
                }
            }
        ]
    }
}
