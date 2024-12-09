#include "Snake.h"

class Snake::Private
{
    friend class Snake;

    Body body;
    Direction dir = Right;
    Direction rid = Right;
    void make(QPoint head)
    {
        for(int l = 0; l < 5; ++l)
        {
            QPoint cell = head - QPoint(l, 0);
            body.append(cell);
        }
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

Snake::Direction Snake::direction(Direction dir)
{
    if(p->rid != ((dir + 2) % 4))
    {
        p->dir = dir;
    }
    return p->dir;
}

QPoint Snake::next()
{
    QPoint diff[] =
    {
        { 1,  0},
        { 0, -1},
        {-1,  0},
        { 0,  1},
    };
    return p->body.first() + diff[p->dir];
}

void Snake::move(QPoint next, bool eat)
{
    p->rid = p->dir;
    p->body.prepend(next);
    if(!eat)
        p->body.removeLast();
}
