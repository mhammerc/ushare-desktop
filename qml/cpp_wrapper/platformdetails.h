#ifndef PLATFORMDETAILS
#define PLATFORMDETAILS

#include <QObject>

class PlatformDetails : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isWindows READ isWindows) /* lol */
    Q_PROPERTY(bool isLinux READ isLinux) /* <3 */
    Q_PROPERTY(bool isMac READ isMac) /* Beurk #TROLL */

public:

    PlatformDetails(QObject * parent = 0) : QObject(parent) {}

    bool isWindows()
    {
#ifdef Q_OS_MSDOS
        return true;
#else
        return false;
#endif
    }

    bool isLinux()
    {
#ifdef Q_OS_LINUX
        return true;
#else
        return false;
#endif
    }

    bool isMac()
    {
#ifdef Q_OS_MAC
        return true;
#else
        return false;
#endif
    }
};

#endif // PLATFORMDETAILS

