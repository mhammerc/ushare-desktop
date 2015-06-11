import QtQuick 2.0
import Material 0.1
import Material.Extras 0.1
import U.Global 1.0
import "../components" as U
import "../components/usquare_online.js" as UOnline
import "../components/network.js" as Network
import "../components/md5.js" as Crypto

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
        visible: (Global.connected && !Global.isLoading && root.uploads && root.uploads.files && root.uploads.files.length !== 0);
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
                        model:
                        {
                            if(root.uploads)
                                return root.uploads.files;
                            else
                                return null;
                        }

                        U.FileCard
                        {
                            fileInformations: modelData;
                        } /* U.FileCard */
                    } /* Repeater */
                } /* Grid */
            } /* Item */
        } /* Flickable */
    } /* Item */

    /** If there is no files yet **/
    Item
    {
        visible: (Global.connected && !Global.isLoading && root.uploads && root.uploads.files && root.uploads.files.length === 0);
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
        visible: !Global.connected && !Global.isLoading;
    }

    /* On loading */
    U.Loading
    {
        visible: Global.isLoading || (typeof uploads === 'undefined' && Global.connected === true);
    }

    Connections
    {
        target: login
        onSuccessLogin:
        {
            updateDatas();
        }
    }

    Connections
    {
        target: register
        onSuccessRegister:
        {
            updateDatas();
        }
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
            if(!Global.connected || Global.isLoading)
            {
                return;
            }

            updateDatas();
        }
    }

    function updateDatas()
    {
        var onGetUploads = function(uploads)
        {
            root.uploads = uploads;
        }

        UOnline.getUploads(50, onGetUploads);
    }
}

