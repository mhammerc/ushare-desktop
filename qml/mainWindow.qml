import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: uplimg

    theme {
        accentColor: "#009688"
    }

    initialPage: page

    property var components: ["My files", "My account", "Settings"]

    property string selectedComponent: components[0]

    Page {
        id: page

        title: "Uplimg"

        ListItem.Standard {}

        /*actions: [
            Action {
                iconName: "content/add"
            },

            Action {
                iconName: "action/search"
                name: "Search"
            },

            Action {
                iconName: "action/language"
                name: "Language"
            },

            Action {
                iconName: "action/account_circle"
                name: "Account"
            },

            Action {
                iconName: "action/settings"
                name: "Settings"
            }
        ]*/

        Sidebar {
            id: sidebar

            Column {
                width: parent.width

                Repeater {
                    model: uplimg.components
                    delegate: ListItem.Standard {
                        text: modelData
                        selected: modelData == selectedComponent
                        onTriggered: selectedComponent = modelData
                    }
                }
            }
        }

        Loader {
            anchors {
                left: sidebar.right
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            // selectedComponent will always be valid, as it defaults to the first component
            source: Qt.resolvedUrl("%.qml").arg(selectedComponent.replace(" ", ""))
            asynchronous: true
        }
    }
}
