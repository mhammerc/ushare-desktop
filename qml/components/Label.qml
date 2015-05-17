import QtQuick 2.0
import Material 0.1

Label
{
    color:
    {
        if(Theme.isDarkColor(theme.backgroundColor))
        {
            return Theme.dark.textColor;
        }
        else
        {
            return Theme.light.textColor;
        }
    }
}




