import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2

Rectangle {
    property string plotId
    signal close()

    color: Material.color(Material.Green)
    radius: 5
    height: 15
    width: row.width

    RowLayout {
        id: row
        height: parent.height
        spacing: 2

        Label {
            // TODO: bad conversion...
            text: Timeline.plots.value(plotId)
            font.pointSize: 9
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignVCenter
        }

        Rectangle {
            height: parent.height
            width: 1
            border.color: Material.color(Material.Grey)
            border.width: 1
        }

        Text {
            text: "x"
            font.pointSize: 9
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignVCenter

            MouseArea {
                anchors.fill: parent
                onClicked: close()
            }
        }
    }
}
