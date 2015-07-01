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

import QtQuick 2.2
import QtQuick.Layouts 1.1
import "qrc:/qml-material/modules/Material" 0.1
import "qrc:/qml-material/modules/Material/ListItems" 0.1 as ListItem
import "qrc:/qml-extras/modules/Material/Extras" 0.1
import "." as U

U.Dialog
{
    id: dialog;

    title: qsTr("Login");

    height: Units.dp(350);

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
                    content: CheckBox
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

    Connections
    {
        target: uShareOnline;

        onConnected:
        {
            if(!dialog.focus) return;

            if(response && typeof response.success === 'undefined')
            {
                statusLabel.text = qsTr('Can\'t connect to the servers of uShare Online');
                statusLabel.error = true;
                statusLabel.visible = true;
                return;
            }

            if(response && !response.success)
            {
                statusLabel.text = response.message ? response.message : qsTr('Wrong credentials');
                statusLabel.error = true;
                statusLabel.visible = true;
                return;
            }

            if(rememberCheckbox.checked)
            {
                Settings.setValue('username', usernameField.text);
                Settings.setValue('password', passwordField.text);
            }

            resetFields();
            close();
        }
    }

    function resetFields()
    {
        usernameField.text = '';
        passwordField.text = '';
        statusLabel.visible = false;
    }

    function tryToConnect()
    {
        uShareOnline.connect(usernameField.text, passwordField.text);

        statusLabel.text = qsTr('Connecting...');
        statusLabel.error = false;
        statusLabel.visible = true;
    }
}
