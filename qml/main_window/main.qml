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

import QtQuick 2.2
import "qrc:/qml-material/modules/Material" 0.1
import "qrc:/qml-material/modules/Material/ListItems" 0.1 as ListItem
import "."
import "../components" as U


ApplicationWindow
{
    id: baseItem;
    width: 780;
    height: 600;

    minimumWidth: 640;
    minimumHeight: 480;

    title: 'uShare';

    theme
    {
        primaryColor: Settings.value('color/primaryColor', '#2196F3');
        accentColor: Settings.value('color/accentColor','#4CAF50');
        backgroundColor: Settings.value('color/backgroundColor', '#fafafa');
    }

    initialPage: page;

    Page
    {
        id: page;
        title: "uShare";

        tabs:
        [
            {
                text: qsTr("Overview"),
                icon: "action/home",
            },
            qsTr("Uploads"),
            qsTr("Settings"),
        ];

        actions:
        [
            Action
            {
                iconName: "image/color_lens";
                name: qsTr("Colors");
                onTriggered: colorPicker.show();
            }
        ]

        TabView
        {
            id: tabView;
            anchors.fill: parent;

            model: tabs;
            currentIndex: page.selectedTab;
        }

        VisualItemModel
        {
            id: tabs;

            // Tab 1 "Overview"
            Overview
            {
                width: tabView.width;
                height: tabView.height;
            }

            // Tab 2 "Uploads"
            Uploads
            {
                width: tabView.width;
                height: tabView.height;
            }

            // Tab 3 "Settings"
            SettingsPage
            {
                width: tabView.width;
                height: tabView.height;
            }
        } /* VisualItemModel */
    } /* Page */

    U.ColorPicker
    {
        id: colorPicker;
    }

    U.Login
    {
        id: login

    }

    U.Register
    {
        id: register;
    }

    Snackbar
    {
        id: snackbar;
    }
} /* ApplicationWindow */
