import QtQuick 2.0
import Material 0.1
import Material.Extras 0.1
import U.Global 1.0
import "../components" as U
import "../components/usquare_online.js" as UOnline
import "../components/network.js" as Network
import "../components/md5.js" as Crypto

Item {
    id: root

    property var uploads : null

    onFocusChanged: {
        if(!focus)
        {
            refreshTimer.running = false;
            return;
        }

        refreshTimer.running = true;
    }

    Item {
        anchors.fill: parent
        visible: Global.connected && !Global.isLoading && root.uploads !== null

        Flickable {
            id: flickable

            anchors.fill: parent
            contentHeight: content.height
            contentWidth: width

            Item {
                id: content
                width: flickable.width
                height: grid.implicitHeight + grid.anchors.margins * 2

                Grid {
                    id: grid

                    anchors {
                        fill: parent
                        margins: units.dp(20)
                    }

                    columns: Math.floor(width/units.dp(365))
                    spacing: units.dp(8)

                    Repeater {
                        model: {
                            if(!!root.uploads)
                                return root.uploads.files
                            else
                                return null;
                        }

                        U.FileCard {
                            shortName: modelData.shortName
                            source: {
                                if(modelData.extension === 'jpg' || modelData.extension === 'png')
                                    return modelData.shortName;
                                return;
                            }

                            nOfViews: modelData.views
                            size: modelData.size
                            password: {
                                if(modelData.password === null)
                                    return false;
                                return modelData.password
                            }

                            onLinkCopied: snackbar.open('Link copied!');
                        }
                    }
                }
            }
        }
    }

    /* On offline */
    U.Offline {
        visible: !Global.connected && !Global.isLoading
    }

    /* On loading */
    U.Loading {
        visible: Global.isLoading
    }

    Connections {
        target: login
        onSuccessLogin: {
            updateDatas();
        }
    }

    Connections {
        target: register
        onSuccessRegister: {
            updateDatas();
        }
    }

    Timer {
        id: refreshTimer
        interval: 1000
        running: false
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            if(!Global.connected || Global.isLoading)
                return;

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

