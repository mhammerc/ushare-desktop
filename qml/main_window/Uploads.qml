import QtQuick 2.0
import Material 0.1
import Material.Extras 0.1
import "../components" as U

Item
{
    id: root;

    property var uploads;

    onFocusChanged:
    {
        if(!focus)
        {
            refreshTimer.running = false;
            return;
        }

        refreshTimer.running = true;
    }

    /** All files card **/
    Item
    {
        visible: uShareOnline.connected && root.uploads && root.uploads.files && root.uploads.files.length !== 0;
        anchors.fill: parent;

        Flickable
        {
            anchors.fill: parent;

            contentHeight: content.height;
            contentWidth: width;

            Item
            {
                id: content;

                width: parent.width;
                height: grid.implicitHeight + grid.anchors.margins * 2;

                Grid
                {
                    id: grid;

                    anchors
                    {
                        fill: parent;
                        margins: Units.dp(20);
                    }

                    columns: Math.floor(width/Units.dp(365));
                    spacing: Units.dp(8);

                    Repeater
                    {
                        id: repeater;

                        U.FileCard
                        {
                            fileInformations: uploads.files[modelData];
                        } /* U.FileCard */
                    } /* Repeater */
                } /* Grid */
            } /* Item */
        } /* Flickable */
    } /* Item */

    /** If there is no files yet **/
    Item
    {
        visible: uShareOnline.connected && root.uploads && root.uploads.files && root.uploads.files.length === 0;
        anchors.fill: parent;

        U.Label
        {
            anchors.centerIn: parent;
            horizontalAlignment: Text.AlignHCenter;
            style: 'display1';
            text: 'There are no files yet\n:(';
        }
    }

    /* On offline */
    U.Offline
    {
        visible: !uShareOnline.connected;
    }

    /* On loading */
    U.Loading
    {
        visible: typeof uploads === 'undefined' && uShareOnline.connected;
    }

    Timer
    {
        id: refreshTimer

        interval: 1000
        running: false
        repeat: true
        triggeredOnStart: false

        onTriggered:
        {
            if(!baseItem.visible)
            {
                return;
            }

            if(!uShareOnline.connected || uShareOnline.loading)
            {
                return;
            }

            updateDatas();
        }
    }

    Connections
    {
        target: uShareOnline;

        onGotUploadList:
        {
            if(!response.success)
            {
                snackbar.open('Connection to uShare Online lost :\'(' + response.message ? ' -> ' + response.message : '');
                return;
            }

            root.uploads = response;

            if(repeater.model !== response.files.length)
            {
                repeater.model = response.files.length;
            }
        }
    }

    function updateDatas()
    {
        uShareOnline.getUploadList(50);
    }
}

