#ifndef SNAKE_H
#define SNAKE_H

#include <QVector>
#include <QScopedPointer>

class Snake
{
public:

    struct Cell
    {
        int x;
        int y;

        Cell(int x, int y) : x(x), y(y) {}
    };

    typedef QVector<Cell> Body;

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    Snake(Cell head);
    ~Snake();

    Body& body();

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // SNAKE_H
