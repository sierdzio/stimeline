import QtQuick 2.7
import QtQuick.Controls 2.0

Tumbler {
    delegate: Text {
        text: (index) + 1
        height: paintedHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: 1 - Math.abs(Tumbler.displacement)
    }
}
