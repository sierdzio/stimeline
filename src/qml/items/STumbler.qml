import QtQuick 2.8
import QtQuick.Controls 2.1

Tumbler {
    delegate: Text {
        text: (index) + 1
        height: paintedHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
    }
}
