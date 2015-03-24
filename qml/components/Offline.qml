import QtQuick 2.0
import Material 0.1
import "../components" as U

/* When user is disconnected */
Item {
    anchors.fill: parent

    Column {
        anchors.centerIn: parent
        spacing: units.dp(25)

        U.Label {
            text: "You need to connect to U² Online before using this feature"
        }

        Row {
            spacing: units.dp(5);

            Button {
                text: 'Register'
                elevation: 1
                backgroundColor: Theme.accentColor
                onClicked: {
                    register.show();
                }
            }

            Button {
                text: 'Login'
                elevation: 2
                backgroundColor: Theme.accentColor
                onClicked: {
                    login.show();
                }
            }

            Button {
                text: 'U² Online'
                elevation: 1
                backgroundColor: Theme.accentColor
            }
        }
    }
}

