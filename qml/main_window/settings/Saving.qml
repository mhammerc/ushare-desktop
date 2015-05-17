import QtQuick 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import "../../components" as U
import "../../components/functions.js" as F

Item {
    View {
        anchors.fill: parent
        anchors.margins: Units.dp(16)

        elevation: 1
        radius: Units.dp(2)

        Column {
            id: column
            anchors.fill: parent
            anchors.topMargin: Units.dp(10)
            spacing: Units.dp(5);

            U.Label {
                id: titleLabel

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(16)
                }

                style: "title"
                text: "Online services"
                color: Theme.light.textColor
            }

            U.Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(8)
                }

                text: 'Later...'
                color: Theme.light.textColor
                style: 'subheading'
            }

            U.Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(16)
                }

                style: "title"
                text: "Picture settings"
                color: Theme.light.textColor
            }

            ListItem.SimpleMenu {
                text: "Image format"
                model: ["JPEG", "PNG"]
                selectedIndex: Settings.value("picture/format", 0)
                onSelectedIndexChanged: {
                    if(selectedIndex === 0)
                        imageQuality.enabled = true
                    else
                        imageQuality.enabled = false

                    Settings.setValue("picture/format", selectedIndex)
                }
            }

            Row {
                id: imageQuality
                spacing: Units.dp(16)

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(16)
                }

                U.Label{
                    color: Theme.light.textColor
                    text: 'Image quality'
                    style: 'subheading'
                }

                U.Slider {
                    numericValueLabel: true
                    minimumValue: 0
                    maximumValue: 100
                    darkBackground: false

                    height: 15
                    width: 250

                    value: Settings.value("picture/quality", 100)
                    onValueChanged: {
                        value = F.round(value)
                    }
                    onPressedChanged: {
                        Settings.setValue("picture/quality", value);
                    }
                }
            } /* Row */

            U.Checkbox {
                id: saveOnCheckbox
                checked: F.stringToBoolean(Settings.value("picture/save_on_computer", false))
                text: "Save pictures on computer"
                darkBackground: false

                onCheckedChanged: {
                    Settings.setValue("picture/save_on_computer", checked)
                }
            }

            Row {
                spacing: Units.dp(16)

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(18)
                }

                TextField {
                    id: pathField
                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: 0.4 * parent.width
                    enabled: saveOnCheckbox.checked
                    text: Settings.value("picture/save_path", "unknown")

                    Component.onCompleted: {
                        input.readOnly = true
                    }

                    onTextChanged: {
                        Settings.setValue("picture/save_path", text)
                    }

                } /* TextField */

                Button {
                    text: ".."
                    elevation: 1
                    enabled: saveOnCheckbox.checked
                    onClicked: fileDialog.open()
                } /* Button */
            } /* Row */
        } /* Column */
    } /* View */

    FileDialog {
        id: fileDialog
        title: "Please choose a folder"
        selectFolder: true
        onAccepted: {
            var text;
            if(PlatformDetails.isLinux)
                text = folder.toString().replace("file://", "")
            else if(PlatformDetails.isWindows)
                text = folder.toString().replace("file:///", "");
            else /* Mac ?? */
                text = "Mac not implemented yet"

            pathField.text = text

        }
    } /* FileDialog */

} /* Item */

