import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem

Item {
    id: settings
    property var components: ["General", "Saving", "Keyboard shortcuts", "Updates", "Credits"]

    property string selectedComponent: components[0]

    Sidebar {
        id: sidebar

        Column {
            width: parent.width

            Repeater {
                model: settings.components
                delegate: ListItem.Standard {
                    text: modelData
                    selected: modelData == selectedComponent
                    onClicked: selectedComponent = modelData
                }
            }
        }
    }

    Flickable {
        id: flickable
        anchors {
            left: sidebar.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        clip: true
        contentHeight: Math.max(example.implicitHeight, height)

        Loader {
            id: example
            anchors.fill: parent
            // selectedComponent will always be valid, as it defaults to the first component
            source: Qt.resolvedUrl("settings/%.qml").arg(selectedComponent.replace(" ", ""))
        }
    }
    Scrollbar {
        flickableItem: flickable
    }
}

