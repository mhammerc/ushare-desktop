import QtQuick 2.0
import Material 0.1
import "../components" as U
import "../components/functions.js" as F
import "../components/usquare_online.js" as UOnline

View {

    property var fileInformations // Handle a file object. See the API for more informations

    width: 310
    height: 90
    elevation: 1

    /** Two dividers**/
    Rectangle
    {
        width: 1
        height: 90
        x: 91
        color: Qt.rgba(0,0,0,0.1)
    }

    Rectangle
    {
        width: 1
        height: 90
        x: 210
        color: Qt.rgba(0,0,0,0.1)
    }

    /** First column, miniature of the file **/
    Image
    {
        x: 0
        y: 0
        width: 90
        height: 90

        source: fileInformations.mimetype.slice(0, 6) === "image/" ? fileInformations.silentLink : ''

        fillMode: Image.PreserveAspectFit
    }

    /** Second column, informations about the file **/
    Column
    {
        y: 5
        x: 100
        spacing: 7

        Label
        {
            text: fileInformations.views + ' views'
        }

        Label
        {
            text: F.humanFileSize(fileInformations.size, true);
        }

        Label
        {
            text: fileInformations.password ? fileInformations.password : 'No password'
            color: '#27ae60'
        }

        Label
        {
            text: fileInformations.link
            color: '#2980b9'
        }
    }

    /** Third column, actions on the file **/
    Column
    {
        y: 2
        x: 219
        spacing: 1

        Button
        {
            text: 'Open'
            elevation: 1
            backgroundColor: Theme.accentColor

            width: 82
            height: 28

            onClicked:
            {
                Desktop.openUrl(fileInformations.link);
            }
        }

        Button
        {
            text: 'Copy link'
            elevation: 1
            backgroundColor: Theme.accentColor

            width: 82
            height: 28

            onClicked:
            {
                Clipboard.setText(fileInformations.link);
                snackbar.open('Link copied!');
            }
        }

        Button
        {
            text: 'Delete'
            elevation: 1
            backgroundColor: Theme.accentColor

            width: 82
            height: 28

            onClicked: {
                UOnline.deleteFile(fileInformations.shortname, function(err, result)
                {
                    if(err || !result.success)
                    {
                        snackbar.open(result.message ? result.message : 'An error occurred.');
                        return;
                    }

                    snackbar.open('File deleted!');
                });
            }
        }
    }
} /* View */
