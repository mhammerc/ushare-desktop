import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

Dialog
{
    id: colorPicker;

    title: qsTr("Pick color");

    positiveButtonText: qsTr("Done");

    property bool isCustom : false;

    Column
    {
        spacing: Units.dp(8);

        MenuField
        {
            model: [qsTr("Light"), qsTr("Dark"), qsTr("Custom")];
            width: Units.dp(160);

            selectedIndex:
            {
                var currentTheme = Settings.value('color/theme', 'light');

                if(currentTheme === 'light')
                {
                    colorPicker.isCustom = false;
                    return 0;
                }
                else if(currentTheme === 'dark')
                {
                    colorPicker.isCustom = false;
                    return 1;
                }
                else
                {
                    colorPicker.isCustom = true;
                    return 2;
                }
            }

            onItemSelected:
            {
                if(index == 0) /* Light selected */
                {
                    colorPicker.isCustom = false;

                    theme.backgroundColor = "#fafafa";
                    Settings.setValue('color/backgroundColor', "#fafafa");

                    theme.primaryColor = "#2196F3";
                    Settings.setValue('color/primaryColor', "#2196F3");

                    theme.accentColor = "#4CAF50";
                    Settings.setValue('color/accentColor', "#4CAF50");

                    Settings.setValue('color/theme', 'light');
                }
                else if(index == 1) /* Dark selected */
                {
                    colorPicker.isCustom = false;

                    theme.backgroundColor = "#37474f";
                    Settings.setValue('color/backgroundColor', "#37474f");

                    theme.primaryColor = "#263238";
                    Settings.setValue('color/primaryColor', "#263238");

                    theme.accentColor = "#607D8B";
                    Settings.setValue('color/accentColor', "#607D8B");

                    Settings.setValue('color/theme', 'dark');
                }
                if(index == 2) /* Custom selected */
                {
                    colorPicker.isCustom = true;
                    Settings.setValue('color/theme', 'custom');
                }
            } /* onItemSelected */
        } /* MenuField */

        View
        {
            anchors
            {
                margins: Units.dp(8);
            }

            width: grid.implicitWidth + Units.dp(16);
            height: grid.implicitHeight + selection.implicitHeight + Units.dp(16);

            visible: colorPicker.isCustom;

            elevation: 1;

            Column
            {
                spacing: Units.dp(8);

                anchors
                {
                    fill: parent;
                    topMargin: Units.dp(8);
                    leftMargin: Units.dp(8);
                    rightMargin: Units.dp(8);
                }

                Grid
                {
                    id: grid

                    columns: 7;
                    spacing: Units.dp(8);

                    anchors.horizontalCenter: parent.horizontalCenter;

                    Repeater
                    {
                        model: [
                            "red", "pink", "purple", "deepPurple", "indigo",
                            "blue", "lightBlue", "cyan", "teal", "green",
                            "lightGreen", "lime", "yellow", "amber", "orange",
                            "deepOrange", "grey", "blueGrey", "brown", "black",
                            "white"
                        ];

                        Rectangle
                        {
                            width: Units.dp(30);
                            height: Units.dp(30);
                            radius: Units.dp(2);
                            color: Palette.colors[modelData]["500"];
                            border.width: modelData === "white" ? Units.dp(2) : 0;
                            border.color: Theme.alpha("#000", 0.26);

                            Ink
                            {
                                anchors.fill: parent;

                                onPressed:
                                {
                                    switch(selection.selectedIndex)
                                    {
                                        case 0:
                                            theme.primaryColor = parent.color;
                                            Settings.setValue('color/primaryColor', parent.color);
                                            break;
                                        case 1:
                                            theme.accentColor = parent.color;
                                            Settings.setValue('color/accentColor', parent.color);
                                            break;
                                        case 2:
                                            theme.backgroundColor = parent.color;
                                            Settings.setValue('color/backgroundColor', parent.color);
                                            break;
                                    } /* Switch */
                                } /* on Pressed */
                            } /* Ink */
                        } /* Rectangle */
                    } /* Repeater */
                } /* Grid color */

                MenuField
                {
                    id: selection;
                    visible: colorPicker.isCustom;

                    model: [qsTr("Primary color"), qsTr("Accent color"), qsTr("Background color")];
                    width: Units.dp(160);
                }
            }
        }
    } /* Column */
} /* Dialog color chooser */

