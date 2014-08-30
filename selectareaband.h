/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef SELECTAREABAND_H
#define SELECTAREABAND_H

#include <QRubberBand>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPoint>
#include <QRect>
#include <QPoint>
#include <QCursor>
#include <QPalette>
#include <cstdlib>
#include <ctime>

#include "shared.h"

class FileManager;

/**
  This class simply represent the area band showed when selecting area to select area for new screen.
 */
class SelectAreaBand : public QLabel
{
    Q_OBJECT
public:
    SelectAreaBand(FileManager * manager, QWidget * parent = 0);
    virtual ~SelectAreaBand();

    void selectArea();

protected:
    QRubberBand * rubberBand;
    QPoint origin;
    FileManager * manager;

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void keyPressEvent(QKeyEvent *);


signals:
    void areaTaken(QRect);
    void areaCanceled();
};

#endif // SELECTAREABAND_H
