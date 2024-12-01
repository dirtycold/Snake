#ifndef GARDEN_H
#define GARDEN_H

#include <QSize>
#include <QScopedPointer>

class Garden
{
public:
    Garden();
    ~Garden();

    QSize size() const;

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // GARDEN_H
