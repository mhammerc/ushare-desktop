import Material 0.1
import Material.Extras 0.1
import QtQuick 2.0

View
{
    id: profileCard;
    elevation: 1;

    width: 250;
    height: 60;

    property alias name: nameLabel.text;
    property alias description: descriptionLabel.text;
    property alias imageSource: profilePicture.source;
    property string twitterUrl;

    Row
    {
        anchors
        {
            fill: parent;
            margins: Units.dp(8);
        }

        spacing: Units.dp(8);

        CircleImage
        {
            id: profilePicture;
            anchors.verticalCenter: parent.verticalCenter;

            source: 'qrc:/design/inconnu.jpg';

            width: 50;
            height: 50;
        }

        Column
        {
            spacing: Units.dp(5);

            Label
            {
                id: nameLabel;
                style: 'title';
            }

            Label
            {
                id: descriptionLabel;
            }
        }

    }

    Icon
    {
        anchors
        {
            right: parent.right
            margins: Units.dp(8);
            verticalCenter: parent.verticalCenter;
        }

        name: 'awesome/twitter'
        color: '#3498db';

        MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                Desktop.openUrl(profileCard.twitterUrl);
            }
        }
    }
}

