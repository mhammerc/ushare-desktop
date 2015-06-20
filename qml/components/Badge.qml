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

Rectangle
{
    width: label.implicitWidth + 10;
    height: label.implicitHeight + 7;

    radius: 8;

    property alias text: label.text;

    Label
    {
        id: label;

        anchors
        {
            horizontalCenter: parent.horizontalCenter;
            verticalCenter: parent.verticalCenter;
        }

        color: "white";
    }
}

