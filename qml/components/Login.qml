import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1
import "." as U
import "./usquare_online.js" as UOnline

U.Dialog {
    id: dialog
    title: "Login"
    height: units.dp(350)

    signal successLogin()

    /* Login form */
    Column {
        id: login
        spacing: units.dp(10)

        Label {
            style: 'subheading'
            text: 'You are not connected. Try to login to continue.';
        }

        View {
            elevation: 2
            width: units.dp(300)
            height: units.dp(250)

         Column {
                id: fieldColumn

                anchors {
                    fill: parent
                    topMargin: units.dp(16)
                    bottomMargin: units.dp(16)
                }

                Label {
                    anchors {
                        left: parent.left
                        right: parent.right
                        margins: units.dp(16)
                    }

                    style: "title"
                    text: "Please enter your credentials"
                }

                Item {
                    Layout.fillWidth: false
                    Layout.preferredHeight: units.dp(0)
                }

                ListItem.Standard {
                    action: Icon {
                        anchors.centerIn: parent
                        name: "action/account_child"
                    }

                    content: TextField {
                        id: usernameField
                        placeholderText: "Username"

                        width: parent.width
                        anchors.centerIn: parent
                    }
                }

                ListItem.Standard {
                    action: Icon {
                        anchors.centerIn: parent
                        name: "action/https"
                    }

                    content: TextField {
                        id: passwordField
                     placeholderText: "Password"

                     input.echoMode: TextInput.Password

                     width: parent.width
                     anchors.centerIn: parent
                    }
                }

                ListItem.Standard {
                    content: Checkbox {
                        id: rememberCheckbox
                        text: 'Remember'
                        checked: true
                    }
                }

                Label {
                    anchors {
                        left: parent.left
                        right: parent.right
                        margins: units.dp(5)
                    }

                    id: errorLabel
                    color: '#c0392b'
                    visible: false
                }
            }
        }
    }

    onAccepted: {
        tryToConnect();
    }

    onRejected: {
        resetFields();
        close();
    }

    function resetFields()
    {
        usernameField.text = '';
        passwordField.text = '';
        errorLabel.visible = false;
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
                    errorLabel.text = 'Bad username or password';
                else
                    errorLabel.text = 'Can\'t connect to U² Online';
                errorLabel.visible = true
                return;
            }

            if(!result.success)
            {
                errorLabel.text = 'Bad credentials';
                errorLabel.visible = true;
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

        UOnline.connect(username, password, dialog, callback);
    }
}
