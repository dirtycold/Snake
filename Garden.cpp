#include "Garden.h"
#include "Snake.h"
#include <QPainter>

class Garden::Private
{
    friend class Garden;

    int width = 31;
    int height = 31;

    QSize size = QSize(width, height);
};

Garden::Garden()
    : p(new Private)
{
}

Garden::~Garden()
{
}

QSize Garden::size() const
{
    return p->size;
}
