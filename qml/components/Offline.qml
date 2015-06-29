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
import Material 0.1
import "../components" as U

/* When user is disconnected */
Item
{
    anchors.fill: parent;

    Column
    {
        anchors.centerIn: parent;
        spacing: Units.dp(25);

        U.Label
        {
            text: qsTr("You need to connect to uShare Online before using this feature");
        }

        Row
        {
            spacing: Units.dp(5);

            Button
            {
                text: qsTr('Register');
                elevation: 1;
                backgroundColor: Theme.accentColor;
                onClicked:
                {
                    register.show();
                }
            }

            Button
            {
                text: qsTr('Login');
                elevation: 2;
                backgroundColor: Theme.accentColor;
                onClicked:
                {
                    login.show();
                }
            }

            Button
            {
                text: qsTr('uShare Online');
                elevation: 1;
                backgroundColor: Theme.accentColor;
            }
        }
    }
}

