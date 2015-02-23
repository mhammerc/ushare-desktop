import QtQuick 2.0
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import "../../components" as U
import "../../components/functions.js" as F

Item {
    View {
        anchors.fill: parent
        anchors.margins: units.dp(16)

        elevation: 1
        radius: units.dp(2)

        Column {
            anchors.fill: parent
            anchors.topMargin: units.dp(10)
            spacing: units.dp(7);

            U.Label {
                id: titleLabel

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: units.dp(16)
                }

                style: "title"
                text: "General settings"
                color: Theme.light.textColor
            }

            U.Checkbox {
                text: 'Run on startup'
                checked: false
                darkBackground: false
            }

            ListItem.SimpleMenu {
                text: "Language"
                model: ["English", "French"]
            }

            U.Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: units.dp(16)
                }

                style: "title"
                text: "On successful upload"
                color: Theme.light.textColor
            }

            U.Checkbox {
                id: sound
                text: 'Play a sound'
                checked: F.stringToBoolean(Settings.value('playSound', false))
                darkBackground: false
                onCheckedChanged: {
                    Settings.setValue('playSound', checked)
                    Settings.value('playSound', checked)
                }
            }

            U.Checkbox {
                id: progressWindow
                text: 'Show upload progress'
                checked: F.stringToBoolean(Settings.value('ShowProgressWindow', false))
                darkBackground: false
                onCheckedChanged: {
                    Settings.setValue('ShowProgressWindow', checked)
                }
            }

            U.Checkbox {
                id: clipboard
                text: 'Copy web link to clipboard'
                checked: F.stringToBoolean(Settings.value('copyLinkToClipboard', false))
                darkBackground: false
                onCheckedChanged: {
                    Settings.setValue('copyLinkToClipboard', checked)
                    //console.log(checked);
                }
            }

            U.Checkbox {
                id: browser
                text: 'Open file in browser'
                checked: F.stringToBoolean(Settings.value('openFileInBrowser', false))
                darkBackground: false
                onCheckedChanged: {
                    Settings.setValue('openFileInBrowser', checked)
                }
            }
        } /* Column */
    } /* View */
} /* Item */

