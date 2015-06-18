import QtQuick 2.0
import Material 0.1
import "../../components" as U

Item
{
    id: root;
    property var informations: null;

    Component.onCompleted:
    {
        getInfos();
    }

    View
    {
        anchors.fill: parent;
        anchors.margins: Units.dp(16);

        elevation: 1;
        radius: Units.dp(2);

        /* Main View */
        Item
        {
            anchors.fill: parent;
            visible: root.informations !== null && informations.version !== Settings.appVersion;

            Column
            {
                anchors.fill: parent;
                anchors.topMargin: Units.dp(10);
                spacing: Units.dp(5);

                Label
                {
                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(16);
                    }

                    style: 'title';
                    text: qsTr('Updates');
                }

                Label
                {
                    id: actualVersion;
                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(16);
                    }

                    style: 'subheading';
                    text: qsTr('Actual version: %1').arg(Settings.appVersion);
                }

                Label
                {
                    id: latestVersion;
                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(16);
                    }

                    style: 'subheading';
                    text: qsTr('Latest version: %1').arg(informations.version);
                }

                Row
                {
                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(16);
                    }

                    Label
                    {
                        style: 'subheading';
                        text: qsTr('Description: ');
                    }

                    Label
                    {
                        style: 'subheading';
                        text: informations.description;
                    }
                }

                Button
                {
                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(16);
                    }

                    text: qsTr('Update now!');
                    enabled: actualVersion !== latestVersion;
                    elevation: 1;
                    backgroundColor: Theme.accentColor;

                    onClicked:
                    {
                        Desktop.openUrl(informations.link);
                    }
                }
            }
        }

        /* No update available */
        Item
        {
            anchors.fill: parent;
            visible: root.informations !== null && informations.version === Settings.appVersion;

            Label
            {
                anchors
                {
                    centerIn: parent;
                }

                text: qsTr('No update available :-)');
                style: 'headline';
            }
        }

        /* On loading */
        U.Loading
        {
            visible: informations === null;
        }
    }

    Connections
    {
        target: uShareOnline;

        onGotUpdates:
        {
            for(var i = 0; i < response.length; ++i)
            {
                if(response[i].os === Settings.os && response[i].arch === Settings.arch)
                    informations = response[i];
            }
        }
    }

    function getInfos()
    {
        uShareOnline.getUpdates();
    }
}

