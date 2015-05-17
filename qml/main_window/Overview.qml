import QtQuick 2.0
import Material 0.1
import Material.Extras 0.1
import U.Global 1.0
import "../components" as U
import "../components/usquare_online.js" as UOnline
import "../components/network.js" as Network
import "../components/md5.js" as Crypto

Item
{
    id: root;

    /* Hold user's datas. See the API to know what is the object */
    property var datas: ({});

    onFocusChanged:
    {
        if(!focus)
        {
            refreshTimer.running = false;
            return;
        }

        refreshTimer.running = true;
    }

    Component.onCompleted:
    {
        onStart();
    }

    /* When user is connected */
    Item
    {
        anchors.fill: parent;
        visible: Global.connected && !Global.isLoading;

        Row
        {
            anchors
            {
                fill: parent;
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

                        source: "qrc:/design/inconnu.jpg";
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

                        onClicked: snackbar.open("Opening uShare online");
                    }

                    Row
                    {
                        anchors.horizontalCenter: parent.horizontalCenter;
                        spacing: Units.dp(5);

                        Button
                        {
                            text: "Edit account";

                            backgroundColor: Theme.accentColor;
                            elevation: 1;

                            onClicked: snackbar.open("Opening uShare online");
                        }

                        Button
                        {
                            text: "Disconnect";

                            backgroundColor: Theme.accentColor;
                            elevation: 1;

                            onClicked:
                            {
                                disconnect();
                                snackbar.open("Successful logout");
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
                            text: "vues sur vos fichiers";

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
                            text: "fichiers envoyé aujourd'hui";

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
                            text: "fichiers envoyés au total";

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
        visible: !Global.connected && !Global.isLoading;
    }

    /* On loading */
    U.Loading
    {
        visible: Global.isLoading;
    }

    // DEBUG ONLY
    ActionButton
    {
        anchors
        {
            right: parent.right;
            bottom: parent.bottom;
            margins: Units.dp(32);
        }

        onClicked:
        {
            updateDatas(false);
        }

        iconName: "content/add";
    }

    Timer
    {
        id: refreshTimer;

        interval: 1000;
        running: false;
        repeat: true;
        triggeredOnStart: false;

        onTriggered:
        {
            if(!Global.connected || Global.isLoading)
            {
                return;
            }

            updateDatas(true);
        }
    }

    Connections
    {
        target: Global;

        onConnectedChanged:
        {
            if(!Global.connected)
            {
                refreshTimer.running = false;
            }
        }
    }

    Connections
    {
        target: login;

        onSuccessLogin:
        {
            UOnline.initWebSocket(root);
        }
    }

    Connections
    {
        target: register;

        onSuccessRegister:
        {
            UOnline.initWebSocket(root);
        }
    }

    /* When the application is started and loaded */
    function onStart()
    {
        UOnline.setSettings(Settings);

        UOnline.onWsConnected(wsConnected);
        UOnline.onWsDisconnected(disconnect);
        UOnline.onWsError(wsError);

        if(Settings.value('username', false) === 'false' || Settings.value('password', false) === 'false')
        {
            return;
        }

        Global.hasLogin = true;
        Global.isLoading = true;


        UOnline.connect(Settings.value('username', false), Settings.value('password', false), function(err, result)
        {
            if(err || !result.success)
            {
                Global.hasLogin = false;
                Global.isLoading = false;
                Global.connected = false;
                return;
            }

            Settings.setValue("account_key", result.accountkey);
            Settings.setValue("private_key", result.privatekey);

            UOnline.initWebSocket(root);
        });
    }

    /* Update datas on overview screen. If it is not lite, also update gravatar. */
    function updateDatas(lite)
    {
        Global.isLoading = lite ? false : true;

        var onGetUserInfos = function(result)
        {

            if(!result.success)
            {
                snackbar.open('An error occurred');
                console.log(JSON.stringify(result));
                return;
            }

            datas = result;

            if(!lite)
            {
                updateAvatar();
                Global.isLoading = false;
            }
        }

        UOnline.getUserInfos(onGetUserInfos);
    }

    function updateAvatar()
    {
        Network.gravatar(datas.email, Crypto.md5, function(url)
        {
            if(url !== null)
            {
                gravatar.source = url;
                return;
            }

            gravatar.source = "qrc:/design/inconnu.jpg";
        });
    }

    function disconnect()
    {
        Global.hasLogin = false;
        Global.connected = false;
        Global.isLoading = false;

        UOnline.disconnect();

        Settings.setValue('username', false);
        Settings.setValue('password', false);
        Settings.setValue('account_key', false);
        Settings.setValue('private_key', false);

        datas = null;
    }

    function wsConnected()
    {
        Global.connected = true;
        Global.isLoading = true;

        UOnline.wsAuth(function(result)
        {
            if(result.success === true)
            {
                updateDatas(false);
                refreshTimer.start();
            }
            else
            {
                snackbar.open('Cant login, check your credentials');

                Global.connected = false;
                Global.isLoading = false;
                Global.hasLogin = false;
            }
        });
    }

    function wsError()
    {
        snackbar.open('Connection lost, error occurred');
        disconnect();
    }

}
