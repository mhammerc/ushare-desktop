import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1
import "." as U
import "./usquare_online.js" as UOnline

U.Dialog
{
    id: dialog;

    title: "Login";

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
            text: 'You are not connected. Try to login to continue.';
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
                    text: "Please enter your credentials";

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
                        name: "action/account_child";
                    }

                    content: TextField
                    {
                        id: usernameField;
                        placeholderText: "Username";

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
                        placeholderText: "Password";

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
                        text: 'Remember';
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
        var password = passwordField.text;

        var callback = function(err, result)
        {
            if(err !== null)
            {
                if(err === 401)
                {
                    statusLabel.text = 'Bad username or password';
                }
                else
                {
                    statusLabel.text = 'Can\'t connect to U² Online';
                }

                statusLabel.error = true;
                statusLabel.visible = true
                return;
            }

            if(!result.success)
            {
                statusLabel.error = true;
                statusLabel.text = 'Bad credentials';
                statusLabel.visible = true;
            }
            else
            {
                if(rememberCheckbox.checked)
                {
                    Settings.setValue('username', username);
                    Settings.setValue('password', password);
                }

                successLogin();
                resetFields();
                close();
            }
        }

        statusLabel.text = 'Connecting...'
        statusLabel.error = false;
        statusLabel.visible = true;
        UOnline.connect(username, password, dialog, callback);
    }
}
