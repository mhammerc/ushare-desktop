import QtQuick 2.0
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import "../../components" as U
import "../../components/functions.js" as F

Item {
    View {
        anchors.fill: parent
        anchors.margins: Units.dp(16)

        elevation: 1
        radius: Units.dp(2)

        Column {
            anchors.fill: parent
            anchors.topMargin: Units.dp(10)
            spacing: Units.dp(5);

            U.Label {
                id: titleLabel

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(16)
                }

                style: "title"
                text: "General settings"
                color: Theme.light.textColor
            }

            U.Checkbox {
                text: 'Run on startup'
                checked: F.stringToBoolean(Settings.value('run_on_startup', false))
                darkBackground: false
                onCheckedChanged: Settings.setValue('run_on_startup', checked)
            }

            ListItem.SimpleMenu {
                text: "Language"
                model: ["English", "French"]
                selectedIndex: Settings.value("language", 0)
                onSelectedIndexChanged: Settings.setValue("language", selectedIndex)
            }

            U.Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(16)
                }

                style: "title"
                text: "On upload"
                color: Theme.light.textColor
            }

            U.Checkbox {
                id: sound
                text: 'Play a sound'
                checked: F.stringToBoolean(Settings.value('play_sound', false))
                darkBackground: false
                onCheckedChanged: Settings.setValue('play_sound', checked)
            }

            U.Checkbox {
                id: notificationWindow
                text: 'Notify me on successful upload'
                checked: F.stringToBoolean(Settings.value('show_notification_window', false))
                darkBackground: false
                onCheckedChanged: Settings.setValue('show_notification_window', checked)
            }

            U.Checkbox {
                id: progressWindow
                text: 'Show upload progress'
                checked: F.stringToBoolean(Settings.value('show_progress_window', false))
                darkBackground: false
                onCheckedChanged: Settings.setValue('show_progress_window', checked)
            }

            U.Checkbox {
                id: clipboard
                text: 'Copy web link to clipboard'
                checked: F.stringToBoolean(Settings.value('copy_link_to_clipboard', false))
                darkBackground: false
                onCheckedChanged: Settings.setValue('copy_link_to_clipboard', checked)
            }

            U.Checkbox {
                id: browser
                text: 'Open file in browser'
                checked: F.stringToBoolean(Settings.value('open_file_in_browser', false))
                darkBackground: false
                onCheckedChanged: Settings.setValue('open_file_in_browser', checked)
            } /* U.Checkbox */
        } /* Column */
    } /* View */
} /* Item */

