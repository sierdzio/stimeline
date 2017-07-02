import QtQuick 2.8
import QtQuick.Controls 2.1
import CustomItems 1.0
import Assistant 1.0
import "../cards"

Page {
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        SObjectListPage {
            id: pagePeople
            model: Timeline.personModel
            onEditRequest: openEditor(object)
            onAddObjectRequest: openEmptyEditor(SObject.Person)
        }

        SObjectListPage {
            id: pageArtifacts
            model: Timeline.artifactModel
            onEditRequest: openEditor(object)
            onAddObjectRequest: openEmptyEditor(SObject.Artifact)
        }

        SObjectListPage {
            id: pagePlaces
            model: Timeline.placeModel
            onEditRequest: openEditor(object)
            onAddObjectRequest: openEmptyEditor(SObject.Place)
        }

        SObjectListPage {
            id: pageMaps
            model: Timeline.mapModel
            onEditRequest: openEditor(object)
            onAddObjectRequest: openEmptyEditor(SObject.Map)
        }
    }

    footer: TabBar {
        property int previousIndex: -1
        property int __tempIndex: 0

        id: tabBar
        currentIndex: swipeView.currentIndex
        onCurrentIndexChanged: {
            previousIndex = __tempIndex;
            __tempIndex = currentIndex;
        }

        TabButton {
            text: qsTr("People")
        }
        TabButton {
            text: qsTr("Artifacts")
        }
        TabButton {
            text: qsTr("Places")
        }
        TabButton {
            text: qsTr("Maps")
        }
    }
}
