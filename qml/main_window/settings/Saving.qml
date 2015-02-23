import QtQuick 2.0
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import "../../components" as U

Item {
    View {
        anchors.fill: parent
        anchors.margins: units.dp(16)

        elevation: 1
        radius: units.dp(2)

    Column {
        id: column
            anchors.fill: parent
            anchors.topMargin: units.dp(10)
            spacing: units.dp(16);

            U.Label {
                id: titleLabel

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: units.dp(16)
                }

                style: "title"
                text: "Online services"
                color: Theme.light.textColor
            }

            U.Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: units.dp(8)
                }

                text: 'Later...'
                color: Theme.light.textColor
                style: 'subheading'
            }

            U.Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: units.dp(16)
                }

                style: "title"
                text: "Picture settings"
                color: Theme.light.textColor
            }

            ListItem.SimpleMenu {
                text: "Image format"
                model: ["JPEG", "PNG"]
            }

            Row {
                spacing: 10

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: units.dp(8)
                }

                U.Label{
                    color: Theme.light.textColor
                    text: 'Image quality'
                    style: 'subheading'
                }

                U.Slider {
                    value: 100
                    tickmarksEnabled: true
                    numericValueLabel: true
                    stepSize: 10
                    minimumValue: 0
                    maximumValue: 100
                    darkBackground: false
                    Layout.alignment: Qt.AlignTop
                    height: 15
                    width: 250
                }
            }

            Row {
                spacing: 10

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: units.dp(8)
                }

                U.Label{
                    color: Theme.light.textColor
                    text: 'Save picture on computer'
                    style : 'subheading'
                }

                U.Checkbox {
                    id: saveOnCheckbox
                    checked: false
                    height: 15
                }

                Button {
                    text: ".."
                    elevation: 1
                    height: 15
                    checkable: true
                    enabled: saveOnCheckbox.checked
                }
            }
        } /* Column */
    } /* View */
} /* Item */

