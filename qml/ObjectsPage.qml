import QtQuick 2.8
import QtQuick.Controls 2.1
import CustomItems 1.0
import Assistant 1.0
import "views"
import "cards"

Page {
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        SItemListView {
            id: pagePeople
            model: Timeline.personModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Person
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 140
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Person)
        }

        SItemListView {
            id: pageArtifacts
            model: Timeline.artifactModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Artifact
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 140
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Artifact)
        }

        SItemListView {
            id: pagePlaces
            model: Timeline.placeModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Place
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 140
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Place)
        }

        SItemListView {
            id: pageMaps
            model: Timeline.mapModel
            delegate: ObjectCard {
                objectId: model.id
                type: SObject.Map
                name: model.name
                picturePath: model.picturePath
                description: model.description
                from: model.from
                to: model.to
                width: 350
                height: 140
                onEdit: openEditor(objectId, type, name, picturePath, description, from, to)
            }

            onClicked: openEditor(Assistant.generateId(), SObject.Map)
        }
    }

//    PageIndicator {
//        id: indicator

//        count: swipeView.count
//        currentIndex: swipeView.currentIndex

//        anchors.bottom: swipeView.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//    }

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
