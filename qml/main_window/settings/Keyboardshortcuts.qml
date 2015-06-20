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

import QtQuick 2.4
import Material 0.1
import uShare 0.1

Item
{
    id: shortcutPage;

    View
    {
        anchors
        {
            fill: parent;
            margins: Units.dp(16);
        }

        elevation: 1;

        Column
        {
            spacing: Units.dp(16);

            anchors
            {
                fill: parent;
                margins: Units.dp(8);
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
                text: qsTr('Keyboard shortcuts')
            }

            Label
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                    margins: Units.dp(8);
                }

                style: 'subheading';
                text: qsTr('Easily edit your shortcuts for quick access to mains functions');
            }

            Grid
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                    margins: Units.dp(8);
                }

                columns: 2;
                spacing: Units.dp(16);
                verticalItemAlignment: Grid.AlignVCenter;

                Label
                {
                    text: qsTr('Capture fullscreen')
                    style: 'subheading';
                }

                TextField
                {
                    id: fullScreen;
                    helperText: qsTr('Base: ALT+1');
                    readOnly: true;

                    onTextChanged:
                    {
                        if(!activeFocus) return;

                        Settings.setValue('fullscreen_shortcut', text);
                        Shortcuts.setFullScreen(text);
                    }

                    onActiveFocusChanged:
                    {
                        if(activeFocus)
                        {
                            Shortcuts.disableShortcuts();
                        }
                        else
                        {
                            Shortcuts.enableShortcuts();
                        }
                    }
                }

                Label
                {
                    text: qsTr('Capture selected area')
                    style: 'subheading';
                }

                TextField
                {
                    id: areaScreen;
                    helperText: qsTr('Base: ALT+2');
                    readOnly: true;

                    onTextChanged:
                    {
                        if(!activeFocus) return;

                        Settings.setValue('selectedareascreen_shortcut', text);
                        Shortcuts.setAreaScreen(text);
                    }

                    onActiveFocusChanged:
                    {
                        if(activeFocus)
                        {
                            Shortcuts.disableShortcuts();
                        }
                        else
                        {
                            Shortcuts.enableShortcuts();
                        }
                    }
                }

                Label
                {
                    text: qsTr('Cook new paste')
                    style: 'subheading';
                }

                TextField
                {
                    id: newPaste;
                    helperText: qsTr('Base: ALT+3');
                    readOnly: true;

                    onTextChanged:
                    {
                        if(!activeFocus) return;

                        Settings.setValue('newpaste_shortcut', text);
                        Shortcuts.setNewPaste(text);
                    }

                    onActiveFocusChanged:
                    {
                        if(activeFocus)
                        {
                            Shortcuts.disableShortcuts();
                        }
                        else
                        {
                            Shortcuts.enableShortcuts();
                        }
                    }
                }

                Label
                {
                    text: qsTr('Send new file')
                    style: 'subheading';
                }

                TextField
                {
                    id: sendFile;
                    helperText: qsTr('Base: ALT+4');
                    readOnly: true;

                    onTextChanged:
                    {
                        if(!activeFocus) return;

                        Settings.setValue('sendfile_shortcut', text);
                        Shortcuts.setSendFile(text);
                    }

                    onActiveFocusChanged:
                    {
                        if(activeFocus)
                        {
                            Shortcuts.disableShortcuts();
                        }
                        else
                        {
                            Shortcuts.enableShortcuts();
                        }
                    }
                }

                Label
                {
                    text: qsTr('Send clipboard')
                    style: 'subheading';
                }

                TextField
                {
                    id: sendClipboard;
                    helperText: qsTr('Base: ALT+5');
                    readOnly: true;

                    onTextChanged:
                    {
                        if(!activeFocus) return;

                        Settings.setValue('sendclipboard_shortcut', text);
                        Shortcuts.setSendClipboard(text);
                    }

                    onActiveFocusChanged:
                    {
                        if(activeFocus)
                        {
                            Shortcuts.disableShortcuts();
                        }
                        else
                        {
                            Shortcuts.enableShortcuts();
                        }
                    }
                }
            }

            Label
            {
                text: qsTr('Global shortcuts are disabled while editing.');
                color: 'red';
            }
        }
    }

    Component.onCompleted:
    {
        fullScreen.text = Settings.value('fullscreen_shortcut', false);
        areaScreen.text = Settings.value('selectedareascreen_shortcut', false);
        newPaste.text = Settings.value('newpaste_shortcut', false);
        sendFile.text = Settings.value('sendfile_shortcut', false);
        sendClipboard.text = Settings.value('sendclipboard_shortcut', false);
    }

    ShortcutGetter
    {
        onKeyChanged:
        {
            if(fullScreen.activeFocus)
            {
                fullScreen.text = key;
            }
            else if(areaScreen.activeFocus)
            {
                areaScreen.text = key;
            }
            else if(newPaste.activeFocus)
            {
                newPaste.text = key;
            }
            else if(sendFile.activeFocus)
            {
                sendFile.text = key;
            }
            else if(sendClipboard.activeFocus)
            {
                sendClipboard.text = key;
            }
        }
    }
}

