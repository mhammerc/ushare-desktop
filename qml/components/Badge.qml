import QtQuick 2.0

Rectangle {
    width: label.implicitWidth + 10
    height: label.implicitHeight + 10

    radius: 5

    property alias text: label.text

    Label {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        id: label
        color: "white"
    }
}

