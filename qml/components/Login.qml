import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1
import U.Global 1.0
import "." as U
import "./usquare_online.js" as UOnline

U.Dialog
{
    id: dialog;

    title: qsTr("Login");

    height: Units.dp(350);

    signal successLogin();

    /* Login form */
    Column
    {
        id: login;
        spacing: Units.dp(10);

        Label
        {
            style: 'subheading';
            text: qsTr('You are not connected. Try to login to continue.');
        }

        View
        {
            elevation: 2;
            width: Units.dp(300);
            height: Units.dp(250);

            Column
            {
                id: fieldColumn;

                anchors
                {
                    fill: parent;
                    topMargin: Units.dp(16);
                    bottomMargin: Units.dp(16);
                }

                Label
                {
                    text: qsTr("Please enter your credentials");

                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(16);
                    }

                    style: "title";
                }

                Item
                {
                    Layout.fillWidth: false;
                    Layout.preferredHeight: Units.dp(0);
                }

                ListItem.Standard
                {
                    action: Icon
                    {
                        anchors.centerIn: parent;
                        name: "action/account_circle";
                    }

                    content: TextField
                    {
                        id: usernameField;
                        placeholderText: qsTr("Username");

                        anchors.centerIn: parent;
                        width: parent.width;

                        floatingLabel: true;
                    }
                }

                ListItem.Standard
                {
                    action: Icon
                    {
                        anchors.centerIn: parent;
                        name: "action/https";
                    }

                    content: TextField
                    {
                        id: passwordField;
                        placeholderText: qsTr("Password");

                        anchors.centerIn: parent;
                        width: parent.width;

                        echoMode: TextInput.Password;
                        floatingLabel: true;
                    }
                }

                ListItem.Standard
                {
                    content: Checkbox
                    {
                        id: rememberCheckbox;
                        text: qsTr('Remember');
                        checked: true;
                    }
                }

                Label
                {
                    id: statusLabel;

                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(5);
                    }

                    property bool error: false;

                    color:
                    {
                        if(error)
                        {
                            return '#c0392b';
                        }
                        else
                        {
                            return '#27ae60';
                        }
                    }

                    visible: false;
                }
            }
        }
    }

    onAccepted:
    {
        tryToConnect();
    }

    onRejected:
    {
        resetFields();
        close();
    }

    function resetFields()
    {
        usernameField.text = '';
        passwordField.text = '';
        statusLabel.visible = false;
    }

    function tryToConnect()
    {
        var username = usernameField.text;
        var password = Desktop.sha256(passwordField.text)

        var callback = function(err, result)
        {
            if(err !== null || !result.success)
            {
                statusLabel.text = result && result.message ? result.message : 'Wrong credentials';
                statusLabel.error = true;
                statusLabel.visible = true;
                return;
            }

            if(rememberCheckbox.checked)
            {
                Settings.setValue('username', username);
                Settings.setValue('password', password);
            }

            Settings.setValue("account_key", result.accountkey);
            Settings.setValue("private_key", result.privatekey);

            Global.hasLogin = true;
            Global.isLoading = true;
            Global.connected = true;

            successLogin();
            resetFields();
            close();
        }

        statusLabel.text = qsTr('Connecting...');
        statusLabel.error = false;
        statusLabel.visible = true;
        UOnline.connect(username, password, callback);
    }
}
