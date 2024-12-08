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
        Right,
        Up,
        Left,
        Down,
    };

    Snake(QPoint head);
    ~Snake();

    const Body& body() const;
    Direction direction() const;
    Direction direction(Direction dir);
    QPoint next();
    void move(QPoint next, bool eat);

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // SNAKE_H
