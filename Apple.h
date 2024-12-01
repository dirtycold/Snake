#ifndef APPLE_H
#define APPLE_H

#include <QPoint>
#include <QScopedPointer>

class Apple
{
public:
    Apple(QPoint cell);
    ~Apple();

    QPoint position() const;
    QPoint move(QPoint cell);

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // APPLE_H
