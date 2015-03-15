import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

Dialog {
    id: colorPicker
    title: "Pick color"

    positiveButtonText: "Done"

    property bool isCustom : false

    Column {
        spacing: units.dp(8)

        MenuField {
            id: selectionMainTheme
            model: ["Light", "Dark", "Custom"]
            width: units.dp(160)
            selectedIndex: {
                var currentTheme = Settings.value('color/theme', 'light')

                if(currentTheme === 'light'){
                    colorPicker.isCustom = false
                    return 0
                }
                else if(currentTheme === 'dark') {
                    colorPicker.isCustom = false
                    return 1
                }
                else {
                    colorPicker.isCustom = true
                    return 2
                }
            }

            onItemSelected: {
                if(index == 0) /* Light selected */
                {
                    colorPicker.isCustom = false

                    theme.backgroundColor = "#fafafa"
                    Settings.setValue('color/backgroundColor', "#fafafa")

                    theme.primaryColor = "#2196F3"
                    Settings.setValue('color/primaryColor', "#2196F3")

                    theme.accentColor = "#4CAF50"
                    Settings.setValue('color/accentColor', "#4CAF50")

                    Settings.setValue('color/theme', 'light')
                }
                else if(index == 1) /* Dark selected */
                {
                    colorPicker.isCustom = false

                    theme.backgroundColor = "#37474f"
                    Settings.setValue('color/backgroundColor', "#37474f")

                    theme.primaryColor = "#263238"
                    Settings.setValue('color/primaryColor', "#263238")

                    theme.accentColor = "#607D8B"
                    Settings.setValue('color/accentColor', "#607D8B")

                    Settings.setValue('color/theme', 'dark')

                }
                if(index == 2) /* Custom selected */
                {
                    colorPicker.isCustom = true
                    Settings.setValue('color/theme', 'custom')
                }
            } /* onItemSelected */
        } /* MenuField */

        Grid {
            visible: colorPicker.isCustom
            columns: 7
            spacing: units.dp(8)

            Repeater {
                model: [
                    "red", "pink", "purple", "deepPurple", "indigo",
                    "blue", "lightBlue", "cyan", "teal", "green",
                    "lightGreen", "lime", "yellow", "amber", "orange",
                    "deepOrange", "grey", "blueGrey", "brown", "black",
                    "white"
                ]

                Rectangle {
                    width: units.dp(30)
                    height: units.dp(30)
                    radius: units.dp(2)
                    color: Palette.colors[modelData]["500"]
                    border.width: modelData === "white" ? units.dp(2) : 0
                    border.color: Theme.alpha("#000", 0.26)

                    Ink {
                        anchors.fill: parent

                        onPressed: {
                            switch(selection.selectedIndex) {
                                case 0:
                                    theme.primaryColor = parent.color
                                    Settings.setValue('color/primaryColor', parent.color)
                                    break;
                                case 1:
                                    theme.accentColor = parent.color
                                    Settings.setValue('color/accentColor', parent.color)
                                    break;
                                case 2:
                                    theme.backgroundColor = parent.color
                                    Settings.setValue('color/backgroundColor', parent.color)
                                    break;
                            } /* Switch */
                        } /* on Pressed */
                    } /* Ink */
                } /* Rectangle */
            } /* Repeater */
        } /* Grid color */

        MenuField {
            visible: colorPicker.isCustom
            id: selection
            model: ["Primary color", "Accent color", "Background color"]
            width: units.dp(160)
        }
    } /* Column */
} /* Dialog color chooser */

