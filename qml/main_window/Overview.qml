import QtQuick 2.0
import Material 0.1
import Material.Extras 0.1
import "../components" as U

Item
{
    id: root;

    /* Hold user's datas. See the API to know what is the object */
    property var datas: ({});

    Component.onCompleted:
    {
        onStart();
    }

    /* When user is connected */
    Item
    {
        anchors.fill: parent;

        visible: uShareOnline.connected && datas.username;

        Row
        {
            anchors
            {
                centerIn: parent;
                margins: Units.dp(32);
            }

            spacing: Units.dp(16);

            View
            {
                width: 300;
                height: 285;

                elevation: 2;

                Column
                {
                    anchors
                    {
                        fill: parent;
                        margins: Units.dp(8);
                    }

                    spacing: Units.dp(8);

                    CircleImage
                    {
                        id: gravatar;
                        anchors.horizontalCenter: parent.horizontalCenter;

                        width: 85;
                        height: 85;

                        source: datas.avatarUrl;
                    }

                    Label
                    {
                        text: datas.username ? datas.username : '0';

                        anchors
                        {
                            horizontalCenter: parent.horizontalCenter;
                            margins: Units.dp(16);
                        }

                        style: "display2";
                        color: Theme.light.textColor;
                    }

                    U.Badge
                    {
                        text: datas.accountType ? datas.accountType : '0';

                        anchors.horizontalCenter: parent.horizontalCenter;
                        color: "#c0392b"
                    }

                    Button
                    {
                        text: "uShare Online";

                        anchors.horizontalCenter: parent.horizontalCenter;
                        elevation: 1;
                        backgroundColor: Theme.accentColor;

                        onClicked: snackbar.open(qsTr("Opening uShare online"));
                    }

                    Row
                    {
                        anchors.horizontalCenter: parent.horizontalCenter;
                        spacing: Units.dp(5);

                        Button
                        {
                            text: qsTr("Edit account");

                            backgroundColor: Theme.accentColor;
                            elevation: 1;

                            onClicked: snackbar.open(qsTr("Opening uShare online"));
                        }

                        Button
                        {
                            text: qsTr("Disconnect");

                            backgroundColor: Theme.accentColor;
                            elevation: 1;

                            onClicked:
                            {
                                disconnect();
                                snackbar.open(qsTr("Successful logout"));
                            }
                        }
                    } /* Row */
                } /* Column */
            } /* View */

            View
            {
                width: 300;
                height: 285;

                anchors.leftMargin: Units.dp(2);

                elevation: 2;

                Column
                {
                    anchors
                    {
                        fill: parent;
                        margins: Units.dp(8);
                    }

                    spacing: Units.dp(30);

                    Column
                    {
                        anchors
                        {
                            left: parent.left;
                            right: parent.right;
                            margins: Units.dp(8);
                        }

                        spacing: Units.dp(5);

                        Label // Number of views
                        {
                            text: datas.numberOfViews ? datas.numberOfViews : '0';

                            anchors.horizontalCenter: parent.horizontalCenter;

                            style: "display2";
                            color: "#c0392b";
                        }

                        Label
                        {
                            text: qsTr("views on your files");

                            anchors.horizontalCenter: parent.horizontalCenter;
                            style: "title";
                        }
                    }

                    Column
                    {
                        anchors
                        {
                            left: parent.left;
                            right: parent.right;
                            margins: Units.dp(8);
                        }

                        spacing: Units.dp(5);

                        Label // Number of files saved today
                        {
                            text: datas.numberOfFilesSavedToday ? datas.numberOfFilesSavedToday : '0';

                            anchors.horizontalCenter: parent.horizontalCenter;
                            style: "display2";
                            color: "#c0392b";
                        }

                        Label
                        {
                            text: qsTr("numbers of files saved today");

                            anchors.horizontalCenter: parent.horizontalCenter;
                            style: "title";
                        }
                    }

                    Column
                    {
                        anchors
                        {
                            left: parent.left;
                            right: parent.right;
                            margins: Units.dp(8);
                        }

                        spacing: Units.dp(5);


                        Label // Number of files saved
                        {
                            text: datas.numberOfFilesSaved ? datas.numberOfFilesSaved : '0';

                            anchors.horizontalCenter: parent.horizontalCenter;
                            style: "display2";
                            color: "#c0392b";
                        }

                        Label
                        {
                            text: qsTr("number of files saved");

                            anchors.horizontalCenter: parent.horizontalCenter;
                            style: "title";
                        } /* Label */
                    } /* Column */
                } /* Column */
            } /* View */
        } /* Row */
    } /* Main Item when user is connected */

    /* When user is disconnected */
    U.Offline
    {
        visible: !uShareOnline.connected;
    }

    /* On loading */
    U.Loading
    {
        visible: uShareOnline.connected && !datas.username;
    }

    Timer
    {
        id: refreshTimer;

        interval: 1000;
        running: root.focus;
        repeat: true;
        triggeredOnStart: false;

        onTriggered:
        {
            if(!baseItem.visible)
            {
                return;
            }

            if(!uShareOnline.connected || uShareOnline.loading)
            {
                return;
            }

            updateDatas();
        }
    }

    Connections
    {
        target: uShareOnline;

        onConnectedChanged:
        {
            if(!uShareOnline.connected)
            {
                refreshTimer.running = false;
            }
            else
            {
                refreshTimer.running = true;
            }
        }

        onGotUserInfos:
        {
            if(!response.success)
            {
                snackbar.open('Connection to uShare Online lost :\'(' + response.message ? ' -> ' + response.message : '');
                return;
            }

            datas = response;
        }
    }

    Connections
    {
        target: register;

        onSuccessRegister:
        {
            onStart();
        }
    }

    /* When the application is started and loaded */
    function onStart()
    {
        if(Settings.value('username', false) === 'false' || Settings.value('password', false) === 'false')
        {
            return;
        }

        uShareOnline.connect(Settings.value('username', false), Settings.value('password', false));
    }

    /* Update datas on overview screen. If it is not lite, also update gravatar. */
    function updateDatas()
    {
        uShareOnline.getUserInfos();
    }

    function disconnect()
    {
        uShareOnline.disconnect();

        Settings.setValue('username', false);
        Settings.setValue('password', false);

        datas = null;
    }
}
