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




