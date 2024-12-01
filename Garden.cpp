#include "Garden.h"
#include "Snake.h"
#include <QPainter>

class Garden::Private
{
    friend class Garden;

    int width = 32;
    int height = 32;

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
