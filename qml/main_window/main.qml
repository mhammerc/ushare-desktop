import QtQuick 2.2
import U.Global 1.0
import "."
import Material 0.1
import Material.ListItems 0.1 as ListItem
import "../components" as U


ApplicationWindow {
    id: megaRoot

    width: 670
    height: 600

    theme {
        primaryColor: Settings.value('color/primaryColor', '#2196F3')
        accentColor: Settings.value('color/accentColor','#4CAF50')
        backgroundColor: Settings.value('color/backgroundColor', '#fafafa')
    }

    initialPage: page

    Page {
        id: page
        title: "U²"

        tabs: [
            {
                text: "Overview",
                icon: "action/home"
            },
            "Uploads",
            "Settings"
        ]

        actions: [
            Action {
                iconName: "image/color_lens"
                name: "Colors"
                onTriggered: colorPicker.show()
            }
        ]

        TabView {
            id: tabView
            anchors.fill: parent
            currentIndex: page.selectedTab
            model: tabs
        }

        VisualItemModel {
            id: tabs

            // Tab 1 "Overview"
            Overview {
                width: tabView.width
                height: tabView.height
            }

            // Tab 2 "Uploads"
            Uploads {
                width: tabView.width
                height: tabView.height
            }

            // Tab 3 "Settings"
            SettingsPage {
                width: tabView.width
                height: tabView.height
            }
        } /* VisualItemModel */
    } /* Page */

    U.ColorPicker {
        id: colorPicker
    }

    U.Login {
        id: login

        onSuccessLogin: {
            snackbar.open('Great, you\'re connected!');
            Global.connected = true
        }
    }

    U.Register{
        id: register

        onSuccessRegister: {
            snackbar.open('Great, you\'re connected!');
            Global.connected = true
        }
    }

    Snackbar {
        id: snackbar
    }
} /* ApplicationWindow */
