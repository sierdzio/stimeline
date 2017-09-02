import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Assistant 1.0

Frame {
    property var object: Assistant.defaultObject()
    signal plotRemoved(string plotId)
    height: 15

    /*!
     * We're using Flow on the assumption that the number of tags per SObject will
     * be small. But maybe this will not hold true - then ListView will be more
     * fitting. Or custom-written FlowView or something.
     */
    RowLayout {
        height: 15

        Flow {
            spacing: 5
            Layout.fillWidth: true

            Repeater {
                id: repeater
                height: 15
                model: object.plotCount()

                delegate: Plot {
                    plotId: object.plotIdAt(index)
                    onClose: plotRemoved(plotId)
                }
            }
        }

//        Rectangle {
//            id: btn
//            width: 14
//            height: 14
//            radius: 3
//            border.width: 1

//            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

//            Text {
//                anchors.fill: parent
//                text: "+"
//                font.pixelSize: 12
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//            }

//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    console.log("Opening plot editor with: " + object.name)
//                    plotEditor.object = object
//                    plotEditor.open()
//                }
//            }
//        }
    }
}
