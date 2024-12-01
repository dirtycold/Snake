#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QVector>
#include <QScopedPointer>

class Snake
{
public:
    typedef QVector<QPoint> Body;

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    Snake(QPoint head);
    ~Snake();

    const Body& body() const;

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // SNAKE_H
