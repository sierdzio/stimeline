import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Page {
    id: root

    Flickable {
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: column.height
        contentWidth: column.width

        ColumnLayout {
            id: column
            width: root.width
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
            Item { height: 25; width: 1 } // Invisible padding
            Text {
                Layout.fillWidth: true
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
