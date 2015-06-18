#ifndef SHORTCUTGETTER_H
#define SHORTCUTGETTER_H

#include <QApplication>
#include <QObject>
#include <QKeyEvent>

class ShortcutGetter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key NOTIFY keyChanged)
public:
    explicit ShortcutGetter(QObject *parent = 0);

    QString key();

    bool eventFilter(QObject * obj, QEvent * e);

private:
    void setKey(QString key);

    QString _key;

signals:
    void keyChanged(QString key);

public slots:
};

#endif // SHORTCUTGETTER_H
