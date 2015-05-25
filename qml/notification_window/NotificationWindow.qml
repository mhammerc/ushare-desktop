import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

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

            source: "qrc:/images/uplimg_icon.png";
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

