#include "Snake.h"

class Snake::Private
{
    friend class Snake;

    Body body;
    int length = 5;
    Direction dir = Right;

    void make(QPoint head)
    {
        for(int l = 0; l < length; ++l)
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
