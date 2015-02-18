import QtQuick 2.0
import Material 0.1

Item {
    Column {
        anchors.centerIn: parent
        spacing: units.dp(25)

        Label {
            text: "You need to connect to Uplimg web before use this (" + Settings.value("username", "haha") + ")"
        }
    }
}

