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
import "qrc:/qml-material/modules/Material" 0.1

Slider
{
    darkBackground:
    {
        if(Theme.isDarkColor(theme.backgroundColor))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
