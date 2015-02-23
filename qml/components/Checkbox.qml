import QtQuick 2.0
import Material 0.1

Checkbox {
    darkBackground: {
                if(Theme.isDarkColor(theme.backgroundColor))
                    return true
                else
                    return false
                }
}

