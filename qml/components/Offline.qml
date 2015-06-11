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
            text: qsTr("You need to connect to U² Online before using this feature");
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

