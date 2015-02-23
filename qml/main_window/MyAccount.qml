import QtQuick 2.0
import Material 0.1
import "../components" as U

Item {
    Column {
        anchors.centerIn: parent
        spacing: units.dp(25)

        U.Label {
            text: "You need to connect to U² online before use this feature"
        }
    }
}

