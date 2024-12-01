#include "Snake.h"

class Snake::Private
{
    friend class Snake;

    Body body;
    int length = 5;
    Direction dir = Right;

    void make(Cell head)
    {
        for(int l; l < length; ++l)
        {
            Cell cell = head;
            cell.x = head.x - l;
            body.append(cell);
        }
    }
};

Snake::Snake(Cell head)
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
