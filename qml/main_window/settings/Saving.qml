import QtQuick 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import '../../components' as U
import '../../components/functions.js' as F

Item
{
    View
    {
        anchors
        {
            fill: parent;
            margins: Units.dp(16);
        }

        elevation: 1;
        radius: Units.dp(2);

        Column
        {
            anchors
            {
                fill: parent;
                topMargin: Units.dp(10);
            }

            spacing: Units.dp(5);

            Label
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                    margins: Units.dp(16);
                }

                style: 'title';
                text: qsTr('Picture settings');
            }

            ListItem.SimpleMenu
            {
                text: qsTr('Image format');
                model: ['JPEG', 'PNG'];
                selectedIndex: Settings.value('picture/format', 0);

                onSelectedIndexChanged:
                {
                    if(selectedIndex === 0)
                    {
                        imageQuality.enabled = true;
                    }
                    else
                    {
                        imageQuality.enabled = false;
                    }

                    Settings.setValue("picture/format", selectedIndex);
                }
            }

            Row
            {
                id: imageQuality;
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                    margins: Units.dp(16);
                }

                spacing: Units.dp(16);

                Label
                {
                    text: qsTr('Image quality');
                    style: 'subheading';
                }

                Slider
                {
                    numericValueLabel: true;
                    minimumValue: 0;
                    maximumValue: 100;

                    height: 15;
                    width: 250;

                    value: Settings.value('picture/quality', 100);

                    onValueChanged:
                    {
                        value = F.round(value);
                    }

                    onPressedChanged:
                    {
                        Settings.setValue('picture/quality', value);;
                    }
                }
            } /* Row */

            CheckBox
            {
                id: saveOnCheckbox;
                checked: F.stringToBoolean(Settings.value('picture/save_on_computer', false));
                text: qsTr('Save pictures on computer');

                onCheckedChanged:
                {
                    Settings.setValue('picture/save_on_computer', checked);
                }
            }

            Row
            {
                anchors
                {
                    left: parent.left;
                    right: parent.right;
                    margins: Units.dp(18);
                }

                spacing: Units.dp(16);

                TextField
                {
                    id: pathField;
                    Layout.alignment: Qt.AlignVCenter;
                    Layout.preferredWidth: 0.4 * parent.width;
                    enabled: saveOnCheckbox.checked;
                    text: Settings.value('picture/save_path', 'unknown');

                    Component.onCompleted:
                    {
                        readOnly = true;
                    }

                    onTextChanged:
                    {
                        Settings.setValue('picture/save_path', text);
                    }
                } /* TextField */

                Button
                {
                    text: '..';
                    elevation: 1;
                    backgroundColor: Theme.accentColor;
                    enabled: saveOnCheckbox.checked;
                    onClicked: fileDialog.open();
                } /* Button */
            } /* Row */
        } /* Column */
    } /* View */

    FileDialog
    {
        id: fileDialog;
        title: qsTr('Please choose a folder');
        selectFolder: true;
        onAccepted:
        {
            var text;

            if(PlatformDetails.isLinux)
            {
                text = folder.toString().replace('file://', '');
            }
            else if(PlatformDetails.isWindows)
            {
                text = folder.toString().replace('file:///', '');
            }
            else /* Mac ?? */
            {
                text = "Mac not implemented yet"
            }

            pathField.text = text;
        }
    } /* FileDialog */
} /* Item */

