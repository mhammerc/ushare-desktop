/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

import QtQuick 2.0
import "qrc:/qml-material/modules/Material" 0.1
import "qrc:/qml-material/modules/Material/ListItems" 0.1 as ListItem

Item {
    id: settings;
    property var components: [qsTr("General"), qsTr("Saving"), qsTr("Keyboard shortcuts"), qsTr("Updates"), qsTr("Credits")];
    property var componentsName: ['General', 'Saving', 'Keyboard shortcuts', 'Updates', 'Credits'];

    property int selectedComponent: 0;

    Sidebar {
        id: sidebar

        Column {
            width: parent.width

            Repeater {
                model: settings.components
                delegate: ListItem.Standard {
                    text: modelData
                    selected: modelData === components[selectedComponent];
                    onClicked: selectedComponent = components.indexOf(modelData);
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
            source: Qt.resolvedUrl("settings/%.qml").arg(componentsName[selectedComponent].replace(" ", ""));
        }
    }
    Scrollbar {
        flickableItem: flickable
    }
}

