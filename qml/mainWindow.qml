import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem


ApplicationWindow {
    id: usquare

    theme {
        accentColor: "#009688"
    }

    initialPage: page

    Page {
        id: page
        title: "U²"

        tabs: [
            // Each tab can have text and an icon
            {
                text: "Overview",
                icon: "action/home"
            },
            "My account",
            "Settings"
        ]

        // TabView is simply a customized ListView
        // You can use any model/delegate for the tab contents,
        // but a VisualItemModel works well
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

            // Tab 2 "My account"
            MyAccount {
                width: tabView.width
                height: tabView.height
            }

            // Tab 3 "Settings"
            SettingsPage {
                width: tabView.width
                height: tabView.height
            }
        }
    }

}
