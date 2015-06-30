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
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1
import '.' as U

U.Dialog
{
    id: dialog;
    title: qsTr('Register');
    height: Units.dp(450);

    property bool hasError: false;

    signal successRegister(string username, string password);

    /* Register form */
    Column
    {
        id: register;
        spacing: Units.dp(10);

        Label
        {
            style: 'subheading';
            text: qsTr('Fill fields below to get registered');
        }

        View
        {
            elevation: 2;
            width: Units.dp(400);
            height: Units.dp(350);

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
                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(16);
                    }

                    style: 'title';
                    text: qsTr('Please fill fields');
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
                        name: 'action/account_circle';
                    }

                    content: TextField
                    {
                        id: usernameField;
                        placeholderText: qsTr('Username');

                        width: parent.width;
                        anchors.centerIn: parent;

                        floatingLabel: true;

                    }
                }

                ListItem.Standard
                {
                    action: Icon
                    {
                        anchors.centerIn: parent;
                        name: 'action/https';
                    }

                    content: RowLayout
                    {
                        anchors.centerIn: parent;
                        width: parent.width;

                        TextField
                        {
                            id: passwordField;
                            placeholderText: qsTr('Password');

                            Layout.alignment: Qt.AlignVCenter
                            Layout.preferredWidth: 0.45 * parent.width

                            echoMode: TextInput.Password
                            floatingLabel: true;
                        }

                        TextField
                        {
                            id: passwordField2;
                            placeholderText: qsTr('Repeat password');

                            Layout.alignment: Qt.AlignVCenter;
                            Layout.preferredWidth: 0.45 * parent.width;

                            echoMode: TextInput.Password;
                            floatingLabel: true;

                            hasError:
                            {
                                 if(passwordField.text !== passwordField2.text)
                                 {
                                     dialog.hasError = true;
                                     return true;
                                 }
                                 else
                                 {
                                     dialog.hasError = false;
                                     return false;
                                 }
                            }
                        }
                    }
                }

                ListItem.Standard
                {
                    action: Icon
                    {
                        anchors.centerIn: parent;
                        name: 'communication/email';
                    }

                    content: TextField
                    {
                        id: emailField;
                        placeholderText: qsTr('Email');

                        anchors.centerIn: parent;
                        width: parent.width;

                        floatingLabel: true;

                        hasError:
                        {
                            if(text)
                            {
                                dialog.hasError = true;
                                return !Desktop.isValidEmail(text);
                            }

                            dialog.hasError = false;
                            return false;
                        }
                    }
                }

                ListItem.Standard
                {
                    content: CheckBox
                    {
                        id: rememberCheckbox;
                        text: qsTr('Remember for further login attempt');
                        checked: true;
                    }
                }

                ListItem.Standard
                {
                    content: CheckBox
                    {
                        id: acceptConditionsCheckbox;
                        text: qsTr('I accept CGU');
                        checked: false;
                    }
                }

                Label
                {
                    anchors
                    {
                        left: parent.left;
                        right: parent.right;
                        margins: Units.dp(5);
                    }

                    text: qsTr('Open CGU');
                    color: '#4aa3df';

                    MouseArea
                    {
                        anchors.fill: parent;
                        onClicked: Desktop.openUrl('http://ushare.so/itdw');
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
        if(!usernameField.text || !passwordField.text
                || !passwordField2.text || !emailField.text)
        {
            statusLabel.error = true;
            statusLabel.text = qsTr('You must fill all fields.');
            statusLabel.visible = true;
            return;
        }
        else if(!acceptConditionsCheckbox.checked)
        {
            statusLabel.error = true;
            statusLabel.text = qsTr('You must agree the conditions.');
            statusLabel.visible = true;
            return;
        }
        else if(!Desktop.isValidEmail(emailField.text))
        {
            statusLabel.error = true;
            statusLabel.text = qsTr('Your email must be valid.');
            statusLabel.visible = true;
            return;
        }
        else if(passwordField.text !== passwordField2.text)
        {
            statusLabel.error = true;
            statusLabel.text = qsTr('Your passwords must match.');
            statusLabel.visible = true;
            return;
        }

        statusLabel.visible = false;
        tryToRegister();
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
        passwordField2.text = '';
        emailField.text = '';
        acceptConditionsCheckbox.checked = false;
        statusLabel.visible = false;
    }

    Connections
    {
        target: uShareOnline;

        onRegistered:
        {
            if(!response.success && !response.message)
            {
                statusLabel.text = qsTr('Can\'t reach uShare Online servers at the moment.');
                statusLabel.error = true;
                statusLabel.visible = true;

                return;
            }

            if(!response.success)
            {
                statusLabel.text = response.message;
                statusLabel.error = true;
                statusLabel.visible = true;

                return;
            }

            if(rememberCheckbox.checked)
            {
                Settings.setValue('username', usernameField.text);
                Settings.setValue('password', passwordField.text);
            }


            successRegister(usernameField.text, passwordField.text);
            resetFields();
            close();
        }
    }

    function tryToRegister()
    {
        uShareOnline.register_(usernameField.text, passwordField.text, emailField.text);

        statusLabel.error = false;
        statusLabel.text = qsTr('Loading...');
        statusLabel.visible = true;
    }
}
