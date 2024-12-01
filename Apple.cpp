#include "Apple.h"

class Apple::Private
{
    friend class Apple;

    QPoint pos;
};

Apple::Apple(QPoint cell)
    : p(new Private)
{
    p->pos = cell;
}

Apple::~Apple()
{
}

QPoint Apple::position() const
{
    return p->pos;
}

QPoint Apple::move(QPoint cell)
{
    p->pos = cell;
    return position();
}
