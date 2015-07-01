/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

import QtQuick 2.2
import "qrc:/qml-material/modules/Material" 0.1

Window
{
    id: root;
    width: 380;
    height: 30;
    //flags: Qt.WindowStaysOnTopHint | Qt.WindowCloseButtonHint

    maximumWidth: width;
    minimumWidth: width;

    maximumHeight: height;
    minimumHeight: height;

    x: Desktop.size.width - width - 10;
    y: Desktop.size.height - height - 15;

    property real progress: 0;

    property int bytesTotal: 0;

    signal cancellationAsked;

    Item
    {
        anchors
        {
            fill: parent;
            leftMargin: 5;
        }

        Row
        {
            spacing: 7;
            anchors.verticalCenter: parent.verticalCenter;

            Label
            {
                text: qsTr('uSharing... (%1/%2)').arg(humanFileSize(bytesTotal * progress, true)).arg(humanFileSize(bytesTotal, true));
                verticalAlignment: Text.AlignVCenter;
            }

            ProgressBar
            {
                width: 165;
                height: 5;
                anchors.verticalCenter: parent.verticalCenter;

                value: root.progress;
                color: theme.accentColor;

                Behavior on value { NumberAnimation { duration: 450 } }
            }

            Label
            {
                text: Math.round(root.progress*100) + "%";
                verticalAlignment: Text.AlignVCenter;
            }

            Icon
            {
                width: 5;
                height: 5;
                anchors.verticalCenter: parent.verticalCenter;

                name: "awesome/remove";
                color: "#c0392b";
                size: 1;

                MouseArea
                {
                    id: cancel;
                    anchors.fill: parent;
                    cursorShape: Qt.PointingHandCursor;
                }

                Component.onCompleted:
                {
                    cancel.clicked.connect(root.cancellationAsked);
                }
            } /* Icon */
        } /* Row */
    } /* Item */

    function humanFileSize(bytes, si)
    {
        var thresh = si ? 1000 : 1024;

        if(bytes < thresh) return bytes + ' B';

        var Units = si ? ['kB','MB','GB','TB','PB','EB','ZB','YB'] : ['KiB','MiB','GiB','TiB','PiB','EiB','ZiB','YiB'];
        var u = -1;

        do
        {
            bytes /= thresh;
            ++u;
        } while(bytes >= thresh);

        return bytes.toFixed(1)+' '+Units[u];
    } /* humanFileSize(bytes, si) */
} /* Window */
