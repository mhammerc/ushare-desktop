import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

Window {
    id: usquare
    width: 405
    height: 30
    flags: Qt.WindowStaysOnTopHint | Qt.WindowCloseButtonHint

    maximumWidth: width
    minimumWidth: width

    maximumHeight: height
    minimumHeight: height

    property real progress : 0

    property bool isUploading : true

    property string link: ""

    property int bytesTotal: 0

    signal cancellationAsked


    Item {
        id: uploading
        anchors.fill: parent
        anchors.leftMargin: 5

        visible: isUploading

        Row {
            id: row1
            spacing: 7
            anchors.verticalCenter: parent.verticalCenter

            Label {
                id: label1
                text: "Uploading... (" + humanFileSize(bytesTotal*progress, true) + "/" + humanFileSize(bytesTotal, true) + ")";
                verticalAlignment: Text.AlignVCenter
            }

            ProgressBar {
                id: progressBar1
                anchors.verticalCenter: parent.verticalCenter
                progress: usquare.progress
                width: 165
                height: 5

                Behavior on progress { NumberAnimation { duration: 450 } }
            }

            Label {
                id: label2
                text: Math.round(usquare.progress*100) + "%"
                verticalAlignment: Text.AlignVCenter
            }

            Icon {
                id: icon1
                anchors.verticalCenter: parent.verticalCenter
                width: 5
                height: 5
                name: "awesome/remove"
                color: "#c0392b"
                size: 1

                MouseArea {
                    id: cancel
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }

                Component.onCompleted: {
                    cancel.clicked.connect(usquare.cancellationAsked)
                }
            } /* Icon */
        } /* Row */
    } /* Item */

    Item {
        anchors.centerIn: parent
        anchors.fill: parent
        id: uploaded

        visible: !isUploading

        MouseArea {
            anchors.fill: parent
            onClicked: Qt.openUrlExternally(link)
            cursorShape: Qt.PointingHandCursor
        }

        Label {
            textFormat: Text.RichText
            anchors.fill: parent
            text: "Your file is uploaded ! The link is <a href=\"" + link + "\">" + link +"</a>"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        } /* Label */
    } /* Item */

    function humanFileSize(bytes, si) {
        var thresh = si ? 1000 : 1024;
        if(bytes < thresh) return bytes + ' B';
        var units = si ? ['kB','MB','GB','TB','PB','EB','ZB','YB'] : ['KiB','MiB','GiB','TiB','PiB','EiB','ZiB','YiB'];
        var u = -1;
        do {
            bytes /= thresh;
            ++u;
        } while(bytes >= thresh);
        return bytes.toFixed(1)+' '+units[u];
    } /* humanFileSize(bytes, si) */
} /* Window */
