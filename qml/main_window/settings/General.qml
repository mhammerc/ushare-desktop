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
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import "../../components" as U
import "../../components/functions.js" as F

Item
{
    View
    {
        anchors
        {
            fill: parent;
            margins: Units.dp(16);
        }

        elevation: 1;
        radius: Units.dp(2);

        Column
        {
            anchors
            {
                fill: parent;
                topMargin: Units.dp(10);
            }

            spacing: Units.dp(5);

            Label
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                    margins: Units.dp(16);
                }

                style: 'title';
                text: qsTr('General settings');
            }

            CheckBox
            {
                text: qsTr('Run on startup');
                checked: F.stringToBoolean(Settings.value('run_on_startup', false));
                onCheckedChanged: Settings.setValue('run_on_startup', checked);
            }

            ListItem.SimpleMenu
            {
                text: qsTr('Language');
                model: ['English', 'Français'];
                selectedIndex:
                {
                    var locale = Settings.value('language', 'en');

                    if(locale === 'en') return 0;
                    else if(locale === 'fr') return 1;
                }
                onSelectedIndexChanged:
                {
                    if(selectedIndex === 0) Settings.setValue('language', 'en');
                    else if(selectedIndex === 1) Settings.setValue('language', 'fr');
                }
            }

            Label
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                    margins: Units.dp(16);
                }

                style: 'title';
                text: qsTr('On upload');
            }

            CheckBox
            {
                id: sound;
                text: qsTr('Play a sound');
                checked: F.stringToBoolean(Settings.value('play_sound', false));
                onCheckedChanged: Settings.setValue('play_sound', checked);
            }

            CheckBox
            {
                id: notificationWindow;
                text: qsTr('Notify me on successful upload');
                checked: F.stringToBoolean(Settings.value('show_notification_window', false));
                onCheckedChanged: Settings.setValue('show_notification_window', checked);
            }

            CheckBox
            {
                id: progressWindow;
                text: qsTr('Show upload progress');
                checked: F.stringToBoolean(Settings.value('show_progress_window', false));
                onCheckedChanged: Settings.setValue('show_progress_window', checked);
            }

            CheckBox
            {
                id: clipboard;
                text: qsTr('Copy web link to clipboard');
                checked: F.stringToBoolean(Settings.value('copy_link_to_clipboard', false));
                onCheckedChanged: Settings.setValue('copy_link_to_clipboard', checked);
            }

            CheckBox
            {
                id: browser;
                text: qsTr('Open file in browser');
                checked: F.stringToBoolean(Settings.value('open_file_in_browser', false));
                onCheckedChanged: Settings.setValue('open_file_in_browser', checked);
            } /* U.Checkbox */
        } /* Column */
    } /* View */
} /* Item */

