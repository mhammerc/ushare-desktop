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

