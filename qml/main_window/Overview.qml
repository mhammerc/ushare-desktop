import QtQuick 2.0
import Material 0.1
import Material.Extras 0.1
import U.Global 1.0
import "../components" as U
import "../components/usquare_online.js" as UOnline
import "../components/network.js" as Network
import "../components/md5.js" as Crypto

Item {
    id: root

    onFocusChanged: {
        if(!focus)
        {
            refreshTimer.running = false;
            return;
        }

        refreshTimer.running = true;
    }

    Component.onCompleted: {
        isLoading = true;
        onStart();
    }

    /* When user is connected */
    Item {
        anchors.fill: parent
        visible: Global.connected && !Global.isLoading
        Row {
        anchors.fill: parent
        anchors.margins: units.dp(32);
        spacing: units.dp(16);

        View {
            width: 300
            height: 285

            elevation: 2

            Column {
                anchors.fill: parent
                anchors.margins: units.dp(8)
                spacing: units.dp(8);

                CircleImage {
                    id: gravatar
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: 85
                    height: 85

                    source: "qrc:/design/inconnu.jpg"
                }

                Label {
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        margins: units.dp(16)
                    }

                    id: username
                    text: ""
                    style:"display2"
                    color:Theme.light.textColor
                }

                U.Badge {
                    anchors.horizontalCenter: parent.horizontalCenter

                    id: accountType
                    text: "VIP"
                    color: "#c0392b"
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    elevation: 1
                    backgroundColor: Theme.accentColor
                    text: "U² Online"
                    onClicked: snackbar.open("Opening U² online")
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: units.dp(5);

                    Button {
                        backgroundColor: Theme.accentColor
                        text: "Edit account"
                        elevation: 1
                        onClicked: snackbar.open("Opening U² online")
                    }

                    Button {
                        backgroundColor: Theme.accentColor
                        text: "Disconnect"
                        elevation: 1
                        onClicked: {
                            disconnect();
                            snackbar.open("Successful logout")
                        }
                    }
                }
            } /* Column */
        } /* View */

        View {
            width: 300
            height: 285
            anchors.leftMargin: units.dp(2)

            elevation: 2

            Column {
                anchors.fill: parent
                anchors.margins: units.dp(8)
                spacing: units.dp(30);

                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: units.dp(8)
                    spacing: units.dp(5);

                    Label {
                        id: nOfViews;
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: ""
                        style: "display2"
                        color: "#c0392b"
                    }

                    Label {
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "vues sur vos fichiers"
                        style: "title"
                    }
                }

                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: units.dp(8)
                    spacing: units.dp(5);

                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "5"
                        style: "display2"
                        color: "#c0392b"
                    }

                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "fichiers envoyé aujourd'hui"
                        style: "title"
                    }
                }

                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: units.dp(8)
                    spacing: units.dp(5);


                    Label {
                        id: nOfFilesSaved;
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: ""
                        style: "display2"
                        color: "#c0392b"
                    }

                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "fichiers envoyés au total"
                        style: "title"
                    }
                }
            }
        }
        }
    }

    /* When user is disconnected */
    U.Offline {
        visible: !Global.connected && !Global.isLoading
    }

    /* On loading */
    U.Loading {
        visible: Global.isLoading
    }

    ActionButton {
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: units.dp(32)
        }

        onClicked: {
            updateDatas();
        }

        iconName: "content/add"
    }

    Snackbar {
        id: snackbar
    }

    U.Login {
        id: login

        onSuccessLogin: {
            snackbar.open('Great, you\'re connected!');
            Global.connected = true
            updateDatas();
        }
    }

    Timer {
        id: refreshTimer
        interval: 1000
        running: false
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            if(!Global.connected || Global.isLoading)
                return;

            updateDatas(true);
        }
    }

    Connections {
        target: Global
        onConnectedChanged: {
            if(!Global.connected)
            {
                refreshTimer.running = false;
            }
        }
    }

    function disconnect()
    {
        Global.connected = false
        UOnline.disconnect();
        Settings.setValue('username', false);
        Settings.setValue('password', false);
    }

    function updateDatas(lite)
    {
        Global.isLoading = lite ? false : true

        var onGetUserInfos = function(result)
        {
            if(!lite)
            {
                if(username.text !== result.username)
                    username.text = result.username;
            }

            if(nOfViews.text !== result.nOfViews)
                nOfViews.text = result.nOfViews;

            if(nOfFilesSaved.text !== result.nOfFilesSaved)
                nOfFilesSaved.text = result.nOfFilesSaved;

            if(result.accountType === "vip")
            {
                if(accountType.text != "VIP :-D")
                    accountType.text = "VIP :-D";
            }
            else if(result.accountType === "premium")
            {
                if(accountType.text != "Premium")
                    accountType.text = "Premium";
            }
            else if(result.accountType === "regular")
            {
                if(accountType.text != "Regular")
                    accountType.text = "Regular"
            }


            if(!lite)
            {
                Network.gravatar(result.email, Crypto.md5, function(url)
                {
                    if(url !== null)
                    {
                        gravatar.source = url;
                    }
                });
            }

            Global.isLoading = false;
        }

        UOnline.getUserInfos(onGetUserInfos);
    }

    function wsConnected()
    {
        Global.connected = true;
        Global.isLoading = true;
        updateDatas(false);
        refreshTimer.start();
        console.log('connected');
    }

    function wsError()
    {
        snackbar.open("Connection lost, error occurred");
        disconnect();
    }

    function onStart()
    {
        if(!Settings.value('username', false) || !Settings.value('password', false))
        {
            return;
        }

        Global.hasLogin = true

        UOnline.onWsConnected(wsConnected);
        UOnline.onWsDisconnected(disconnect);
        UOnline.onWsError(wsError);
        UOnline.connect(Settings.value('username', false), Settings.value('password', false), root, function(err, result){            Settings.setValue("account_key", result.accountKey);
            Settings.setValue("private_key", result.privateKey);});
    }
}
