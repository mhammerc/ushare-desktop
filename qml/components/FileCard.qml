import QtQuick 2.0
import Material 0.1
import "../components" as U
import "../components/functions.js" as F
import "../components/usquare_online.js" as UOnline

View {

    property string nOfViews: ''
    property real size: 0
    property string password: ''
    property string shortName: ''
    property string source: ''

    signal linkCopied

    Component.onCompleted: {
        copyLink1.clicked.connect(linkCopied);
    }

    onNOfViewsChanged: {
        nOfViews1.text = nOfViews + ' views'
    }

    onShortNameChanged: {
        link1.text = Settings.domainName + '/' + shortName;
    }

    onSizeChanged: {
        size1.text = F.humanFileSize(size, true);
    }

    onPasswordChanged: {
        if(password === 'false')
            return;
        password1.text = password;
    }

    onSourceChanged: {
        miniature.source = Settings.silentViewUrl + source;
    }

    width: 310
    height: 90
    elevation: 1

    Image {
        id: miniature

        x: 0
        y: 0
        width: 90
        height: 90

        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        width: 1
        height: 90
        x: 91
        color: Qt.rgba(0,0,0,0.1)
    }

    Rectangle {
        width: 1
        height: 90
        x: 210
        color: Qt.rgba(0,0,0,0.1)
    }

    Column {
        y: 5
        x: 100
        spacing: 7

        Label {
            id: nOfViews1
            text: '14 Views'
        }

        Label {
            id: size1
            text: '9 MB'
        }

        Label {
            id: password1
            text: 'No password'
            color: '#27ae60'
        }

        Label {
            id: link1
            text: 'http://usqua.re/xyz'
            color: '#2980b9'
        }
    }

    Column {
        y: 2
        x: 219
        spacing: 1

        Button {
            id: open
            text: 'Open'
            elevation: 1
            backgroundColor: Theme.accentColor

            width: 82
            height: 28

            onClicked: {
                Desktop.openUrl('http://' + link1.text);
            }
        }

        Button {
            id: copyLink1
            text: 'Copy link'
            elevation: 1
            backgroundColor: Theme.accentColor

            width: 82
            height: 28

            onClicked: {
                Clipboard.setText('http://' + link1.text);
            }
        }

        Button {
            text: 'Delete'
            elevation: 1
            backgroundColor: Theme.accentColor

            width: 82
            height: 28

            onClicked: {
                UOnline.deleteFile(shortName, function(err, result){snackbar.open('File deleted!')});
            }
        }
    }
} /* View */
