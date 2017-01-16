import QtQuick 2.8

Item {
    property string relativeSource
    Image {
        anchors.fill: parent
        source: relativeSource.length > 0? "file://" + Timeline.basePicturePath() + "/" + relativeSource : ""
        fillMode: Image.PreserveAspectFit
    }
}
