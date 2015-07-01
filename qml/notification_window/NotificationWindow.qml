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

import QtQuick 2.4
import "qrc:/qml-material/modules/Material" 0.1

Window
{
    id: root;
    width: 280;
    height: 84;

    flags: Qt.WindowStaysOnTopHint | Qt.CustomizeWindowHint | Qt.FramelessWindowHint;

    maximumWidth: width;
    minimumWidth: width;

    maximumHeight: height;
    minimumHeight: height;

    property real windowCount;
    property string title : "";
    property string text : "";
    property real count : 0;

    x: Desktop.size.width - width - 10;
    y: Desktop.size.height - ((height + 7) * windowCount) - 10;


    signal closeAsked;
    signal clickedInWindow;

        Rectangle
        {
            anchors.fill: parent;

            border
            {
                width: 1;
                color: Settings.value('color/primaryColor', '#4CAF50');
                pixelAligned: true;
            }
        }

        Image
        {
            width: 64;
            height: 64;

            x: 10;
            y: 10;

            mipmap: true;
            asynchronous: true;

            source: "qrc:/images/ushare_icon.png";
        }

        Column
        {
            x: 90;
            y: 10;

            Label
            {
                 style: "subheading";
                 text: title;
            }

            Label
            {
                text: root.text;
            }
        }

        Image
        {
            width: 34;
            height: 26;

            x: root.width - 35;
            y: 1;

            source: "qrc:/design/icon_close_unhover.png";

            MouseArea
            {
                id: exitMouse;
                anchors.fill: parent;
                hoverEnabled: true;

                onEntered:
                {
                    parent.source = "qrc:/design/icon_close_hover.png";
                    windowMouse.enabled = false;
                }

                onExited:
                {
                    parent.source = "qrc:/design/icon_close_unhover.png";
                    windowMouse.enabled = true;
                }

                Component.onCompleted:
                {
                    exitMouse.clicked.connect(root.closeAsked);
                }
            }
        }

        Label
        {
            x: root.width - 18;
            y: root.height - 20;

            text: root.count;
        }

        MouseArea
        {
            id: windowMouse;
            anchors.fill: parent;
            cursorShape: Qt.PointingHandCursor;

            Component.onCompleted:
            {
                windowMouse.clicked.connect(root.clickedInWindow);
            }
        }
}

