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
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtMultimedia 5.4
import "qrc:/qml-material/modules/Material" 0.1
import "../../components" as U

Item
{
    View
    {
        id: view;

        anchors
        {
            fill: parent;
            margins: Units.dp(16);
        }

        elevation: 1

        Icon
        {
            anchors
            {
                top: parent.top;
                right: parent.right;
                margins: Units.dp(8);
            }

            property bool soundEnabled: false;
            name: soundEnabled ? 'av/volume_up' : 'av/volume_off';

            color: Theme.accentColor;

            onSoundEnabledChanged:
            {
                if(soundEnabled)
                {
                    audioPlayer.play();
                }
                else
                {
                    audioPlayer.stop();
                }
            }

            MouseArea
            {
                anchors.fill: parent;

                onClicked:
                {
                    parent.soundEnabled = !parent.soundEnabled;
                }
            }
        }

        Column
        {
            id: column;

            anchors
            {
                left: parent.left;
                right: parent.right;
                margins: Units.dp(8);
            }

            spacing: Units.dp(8);

            Label
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                }

                text: 'uShare';
                style: 'title';
                horizontalAlignment: Text.AlignHCenter;
            }

            Label
            {
                text: qsTr('You are so many to help us every days...');
            }

            Label
            {
                text: qsTr('We can\'t say thank you to all of you!');
            }

            Label
            {
                text: qsTr('So we tell this here : <strong>Thank you!</strong>');
            }

            Label
            {
                text: qsTr('We love you.');
                color: 'red';
            }

            Label
            {
                text: qsTr('And, for sure, don\'t forget to be #Happy4Ever!');
            }

            Label
            {
                text: qsTr('Our servers are freely and generously powered by <a href="https://client.dedizones.com/link.php?id=46">Dedishops</a>');

                MouseArea
                {
                    anchors.fill: parent;

                    onClicked: Desktop.openUrl('https://client.dedizones.com/link.php?id=46');
                }
            }

            ThinDivider
            {}

            Row
            {
                anchors
                {
                    horizontalCenter: parent.horizontalCenter;
                }

                Button
                {
                    text: 'Made by uSquare';
                    onClicked: Qt.openUrlExternally('https://usquare.io');
                }

                Button
                {
                    text: 'Our website';
                    onClicked: Qt.openUrlExternally('http://www.ushare.so');
                }

                Button
                {
                    text: 'Find us on GitHub';
                    onClicked: Qt.openUrlExternally('https://github.com/uShare-app');
                }
            }

            Row
            {
                anchors
                {
                    horizontalCenter: parent.horizontalCenter;
                }

                Button
                {
                    text: 'Made with Material Design icons';
                    onClicked: Qt.openUrlExternally('https://github.com/google/material-design-icons');
                }

                Button
                {
                    text: 'Made with Qt';
                    onClicked: Desktop.aboutQt();
                }
            }

            ThinDivider
            {}

            Label
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                }

                text: 'Contributors list';
                style: 'title';
                horizontalAlignment: Text.AlignHCenter;
            }
        }

        Flickable
        {
            anchors
            {
                top: column.bottom;
                bottom: parent.bottom;
                left: parent.left;
                right: parent.right;
            }

            contentHeight: content.height;
            contentWidth: width;
            clip: true;

            Item
            {
                id: content;
                anchors.margins: Units.dp(16);

                width: parent.width;
                height: grid.implicitHeight + anchors.margins * 2;

                Grid
                {
                    id: grid;

                    anchors
                    {
                        centerIn: parent;
                    }

                    columns: Math.floor(column.width / (250 + Units.dp(8))) ? Math.floor(column.width / (250 + Units.dp(8))) : 1;
                    spacing: Units.dp(8);

                    U.ProfileCard
                    {
                        name: 'Martin H.';
                        description: qsTr('A superhero');
                        imageSource: 'qrc:/images/martin.jpg';
                        twitterUrl: 'https://twitter.com/_MartinH_';
                    }

                    U.ProfileCard
                    {
                        name: 'Yohann H.';
                        description: qsTr('uShare Online Officer');
                        imageSource: 'qrc:/images/yohann.jpg';
                        twitterUrl: 'https://twitter.com/WatchDroid';
                    }

                    U.ProfileCard
                    {
                        name: 'Aymeric B.';
                        description: qsTr('Marketing Director');
                        imageSource: 'qrc:/images/aymeric.png';
                        twitterUrl: 'https://twitter.com/MimimDragneel';
                    }

                    U.ProfileCard
                    {
                        name: 'Mickael V.';
                        description: qsTr('Minecraft director');
                        imageSource: 'qrc:/images/fanor.jpg';
                        twitterUrl: 'https://twitter.com/Fanor79';
                    }

                    U.ProfileCard
                    {
                        name: 'Benjamin B.';
                        description: qsTr('Material Design specialist');
                        imageSource: 'qrc:/images/benjamin.jpg';
                        twitterUrl: 'https://twitter.com/benjam62217'
                    }

                    U.ProfileCard
                    {
                       name: 'Julien P.';
                       description: qsTr('Tester Director ㅡ Anime Fan');
                       imageSource: 'qrc:/images/julien.png';
                       twitterUrl: 'https://twitter.com/Dokuragon';
                    }

                    U.ProfileCard
                    {
                       name: 'Antoine O.';
                       description: qsTr('Helper programmer');
                       imageSource: 'qrc:/images/toinane.jpg';
                       twitterUrl: 'https://twitter.com/toinane';
                    }

                    U.ProfileCard
                    {
                        name: 'Jalal A.';
                        description: qsTr('Helper');
                        imageSource: 'qrc:/images/jalal.jpg';
                        twitterUrl: 'https://twitter.com/xXGaminGXx33';
                    }

                    U.ProfileCard
                    {
                        name: 'GraphOne';
                        description: qsTr('Superb group of graphic designers');
                        imageSource: 'qrc:/images/graphone.png';
                        twitterUrl: 'https://twitter.com/GroupeGraph_FR';
                    }

                    U.ProfileCard
                    {
                        name: 'BleuDiamant';
                        description: qsTr('One fucking diamond!');
                        imageSource: 'qrc:/images/bleudiamant.png';
                        twitterUrl: 'https://twitter.com/BleuDiamantFR';
                    }
                }
            }
        }
    }

    MediaPlayer
    {
        id: audioPlayer;
        source: 'qrc:/sounds/rocky.mp3';
        loops: MediaPlayer.Infinite;
        autoLoad: true;

        onError:
        {
            console.log(errorString);
        }
    }
}

