#include "Snake.h"

class Snake::Private
{
    friend class Snake;

    Body body;
    Direction dir = Right;
    void make(QPoint head)
    {
        for(int l = 0; l < 5; ++l)
        {
            QPoint cell = head - QPoint(l, 0);
            body.append(cell);
        }
    }

    QPoint next()
    {
        QPoint diff[] =
        {
            { 1,  0},
            { 0,  1},
            {-1,  0},
            { 0, -1},
        };
        return body.first() + diff[dir];
    }
};

Snake::Snake(QPoint head)
    : p(new Private)
{
    p->make(head);
}

Snake::~Snake()
{
}

const Snake::Body& Snake::body() const
{
    return p->body;
}

Snake::Direction Snake::direction() const
{
    return p->dir;
}

Snake::Direction Snake::direction(Direction dir)
{
    if(p->dir != ((dir + 2) % 4))
    {
        p->dir = dir;
    }
    return direction();
}

QPoint Snake::move()
{
    p->body.prepend(p->next());
    p->body.removeLast();
    return p->body.first();
}
