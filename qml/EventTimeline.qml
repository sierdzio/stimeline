import QtQuick 2.7
import QtGraphicalEffects 1.0
import CustomItems 1.0

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

    Flickable {
        anchors.fill: parent
        flickableDirection: Flickable.HorizontalFlick
        focus: true

        EventTimelineView {
            height: parent.height
        }
    }
}
